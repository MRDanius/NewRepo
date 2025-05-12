// FineTable.h
#pragma once
#include <string>
#include "IntHashMap.h" 

class FineTable {
public:
    struct Fine {
        int id;
        double amount;
        std::string type;
        Fine* next;
    };

private:
    Fine* head;
    IntHashMap idToFineMap;
    const std::string filename = "fines.txt";
    const int ID_LENGTH = 5;

    void parseLine(const std::string& line);
    void clear();
    int getNextId();

public:
    FineTable();
    ~FineTable();

    void load();
    void save();
    void addFine(double amount, const std::string& type);
    Fine* getFineById(int fineId);
    Fine* getAllFines();
    void deleteRecord(int fineId);
    void updateReferences(int oldId, int newId = 0);
};