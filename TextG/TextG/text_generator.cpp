//#include "text_generator.h"
//#include "tg_utils.h"
//#include <fstream>
//#include <cstring>
//#include <cstdlib>
//#include <ctime>
//
//TextGenerator::TextGenerator() {
//    load_unigram();
//    load_bigram();
//    srand(0);
//}
//
//void TextGenerator::load_unigram() {
//    std::ifstream file("unigram.txt");
//    if (!file) return;
//
//    char word[100];
//    int id;
//    while (file >> word >> id) {
//        word_map.insert(word, id);
//        if (id >= next_id) next_id = id + 1;
//    }
//}
//
//void TextGenerator::load_bigram() {
//    std::ifstream file("bigram.txt");
//    if (!file) return;
//
//    int from, to, count;
//    while (file >> from >> to >> count) {
//        for (int i = 0; i < count; ++i)
//            bigram_map.insert_or_update(from, to);
//    }
//}
//
//void TextGenerator::save_unigram() const {
//    std::ofstream file("unigram.txt");
//    if (!file) return;
//
//    for (int b = 0; b < word_map.capacity; ++b) {
//        WordHashMap::Node* node = word_map.buckets[b];
//        while (node) {
//            file << node->entry.word << " " << node->entry.id << "\n";
//            node = node->next;
//        }
//    }
//}
//
//void TextGenerator::save_bigram() const {
//    std::ofstream file("bigram.txt");
//    if (!file) return;
//
//    for (int b = 0; b < bigram_map.capacity; ++b) {
//        BigramHashMap::Node* node = bigram_map.buckets[b];
//        while (node) {
//            file << node->entry.key.from_id << " "
//                << node->entry.key.to_id << " "
//                << node->entry.count << "\n";
//            node = node->next;
//        }
//    }
//}

//void TextGenerator::train(const char* filename) {
//    std::ifstream file(filename);
//    if (!file) {
//        std::cerr << "Ошибка: Не удалось открыть файл!" << std::endl;
//        return;
//    }
//
//    char line[1024];
//    const char* delimiters = " \t\n.,!?";
//
//    while (file.getline(line, 1024)) {
//        char* next_token = nullptr;
//        char* token = strtok_s(line, delimiters, &next_token);
//        const char* prev_token = nullptr;
//
//        while (token != nullptr) {
//            remove_punctuation(token);
//            lowercase(token);
//
//            if (strlen(token) == 0) {
//                token = strtok_s(nullptr, delimiters, &next_token);
//                continue;
//            }
//
//            if (word_map.get(token) == -1)
//                word_map.insert(token, next_id++);
//
//            if (prev_token != nullptr) {
//                int from = word_map.get(prev_token);
//                int to = word_map.get(token);
//                if (from != -1 && to != -1) {
//                    bigram_map.insert_or_update(from, to);
//                }
//            }
//
//            prev_token = token;
//            token = strtok_s(nullptr, delimiters, &next_token);
//        }
//    }
//
//    save_unigram();
//    save_bigram();
//}

//void TextGenerator::train(const char* filename) {
//    std::ifstream file(filename);
//    if (!file) {
//        std::cerr << "Ошибка: Не удалось открыть файл!" << std::endl;
//        return;
//    }
//
//    char line[1024];
//    const char* delimiters = " \t\n"; // Теперь разделители только пробелы и табы
//
//    while (file.getline(line, 1024)) {
//        char* next_token = nullptr;
//        char* token = strtok_s(line, delimiters, &next_token);
//        const char* prev_token = nullptr;
//        bool prev_had_punct = false;
//
//        while (token != nullptr) {
//            bool current_had_punct = remove_punctuation(token);
//            lowercase(token);
//
//            if (strlen(token) == 0) {
//                token = strtok_s(nullptr, delimiters, &next_token);
//                continue;
//            }
//
//            if (word_map.get(token) == -1)
//                word_map.insert(token, next_id++);
//
//            // Создаём биграмму только если предыдущий токен не имел пунктуации
//            if (prev_token != nullptr && !prev_had_punct) {
//                int from = word_map.get(prev_token);
//                int to = word_map.get(token);
//                if (from != -1 && to != -1) {
//                    bigram_map.insert_or_update(from, to);
//                }
//            }
//
//            prev_had_punct = current_had_punct;
//            prev_token = token;
//            token = strtok_s(nullptr, delimiters, &next_token);
//        }
//    }
//
//    save_unigram();
//    save_bigram();
//}
//
//void TextGenerator::generate(const char* start, int n_words) const {
//    char current_word[100];
//    copy_string(current_word, start, 100);
//    lowercase(current_word);
//
//    for (int i = 0; i < n_words; ++i) {
//        int current_id = word_map.get(current_word);
//        if (current_id == -1) {
//            int word_count = word_map.size;
//            if (word_count == 0) break;
//
//            int random_idx = rand() % word_count;
//            int cnt = 0;
//
//            for (int b = 0; b < word_map.capacity; ++b) {
//                WordHashMap::Node* node = word_map.buckets[b];
//                while (node) {
//                    if (cnt == random_idx) {
//                        copy_string(current_word, node->entry.word, 100);
//                        b = word_map.capacity;
//                        break;
//                    }
//                    cnt++;
//                    node = node->next;
//                }
//            }
//
//            std::cout << current_word << " ";
//            continue;
//        }
//
//        BigramEntry candidates[100];
//        int candidates_size = 0;
//
//        for (int b = 0; b < bigram_map.capacity; ++b) {
//            BigramHashMap::Node* node = bigram_map.buckets[b];
//            while (node) {
//                if (node->entry.key.from_id == current_id) {
//                    candidates[candidates_size++] = node->entry;
//                }
//                node = node->next;
//            }
//        }
//
//        int total = 0;
//        for (int j = 0; j < candidates_size; ++j)
//            total += candidates[j].count;
//
//        if (total == 0) break;
//
//        int r = rand() % total;
//        int sum = 0;
//        for (int j = 0; j < candidates_size; ++j) {
//            sum += candidates[j].count;
//            if (sum > r) {
//                int to_id = candidates[j].key.to_id;
//
//                for (int b = 0; b < word_map.capacity; ++b) {
//                    WordHashMap::Node* node = word_map.buckets[b];
//                    while (node) {
//                        if (node->entry.id == to_id) {
//                            copy_string(current_word, node->entry.word, 100);
//                            b = word_map.capacity;
//                            break;
//                        }
//                        node = node->next;
//                    }
//                }
//
//                std::cout << current_word << " ";
//                break;
//            }
//        }
//    }
//    std::cout << std::endl;
//}
//

