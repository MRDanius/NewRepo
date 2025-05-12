// FineRegistry.h
#pragma once
#include <string>
#include "IntHashMap.h"

class FineRegistry {
public:
    struct FineRecord {
        int id;
        int driverId;
        int cityId;
        int fineId;
        bool isPaid;
        FineRecord* next;
    };

private:
    FineRecord* head;
    IntHashMap idToRecordMap;
    const std::string filename = "registry.txt";
    const int ID_LENGTH = 5;

    void parseLine(const std::string& line);
    void clear();
    int getNextId();

public:
    FineRegistry();
    ~FineRegistry();

    void load();
    void save();
    void addRecord(int driverId, int cityId, int fineId, bool isPaid);
    FineRecord* getRecordsByDriver(int driverId);
    FineRecord* getRecordsByCity(int cityId);
    void markAsPaid(int recordId);
    void deleteRecord(int recordId);
    void updateDriverReferences(int oldDriverId);
    void updateCityReferences(int oldCityId);
};