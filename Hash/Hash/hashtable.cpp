#include "hashtable.h"
#include <iostream>
#include <cstring>
using namespace std;

ListNode::ListNode() : next(nullptr) {
    memset(word, 0, sizeof(word));
}

Bucket::Bucket() : count(0), head(nullptr) {}

HashTable::HashTable(int h, int C) : h(h), C(C) {
    table = new Bucket[C];
}

HashTable::~HashTable() {
    for (int i = 0; i < C; ++i) {
        ListNode* current = table[i].head;
        while (current) {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] table;
}

int HashTable::calculateHash(const char* word) const {
    int hash = 0;
    int power = 1;
    for (int i = 0; word[i] && i < 4; ++i) {
        hash = (hash + word[i] * power) % C;
        power = (power * h) % C;
    }
    return hash;
}

bool HashTable::existsInBucket(const Bucket& bucket, const char* word) const {
    ListNode* current = bucket.head;
    while (current) {
        if (strncmp(current->word, word, 4) == 0) return true;
        current = current->next;
    }
    return false;
}

bool HashTable::addWordIfUnique(const char* word) {
    int hash = calculateHash(word);
    if (existsInBucket(table[hash], word)) return false;

    ListNode* newNode = new ListNode();
    strncpy_s(newNode->word, word, 4);
    newNode->word[4] = '\0';
    newNode->next = table[hash].head;
    table[hash].head = newNode;
    table[hash].count++;
    return true;
}

void HashTable::printBucketCounts() const {
    for (int i = 0; i < C; ++i) {
        cout << "Bucket " << i << ": " << table[i].count << " elements\n";
    }
}

int HashTable::getBucketCount() const {
    return C;
}

void HashTable::exportToCSV(std::ofstream& file) const {
    for (int i = 0; i < C; ++i) {
        file << C << ";" << i << ";" << table[i].count << "\n";
    }
}