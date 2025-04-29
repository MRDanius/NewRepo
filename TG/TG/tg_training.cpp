#include "text_generator.h"
#include <fstream>
#include <iostream>

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

            int len = string_length(token);
            char* word = new char[len + 1];
            copy_string(word, token, len + 1);
            lowercase(word);

            if (prev_token) {
                int from = get_id(prev_token);
                int to = get_id(word);
                add_bigram(from, to);
                delete[] prev_token;
            }

            prev_token = word;
        }

        if (prev_token) delete[] prev_token;
    }

    save_unigram();
    save_bigram();
    std::cout << "Обучение завершено. Слов: " << word_count
        << ", Биграмм: " << bigram_count << std::endl;
}

int TextGenerator::get_id(const char* word) {
    for (int i = 0; i < word_count; ++i) {
        if (strcmp(word_to_id[i].word, word) == 0) {
            return word_to_id[i].id;
        }
    }

    if (word_count >= max_words) expand_words();

    copy_string(word_to_id[word_count].word, word, 100);
    word_to_id[word_count].id = next_id;
    copy_string(id_to_word[word_count].word, word, 100);
    id_to_word[word_count].id = next_id;

    word_count++;
    return next_id++;
}

void TextGenerator::add_bigram(int from, int to) {
    for (int i = 0; i < bigram_count; ++i) {
        if (bigrams[i].from_id == from && bigrams[i].to_id == to) {
            bigrams[i].count++;
            return;
        }
    }

    if (bigram_count >= max_bigrams) expand_bigrams();
    bigrams[bigram_count] = { from, to, 1 };
    bigram_count++;
}

void TextGenerator::save_unigram() const {
    std::ofstream file("unigram.txt");
    if (!file) {
        std::cerr << "Ошибка сохранения unigram.txt!" << std::endl;
        return;
    }
    for (int i = 0; i < word_count; ++i) {
        file << word_to_id[i].word << " " << word_to_id[i].id << "\n";
    }
}

void TextGenerator::save_bigram() const {
    std::ofstream file("bigram.txt");
    if (!file) {
        std::cerr << "Ошибка сохранения bigram.txt!" << std::endl;
        return;
    }
    for (int i = 0; i < bigram_count; ++i) {
        file << bigrams[i].from_id << " " << bigrams[i].to_id << " " << bigrams[i].count << "\n";
    }
}