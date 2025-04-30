//#include "tg_utils.h"
//#include <cctype>
//#include <cstring>
//
//void lowercase(char* str) {
//    for (int i = 0; str[i]; ++i)
//        str[i] = tolower(static_cast<unsigned char>(str[i]));
//}
//
//void copy_string(char* dest, const char* src, int max_len) {
//    int i;
//    for (i = 0; i < max_len - 1 && src[i]; ++i)
//        dest[i] = src[i];
//    dest[i] = '\0';
//}
//
//void remove_punctuation(char* str) {
//    int len = strlen(str);
//    while (len > 0 && ispunct(static_cast<unsigned char>(str[len - 1]))) {
//        str[len - 1] = '\0';
//        len--;
//    }
//}

#include "tg_utils.h"
#include <cctype>
#include <cstring>

bool remove_punctuation(char* str) {
    int len = strlen(str);
    bool had_punctuation = false;

    // Удаление пунктуации в конце
    while (len > 0 && ispunct(static_cast<unsigned char>(str[len - 1]))) {
        str[len - 1] = '\0';
        len--;
        had_punctuation = true;
    }

    // Удаление пунктуации в начале
    int start = 0;
    while (str[start] && ispunct(static_cast<unsigned char>(str[start]))) {
        start++;
        had_punctuation = true;
    }

    if (start > 0) {
        memmove(str, str + start, len - start + 1);
    }

    return had_punctuation;
}

void lowercase(char* str) {
    for (int i = 0; str[i]; ++i)
        str[i] = tolower(static_cast<unsigned char>(str[i]));
}

void copy_string(char* dest, const char* src, int max_len) {
    int i;
    for (i = 0; i < max_len - 1 && src[i]; ++i)
        dest[i] = src[i];
    dest[i] = '\0';
}