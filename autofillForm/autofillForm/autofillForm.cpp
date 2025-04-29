#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

const int MAX_TEMPLATE_LENGTH = 512; // Длина строки шаблона

int main() {
    ifstream templateFile("letter.txt"); // Шаблон письма
    ifstream namesFile("names.txt");     // Файл с именами

    
    char templateContent[MAX_TEMPLATE_LENGTH] = {};
    templateFile.read(templateContent, MAX_TEMPLATE_LENGTH);
    templateFile.close();

    string name; // Для имени

    // Обработка шаблона 
    while (getline(namesFile, name)) {
        // Формирование имени выходного файла
        string outputFileName = "letter_to_" + name + ".txt";

        ofstream outputFile(outputFileName);
        
        const char* current = templateContent; // Указатель на текущий символ
        while (*current != '\0') {
            // Проверка на `***`
            if (*current == '*' && *(current + 1) == '*' && *(current + 2) == '*') {
                outputFile << name; // Вставка имени
                current += 3;       // Пропустить маркер `***`
            }
            else {
                outputFile.put(*current); // Копирование символа
                current++;
            }
        }

        outputFile.close();
    }

    namesFile.close();

    cout << "Files created successfully.\n";
    return 0;
}
