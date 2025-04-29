#include "GameLauncher.h"
#include "Game.h"
#include "Players.h"
#include <iostream>
#include <cctype>

using namespace std;

void GameLauncher::start() {
    while (true) {
        cout << "\n=== Tic Tac Toe ===\n";
        cout << "1. New Game\n2. Exit\nChoose: ";

        char choice;
        cin >> choice;

        if (choice == '2') break;
        if (choice != '1') {
            cout << "Wrong choice!\n";
            continue;
        }

        // Выбор режима бота
        int mode, diff;
        cout << "Bot mode (1-normal, 2-extend the game): ";
        cin >> mode;
        cout << "Difficulty (1-easy, 2-medium, 3-hard): ";
        cin >> diff;

        Player* p1 = new HumanPlayer();
        Player* p2 = new BotPlayer(
            static_cast<BotPlayer::Mode>(mode - 1),
            static_cast<BotPlayer::Difficulty>(diff - 1)
        );

        Game game(p1, p2);
        char winner = game.play();

        delete p1;
        delete p2;
    }
    cout << "Goodbye!\n";
}