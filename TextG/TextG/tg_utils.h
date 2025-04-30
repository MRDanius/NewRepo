//#pragma once
//
//void lowercase(char* str);
//void copy_string(char* dest, const char* src, int max_len);
//void remove_punctuation(char* str);

#pragma once

bool remove_punctuation(char* str); // Возвращает true, если были удалены знаки пунктуации
void lowercase(char* str);
void copy_string(char* dest, const char* src, int max_len);