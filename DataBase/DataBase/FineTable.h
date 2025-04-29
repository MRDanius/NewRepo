#pragma once

#include <string>


struct Fine {
    int id;          // ���������� ������������� ������
    double amount;   // ����� ������
    std::string type; // ��� ��������� (��������, "���������� ��������")
    Fine* next;      // ��������� �� ��������� ������� � ������
};

class FineTable {
    Fine* head;                   // ��������� �� ������ ������ �������
    const std::string filename = "����/.."; // ���� � ����� ������

    void clear();                 // ������� ������
    void parseLine(const std::string& line); // ������� ������ � ������ Fine

public:
    FineTable();                  // �����������
    ~FineTable();                 // ����������

    void load();                  // �������� ������ �� �����
    void save();                  // ���������� ������ � ����
    Fine* getFineById(int fineId); // ����� ������ �� ID
    Fine* getAllFines();          // ���������� ��������� �� ������ ������
};