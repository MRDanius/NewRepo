#include <iostream>
#include <cctype>  // Для функций isalpha и isdigit
#include <cstring> 

// Функция для проверки, является ли строка числом
bool isNumber(const char* str) {
    bool hasDigit = false;
    int plusCount = 0;
    int minusCount = 0;
    bool hasDotOrComma = false;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (isdigit(str[i])) {
            hasDigit = true;  // Найдена хотя бы одна цифра
        }
        if (str[i] == '+') {
            plusCount++;
        }
        if (str[i] == '-') {
            minusCount++;
        }
        if (str[i] == '.' || str[i] == ',') {
            if (hasDotOrComma) return false;  // Более одной точки или запятой
            hasDotOrComma = true;
        }
        if (!isdigit(str[i]) && str[i] != '+' && str[i] != '-' && str[i] != '.' && str[i] != ',') {
            return false;  // Неверный символ
        }
    }

    // Числом считается строка, если:
    // - Содержит хотя бы одну цифру, и
    // - Соблюдены ограничения на количество символов +, -, точки или запятой
    return hasDigit && (plusCount <= 1 && minusCount <= 1 && (!hasDotOrComma || hasDotOrComma == true));
}

// Функция для проверки, является ли строка словом
bool isWord(const char* str) {
    bool hasAlpha = false;
    int plusCount = 0;
    int minusCount = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (isalpha(str[i])) {
            hasAlpha = true;  // Есть хотя бы одна буква
        }
        if (isdigit(str[i])) {
            return false;  // Если есть хотя бы одна цифра, это не слово
        }
        if (str[i] == '+') {
            plusCount++;
        }
        if (str[i] == '-') {
            minusCount++;
        }
    }

    // Слово, если есть буквы, или если есть более одного знака + или - и это не число
    return hasAlpha || plusCount > 1 || minusCount > 1;
}

int main() {
    const int maxSize = 16;
    char input[maxSize];

    std::cout << "Enter string: ";
    std::cin.getline(input, maxSize);

    // Проверяем, является ли строка словом или числом
    if (isWord(input)) {
        std::cout << "\"" << input << "\" is word." << std::endl;
        if (isNumber(input)) {
            std::cout << "\"" << input << "\" is digit." << std::endl;
        }
        else {
            std::cout << "\"" << input << "\" is not word or digit." << std::endl;
        }

        return 0;
    }
}





//Даётся последовательнотсь символов(через cin), строка может содержать любые символы с клавиатуры(на английской раскладке). Нужно обработать её так, 
// чтобы вывести количество слов(Последовательность символов 
// будет являться словом только тогда и толька тогда когда она не является числом или хотя бы один из её смиволов буква, содержит цифры но не является числом). 
// Числом является последовательность когда хотя бы один её элемент цифра или +, - или ".", ",", при этомне более одного + и одного - и не более одной "." или ",". 
// Разделителями является пробел и табуляция. Все остальные символы с клавиатуры - это мусор. При реализации использовать c++, 
// исключительно си-строки не более 16 символ(вместе с термининрующем нулём). Вывести слова через пробел. Для считывания использовать get. 
// Для проверки использовать isalpha(char a), isdigit( char a)