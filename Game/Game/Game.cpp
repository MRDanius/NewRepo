#include "Game.h"
#include <cstring>
#include <limits>

Game::Game(Player* p1, Player* p2)
    : current_player_index(0) {
    players[0] = p1;
    players[1] = p2;

    // Инициализация пустой доски
    memset(board, ' ', sizeof(board));
}

Game::~Game() {
    // Игроки удаляются в GameLauncher
}

bool Game::isCellOccupied(const Cell& cell) const { // Исправленная реализация
    if (cell.row < 0 || cell.row >= 3 || cell.col < 0 || cell.col >= 3)
        return true;
    return board[cell.row][cell.col] != ' ';
}

void Game::getBoardState(char out[3][3]) const {
    memcpy(out, board, sizeof(board));
}

bool Game::check_line(char player, int start_row, int start_col, int drow, int dcol) const {
    for (int i = 0; i < 3; i++) {
        int row = start_row + i * drow;
        int col = start_col + i * dcol;
        if (board[row][col] != player) return false;
    }
    return true;
}

bool Game::checkWin(char player) const {
    // Проверка строк и столбцов
    for (int i = 0; i < 3; i++) {
        if (check_line(player, i, 0, 0, 1)) return true;  // Горизонтали
        if (check_line(player, 0, i, 1, 0)) return true;  // Вертикали
    }

    // Проверка диагоналей
    return check_line(player, 0, 0, 1, 1) ||  // Главная диагональ
        check_line(player, 0, 2, 1, -1);    // Побочная диагональ
}

bool Game::checkDraw() const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

void Game::printBoard() const {
    std::cout << "   A B C\n";
    for (int i = 0; i < 3; i++) {
        std::cout << i + 1 << "  ";
        for (int j = 0; j < 3; j++) {
            std::cout << (board[i][j] == ' ' ? ' ' : board[i][j]);
            if (j < 2) std::cout << "|";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "   -+-+-\n";
    }
    std::cout << std::endl;
}

char Game::play() {
    while (true) {
        printBoard();

        // Получаем текущего игрока
        Player* current_player = players[current_player_index];
        Cell move;

        // Получаем и проверяем ход
        do {
            move = current_player->getMove(*this);
        } while (!isCellOccupied(move));

        // Обновляем доску
        board[move.row][move.col] = current_player->symbol;

        // Проверка победы
        if (checkWin(current_player->symbol)) {
            printBoard();
            return current_player->symbol;
        }

        // Проверка ничьей
        if (checkDraw()) {
            printBoard();
            return ' ';
        }

        // Переход хода
        current_player_index = (current_player_index + 1) % 2;
    }
}