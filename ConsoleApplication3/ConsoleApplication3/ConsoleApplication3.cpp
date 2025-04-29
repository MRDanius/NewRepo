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
            hasDigit = true;  // Найдена хотя бы одна цифра
        }
        else if (str[i] == '+') {
            plusCount++;
            
        }
        else if (str[i] == '-') {
            minusCount++;
            
        }
        //else if (str[i] == '.' || str[i] == ',') {
        //    if (hasDotOrComma) return false;  // Более одной точки или запятой
        //    hasDotOrComma = true;
        //}
        else {
            return false;  // Недопустимый символ
        }
    }

    // Числом считается строка, если:
    // - Содержит хотя бы одну цифру, и
    // - Соблюдены ограничения на количество +, -, . или ,
    return hasDigit || plusCount == 1 || minusCount == 1;
}

// Функция для проверки, является ли строка словом
bool isWord(const char* str) {
    bool hasAlpha = false;
    int plusCount = 0;
    int minusCount = 0;
    int dotOrCommaCount = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
    //    if (isalpha(str[i])) {
    //        return hasAlpha = true;  // Есть хотя бы одна буква
    //        if (str[i] == '+') {
    //            plusCount++;
    //        }
    //        if (str[i] == '-') {
    //            minusCount++;
    //        }
    //        if (str[i] == '.' || str[i] == ',') {
    //            dotOrCommaCount++;

    //            if (isdigit(str[i]) || plusCount == 1 || minusCount == 1 || dotOrCommaCount == 1) {
    //                return false;  // Если есть цифра, это не слово
    //            }
    //        }
    //    }
    //}
        
        //if (isalpha(str[i])) {
        //    hasAlpha = true;  // Есть хотя бы одна буква
        //}
        //else if (str[i] == '+') {
        //    plusCount++;
        //}
        //else if (str[i] == '-') {
        //    minusCount++;
        //}
        //else if (str[i] == '.' || str[i] == ',') {
        //    dotOrCommaCount++;
        //}
        //else if (isdigit(str[i]) || plusCount == 1 || minusCount == 1 || dotOrCommaCount == 1) {
        //    return false;  // Если есть цифра, это не слово
        //}
        if (isalpha(str[i])) {
            hasAlpha = true;  // Есть хотя бы одна буква
        }
        if (str[i] == '+') {
            plusCount++;
        }
        if (str[i] == '-') {
            minusCount++;
        }
        if (str[i] == '.' || str[i] == ',') {
            dotOrCommaCount++;
        }
        if (isdigit(str[i]) || plusCount == 1 || minusCount == 1 || dotOrCommaCount == 1) {
            return false;  // Если есть цифра, это не слово
        }

    }

    // Строка является словом, если в ней есть хотя бы одна буква
    // или если в ней больше одного знака +, -, или точки/запятой
    return hasAlpha || plusCount > 1 || minusCount > 1 || dotOrCommaCount > 1;
}

int main() {
    char input[maxSize];
    char word[maxSize];
    int index = 0;

    std::cout << "Enter string: ";

    while (true) {
        char ch;
        std::cin.get(ch);

        // Условия выхода из цикла при конце строки или начале нового слова
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == EOF) {
            word[index] = '\0';  // Завершаем текущий токен

            if (index > 0) {  // Проверка непустого токена
                if (isWord(word) && !isNumber(word)) {
                    std::cout << word << " ";
                }
            }

            index = 0;  // Обнуление индекса для нового слова
            if (ch == '\n' || ch == EOF) break;  // Завершаем ввод при переходе на новую строку или EOF
        }
        else if (isalpha(ch) || isdigit(ch) || ch == '+' || ch == '-' || ch == '.' || ch == ',') {
            if (index < maxSize - 1) {
                word[index++] = ch;  // Добавляем символ к слову
            }
        }
    }

    std::cout << std::endl;
    return 0;

}