#include "text_generator.h"
#include "tg_utils.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

TextGenerator::TextGenerator() {
    load_unigram();
    load_bigram();
    srand(0);
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

void TextGenerator::save_unigram() const {
    std::ofstream file("unigram.txt");
    if (!file) return;

    for (int b = 0; b < word_map.capacity; ++b) {
        WordHashMap::Node* node = word_map.buckets[b];
        while (node) {
            file << node->entry.word << " " << node->entry.id << "\n";
            node = node->next;
        }
    }
}

void TextGenerator::save_bigram() const {
    std::ofstream file("bigram.txt");
    if (!file) return;

    for (int b = 0; b < bigram_map.capacity; ++b) {
        BigramHashMap::Node* node = bigram_map.buckets[b];
        while (node) {
            file << node->entry.key.from_id << " "
                << node->entry.key.to_id << " "
                << node->entry.count << "\n";
            node = node->next;
        }
    }
}

void TextGenerator::train(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка: Не удалось открыть файл!" << std::endl;
        return;
    }

    char line[1024];
    const char* delimiters = " \t\n";

    while (file.getline(line, 1024)) {
        char* next_token = nullptr;
        char* token = strtok_s(line, delimiters, &next_token);
        const char* prev_token = nullptr;
        bool prev_had_punct = false;

        while (token != nullptr) {
            bool current_had_punct = remove_punctuation(token);
            lowercase(token);

            if (strlen(token) == 0) {
                token = strtok_s(nullptr, delimiters, &next_token);
                continue;
            }

            if (word_map.get(token) == -1)
                word_map.insert(token, next_id++);

            if (prev_token != nullptr && !prev_had_punct) {
                int from = word_map.get(prev_token);
                int to = word_map.get(token);
                if (from != -1 && to != -1) {
                    bigram_map.insert_or_update(from, to);
                }
            }

            prev_had_punct = current_had_punct;
            prev_token = token;
            token = strtok_s(nullptr, delimiters, &next_token);
        }
    }

    save_unigram();
    save_bigram();
}

void TextGenerator::generate(const char* start, int n_words) const {
    char current_word[100];
    copy_string(current_word, start, 100);
    lowercase(current_word);

    for (int i = 0; i < n_words; ) {
        int current_id = word_map.get(current_word);
        bool word_printed = false;

        // Fallback для неизвестных слов
        if (current_id == -1) {
            current_id = get_random_word_id();
            if (current_id != -1) {
                get_word_by_id(current_id, current_word);
                std::cout << current_word << " ";
                word_printed = true;
            }
        }

        // Попытка генерации через биграммы
        if (current_id != -1 && !word_printed) {
            BigramEntry candidates[100];
            int candidates_size = 0;
            int total = 0;

            for (int b = 0; b < bigram_map.capacity; ++b) {
                BigramHashMap::Node* node = bigram_map.buckets[b];
                while (node) {
                    if (node->entry.key.from_id == current_id) {
                        candidates[candidates_size++] = node->entry;
                        total += node->entry.count;
                    }
                    node = node->next;
                }
            }

            if (total > 0) {
                int r = rand() % total;
                int sum = 0;
                for (int j = 0; j < candidates_size; ++j) {
                    sum += candidates[j].count;
                    if (sum > r) {
                        current_id = candidates[j].key.to_id;
                        get_word_by_id(current_id, current_word);
                        std::cout << current_word << " ";
                        word_printed = true;
                        break;
                    }
                }
            }
        }

        // Резервный случайный выбор
        if (!word_printed) {
            current_id = get_random_word_id();
            if (current_id != -1) {
                get_word_by_id(current_id, current_word);
                std::cout << current_word << " ";
            }
        }

        i++;
    }
    std::cout << std::endl;
}

int TextGenerator::get_random_word_id() const {
    if (word_map.size == 0) return -1;
    int random_idx = rand() % word_map.size;
    int cnt = 0;

    for (int b = 0; b < word_map.capacity; ++b) {
        WordHashMap::Node* node = word_map.buckets[b];
        while (node) {
            if (cnt == random_idx) return node->entry.id;
            cnt++;
            node = node->next;
        }
    }
    return -1;
}

void TextGenerator::get_word_by_id(int id, char* buffer) const {
    for (int b = 0; b < word_map.capacity; ++b) {
        WordHashMap::Node* node = word_map.buckets[b];
        while (node) {
            if (node->entry.id == id) {
                copy_string(buffer, node->entry.word, 100);
                return;
            }
            node = node->next;
        }
    }
    buffer[0] = '\0';
}