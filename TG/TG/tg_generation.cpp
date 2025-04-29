#include "text_generator.h"
#include <random>
#include <vector>

const char* TextGenerator::get_word(int id) const {
    for (int i = 0; i < word_count; ++i) {
        if (id_to_word[i].id == id) {
            return id_to_word[i].word;
        }
    }
    return nullptr;
}

void TextGenerator::generate(const char* start, int n_words) {
    if (word_count == 0) {
        std::cerr << "Ошибка: Модель не обучена!" << std::endl;
        return;
    }

    char current_word[100];
    copy_string(current_word, start, 99);
    std::cout << current_word << " ";

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < n_words; ++i) {
        int current_id = get_id(current_word);
        if (current_id == -1) {
            std::uniform_int_distribution<> dist(0, word_count - 1);
            current_id = dist(gen);
            copy_string(current_word, id_to_word[current_id].word, 99);
            std::cout << current_word << " ";
            continue;
        }

        int total = 0;
        for (int j = 0; j < bigram_count; ++j) {
            if (bigrams[j].from_id == current_id) {
                total += bigrams[j].count;
            }
        }

        if (total > 0) {
            std::uniform_int_distribution<> dist(0, total - 1);
            int r = dist(gen);
            int sum = 0;
            for (int j = 0; j < bigram_count; ++j) {
                if (bigrams[j].from_id == current_id) {
                    sum += bigrams[j].count;
                    if (sum > r) {
                        const char* word = get_word(bigrams[j].to_id);
                        copy_string(current_word, word, 99);
                        std::cout << word << " ";
                        break;
                    }
                }
            }
        }
        else {
            std::uniform_int_distribution<> dist(0, word_count - 1);
            int idx = dist(gen);
            copy_string(current_word, id_to_word[idx].word, 99);
            std::cout << current_word << " ";
        }
    }
    std::cout << std::endl;
}