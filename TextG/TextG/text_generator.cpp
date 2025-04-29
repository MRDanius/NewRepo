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
//
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
#include "text_generator.h"
#include "tg_utils.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>

TextGenerator::TextGenerator() {
    load_unigram();
    load_bigram();
    srand(static_cast<unsigned>(time(nullptr)));
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
        std::cerr << "Error: Failed to open file!" << std::endl;
        return;
    }

    char line[1024];
    const char* weak_delimiters = " \t";
    const char* strong_delimiters = ".,!?;—–()\"':\n\r";
    char prev_token_buffer[100] = { 0 };

    while (file.getline(line, 1024)) {
        char* current_pos = line;
        prev_token_buffer[0] = '\0';

        while (*current_pos) {
            // Пропускаем разделители
            while (*current_pos &&
                (strchr(weak_delimiters, *current_pos) ||
                    strchr(strong_delimiters, *current_pos)))
            {
                if (strchr(strong_delimiters, *current_pos)) {
                    prev_token_buffer[0] = '\0';
                }
                current_pos++;
            }

            if (!*current_pos) break;

            // Извлекаем токен
            char* token_start = current_pos;
            while (*current_pos &&
                !strchr(weak_delimiters, *current_pos) &&
                !strchr(strong_delimiters, *current_pos))
            {
                current_pos++;
            }

            char token[100];
            // Исправлено: передаём 100 как размер буфера
            copy_string(token, token_start, 100);
            remove_punctuation(token);
            lowercase(token);

            if (strlen(token) == 0) continue;

            // Добавляем слово в словарь
            if (word_map.get(token) == -1) {
                word_map.insert(token, next_id++);
            }

            // Добавляем биграмму, если есть предыдущий токен
            if (prev_token_buffer[0] != '\0') {
                int from = word_map.get(prev_token_buffer);
                int to = word_map.get(token);
                if (from != -1 && to != -1) {
                    bigram_map.insert_or_update(from, to);
                }
            }

            // Сохраняем токен
            strcpy_s(prev_token_buffer, token);

            // Сброс при сильном разделителе
            if (*current_pos && strchr(strong_delimiters, *current_pos)) {
                prev_token_buffer[0] = '\0';
            }
        }
    }

    save_unigram();
    save_bigram();
}

void TextGenerator::generate(const char* start, int n_words) const {
    char current_word[100];
    copy_string(current_word, start, 100);
    lowercase(current_word);

    for (int i = 0; i < n_words; ++i) {
        int current_id = word_map.get(current_word);
        if (current_id == -1) {
            int word_count = word_map.size;
            if (word_count == 0) break;

            int random_idx = rand() % word_count;
            int cnt = 0;

            for (int b = 0; b < word_map.capacity; ++b) {
                WordHashMap::Node* node = word_map.buckets[b];
                while (node) {
                    if (cnt == random_idx) {
                        copy_string(current_word, node->entry.word, 100);
                        b = word_map.capacity;
                        break;
                    }
                    cnt++;
                    node = node->next;
                }
            }

            std::cout << current_word << " ";
            continue;
        }

        BigramEntry candidates[100];
        int candidates_size = 0;

        for (int b = 0; b < bigram_map.capacity; ++b) {
            BigramHashMap::Node* node = bigram_map.buckets[b];
            while (node) {
                if (node->entry.key.from_id == current_id) {
                    if (candidates_size < 100) {
                        candidates[candidates_size++] = node->entry;
                    }
                }
                node = node->next;
            }
        }

        int total = 0;
        for (int j = 0; j < candidates_size; ++j) {
            total += candidates[j].count;
        }

        if (total == 0) break;

        int r = rand() % total;
        int sum = 0;
        for (int j = 0; j < candidates_size; ++j) {
            sum += candidates[j].count;
            if (sum > r) {
                int to_id = candidates[j].key.to_id;

                for (int b = 0; b < word_map.capacity; ++b) {
                    WordHashMap::Node* node = word_map.buckets[b];
                    while (node) {
                        if (node->entry.id == to_id) {
                            copy_string(current_word, node->entry.word, 100);
                            b = word_map.capacity;
                            break;
                        }
                        node = node->next;
                    }
                }

                std::cout << current_word << " ";
                break;
            }
        }
    }
    std::cout << std::endl;
}