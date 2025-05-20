//// DriverTable.h
//#pragma once
//#include <string>
//#include "IntHashMap.h"
//
//class DriverTable {
//public:
//    struct Driver {
//        int id;
//        std::string fullName;
//        std::string birthDate;
//        int cityId;
//        Driver* next;
//    };
//    IntHashMap idToDriverMap;
//private:
//    Driver* head;
//    const std::string filename = "drivers.txt";
//    const int ID_LENGTH = 5;
//
//    void parseLine(const std::string& line);
//    void clear();
//    int getNextId();
//
//public:
//    DriverTable();
//    ~DriverTable();
//
//    void load();
//    void save();
//    void addDriver(const std::string& fullName, const std::string& birthDate, int cityId);
//    std::string getDriverInfo(int driverId);
//    Driver* getAllDrivers();
//    void deleteRecord(int driverId);
//    void updateReferences(int oldId, int newId = 0);
//    void updateCityReferences(int oldCityId);
//};

//#pragma once
//#include <string>
//#include <map>
//#include "IntHashMap.h"
//#include "CityTable.h"
//
//class DriverTable {
//    struct DriverNode {
//        int id;
//        std::string fullName;
//        std::string birthDate;
//        int cityId;
//        DriverNode* next;
//        DriverNode(const int& id, const std::string& fullName,
//            const std::string& birthDate, int cityId, DriverNode* next)
//            : id(id), fullName(fullName), birthDate(birthDate),
//            cityId(cityId), next(next) {
//        }
//    };
//
//    DriverNode* head;
//    IntHashMap idToDriverMap;
//    std::map<std::string, int> nameToIdMap;
//    const std::string filename = "drivers.txt";
//    const int ID_LENGTH = 5;
//    mutable DriverNode* currentIterator = nullptr;
//
//    const int& generateNextId();
//    void parseLine(const std::string& line);
//    void clearList();
//
//public:
//    DriverTable();
//    ~DriverTable();
//
//    void loadFromFile();
//    void saveToFile();
//    void addDriver(const std::string& fullName,
//        const std::string& birthDate,
//        const int& cityId);
//    void deleteDriver(const std::string& name);
//
//    struct DriverInfo {
//        std::string fullName;
//        std::string birthDate;
//        std::string cityName;
//    };
//
//    DriverInfo getDriverInfo(const std::string& name) const;
//    const int& getDriverId(const std::string& name) const;
//    int getCityIdForDriver(const std::string& name) const;
//
//    void driverIteratorReset() const;
//    bool driverIteratorHasNext() const;
//    DriverInfo driverIteratorNext(const CityTable& cityTable) const;
//    void updateCityReferences(const int& cityId);
//    
//    DriverInfo getDriverInfoById(const int& driverId) const;
//};


//#pragma once
//#include <string>
//#include <map>
//#include "IntHashMap.h"
//#include "CityTable.h"
//
//class DriverTable {
//public:
//    struct DriverInfo {
//        int id;
//        std::string fullName;
//        std::string birthDate;
//        int cityId;
//    };
//
//private:
//    struct DriverNode {
//        int id;
//        std::string fullName;
//        std::string birthDate;
//        int cityId;
//        DriverNode* next;
//
//        DriverNode(int id, const std::string& fullName,
//            const std::string& birthDate, int cityId, DriverNode* next)
//            : id(id), fullName(fullName), birthDate(birthDate),
//            cityId(cityId), next(next) {
//        }
//    };
//
//    DriverNode* head;
//    IntHashMap idToDriverMap;
//    std::map<std::string, int> nameToIdMap;
//    const std::string filename = "drivers.txt";
//    const int ID_LENGTH = 5;
//    mutable DriverNode* currentIterator = nullptr;
//
//    const int& generateNextId();
//    void parseLine(const std::string& line);
//    void clearList();
//
//public:
//    DriverTable();
//    ~DriverTable();
//
//    void loadFromFile();
//    void saveToFile();
//    void addDriver(const std::string& fullName,
//        const std::string& birthDate,
//        int cityId);
//    void deleteDriver(const std::string& name);
//
//    DriverInfo getDriverInfo(const std::string& name) const;
//    DriverInfo getDriverInfoById(int driverId) const;
//    int getCityIdForDriver(const std::string& name) const;
//    void updateCityReferences(int oldCityId);
//
//    void driverIteratorReset() const;
//    bool driverIteratorHasNext() const;
//    DriverInfo driverIteratorNext() const;
//    const int& getDriverId(const std::string& name) const;
//};


