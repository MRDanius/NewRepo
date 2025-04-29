#pragma once
#include <cctype>

void lowercase(char* str);
void copy_string(char* dest, const char* src, int max_len);
const char* string_tokenize(const char* str, const char* delimiters, int& start_pos);
int string_length(const char* str);