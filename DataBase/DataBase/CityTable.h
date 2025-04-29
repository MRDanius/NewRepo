#pragma once

#include <string>

// ��������� ��� �������� ������ � ������
struct City {
    int id;          // ���������� ������������� ������
    std::string name; // �������� ������
    City* next;      // ��������� �� ��������� ������� � ������
};

class CityTable {
    City* head;                   // ��������� �� ������ ������ �������
    const std::string filename = "����/.."; // ���� � ����� ������

    void clear();                 // ������� ������ (�������� ���� ���������)
    void parseLine(const std::string& line); // ������� ������ �� ����� � ������ City

public:
    CityTable();                  // ����������� 
    ~CityTable();                 // ���������� (�������� clear())

    void load();                  // �������� ������ �� ����� � ������
    void save();                  // ���������� ������ � ����
    std::string getCityName(int cityId); // ��������� �������� ������ �� ID
    City* getAllCities();         // ���������� ��������� �� ������ ������ �������
};