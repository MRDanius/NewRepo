//#pragma once
//#include "tg_hash_map.h"
//#include <iostream>
//
//class TextGenerator {
//private:
//    WordHashMap word_map;
//    BigramHashMap bigram_map;
//    int next_id = 0;
//
//    void load_unigram();
//    void load_bigram();
//    void save_unigram() const;
//    void save_bigram() const;
//
//public:
//    TextGenerator();
//    void train(const char* filename);
//    void generate(const char* start, int n_words) const;
//};


#pragma once
#include "tg_hash_map.h"
#include <iostream>

class TextGenerator {
private:
    WordHashMap word_map;
    BigramHashMap bigram_map;
    int next_id = 0;

    void load_unigram();
    void load_bigram();
    void save_unigram() const;
    void save_bigram() const;

    // Новые вспомогательные методы
    int get_random_word_id() const;
    void get_word_by_id(int id, char* buffer) const;

public:
    TextGenerator();
    void train(const char* filename);
    void generate(const char* start, int n_words) const;
};