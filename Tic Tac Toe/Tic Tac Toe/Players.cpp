//#include "Players.h"
//#include "Game.h"
//#include "GameState.h"
//#include "Cell.h"
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <climits>
//#include <limits>
//
//// HumanPlayer implementation
//Cell HumanPlayer::getMove(const Game& game) {
//    std::string input;
//    while (true) {
//        std::cout << "\nYour move (" << getSymbol() << "): ";
//        if (!(std::cin >> input)) {
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            std::cout << "Input error! Try again.\n";
//            continue;
//        }
//
//        // Validate input format
//        if (input.size() != 2) {
//            std::cout << "Invalid format! Use A1-C3\n";
//            continue;
//        }
//
//        // Convert to coordinates
//        int col = toupper(input[0]) - 'A';
//        int row = input[1] - '1';
//
//        // Validate coordinates
//        if (col < 0 || col > 2 || row < 0 || row > 2) {
//            std::cout << "Invalid coordinates!\n";
//            continue;
//        }
//
//        Cell cell{ row, col };
//        if (!game.isCellOccupied(cell)) return cell;
//
//        std::cout << "Cell is occupied!\n";
//    }
//}
//
//// BotPlayer implementation
//BotPlayer::BotPlayer(Difficulty diff) : difficulty(diff) {
//    srand(static_cast<unsigned>(time(nullptr)));
//}
//
//Cell BotPlayer::getMove(const Game& game) {
//    auto getRandomMove = [&]() {
//        char board[3][3];
//        game.getBoardState(board);
//        Cell moves[9];
//        int count = 0;
//        for (int i = 0; i < 3; i++) {
//            for (int j = 0; j < 3; j++) {
//                if (board[i][j] == ' ') {
//                    moves[count++] = { i, j };
//                }
//            }
//        }
//        return moves[rand() % count];
//        };
//
//    // Random mode
//    if (difficulty == RANDOM) return getRandomMove();
//
//    // State-based logic
//    GameState* current_state = findCurrentState(game);
//    if (!current_state || current_state->children_count == 0) {
//        return getRandomMove();
//    }
//
//    // Score calculation
//    int best_score = (difficulty == EASY) ? INT_MAX : INT_MIN;
//    int best_child_id = -1;
//
//    for (int i = 0; i < current_state->children_count; i++) {
//        GameState* child = all_states[current_state->child_ids[i]];
//        int score = calculateScore(child);
//
//        if ((difficulty == EASY && score < best_score) ||
//            (difficulty != EASY && score > best_score)) {
//            best_score = score;
//            best_child_id = current_state->child_ids[i];
//        }
//    }
//
//    // Find changed cell
//    if (best_child_id != -1) {
//        GameState* best_child = all_states[best_child_id];
//        for (int i = 0; i < 3; i++) {
//            for (int j = 0; j < 3; j++) {
//                if (current_state->board[i][j] != best_child->board[i][j]) {
//                    return { i, j };
//                }
//            }
//        }
//    }
//    return getRandomMove();
//}
//
//GameState* BotPlayer::findCurrentState(const Game& game) const {
//    char current_board[3][3];
//    game.getBoardState(current_board);
//
//    for (int i = 0; i < state_count; i++) {
//        if (memcmp(all_states[i]->board, current_board, 9) == 0) {
//            return all_states[i];
//        }
//    }
//    return nullptr;
//}
//
//int BotPlayer::calculateScore(const GameState* state) const {
//    const bool is_x = (getSymbol() == 'X');
//
//    switch (difficulty) {
//    case EASY:   // Minimize own wins
//        return is_x ?
//            state->o_steps * 1000 - state->x_steps :
//            state->x_steps * 1000 - state->o_steps;
//
//    case HARD:   // Maximize own wins
//        return is_x ?
//            1000 - state->x_steps * 10 :
//            1000 - state->o_steps * 10;
//
//    case PROLONG: // Maximize draw
//        return state->draw_steps * 100;
//
//    default: return 0;
//    }
//}



#include "Players.h"
#include "Game.h"
#include "GameState.h"
#include "Cell.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <limits>

// HumanPlayer
Cell HumanPlayer::getMove(const Game& game) {
    std::string input;
    while (true) {
        std::cout << "\nYour move (" << getSymbol() << "): ";
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input error! Try again.\n";
            continue;
        }

        int col = toupper(input[0]) - 'A';
        int row = input[1] - '1';

        if (col < 0 || col > 2 || row < 0 || row > 2) {
            std::cout << "Invalid coordinates!\n";
            continue;
        }

        Cell cell{ row, col };
        if (!game.isCellOccupied(cell)) return cell;
        std::cout << "Cell is occupied!\n";
    }
}

// BotPlayer
BotPlayer::BotPlayer(Difficulty diff) : difficulty(diff) {
    srand(static_cast<unsigned>(time(nullptr)));
}

Cell BotPlayer::getMove(const Game& game) {
    auto getRandomMove = [&]() {
        char board[3][3];
        game.getBoardState(board);
        Cell moves[9];
        int count = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    moves[count++] = { i, j };
                }
            }
        }
        return moves[rand() % count];
        };

    if (difficulty == RANDOM) return getRandomMove();

    GameState* current_state = findCurrentState(game);
    if (!current_state || current_state->children_count == 0) {
        return getRandomMove();
    }

    int best_score = (difficulty == EASY) ? INT_MAX : INT_MIN;
    int best_child_id = -1;

    for (int i = 0; i < current_state->children_count; i++) {
        int child_id = current_state->child_ids[i];
        if (child_id < 0 || child_id >= state_count) continue;

        GameState* child = all_states[child_id];
        int score = calculateScore(child);

        if ((difficulty == EASY && score < best_score) ||
            (difficulty != EASY && score > best_score)) {
            best_score = score;
            best_child_id = child_id;
        }
    }

    if (best_child_id != -1) {
        GameState* best_child = all_states[best_child_id];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current_state->board[i][j] != best_child->board[i][j]) {
                    return { i, j };
                }
            }
        }
    }
    return getRandomMove();
}

GameState* BotPlayer::findCurrentState(const Game& game) const {
    char current_board[3][3];
    game.getBoardState(current_board);

    for (int i = 0; i < state_count; i++) {
        if (memcmp(all_states[i]->board, current_board, 9) == 0) {
            return all_states[i];
        }
    }
    return nullptr;
}

int BotPlayer::calculateScore(const GameState* state) const {
    const bool is_x = (this->getSymbol() == 'X');
    const bool can_self_win = (is_x && state->x_steps != INT_MAX) ||
        (!is_x && state->o_steps != INT_MAX);
    const bool can_opponent_win = (!is_x && state->x_steps != INT_MAX) ||
        (is_x && state->o_steps != INT_MAX);

    // Приоритет 1: Немедленная победа
    if (is_x && state->x_steps == 0) return 10000;
    if (!is_x && state->o_steps == 0) return 10000;

    // Приоритет 2: Блокировка победы противника на следующем ходу
    if (can_opponent_win) {
        const int opponent_steps = is_x ? state->o_steps : state->x_steps;
        if (opponent_steps == 1) return 9000;
    }

    // Приоритет 3: Собственная победа
    if (can_self_win) {
        const int self_steps = is_x ? state->x_steps : state->o_steps;
        return 800 - self_steps * 10;
    }

    // Приоритет 4: Максимизация шагов до ничьей
    return state->draw_steps * 10;
}