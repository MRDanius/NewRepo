#include "Players.h"
#include "GameState.h"
#include <cstdlib>
#include <ctime>
#include <queue>
#include <climits>
#include "Game.h"

// HumanPlayer реализация
Cell HumanPlayer::getMove(const Game& game) {
    char input[3];
    while (true) {
        std::cout << "Ход игрока " << symbol << " (формат A1): ";
        std::cin >> input;

        if (strlen(input) != 2) {
            std::cout << "Неверный формат!\n";
            continue;
        }

        int col = toupper(input[0]) - 'A';
        int row = input[1] - '1';

        if (col < 0 || col > 2 || row < 0 || row > 2) {
            std::cout << "Неверные координаты!\n";
            continue;
        }

        Cell move = { row, col };
        if (game.isCellOccupied(move)) {
            std::cout << "Клетка занята!\n";
            continue;
        }

        return move;
    }
}

// BotPlayer реализация
BotPlayer::BotPlayer(Mode mode, Difficulty difficulty)
    : bot_mode(mode), bot_difficulty(difficulty), state_tree(nullptr) {
    srand(time(nullptr));
    load_game_tree();
}

BotPlayer::~BotPlayer() {
    delete_state_tree(state_tree);
}

void BotPlayer::load_game_tree() {
    // Инициализация дерева состояний
    char empty_board[3][3] = { {' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '} };
    state_tree = create_state(empty_board);
    build_game_tree(state_tree);
    evaluate_game_tree(state_tree, 'X');
}

void BotPlayer::build_game_tree(GameState* root) {
    std::queue<GameState*> q;
    q.push(root);

    while (!q.empty()) {
        GameState* current = q.front();
        q.pop();

        if (is_terminal(current->board)) continue;

        int x_count = 0, o_count = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current->board[i][j] == 'X') x_count++;
                if (current->board[i][j] == 'O') o_count++;
            }
        }
        char player = (x_count == o_count) ? 'X' : 'O';

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current->board[i][j] == ' ') {
                    GameState* child = create_state(current->board);
                    child->board[i][j] = player;
                    current->children[current->children_count++] = child;
                    q.push(child);
                }
            }
        }
    }
}

void BotPlayer::evaluate_game_tree(GameState* state, char current_player) {
    if (!state) return;

    if (is_win(state->board, 'X')) {
        state->x_steps = 0;
        state->o_steps = INT_MAX;
        state->draw_steps = INT_MAX;
        return;
    }

    if (is_win(state->board, 'O')) {
        state->o_steps = 0;
        state->x_steps = INT_MAX;
        state->draw_steps = INT_MAX;
        return;
    }

    if (is_draw(state->board)) {
        state->draw_steps = 0;
        state->x_steps = INT_MAX;
        state->o_steps = INT_MAX;
        return;
    }

    for (int i = 0; i < state->children_count; i++) {
        evaluate_game_tree(state->children[i], current_player == 'X' ? 'O' : 'X');

        if (current_player == 'X') {
            state->x_steps = std::min(state->x_steps, state->children[i]->x_steps + 1);
        }
        else {
            state->o_steps = std::min(state->o_steps, state->children[i]->o_steps + 1);
        }
        state->draw_steps = std::min(state->draw_steps, state->children[i]->draw_steps + 1);
    }
}

int BotPlayer::calculate_move_score(GameState* state) const {
    if (bot_mode == NORMAL) {
        if (symbol == 'X') {
            return (1000 - state->x_steps * 10) + (bot_difficulty == HARD ? state->draw_steps : 0);
        }
        return (1000 - state->o_steps * 10) + (bot_difficulty == HARD ? state->draw_steps : 0);
    }
    return state->draw_steps * 100;
}

Cell BotPlayer::getMove(const Game& game) {
    char current_board[3][3];
    game.getBoardState(current_board);

    GameState* current_state = nullptr;
    for (int i = 0; i < state_tree->children_count; i++) {
        if (memcmp(state_tree->children[i]->board, current_board, 9) == 0) {
            current_state = state_tree->children[i];
            break;
        }
    }

    if (!current_state || current_state->children_count == 0) {
        // Резервный вариант: случайный ход
        Cell moves[9];
        int count = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current_board[i][j] == ' ') {
                    moves[count++] = { i, j };
                }
            }
        }
        return moves[rand() % count];
    }

    int best_score = (bot_mode == NORMAL) ? INT_MIN : INT_MAX;
    int best_index = 0;

    for (int i = 0; i < current_state->children_count; i++) {
        int score = calculate_move_score(current_state->children[i]);

        if ((bot_mode == NORMAL && score > best_score) ||
            (bot_mode == PROLONG && score < best_score)) {
            best_score = score;
            best_index = i;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (current_state->children[best_index]->board[i][j] != current_board[i][j]) {
                return { i, j };
            }
        }
    }
    return { 0, 0 }; // Запасной вариант
}