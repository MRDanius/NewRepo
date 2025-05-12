//#include "Game.h"
//#include <iostream>
//#include <cstring>
//
//Game::Game(Player* p1, Player* p2) : current_player_idx(0) {
//    players[0] = p1;
//    players[1] = p2;
//    memset(board, ' ', sizeof(board));
//}
//
//Game::~Game() {
//    delete players[0];
//    delete players[1];
//}
//
//bool Game::isCellOccupied(const Cell& cell) const {
//    if (cell.row < 0 || cell.row >= 3 ||
//        cell.col < 0 || cell.col >= 3) return true;
//    return board[cell.row][cell.col] != ' ';
//}
//
//void Game::getBoardState(char out[3][3]) const {
//    memcpy(out, board, sizeof(board));
//}
//
//bool Game::check_line(char player, int row, int col,
//    int dr, int dc) const {
//    for (int i = 0; i < 3; i++) {
//        int r = row + i * dr;
//        int c = col + i * dc;
//        if (r < 0 || r >= 3 || c < 0 || c >= 3 ||
//            board[r][c] != player) return false;
//    }
//    return true;
//}
//
//bool Game::checkWin(char player) const {
//    // Check rows and columns
//    for (int i = 0; i < 3; i++) {
//        if (check_line(player, i, 0, 0, 1)) return true;
//        if (check_line(player, 0, i, 1, 0)) return true;
//    }
//    // Check diagonals
//    return check_line(player, 0, 0, 1, 1) ||
//        check_line(player, 0, 2, 1, -1);
//}
//
//bool Game::checkDraw() const {
//    for (int i = 0; i < 3; i++)
//        for (int j = 0; j < 3; j++)
//            if (board[i][j] == ' ') return false;
//    return true;
//}
//
//void Game::printBoard() const {
//    std::cout << "   A B C\n";
//    for (int i = 0; i < 3; i++) {
//        std::cout << i + 1 << "  ";
//        for (int j = 0; j < 3; j++) {
//            std::cout << board[i][j];
//            if (j < 2) std::cout << "|";
//        }
//        std::cout << (i < 2 ? "\n   -+-+-\n" : "\n");
//    }
//}
//
//char Game::play() {
//    while (true) {
//        printBoard();
//        Player* current = players[current_player_idx];
//        Cell move;
//
//        // Get valid move
//        do {
//            move = current->getMove(*this);
//        } while (isCellOccupied(move));
//
//        // Update board
//        board[move.row][move.col] = current->getSymbol();
//
//        // Check win
//        if (checkWin(current->getSymbol())) {
//            printBoard();
//            return current->getSymbol();
//        }
//
//        // Check draw
//        if (checkDraw()) {
//            printBoard();
//            return ' ';
//        }
//
//        // Switch player
//        current_player_idx = (current_player_idx + 1) % 2;
//    }
//}


#include "Game.h"
#include <iostream>
#include <cstring>

Game::Game(Player* p1, Player* p2) : current_player_idx(0) {
    players[0] = p1;
    players[1] = p2;
    memset(board, ' ', sizeof(board));
}

Game::~Game() {
    delete players[0];
    delete players[1];
}

bool Game::isCellOccupied(const Cell& cell) const {
    if (cell.row < 0 || cell.row >= 3 ||
        cell.col < 0 || cell.col >= 3) return true;
    return board[cell.row][cell.col] != ' ';
}

void Game::getBoardState(char out[3][3]) const {
    memcpy(out, board, sizeof(board));
}

bool Game::check_line(char player, int row, int col,
    int dr, int dc) const {
    for (int i = 0; i < 3; i++) {
        int r = row + i * dr;
        int c = col + i * dc;
        if (r < 0 || r >= 3 || c < 0 || c >= 3 ||
            board[r][c] != player) return false;
    }
    return true;
}

bool Game::checkWin(char player) const {
    for (int i = 0; i < 3; i++) {
        if (check_line(player, i, 0, 0, 1)) return true;
        if (check_line(player, 0, i, 1, 0)) return true;
    }
    return check_line(player, 0, 0, 1, 1) ||
        check_line(player, 0, 2, 1, -1);
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
            std::cout << board[i][j];
            if (j < 2) std::cout << "|";
        }
        std::cout << (i < 2 ? "\n   -+-+-\n" : "\n");
    }
}

char Game::play() {
    while (true) {
        printBoard();
        Player* current = players[current_player_idx];
        Cell move;

        do {
            move = current->getMove(*this);
        } while (isCellOccupied(move));

        board[move.row][move.col] = current->getSymbol();

        if (checkWin(current->getSymbol())) {
            printBoard();
            return current->getSymbol();
        }

        if (checkDraw()) {
            printBoard();
            return ' ';
        }

        current_player_idx = (current_player_idx + 1) % 2;
    }
}