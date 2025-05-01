#include "text_generator.h"
#include <iostream>
#include <limits>

int main() {
    TextGenerator tg;
    tg.train("training.txt");

    char choice = 'y';
    do {
        // Запрос начального слова
        char start_word[100];
        std::cout << "Enter starting word: ";
        std::cin >> start_word;

        // Запрос количества слов
        int n_words;
        while (true) {
            std::cout << "How many words to generate? ";
            if (std::cin >> n_words && n_words > 0) break;

            std::cout << "Error! Please enter a positive number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Генерация текста
        std::cout << "Result: ";
        tg.generate(start_word, n_words);

        // Запрос повтора
        std::cout << "Continue? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(); // Очистка буфера

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
//C:\Users\виталий\source\repos\TextG\TextG
