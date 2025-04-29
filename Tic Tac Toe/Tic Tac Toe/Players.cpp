#define _CRT_SECURE_NO_WARNINGS
#include "Players.h"
#include "Game.h"
#include "GameState.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// HumanPlayer implementation
Cell HumanPlayer::getMove(const Game& game) {
    std::string input;
    while (true) {
        std::cout << "Player " << symbol << " move (e.g., A1): ";
        std::cin >> input;

        // Проверка формата ввода
        if (input.size() != 2) {
            std::cout << "Invalid format. Use A1 notation.\n";
            continue;
        }

        // Конвертация буквы в столбец (A=0, B=1, C=2)
        char col = toupper(input[0]) - 'A';
        // Конвертация цифры в строку (1=0, 2=1, 3=2)
        char row = input[1] - '1';

        // Проверка диапазона
        if (col < 0 || col > 2 || row < 0 || row > 2) {
            std::cout << "Invalid coordinates. Use A1-C3.\n";
            continue;
        }

        Cell cell = { static_cast<int>(row), static_cast<int>(col) };
        if (game.isCellOccupied(cell)) {
            std::cout << "Cell is occupied. Choose another.\n";
            continue;
        }

        return cell;
    }
}

// BotPlayer implementation
BotPlayer::BotPlayer(Mode mode, Difficulty diff)
    : mode(mode), difficulty(diff) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

BotPlayer::~BotPlayer() {}

// Поиск текущего состояния в графе
GameState* BotPlayer::find_current_state(const Game& game) const {
    char current_board[3][3];
    game.getBoardState(current_board);

    for (int i = 0; i < state_count; i++) {
        if (memcmp(all_states[i]->board, current_board, 9) == 0) {
            return all_states[i];
        }
    }
    return nullptr;
}

// Расчет приоритета хода
int BotPlayer::calculate_score(const GameState* state) const {
    if (mode == NORMAL) {
        if (symbol == 'X') {
            return (1000 - state->x_steps * 10) + (difficulty == HARD ? state->draw_steps : 0);
        }
        return (1000 - state->o_steps * 10) + (difficulty == HARD ? state->draw_steps : 0);
    }
    return state->draw_steps * 100; // PROLONG mode
}

// Выбор оптимального хода
Cell BotPlayer::getMove(const Game& game) {
    GameState* current_state = find_current_state(game);

    // Fallback: случайный ход если состояние не найдено
    if (!current_state || current_state->children_count == 0) {
        Cell moves[9];
        int count = 0;
        char board[3][3];
        game.getBoardState(board);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    moves[count++] = { i, j };
                }
            }
        }
        return moves[rand() % count];
    }

    // Поиск лучшего хода
    int best_score = (mode == NORMAL) ? INT_MIN : INT_MAX;
    int best_child_id = -1;

    for (int i = 0; i < current_state->children_count; i++) {
        GameState* child = all_states[current_state->child_ids[i]];
        int score = calculate_score(child);

        if ((mode == NORMAL && score > best_score) ||
            (mode == PROLONG && score < best_score)) {
            best_score = score;
            best_child_id = current_state->child_ids[i];
        }
    }

    // Определение измененной клетки
    GameState* best_child = all_states[best_child_id];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (current_state->board[i][j] != best_child->board[i][j]) {
                return { i, j };
            }
        }
    }
    return { 0, 0 }; // fallback
}