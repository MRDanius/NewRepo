#pragma once

#include <string>

// Структура для хранения данных о городе
struct City {
    int id;          // Уникальный идентификатор города
    std::string name; // Название города
    City* next;      // Указатель на следующий элемент в списке
};

class CityTable {
    City* head;                   // Указатель на начало списка городов
    const std::string filename = "путь/.."; // Путь к файлу данных

    void clear();                 // Очистка списка (удаление всех элементов)
    void parseLine(const std::string& line); // Парсинг строки из файла в объект City

public:
    CityTable();                  // Конструктор 
    ~CityTable();                 // Деструктор (вызывает clear())

    void load();                  // Загрузка данных из файла в список
    void save();                  // Сохранение списка в файл
    std::string getCityName(int cityId); // Получение названия города по ID
    City* getAllCities();         // Возвращает указатель на начало списка городов
};