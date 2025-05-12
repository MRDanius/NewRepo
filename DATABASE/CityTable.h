// CityTable.h
#pragma once
#include <string>
#include "IntHashMap.h"

class CityTable {
public:
    struct City {
        int id;
        std::string name;
        City* next;
    };

private:
    City* head;
    IntHashMap idToCityMap;
    const std::string filename = "cities.txt";
    const int ID_LENGTH = 5;

    void parseLine(const std::string& line);
    void clear();
    int getNextId();

public:
    CityTable();
    ~CityTable();

    void load();
    void save();
    void addCity(const std::string& name);
    std::string getCityName(int cityId);
    City* getAllCities();
    void deleteRecord(int cityId);
    void updateReferences(int oldId, int newId = 0);
};
