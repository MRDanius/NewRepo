#pragma once

#include <string>

// ��������� ��� �������� ������ � ��������
struct Driver {
    int id;             // ���������� ������������� ��������
    std::string fullName; // ��� ��������
    std::string birthDate; // ���� �������� � ������� ����-��-��
    Driver* next;       // ��������� �� ��������� ������� � ������
};

class DriverTable {
    Driver* head;                   // ��������� �� ������ ������ ���������
    const std::string filename = "����/.."; // ���� � ����� ������

    void clear();                   // ������� ������
    void parseLine(const std::string& line); // ������� ������ � ������ Driver

public:
    DriverTable();                  // �����������
    ~DriverTable();                 // ����������

    void load();                    // �������� ������ �� �����
    void save();                    // ���������� ������ � ����
    std::string getDriverInfo(int driverId); // ��������� ���������� � �������� �� ID
    Driver* getAllDrivers();        // ���������� ��������� �� ������ ������
};