//#pragma once
//#include <string>
//#include <map>
//#include "IntHashMap.h"
//#include "CityTable.h"
//
//class DriverTable {
//public:
//    struct DriverInfo {
//        int id;
//        std::string fullName;
//        std::string birthDate;
//        int cityId;
//    };
//
//    DriverInfo getDriverInfoById(int driverId) const;
//private:
//    struct DriverNode {
//        int id;
//        std::string fullName;
//        std::string birthDate;
//        int cityId;
//        DriverNode* next;
//
//        DriverNode(int id, const std::string& fullName,
//            const std::string& birthDate, int cityId, DriverNode* next)
//            : id(id), fullName(fullName), birthDate(birthDate),
//            cityId(cityId), next(next) {
//        }
//    };
//
//    DriverNode* head;
//    IntHashMap idToDriverMap;
//    std::map<std::string, int> nameToIdMap;
//    const std::string filename = "drivers.txt";
//    mutable DriverNode* currentIterator = nullptr;
//
//    const int& generateNextId();
//    void parseLine(const std::string& line);
//    void clearList();
//
//public:
//    DriverTable();
//    ~DriverTable();
//
//    void loadFromFile();
//    void saveToFile();
//    void addDriver(const std::string& fullName,
//        const std::string& birthDate,
//        int cityId);
//    void deleteDriver(const std::string& name);
//
//    DriverInfo getDriverInfo(const std::string& name) const;
//    int getDriverId(const std::string& name) const;
//    int getCityIdForDriver(const std::string& name) const;
//    void updateCityReferences(int oldCityId);
//
//
//    void driverIteratorReset() const;
//    bool driverIteratorHasNext() const;
//    DriverInfo driverIteratorNext() const;
//};

#pragma once
#include <string>
#include <map>
#include "IntHashMap.h"

class DriverTable {
public:
    // ��������� ��� ���������� � ��������
    struct DriverInfo {
        int id;
        std::string fullName;
        std::string birthDate;
        int cityId;
    };

private:
    // ���� ������ ���������
    struct DriverNode {
        int id;
        std::string fullName;
        std::string birthDate;
        int cityId;
        DriverNode* next;

        DriverNode(int id, const std::string& fullName,
            const std::string& birthDate, int cityId, DriverNode* next)
            : id(id), fullName(fullName), birthDate(birthDate),
            cityId(cityId), next(next) {
        }
    };

    // ��������� �������
    struct Filter {
        std::string field;    // ���� ��� ���������� (name, city_id � �.�.)
        std::string pattern;  // ������/������� (��������, "John*", ">100")
        Filter* next;         // ��������� ������ � �������
    };

    // �������� ����
    DriverNode* head;          // ������������ ����
    IntHashMap idToDriverMap;  // ���-������� ��� ������ �� ID
    std::map<std::string, int> nameToIdMap; // ����� ��� -> ID
    Filter* currentFilter;     // �������� �������

    // ��������� �����������
    mutable DriverNode* currentIterator; // ������� ������� ���������
    int idWidth;              // ������ ������� ID
    int nameWidth;            // ������ ������� �����
    int birthDateWidth;       // ������ ������� ���� ��������
    int cityIdWidth;          // ������ ������� ID ������

    // ��������� ������
    void parseLine(const std::string& line);
    void addDriverNode(int id, const std::string& fullName,
        const std::string& birthDate, int cityId);
    bool matchField(const DriverNode* node, const std::string& field,
        const std::string& pattern) const;
    bool checkNumeric(int value, const std::string& pattern) const;
    DriverNode* cloneNode(const DriverNode* src) const;

public:
    // �����������/����������
    DriverTable();
    ~DriverTable();

    // �������� ��������
    void loadFromFile();
    void saveToFile() const;
    void addDriver(const std::string& fullName,
        const std::string& birthDate,
        int cityId);
    void deleteDriver(const std::string& name);

    // ���������� ���������
    void addFilter(const std::string& field, const std::string& pattern);
    void clearFilters();
    DriverNode* applyFilters() const;

    // ��������������� ������
    void updateColumnWidths();
    std::string formatNode(const DriverNode* node) const;

    // ���������
    void driverIteratorReset(DriverNode* start = nullptr) const;
    bool driverIteratorHasNext() const;
    DriverInfo driverIteratorNext() const;

    // �������
    int getDriverId(const std::string& name) const;
    int getCityIdForDriver(const std::string& name) const;
};