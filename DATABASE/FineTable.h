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


#pragma once
#include <string>
#include <map>
#include "IntHashMap.h"

class FineTable {
public:
    enum class Severity { LIGHT, MEDIUM, HEAVY };

    // Структура данных БЕЗ ID
    struct FineInfo {
        std::string type;
        double amount;
        Severity severity;
    };

private:
    struct FineNode {
        int id; // Внутренний ID (не отображается)
        std::string type;
        double amount;
        Severity severity;
        FineNode* next;

        FineNode(int id, const std::string& type,
            double amount, Severity severity, FineNode* next)
            : id(id), type(type), amount(amount),
            severity(severity), next(next) {
        }
    };

    struct Filter {
        std::string field;
        std::string pattern;
        Filter* next;
    };

    FineNode* head;
    IntHashMap idToFineMap;
    std::map<std::string, int> typeToIdMap;
    Filter* currentFilter;

    mutable FineNode* currentIterator;
    int typeWidth;
    int amountWidth;
    int severityWidth;

    void parseLine(const std::string& line);
    void addFineNode(int id, const std::string& type,
        double amount, Severity severity);
    bool matchField(const FineNode* node, const std::string& field,
        const std::string& pattern) const;
    bool checkNumeric(double value, const std::string& pattern) const;
    FineNode* cloneNode(const FineNode* src) const;

public:
    FineTable();
    ~FineTable();

    void loadFromFile();
    void saveToFile() const;
    void addFine(const std::string& type, double amount, Severity severity);
    void deleteFine(const std::string& type);

    static std::string severityToString(Severity severity);
    const int& getFineIdByType(const std::string& type) const;

    void addFilter(const std::string& field, const std::string& pattern);
    void clearFilters();
    FineNode* applyFilters() const;

    void updateColumnWidths();
    std::string formatNode(const FineNode* node) const;

    void fineIteratorReset(FineNode* start = nullptr) const;
    bool fineIteratorHasNext() const;
    FineInfo fineIteratorNext() const;
};