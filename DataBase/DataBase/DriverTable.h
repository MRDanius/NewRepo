#pragma once

#include <string>

// Структура для хранения данных о водителе
struct Driver {
    int id;             // Уникальный идентификатор водителя
    std::string fullName; // ФИО водителя
    std::string birthDate; // Дата рождения в формате ГГГГ-ММ-ДД
    Driver* next;       // Указатель на следующий элемент в списке
};

class DriverTable {
    Driver* head;                   // Указатель на начало списка водителей
    const std::string filename = "путь/.."; // Путь к файлу данных

    void clear();                   // Очистка списка
    void parseLine(const std::string& line); // Парсинг строки в объект Driver

public:
    DriverTable();                  // Конструктор
    ~DriverTable();                 // Деструктор

    void load();                    // Загрузка данных из файла
    void save();                    // Сохранение данных в файл
    std::string getDriverInfo(int driverId); // Получение информации о водителе по ID
    Driver* getAllDrivers();        // Возвращает указатель на начало списка
};