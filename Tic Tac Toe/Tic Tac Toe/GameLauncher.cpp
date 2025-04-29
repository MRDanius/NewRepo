#include "GameLauncher.h"
#include "Game.h"
#include "Players.h"
#include <iostream>
#include <cctype>

void GameLauncher::start() {
    char choice;
    do {
        std::cout << "\n=== Tic Tac Toe ===\n"
            << "1. New game\n"
            << "2. Exit\n"
            << "Select an action: ";
        std::cin >> choice;

        if (choice == '2') break;
        if (choice != '1') {
            std::cout << "Wrong input!\n";
            continue;
        }

        int mode, diff;
        std::cout << "Bot Mode (1-Normal, 2-Extended): ";
        std::cin >> mode;
        std::cout << "Difficulty (1-Easy, 2-Medium, 3-Difficult): ";
        std::cin >> diff;

        // Создание игроков
        Player* human = new HumanPlayer();
        human->setSymbol('X');

        BotPlayer* bot = new BotPlayer(
            static_cast<BotPlayer::Mode>(mode - 1),
            static_cast<BotPlayer::Difficulty>(diff - 1)
        );
        bot->setSymbol('O');

        // Запуск игры
        Game game(human, bot);
        char winner = game.play();

        // Вывод результата
        if (winner == ' ') {
            std::cout << "\nDraw!\n";
        }
        else {
            std::cout << "\nWon " << winner << "!\n";
        }

        delete human;
        delete bot;

    } while (true);

    std::cout << "Goodbye!\n";
}