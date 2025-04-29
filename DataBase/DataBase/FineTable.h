#pragma once

#include <string>


struct Fine {
    int id;          // Уникальный идентификатор штрафа
    double amount;   // Сумма штрафа
    std::string type; // Тип нарушения (например, "Превышение скорости")
    Fine* next;      // Указатель на следующий элемент в списке
};

class FineTable {
    Fine* head;                   // Указатель на начало списка штрафов
    const std::string filename = "путь/.."; // Путь к файлу данных

    void clear();                 // Очистка списка
    void parseLine(const std::string& line); // Парсинг строки в объект Fine

public:
    FineTable();                  // Конструктор
    ~FineTable();                 // Деструктор

    void load();                  // Загрузка данных из файла
    void save();                  // Сохранение данных в файл
    Fine* getFineById(int fineId); // Поиск штрафа по ID
    Fine* getAllFines();          // Возвращает указатель на начало списка
};