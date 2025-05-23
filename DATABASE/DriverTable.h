//#pragma once
//#include <string>
//#include <iostream>
//#include <iomanip>
//#include <regex>
//#include <map>
//#include "IntHashMap.h"
//
//class DriverTable {
//public:
//    // Структура для передачи информации о водителе
//    struct DriverInfo {
//        int    id;
//        std::string fullName;
//        std::string birthDate;
//        int    cityId;
//    };
//
//    // Конструктор / деструктор
//    DriverTable();
//    ~DriverTable();
//
//    // Основные операции
//    void loadFromFile();
//    void saveToFile() const;
//    void addDriver(const std::string& fullName,
//        const std::string& birthDate,
//        int cityId);
//    void deleteDriver(const std::string& fullName);
//
//    // Новый метод: удаление по ID
//    void deleteDriverById(int id);
//
//    // Итератор по списку водителей
//    void driverIteratorReset() const;
//    bool driverIteratorHasNext() const;
//    DriverInfo driverIteratorNext() const;
//
//    // Геттеры
//    int getDriverId(const std::string& fullName) const;
//    int getCityIdForDriver(const std::string& fullName) const;
//
//    // Обновление ссылок при удалении города
//    void updateCityReferences(int deletedCityId);
//
//    bool updateDriverCity(const std::string& fullName, int newCityId);
//
//    std::string getDriverNameById(int id) const;
//
//private:
//    // Узел списка водителей
//    struct DriverNode {
//        int    id;
//        std::string fullName;
//        std::string birthDate;
//        int    cityId;
//        DriverNode* next;
//        DriverNode(int id, const std::string& fullName, const std::string& birthDate,
//            int cityId, DriverNode* next)
//            : id(id), fullName(fullName), birthDate(birthDate),
//            cityId(cityId), next(next) {
//        }
//    };
//
//    // Основные поля
//    DriverNode* head;               // заголовочный узел
//    IntHashMap idToDriverMap;       // хеш-таблица для быстрого поиска по ID
//    std::map<std::string, int> nameToIdMap; // карта «ФИО → ID»
//    mutable DriverNode* currentIterator; // итератор
//
//    // Ширины колонок (для форматированного вывода)
//    int idWidth, nameWidth, birthDateWidth, cityIdWidth;
//
//    // Вспомогательные методы
//    void parseLine(const std::string& line);
//    void addDriverNode(int id, const std::string& fullName,
//        const std::string& birthDate, int cityId);
//    bool validateName(const std::string& name) const;
//    bool validateDate(const std::string& date) const;
//};

//// DriverTable.h
//#pragma once
//#include <string>
//#include <iostream>
//#include <iomanip>
//#include <regex>
//#include <map>
//#include "IntHashMap.h"
//#include <ctime>
//
//class DriverTable {
//public:
//    struct DriverInfo {
//        int    id;
//        std::string fullName;
//        std::string birthDate;
//        int    cityId;
//    };
//
//    DriverTable();
//    ~DriverTable();
//
//    void loadFromFile();
//    void saveToFile() const;
//    void addDriver(const std::string& fullName,
//        const std::string& birthDate,
//        int cityId);
//    void deleteDriver(const std::string& fullName);
//    void deleteDriverById(int id);
//
//    void driverIteratorReset() const;
//    bool driverIteratorHasNext() const;
//    DriverInfo driverIteratorNext() const;
//
//    int getDriverId(const std::string& fullName) const;
//    int getCityIdForDriver(const std::string& fullName) const;
//
//    void updateCityReferences(int deletedCityId);
//    bool updateDriverCity(const std::string& fullName, int newCityId);
//
//    std::string getDriverNameById(int id) const;
//
//    // Редактирование
//    bool updateDriverName(int id, const std::string& newName);
//    bool updateDriverBirthDate(int id, const std::string& newBirthDate);
//    bool updateDriverCity(int id, int newCityId);
//
//private:
//    struct DriverNode {
//        int    id;
//        std::string fullName;
//        std::string birthDate;
//        int    cityId;
//        DriverNode* next;
//        DriverNode(int id, const std::string& fullName, const std::string& birthDate,
//            int cityId, DriverNode* next)
//            : id(id), fullName(fullName), birthDate(birthDate),
//            cityId(cityId), next(next) {
//        }
//    };
//
//    DriverNode* head;
//    IntHashMap idToDriverMap;
//    std::map<std::string, int> nameToIdMap;
//    mutable DriverNode* currentIterator;
//
//    int idWidth, nameWidth, birthDateWidth, cityIdWidth;
//
//    void parseLine(const std::string& line);
//    void addDriverNode(int id, const std::string& fullName,
//        const std::string& birthDate, int cityId);
//
//    bool validateName(const std::string& name) const;
//    bool validateDate(const std::string& date) const;
//    bool validateAge(const std::string& birthDate) const;
//};

