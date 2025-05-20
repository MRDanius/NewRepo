//// FineRegistry.h
//#pragma once
//#include <string>
//#include "IntHashMap.h"
//
//class FineRegistry {
//public:
//    struct FineRecord {
//        int id;
//        int driverId;
//        int cityId;
//        int fineId;
//        std::string violationDate;
//        bool isPaid;
//        FineRecord* next;
//
//    };
//
//private:
//    FineRecord* head;
//    IntHashMap idToRecordMap;
//    const std::string filename = "registry.txt";
//    const int ID_LENGTH = 5;
//
//    void parseLine(const std::string& line);
//    void clear();
//    int getNextId();
//
//public:
//    FineRegistry();
//    ~FineRegistry();
//
//    FineRecord* getAllViolations() const {  // ← Добавляем этот метод
//        return head->next;  // Возвращаем начало списка нарушений
//    }
//
//    void load();
//    void save();
//    void addRecord(int driverId, int cityId, int fineId, const std::string& vioaltionDate, bool isPaid);
//    FineRecord* getRecordsByDriver(int driverId);
//    FineRecord* getRecordsByCity(int cityId);
//    void markAsPaid(int recordId);
//    void deleteRecord(int recordId);
//    void updateDriverReferences(int oldDriverId);
//    void updateCityReferences(int oldCityId);
//};

//#pragma once
//#include <string>
//#include "IntHashMap.h"
//#include "CityTable.h"
//#include "DriverTable.h"
//#include "FineTable.h"
//
//class FineRegistry {
//    struct ViolationNode {
//        int id;
//        int driverId;
//        int cityId;
//        int fineId;
//        std::string date;
//        bool paid;
//        ViolationNode* next;
//        ViolationNode(const int& id, int driverId, int cityId,
//            int fineId, const std::string& date, bool paid,
//            ViolationNode* next)
//            : id(id), driverId(driverId), cityId(cityId),
//            fineId(fineId), date(date), paid(paid), next(next) {
//        }
//    };
//
//    ViolationNode* head;
//    IntHashMap idToViolationMap;
//    const std::string filename = "registry.txt";
//    const int ID_LENGTH = 5;
//    mutable ViolationNode* currentIterator = nullptr;
//
//    const int& generateNextId();
//    void parseLine(const std::string& line);
//    void clearList();
//
//public:
//    FineRegistry();
//    ~FineRegistry();
//
//    void loadFromFile();
//    void saveToFile();
//    void addViolation(const int& driverId, const int& cityId,
//        const int& fineId, const std::string& date);
//
//    struct ViolationInfo {
//        std::string driverName;
//        std::string cityName;
//        std::string fineType;
//        std::string date;
//        bool paid;
//        int recordId;
//    };
//
//    void markAsPaid(const int& recordId);
//    void updateDriverReferences(const int& driverId);
//    void updateCityReferences(const int& cityId);
//
//    void violationIteratorReset() const;
//    bool violationIteratorHasNext() const;
//    ViolationInfo violationIteratorNext(const DriverTable& drivers,
//        const CityTable& cities,
//        const FineTable& fines) const;
//};


//#pragma once
//#include <string>
//#include "IntHashMap.h"
//#include "DriverTable.h"
//#include "CityTable.h"
//#include "FineTable.h"
//
//class FineRegistry {
//public:
//    struct ViolationInfo {
//        int id;
//        std::string driverName;
//        std::string cityName;
//        std::string fineType;
//        std::string date;
//        bool paid;
//        double amount;
//        FineTable::Severity severity;
//    };
//
//private:
//    struct ViolationNode {
//        int id;
//        int driverId;
//        int cityId;
//        int fineId;
//        std::string date;
//        bool paid;
//        ViolationNode* next;
//
//        ViolationNode(int id, int driverId, int cityId,
//            int fineId, const std::string& date,
//            bool paid, ViolationNode* next)
//            : id(id), driverId(driverId), cityId(cityId),
//            fineId(fineId), date(date), paid(paid), next(next) {
//        }
//    };
//
//    ViolationNode* head;
//    IntHashMap idToViolationMap;
//    const std::string filename = "registry.txt";
//    const int ID_LENGTH = 5;
//    mutable ViolationNode* currentIterator = nullptr;
//
//    const int& generateNextId();
//    void parseLine(const std::string& line);
//    void clearList();
//
//public:
//    FineRegistry();
//    ~FineRegistry();
//
//    void loadFromFile();
//    void saveToFile();
//    void addViolation(int driverId, int cityId,
//        int fineId, const std::string& date);
//    void markAsPaid(int recordId);
//    void updateDriverReferences(int driverId);
//    void updateCityReferences(int cityId);
//
//    void violationIteratorReset() const;
//    bool violationIteratorHasNext() const;
//    ViolationInfo violationIteratorNext(const DriverTable& drivers,
//        const CityTable& cities,
//        const FineTable& fines) const;
//};


