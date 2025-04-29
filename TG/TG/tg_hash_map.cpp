#include "tg_hash_map.h"
#include <cstring>

WordHashMap::WordHashMap(int initial_cap) : capacity(initial_cap), size(0) {
    buckets = new Node * [capacity]();
}

WordHashMap::~WordHashMap() {
    for (int i = 0; i < capacity; ++i) {
        Node* node = buckets[i];
        while (node) {
            Node* prev = node;
            node = node->next;
            delete prev;
        }
    }
    delete[] buckets;
}

void WordHashMap::insert(const char* word, int id) {
    int idx = hash(word);
    Node* node = buckets[idx];
    while (node) {
        if (strcmp(node->entry.word, word) == 0) return;
        node = node->next;
    }

    Node* new_node = new Node{};
    copy_string(new_node->entry.word, word, 100);
    new_node->entry.id = id;
    new_node->next = buckets[idx];
    buckets[idx] = new_node;
    size++;
}

int WordHashMap::get(const char* word) const {
    int idx = hash(word);
    Node* node = buckets[idx];
    while (node) {
        if (strcmp(node->entry.word, word) == 0)
            return node->entry.id;
        node = node->next;
    }
    return -1;
}

void WordHashMap::for_each(void (*func)(const WordEntry&)) const {
    for (int i = 0; i < capacity; ++i) {
        Node* node = buckets[i];
        while (node) {
            func(node->entry);
            node = node->next;
        }
    }
}

BigramHashMap::BigramHashMap(int initial_cap) : capacity(initial_cap) {
    buckets = new Node * [capacity]();
}

BigramHashMap::~BigramHashMap() {
    for (int i = 0; i < capacity; ++i) {
        Node* node = buckets[i];
        while (node) {
            Node* prev = node;
            node = node->next;
            delete prev;
        }
    }
    delete[] buckets;
}

void BigramHashMap::insert_or_update(int from, int to) {
    BigramKey key{ from, to };
    int idx = hash(key);

    Node* node = buckets[idx];
    while (node) {
        if (node->entry.key.from_id == from && node->entry.key.to_id == to) {
            node->entry.count++;
            return;
        }
        node = node->next;
    }

    Node* new_node = new Node{};
    new_node->entry.key = key;
    new_node->entry.count = 1;
    new_node->next = buckets[idx];
    buckets[idx] = new_node;
}

void BigramHashMap::for_each(void (*func)(const BigramEntry&)) const {
    for (int i = 0; i < capacity; ++i) {
        Node* node = buckets[i];
        while (node) {
            func(node->entry);
            node = node->next;
        }
    }
}