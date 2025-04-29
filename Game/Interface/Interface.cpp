#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    while (true) {
        cout << "Play? (y/n): ";
        char choice;
        cin >> choice;
        if (tolower(choice) != 'y') break;

        bool p1Bot = false, p2Bot = false;

        cout << "Player 1 (X) is bot? (y/n): ";
        cin >> choice;
        p1Bot = (tolower(choice) == 'y');

        cout << "Player 2 (O) is bot? (y/n): ";
        cin >> choice;
        p2Bot = (tolower(choice) == 'y');

        Game game(p1Bot, p2Bot);
        char winner = game.play();

        if (winner != ' ')
            cout << "Winner: " << winner << "!\n";
        else
            cout << "Draw!\n";
    }

    return 0;
}