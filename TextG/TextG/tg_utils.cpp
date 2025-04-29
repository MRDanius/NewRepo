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

void lowercase(char* str) {
    for (int i = 0; str[i]; ++i)
        str[i] = tolower(static_cast<unsigned char>(str[i]));
}

void copy_string(char* dest, const char* src, int max_len) { //изменено
    int i;
    for (i = 0; i < max_len - 1 && src[i]; ++i) {
        dest[i] = src[i];
    }
    dest[i] = '\0'; 
}

void remove_punctuation(char* str) {
    int len = strlen(str);

    // Удаляем пунктуацию в начале
    int start = 0;
    while (start < len && ispunct(static_cast<unsigned char>(str[start]))) {
        start++;
    }

    // Удаляем пунктуацию в конце
    int end = len - 1;
    while (end >= start && ispunct(static_cast<unsigned char>(str[end]))) {
        end--;
    }

    // Переносим очищенную строку
    if (start > 0 || end < len - 1) {
        int new_len = end - start + 1;
        if (new_len > 0) {
            memmove(str, str + start, new_len);
        }
        str[new_len] = '\0';
    }
}