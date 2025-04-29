#pragma once


#include "Players.h"
#include <iostream>


class Game {
private:
    char board[3][3];
    Player* players[2];
    int currentPlayerIndex;

    bool makeMove(const Cell& cell, char player);
    bool checkLine(char player, int startRow, int startCol, int dRow, int dCol) const;

public:
    Game(Player* p1, Player* p2);
    ~Game();

    bool isCellOccupied(const Cell& cell) const; // Исправленная сигнатура
    void getBoardState(char out[3][3]) const;
    bool checkWin(char player) const;
    bool checkDraw() const;
    void printBoard() const;
    char play();
};

#endif