//// FineTable.h
//#pragma once
//#include <string>
//#include "IntHashMap.h" 
//
//class FineTable {
//public:
//    struct Fine {
//        int id;
//        double amount;
//        std::string type;
//        Fine* next;
//    };
//
//private:
//    Fine* head;
//    IntHashMap idToFineMap;
//    const std::string filename = "fines.txt";
//    const int ID_LENGTH = 5;
//
//    void parseLine(const std::string& line);
//    void clear();
//    int getNextId();
//
//public:
//    FineTable();
//    ~FineTable();
//
//    void load();
//    void save();
//    void addFine(double amount, const std::string& type);
//    Fine* getFineById(int fineId);
//    Fine* getAllFines();
//    void deleteRecord(int fineId);
//    void updateReferences(int oldId, int newId = 0);
//};

//#pragma once
//#include <string>
//#include <map>
//#include "IntHashMap.h"
//
//class FineTable {
//    struct FineNode {
//        int id;
//        std::string type;
//        double amount;
//        FineNode* next;
//        FineNode(const int& id, const std::string& type, double amount, FineNode* next)
//            : id(id), type(type), amount(amount), next(next) {
//        }
//    };
//
//    FineNode* head;
//    IntHashMap idToFineMap;
//    std::map<std::string, int> typeToIdMap;
//    const std::string filename = "fines.txt";
//    const int ID_LENGTH = 5;
//    mutable FineNode* currentIterator = nullptr;
//
//    const int& generateNextId();
//    void parseLine(const std::string& line);
//    void clearList();
//
//public:
//    FineTable();
//    ~FineTable();
//
//    void loadFromFile();
//    void saveToFile();
//    void addFine(const std::string& type, double amount);
//    void deleteFine(const std::string& type);
//
//    struct FineInfo {
//        std::string type;
//        double amount;
//    };
//
//    FineInfo getFineInfoById(const int& id) const;
//    const int& getFineIdByType(const std::string& type) const;
//
//    void fineIteratorReset() const;
//    bool fineIteratorHasNext() const;
//    FineInfo fineIteratorNext() const;
//};


//#pragma once
//#include <string>
//#include <map>
//#include "IntHashMap.h"
//
//class FineTable {
//public:
//    enum class Severity { LIGHT, MEDIUM, HEAVY };
//
//    struct FineInfo {
//        std::string type;
//        double amount;
//        Severity severity;
//    };
//
//private:
//    struct FineNode {
//        int id;
//        std::string type;
//        double amount;
//        Severity severity;
//        FineNode* next;
//
//        FineNode(int id, const std::string& type,
//            double amount, Severity severity,
//            FineNode* next)
//            : id(id), type(type), amount(amount),
//            severity(severity), next(next) {
//        }
//    };
//
//    FineNode* head;
//    IntHashMap idToFineMap;
//    std::map<std::string, int> typeToIdMap;
//    const std::string filename = "fines.txt";
//    const int ID_LENGTH = 5;
//    mutable FineNode* currentIterator = nullptr;
//
//    const int& generateNextId();
//    void parseLine(const std::string& line);
//    void clearList();
//
//public:
//    FineTable();
//    ~FineTable();
//
//    void loadFromFile();
//    void saveToFile();
//    void addFine(const std::string& type, double amount,
//        Severity severity = Severity::LIGHT);
//    void deleteFine(const std::string& type);
//
//    static std::string severityToString(Severity severity);
//    const int& getFineIdByType(const std::string& type) const;
//    FineInfo getFineInfoById(int fineId) const;
//
//    void fineIteratorReset() const;
//    bool fineIteratorHasNext() const;
//    FineInfo fineIteratorNext();
//};


//#pragma once
//#include <string>
//#include <map>
//#include "IntHashMap.h"
//
//class FineTable {
//public:
//    enum class Severity { LIGHT, MEDIUM, HEAVY };
//
//    struct FineInfo {
//        std::string type;
//        double amount;
//        Severity severity;
//    };
//
//private:
//    struct FineNode {
//        int id;
//        std::string type;
//        double amount;
//        Severity severity;
//        FineNode* next;
//
//        FineNode(int id, const std::string& type,
//            double amount, Severity severity,
//            FineNode* next)
//            : id(id), type(type), amount(amount),
//            severity(severity), next(next) {
//        }
//    };
//
//    FineNode* head;
//    IntHashMap idToFineMap;
//    std::map<std::string, int> typeToIdMap;
//    const std::string filename = "fines.txt";
//    mutable FineNode* currentIterator = nullptr;
//
//    const int& generateNextId();
//    void parseLine(const std::string& line);
//    void clearList();
//
//public:
//    FineTable();
//    ~FineTable();
//
//    void loadFromFile();
//    void saveToFile();
//    void addFine(const std::string& type, double amount, Severity severity);
//    void deleteFine(const std::string& type);
//
//    static std::string severityToString(Severity severity);
//    const int& getFineIdByType(const std::string& type) const;
//    FineInfo getFineInfoById(int fineId) const;
//
//    void fineIteratorReset() const;
//    bool fineIteratorHasNext() const;
//    FineInfo fineIteratorNext() const;
//};


// FineTable.h

#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include "IntHashMap.h"

class FineTable {
public:
    // Уровень тяжести штрафа
    enum class Severity { LIGHT, MEDIUM, HEAVY };

    // Структура для передачи информации о штрафе
    struct FineInfo {
        int    id;
        double amount;
        std::string type;
        Severity severity;
    };

    // Конструктор / деструктор
    FineTable();
    ~FineTable();

    // Основные операции
    void loadFromFile();
    void saveToFile() const;
    void addFine(const std::string& type, double amount,
        Severity severity = Severity::LIGHT);
    void deleteFine(const std::string& type);

    // Итератор по списку штрафов
    void fineIteratorReset() const;
    bool fineIteratorHasNext() const;
    FineInfo fineIteratorNext() const;

    // Геттеры
    int getFineIdByType(const std::string& type) const;
    double getAmountById(int id) const;

    // Преобразование Severity в строку
    static std::string severityToString(Severity severity);

private:
    // Узел списка штрафов
    struct FineNode {
        int    id;
        double amount;
        std::string type;
        Severity severity;
        FineNode* next;
        FineNode(int id, double amount, const std::string& type,
            Severity severity, FineNode* next)
            : id(id), amount(amount), type(type),
            severity(severity), next(next) {
        }
    };

    // Основные поля
    FineNode* head;                 // заголовочный узел
    IntHashMap idToFineMap;         // хеш-таблица для быстрого поиска по ID
    std::map<std::string, int> typeToIdMap; // карта «тип → ID»
    mutable FineNode* currentIterator; // итератор

    // Ширины колонок (для форматированного вывода)
    int idWidth, amountWidth, typeWidth, severityWidth;

    // Вспомогательные методы
    void parseLine(const std::string& line);
    void addFineNode(int id, double amount, const std::string& type,
        Severity severity);
};
