#pragma once

struct WordEntry {
    char word[100];
    int id;
};

struct BigramKey {
    int from_id;
    int to_id;
};

struct BigramEntry {
    BigramKey key;
    int count;
};