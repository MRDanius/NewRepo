#include "tg_utils.h"

void lowercase(char* str) {
    for (int i = 0; str[i]; ++i)
        str[i] = tolower(str[i]);
}

void copy_string(char* dest, const char* src, int max_len) {
    int i;
    for (i = 0; i < max_len - 1 && src[i]; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
}

const char* string_tokenize(const char* str, const char* delimiters, int& start_pos) {
    if (!str || start_pos < 0) return nullptr;

    while (str[start_pos]) {
        bool is_delim = false;
        for (int i = 0; delimiters[i]; ++i) {
            if (str[start_pos] == delimiters[i]) {
                is_delim = true;
                break;
            }
        }
        if (!is_delim) break;
        start_pos++;
    }

    if (!str[start_pos]) return nullptr;

    int end = start_pos;
    while (str[end]) {
        bool is_delim = false;
        for (int i = 0; delimiters[i]; ++i) {
            if (str[end] == delimiters[i]) {
                is_delim = true;
                break;
            }
        }
        if (is_delim) break;
        end++;
    }

    static char buffer[1024];
    int length = end - start_pos;
    for (int i = 0; i < length; ++i)
        buffer[i] = str[start_pos + i];
    buffer[length] = '\0';
    start_pos = end;
    return buffer;
}

int string_length(const char* str) {
    int len = 0;
    while (str[len]) len++;
    return len;
}