//#pragma once
//#include "DriverTable.h"
//#include "CityTable.h"
//#include "FineTable.h"
//#include <vector>
//
//class FineRegistry {
//public:
//    struct ViolationInfo {
//        int id;
//        std::string driverName;
//        std::string cityName;
//        std::string fineType;
//        std::string date;
//        double amount;
//        bool paid;
//        FineTable::Severity severity;
//    };
//
//private:
//    struct ViolationNode {
//        int id;
//        int driverId;
//        int cityId;
//        int fineId;
//        std::string date;
//        bool paid;
//        ViolationNode* next;
//
//        ViolationNode(int id, int driverId, int cityId,
//            int fineId, const std::string& date,
//            bool paid, ViolationNode* next)
//            : id(id), driverId(driverId), cityId(cityId),
//            fineId(fineId), date(date), paid(paid), next(next) {
//        }
//    };
//
//    ViolationNode* head;
//    IntHashMap idToViolationMap;
//    const std::string filename = "registry.txt";
//    mutable ViolationNode* currentIterator = nullptr;
//
//    const int& generateNextId();
//    void parseLine(const std::string& line);
//    void clearList();
//
//public:
//    FineRegistry();
//    ~FineRegistry();
//
//    void loadFromFile();
//    void saveToFile();
//    void addViolation(int driverId, int cityId, int fineId, const std::string& date);
//    void markAsPaid(int recordId);
//    void updateDriverReferences(int driverId);
//    void updateCityReferences(int cityId);
//
//    void violationIteratorReset() const;
//    bool violationIteratorHasNext() const;
//    ViolationInfo violationIteratorNext(const DriverTable& drivers,
//        const CityTable& cities,
//        const FineTable& fines) const;
//};

// FineRegistry.h

#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include "IntHashMap.h"
#include "DriverTable.h"
#include "CityTable.h"
#include "FineTable.h"

class FineRegistry {
public:
    // Структура для передачи информации о нарушении
    struct ViolationInfo {
        int    recordId;
        int    driverId;
        int    cityId;
        int    fineId;
        bool   paid;
        std::string date;

        // Детальная информация
        std::string driverName;
        std::string cityName;
        std::string fineType;
        double fineAmount;
    };

    // Конструктор / деструктор
    FineRegistry();
    ~FineRegistry();

    // Основные операции
    void loadFromFile();
    void saveToFile() const;
    void addViolation(int driverId, int cityId, int fineId, const std::string& date);
    void markAsPaid(int recordId);

    // Итератор по списку нарушений (возвращает подробную информацию)
    void violationIteratorReset() const;
    bool violationIteratorHasNext() const;
    ViolationInfo violationIteratorNext(const DriverTable& drivers,
        const CityTable& cities,
        const FineTable& fines) const;

    // Обновление ссылок при удалении водителя или города
    void updateDriverReferences(int deletedDriverId);
    void updateCityReferences(int deletedCityId);

private:
    // Узел списка нарушений
    struct ViolationNode {
        int    recordId;
        int    driverId;
        int    cityId;
        int    fineId;
        bool   paid;
        std::string date;
        ViolationNode* next;
        ViolationNode(int recordId, int driverId, int cityId,
            int fineId, bool paid, const std::string& date,
            ViolationNode* next)
            : recordId(recordId), driverId(driverId), cityId(cityId),
            fineId(fineId), paid(paid), date(date), next(next) {
        }
    };

    // Основные поля
    ViolationNode* head;             // заголовочный узел
    IntHashMap recordToNodeMap;      // хеш-таблица для быстрого поиска по recordId
    mutable ViolationNode* currentIterator; // итератор

    // Ширины колонок (для форматированного вывода)
    int recordIdWidth, driverIdWidth, cityIdWidth, fineIdWidth, paidWidth, dateWidth;

    // Вспомогательные методы
    void parseLine(const std::string& line);
    void addViolationNode(int recordId, int driverId, int cityId,
        int fineId, bool paid, const std::string& date);
};
