//#include <iostream>
//#include <cctype>
//#include <cstring>
//
//const int maxSize = 16;  // Максимальная длина строки
//
//// Функция для проверки, является ли строка числом
//bool isNumber(const char* str) {
//    bool hasDigit = false;
//    int plusCount = 0;
//    int minusCount = 0;
//    bool hasDotOrComma = false;
//
//    for (int i = 0; str[i] != '\0'; ++i) {
//        if (isdigit(str[i])) {
//            hasDigit = true;
//        }
//        else if (str[i] == '+') {
//            plusCount++;
//            if (plusCount > 1) return false;
//        }
//        else if (str[i] == '-') {
//            minusCount++;
//            if (minusCount > 1) return false;
//        }
//        else if (str[i] == '.' || str[i] == ',') {
//            if (hasDotOrComma) return false;
//            hasDotOrComma = true;
//        }
//        else {
//            return false;
//        }
//    }
//    return hasDigit && (plusCount <= 1 && minusCount <= 1 && (!hasDotOrComma || hasDotOrComma == true));
//}
//
//// Функция для проверки, является ли строка словом
//bool isWord(const char* str) {
//    bool hasAlpha = false;
//
//    for (int i = 0; str[i] != '\0'; ++i) {
//        if (isalpha(str[i])) {
//            hasAlpha = true;
//        }
//        else if (isdigit(str[i]) || str[i] == '+' || str[i] == '-' || str[i] == '.' || str[i] == ',') {
//            return false;
//        }
//    }
//    return hasAlpha;
//}
//
//int main() {
//    char input[maxSize];
//    char word[maxSize];
//    int index = 0;
//
//    std::cout << "Enter string: ";
//
//    while (true) {
//        char ch;
//        std::cin.get(ch);
//
//        // Условия выхода из цикла при конце строки или начале нового слова
//        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == EOF) {
//            word[index] = '\0';  // Завершаем текущий токен
//
//            if (index > 0) {  // Проверка непустого токена
//                if (isWord(word) && !isNumber(word)) {
//                    std::cout << word << " ";
//                }
//            }
//
//            index = 0;  // Обнуление индекса для нового слова
//            if (ch == '\n' || ch == EOF) break;  // Завершаем ввод при переходе на новую строку или EOF
//        }
//        else if (isalpha(ch) || isdigit(ch) || ch == '+' || ch == '-' || ch == '.' || ch == ',') {
//            if (index < maxSize - 1) {
//                word[index++] = ch;  // Добавляем символ к слову
//            }
//        }
//    }
//
//    std::cout << std::endl;
//    return 0;
//}
//
// 








//
//
//
//
//
//
////Даётся последовательнотсь символов(через cin), строка может содержать любые символы с клавиатуры(на английской раскладке). Нужно обработать её так, 
//// чтобы вывести только слова(Последовательность символов 
//// будет являться словом только тогда и толька тогда когда она не является числом(То есть там нет цифр, или больше одного минуса, одного плюса или одной точки/запятой) и хотя бы один из её смиволов буква). 
//// Числом является последовательность когда хотя бы один её элемент цифра или +, - или ".", ",", при этом не более одного + и одного - и не более одной "." или ",". 
//// Разделителями является пробел и табуляция. Все остальные символы с клавиатуры - это мусор. При реализации использовать c++, 
//// исключительно си-строки не более 16 символ(вместе с термининрующем нулём). Вывести слова через пробел. Для считывания использовать get. 
//// Для проверки использовать isalpha(char a), isdigit( char a)