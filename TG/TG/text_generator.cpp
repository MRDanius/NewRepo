#include "text_generator.h"
#include <fstream>

TextGenerator::TextGenerator() {
    load_unigram();
    load_bigram();
}

void TextGenerator::load_unigram() {
    std::ifstream file("unigram.txt");
    if (!file) return;

    char word[100];
    int id;
    while (file >> word >> id) {
        word_map.insert(word, id);
        if (id >= next_id) next_id = id + 1;
    }
}

void TextGenerator::load_bigram() {
    std::ifstream file("bigram.txt");
    if (!file) return;

    int from, to, count;
    while (file >> from >> to >> count) {
        for (int i = 0; i < count; ++i)
            bigram_map.insert_or_update(from, to);
    }
}

void save_word(const WordEntry& entry) {
    std::ofstream file("unigram.txt", std::ios::app);
    file << entry.word << " " << entry.id << "\n";
}

void save_bigram_entry(const BigramEntry& entry) {
    std::ofstream file("bigram.txt", std::ios::app);
    file << entry.key.from_id << " " << entry.key.to_id << " " << entry.count << "\n";
}

void TextGenerator::save_unigram() const {
    std::remove("unigram.txt");
    word_map.for_each(save_word);
}

void TextGenerator::save_bigram() const {
    std::remove("bigram.txt");
    bigram_map.for_each(save_bigram_entry);
}

void TextGenerator::train(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка: Не удалось открыть файл!" << std::endl;
        return;
    }

    char line[1024];
    while (file.getline(line, 1024)) {
        int pos = 0;
        const char* prev_token = nullptr;
        const char* delimiters = " \t\n";

        while (true) {
            const char* token = string_tokenize(line, delimiters, pos);
            if (!token) break;

            char word[100];
            copy_string(word, token, 100);
            lowercase(word);

            if (word_map.get(word) == -1)
                word_map.insert(word, next_id++);

            if (prev_token) {
                int from = word_map.get(prev_token);
                int to = word_map.get(word);
                bigram_map.insert_or_update(from, to);
            }

            prev_token = word;
        }
    }

    save_unigram();
    save_bigram();
    std::cout << "Обучение завершено. Слов: " << next_id << std::endl;
}

void TextGenerator::generate(const char* start, int n_words) const {
    char current_word[100];
    copy_string(current_word, start, 100);
    lowercase(current_word);

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < n_words; ++i) {
        int current_id = word_map.get(current_word);
        if (current_id == -1) {
            // Случайное слово через ручной массив
            int word_count = word_map.get_unique_count();
            if (word_count == 0) break;

            WordEntry* all_words = new WordEntry[word_count];
            int idx = 0;
            word_map.for_each([&](const WordEntry& entry) {
                all_words[idx++] = entry;
                });

            std::uniform_int_distribution<> dist(0, word_count - 1);
            const WordEntry& entry = all_words[dist(gen)];
            copy_string(current_word, entry.word, 100);
            delete[] all_words;

            std::cout << current_word << " ";
            continue;
        }

        // Сбор кандидатов через ручной массив
        int candidates_size = 0;
        int candidates_cap = 10;
        BigramEntry* candidates = new BigramEntry[candidates_cap];

        bigram_map.for_each([&](const BigramEntry& e) {
            if (e.key.from_id == current_id) {
                if (candidates_size >= candidates_cap) {
                    // Расширение массива
                    candidates_cap *= 2;
                    BigramEntry* new_arr = new BigramEntry[candidates_cap];
                    for (int j = 0; j < candidates_size; ++j)
                        new_arr[j] = candidates[j];
                    delete[] candidates;
                    candidates = new_arr;
                }
                candidates[candidates_size++] = e;
            }
            });

        // Выбор следующего слова
        int total = 0;
        for (int j = 0; j < candidates_size; ++j)
            total += candidates[j].count;

        if (total == 0) {
            delete[] candidates;
            break;
        }

        std::uniform_int_distribution<> dist(0, total - 1);
        int r = dist(gen);
        int sum = 0;
        bool found = false;
        for (int j = 0; j < candidates_size; ++j) {
            sum += candidates[j].count;
            if (sum > r) {
                int to_id = candidates[j].key.to_id;
                word_map.for_each([&](const WordEntry& entry) {
                    if (entry.id == to_id) {
                        copy_string(current_word, entry.word, 100);
                        found = true;
                    }
                    });
                if (found) {
                    std::cout << current_word << " ";
                    break;
                }
            }
        }

        delete[] candidates;
        if (!found) break;
    }
    std::cout << std::endl;
}