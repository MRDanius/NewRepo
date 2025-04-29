#pragma once

#include <vector>   
#include <string>   


using namespace std;


struct BigramRecord {
    int word1_id;   // ID первого слова в паре
    int word2_id;   // ID второго слова в паре
    int count;      
};


class TextGenerator {
private:
    
    vector<string> words;       // Словарь всех уникальных слов (индекс = ID слова)
    vector<BigramRecord> bigrams; // Список биграм с их частотами

    
    int get_word_id(const string& word);            // Получение ID слова 
    void add_bigram(int word1_id, int word2_id);    // Добавление/обновление биграмы в список
    string to_lower(const string& str);             // Преобразование строки в нижний регистр

public:
    
    void train(const string& filepath);             // Обучение модели на текстовом файле
    string generate(const string& seed, int num_words); // Генерация текста (начальное слово, количество слов)
    void save_model();   // Сохранение модели в файлы
    void load_model();   // Загрузка модели из файлов
};