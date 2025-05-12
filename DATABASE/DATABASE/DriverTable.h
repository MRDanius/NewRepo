// DriverTable.h
#pragma once
#include <string>
#include "IntHashMap.h"

class DriverTable {
public:
    struct Driver {
        int id;
        std::string fullName;
        std::string birthDate;
        int cityId;
        Driver* next;
    };

private:
    Driver* head;
    IntHashMap idToDriverMap;
    const std::string filename = "drivers.txt";
    const int ID_LENGTH = 5;

    void parseLine(const std::string& line);
    void clear();
    int getNextId();

public:
    DriverTable();
    ~DriverTable();

    void load();
    void save();
    void addDriver(const std::string& fullName, const std::string& birthDate, int cityId);
    std::string getDriverInfo(int driverId);
    Driver* getAllDrivers();
    void deleteRecord(int driverId);
    void updateReferences(int oldId, int newId = 0);
    void updateCityReferences(int oldCityId);
};