#pragma once
#include "tg_data_structures.h"

class WordHashMap {
public:
    struct Node {
        WordEntry entry;
        Node* next = nullptr;
    };

    Node** buckets;
    int capacity;
    int size;

    WordHashMap(int initial_cap = 100);
    ~WordHashMap();
    void insert(const char* word, int id);
    int get(const char* word) const;
};

class BigramHashMap {
public:
    struct Node {
        BigramEntry entry;
        Node* next = nullptr;
    };

    Node** buckets;
    int capacity;

    BigramHashMap(int initial_cap = 1000);
    ~BigramHashMap();
    void insert_or_update(int from, int to);
};