#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <regex>
#include <map>
#include "IntHashMap.h"
#include <ctime>

class DriverTable {
public:
    // Структура для передачи информации о водителе
    struct DriverInfo {
        int    id;
        std::string fullName;
        std::string birthDate;
        int    cityId;
    };

    // Конструктор / деструктор
    DriverTable();
    ~DriverTable();

    // Основные операции
    void loadFromFile();
    void saveToFile() const;
    void addDriver(const std::string& fullName,
        const std::string& birthDate,
        int cityId);
    void deleteDriver(const std::string& fullName);
    void deleteDriverById(int id);

    // Итератор по списку водителей
    void driverIteratorReset() const;
    bool driverIteratorHasNext() const;
    DriverInfo driverIteratorNext() const;

    // Геттеры
    int getDriverId(const std::string& fullName) const;
    int getCityIdForDriver(const std::string& fullName) const;
    std::string getDriverNameById(int id) const;  // ← добавлено

    // Обновление ссылок при удалении города
    void updateCityReferences(int deletedCityId);

    // Редактирование данных водителя
    bool updateDriverName(int id, const std::string& newName);
    bool updateDriverBirthDate(int id, const std::string& newBirthDate);
    bool updateDriverCity(int id, int newCityId);

    // Фильтры
    void addFilter(const std::string& field, int cmpType, const std::string& value);
    void clearFilters();
    DriverInfo* applyFilters(int& outCount) const;

    int getFilterCount() const;
    std::string getFilterDescription(int index) const;
    void removeFilterAt(int index);

private:
    // Узел списка водителей
    struct DriverNode {
        int    id;
        std::string fullName;
        std::string birthDate;
        int    cityId;
        DriverNode* next;
        DriverNode(int id, const std::string& fullName, const std::string& birthDate,
            int cityId, DriverNode* next)
            : id(id), fullName(fullName), birthDate(birthDate),
            cityId(cityId), next(next) {
        }
    };

    // Структура фильтра
    struct Filter {
        std::string field;
        int cmpType; // 1: contains, 2: equals
        std::string value;
        Filter* next;
    };

    DriverNode* head;                 // заголовочный узел
    IntHashMap idToDriverMap;         // поиск по ID
    std::map<std::string, int> nameToIdMap; // ФИО → ID
    mutable DriverNode* currentIterator;
    Filter* currentFilter;

    int idWidth, nameWidth, birthDateWidth, cityIdWidth;

    void parseLine(const std::string& line);
    void addDriverNode(int id, const std::string& fullName,
        const std::string& birthDate, int cityId);

    bool validateName(const std::string& name) const;
    bool validateDate(const std::string& date) const;
    bool validateAge(const std::string& birthDate) const;

    bool matchField(const DriverNode* node, const std::string& field,
        int cmpType, const std::string& value) const;
    DriverInfo cloneInfo(const DriverNode* node) const;
};
