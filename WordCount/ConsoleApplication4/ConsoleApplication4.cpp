#include <iostream>
#include <cctype>
#include <cstring>

const int maxSize = 16;  // Максимальная длина строки

// Функция для проверки, является ли строка числом
bool isNumber(const char* str) {
    bool hasDigit = false;
    int plusCount = 0;
    int minusCount = 0;
    bool hasDotOrComma = false;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (isdigit(str[i])) {
            hasDigit = true;
        }
        if (str[i] == '+') {
            if (++plusCount > 1) return false;
        }
        if (str[i] == '-') {
            if (++minusCount > 1) return false;
        }
        if (str[i] == '.' || str[i] == ',') {
            if (hasDotOrComma) return false;
            hasDotOrComma = true;
        }
        if (!isdigit(str[i]) && str[i] != '+' && str[i] != '-' && str[i] != '.' && str[i] != ',') {
            return false;
        }
    }
    return hasDigit && plusCount <= 1 && minusCount <= 1 && (!hasDotOrComma || hasDotOrComma);
}

// Функция для проверки, является ли строка словом
bool isWord(const char* str) {
    bool hasAlpha = false;
    bool isNum = isNumber(str);

    for (int i = 0; str[i] != '\0'; ++i) {
        if (isalpha(str[i])) {
            hasAlpha = true;
            break;
        }
    }

    // Слово, если содержит буквы или если это не число
    return hasAlpha || !isNum;
}

int main() {
    char word[maxSize];
    int index = 0;
    int wordCount = 0;

    std::cout << "Enter string: ";

    while (true) {
        char ch;
        std::cin.get(ch);

        if (ch == ' ' || ch == '\t' || ch == '\n') {
            word[index] = '\0';

            if (index > 0) {
                if (isWord(word)) {
                    std::cout << word << " ";
                    wordCount++;
                }
            }

            index = 0;
            if (ch == '\n') break;
        }
        else if (isalpha(ch) || isdigit(ch) || ch == '+' || ch == '-' || ch == '.' || ch == ',') {
            if (index < maxSize - 1) word[index++] = ch;
        }
    }

    std::cout << "\nWord count: " << wordCount << std::endl;

    return 0;
}
//число  - группа символов состоящая из цифры которая кроме цифр может содержать одну точку или запятую не более одного плюса и одного минуса.
 //    Словом является любая группа символов содержащая хотя бы одну букву или группа цифр не явлющаяся числом. ДОбавить счётчик слов.