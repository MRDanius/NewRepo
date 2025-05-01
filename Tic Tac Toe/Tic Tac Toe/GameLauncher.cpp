#include "GameLauncher.h"
#include "Game.h"
#include "Players.h"
#include <iostream>
#include <cctype>
#include <limits>
void GameLauncher::start() {
    char choice;
    do {
        // Главное меню
        std::cout << "\n=== Tic Tac Toe ===\n"
            << "1. New Game\n"
            << "2. Exit\n"
            << "Select action: ";
        std::cin >> choice;

        if (choice == '2') break;
        if (choice != '1') {
            std::cout << "Invalid input!\n";
            continue;
        }

        // Выбор режима игры
        int game_mode;
        std::cout << "\nGame modes:\n"
            << "1. Player vs Player\n"
            << "2. Player vs Bot\n"
            << "3. Bot vs Bot\n"
            << "Select mode: ";
        std::cin >> game_mode;

        // Выбор символа
        char player_symbol = 'X';
        if (game_mode != 3) {
            std::cout << "Play as (X/O): ";
            std::cin >> player_symbol;
            player_symbol = toupper(player_symbol);
            if (player_symbol != 'X' && player_symbol != 'O')
                player_symbol = 'X';
        }

        // Настройка ботов
        int bot1_diff = 0, bot2_diff = 0;
        if (game_mode >= 2) {
            std::cout << "\nBot difficulties:\n"
                << "1. Random\n"
                << "2. Easy (throws)\n"
                << "3. Hard (optimal)\n"
                << "4. Prolong (draw)\n";

            if (game_mode == 2) {
                std::cout << "Select bot difficulty: ";
                std::cin >> bot1_diff;
            }
            else {
                std::cout << "Select difficulty for Bot 1: ";
                std::cin >> bot1_diff;
                std::cout << "Select difficulty for Bot 2: ";
                std::cin >> bot2_diff;
            }
        }

        // Создание игроков
        Player* p1 = nullptr;
        Player* p2 = nullptr;

        switch (game_mode) {
        case 1: // PvP
            p1 = new HumanPlayer();
            p2 = new HumanPlayer();
            p1->setSymbol('X');
            p2->setSymbol('O');
            break;

        case 2: { // PvB
            HumanPlayer* human = new HumanPlayer();
            BotPlayer* bot = new BotPlayer(
                static_cast<BotPlayer::Difficulty>(bot1_diff - 1)
            );

            human->setSymbol(player_symbol);
            bot->setSymbol(player_symbol == 'X' ? 'O' : 'X');

            p1 = (player_symbol == 'X') ?
                static_cast<Player*>(human) : bot;
            p2 = (player_symbol == 'X') ?
                static_cast<Player*>(bot) : human;
            break;
        }

        case 3: // BvB
            p1 = new BotPlayer(
                static_cast<BotPlayer::Difficulty>(bot1_diff - 1)
            );
            p2 = new BotPlayer(
                static_cast<BotPlayer::Difficulty>(bot2_diff - 1)
            );
            p1->setSymbol('X');
            p2->setSymbol('O');
            break;
        }

        // Запуск игры
        Game game(p1, p2);
        char winner = game.play();

        // Результаты
        std::cout << "\nGame over! ";
        if (winner == ' ') {
            std::cout << "Draw!\n";
        }
        else {
            std::cout << "Winner: " << winner << "!\n";
        }

        // Очистка памяти
        delete p1;
        delete p2;

    } while (true);

    std::cout << "Goodbye!\n";
}