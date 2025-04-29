#pragma once
#include <string>
#include <fstream>

struct ListNode {
    char word[5];
    ListNode* next;
    ListNode();
};

struct Bucket {
    int count;
    ListNode* head;
    Bucket();
};

class HashTable {
private:
    int h;
    int C;
    Bucket* table;
    int calculateHash(const char* word) const;
    bool existsInBucket(const Bucket& bucket, const char* word) const;

public:
    HashTable(int h, int C);
    ~HashTable();

    bool addWordIfUnique(const char* word);
    void printBucketCounts() const;
    int getBucketCount() const;
    void exportToCSV(std::ofstream& file) const;
};