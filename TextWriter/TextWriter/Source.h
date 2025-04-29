#pragma once

#include <vector>   
#include <string>   


using namespace std;


struct BigramRecord {
    int word1_id;   // ID ������� ����� � ����
    int word2_id;   // ID ������� ����� � ����
    int count;      
};


class TextGenerator {
private:
    
    vector<string> words;       // ������� ���� ���������� ���� (������ = ID �����)
    vector<BigramRecord> bigrams; // ������ ������ � �� ���������

    
    int get_word_id(const string& word);            // ��������� ID ����� 
    void add_bigram(int word1_id, int word2_id);    // ����������/���������� ������� � ������
    string to_lower(const string& str);             // �������������� ������ � ������ �������

public:
    
    void train(const string& filepath);             // �������� ������ �� ��������� �����
    string generate(const string& seed, int num_words); // ��������� ������ (��������� �����, ���������� ����)
    void save_model();   // ���������� ������ � �����
    void load_model();   // �������� ������ �� ������
};