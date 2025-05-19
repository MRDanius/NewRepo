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


#pragma once
#include <string>
#include "IntHashMap.h"
#include "DriverTable.h"
#include "CityTable.h"
#include "FineTable.h"

class FineRegistry {
public:
    struct ViolationInfo {
        int id;
        std::string driverName;
        std::string cityName;
        std::string fineType;
        std::string date;
        bool paid;
        double amount;
        FineTable::Severity severity;
    };

private:
    struct ViolationNode {
        int id;
        int driverId;
        int cityId;
        int fineId;
        std::string date;
        bool paid;
        ViolationNode* next;

        ViolationNode(int id, int driverId, int cityId,
            int fineId, const std::string& date,
            bool paid, ViolationNode* next)
            : id(id), driverId(driverId), cityId(cityId),
            fineId(fineId), date(date), paid(paid), next(next) {
        }
    };

    ViolationNode* head;
    IntHashMap idToViolationMap;
    const std::string filename = "registry.txt";
    const int ID_LENGTH = 5;
    mutable ViolationNode* currentIterator = nullptr;

    const int& generateNextId();
    void parseLine(const std::string& line);
    void clearList();

public:
    FineRegistry();
    ~FineRegistry();

    void loadFromFile();
    void saveToFile();
    void addViolation(int driverId, int cityId,
        int fineId, const std::string& date);
    void markAsPaid(int recordId);
    void updateDriverReferences(int driverId);
    void updateCityReferences(int cityId);

    void violationIteratorReset() const;
    bool violationIteratorHasNext() const;
    ViolationInfo violationIteratorNext(const DriverTable& drivers,
        const CityTable& cities,
        const FineTable& fines) const;
};