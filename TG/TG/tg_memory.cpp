#include "text_generator.h"
#include <cstring>

TextGenerator::TextGenerator() :
    word_count(0), bigram_count(0),
    max_words(100), max_bigrams(1000),
    next_id(0)
{
    word_to_id = new WordEntry[max_words];
    id_to_word = new WordEntry[max_words];
    bigrams = new BigramEntry[max_bigrams];
}

TextGenerator::~TextGenerator() {
    delete[] word_to_id;
    delete[] id_to_word;
    delete[] bigrams;
}

void TextGenerator::expand_words() {
    int new_size = max_words * 2;
    WordEntry* new_arr = new WordEntry[new_size];
    for (int i = 0; i < max_words; ++i) {
        new_arr[i] = word_to_id[i];
    }
    delete[] word_to_id;
    word_to_id = new_arr;
    max_words = new_size;
}

void TextGenerator::expand_bigrams() {
    int new_size = max_bigrams * 2;
    BigramEntry* new_arr = new BigramEntry[new_size];
    for (int i = 0; i < max_bigrams; ++i) {
        new_arr[i] = bigrams[i];
    }
    delete[] bigrams;
    bigrams = new_arr;
    max_bigrams = new_size;
}