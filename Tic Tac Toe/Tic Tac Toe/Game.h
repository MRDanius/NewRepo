//#pragma once
//#include "Players.h"
//#include "Cell.h"
//
//class Game {
//private:
//    char board[3][3];
//    Player* players[2];
//    int current_player_idx;
//
//    bool check_line(char player, int start_row, int start_col,
//        int delta_row, int delta_col) const;
//
//public:
//    Game(Player* p1, Player* p2);
//    ~Game();
//
//    bool isCellOccupied(const Cell& cell) const;
//    void getBoardState(char out[3][3]) const;
//    bool checkWin(char player) const;
//    bool checkDraw() const;
//    void printBoard() const;
//    char play();
//};


#pragma once
#include "Players.h"
#include "Cell.h"

class Game {
private:
    char board[3][3];
    Player* players[2];
    int current_player_idx;

    bool check_line(char player, int start_row, int start_col,
        int delta_row, int delta_col) const;

public:
    Game(Player* p1, Player* p2);
    ~Game();

    bool isCellOccupied(const Cell& cell) const;
    void getBoardState(char out[3][3]) const;
    bool checkWin(char player) const;
    bool checkDraw() const;
    void printBoard() const;
    char play();
};