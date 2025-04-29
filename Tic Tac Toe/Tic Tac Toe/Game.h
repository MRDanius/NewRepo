#pragma once


#include "Players.h"

class Game {
private:
    char board[3][3];        // Состояние доски
    Player* players[2];      // Игроки (человек и бот)
    int current_player_idx;  // Индекс текущего игрока

    // Проверка линии (строки, столбца или диагонали)
    bool check_line(char player, int start_row, int start_col, int delta_row, int delta_col) const;

public:
    Game(Player* p1, Player* p2);  // Конструктор
    ~Game();                       // Деструктор

    // Проверка занятости клетки
    bool isCellOccupied(const Cell& cell) const;
    // Получение текущего состояния доски
    void getBoardState(char out[3][3]) const;
    // Проверка победы игрока
    bool checkWin(char player) const;
    // Проверка ничьей
    bool checkDraw() const;
    // Вывод доски в консоль
    void printBoard() const;
    // Запуск игрового цикла
    char play();
};


