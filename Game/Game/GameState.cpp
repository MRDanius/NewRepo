#include "GameState.h"
#include "Game.h"
#include <queue>
#include <cstdio>
#include <climits>
#include <cstring>

// Глобальный массив всех состояний
GameState* all_states[5478] = { nullptr };
int state_count = 0;

GameState* create_state(const char board[3][3]) {
    GameState* state = new GameState;
    memcpy(state->board, board, 9); // Копируем доску
    state->children = new GameState * [9]; // Максимум 9 детей
    state->children_count = 0;
    state->x_steps = INT_MAX;
    state->o_steps = INT_MAX;
    state->draw_steps = INT_MAX;
    return state;
}

void delete_state_tree(GameState* root) {
    if (!root) return;
    for (int i = 0; i < root->children_count; i++) {
        delete_state_tree(root->children[i]);
    }
    delete[] root->children;
    delete root;
}

bool is_win(const char board[3][3], char player) {
    // Проверка строк и столбцов
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    // Проверка диагоналей
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool is_draw(const char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return false;
    return true;
}

bool is_terminal(const char board[3][3]) {
    return is_win(board, 'X') || is_win(board, 'O') || is_draw(board);
}

void generate_all_states() {
    // Начальное состояние - пустая доска
    char empty_board[3][3] = { {' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '} };
    GameState* root = create_state(empty_board);

    std::queue<GameState*> q;
    q.push(root);

    while (!q.empty() && state_count < 5478) {
        GameState* current = q.front();
        q.pop();
        all_states[state_count++] = current;

        if (is_terminal(current->board)) continue;

        // Определяем текущего игрока
        int x_count = 0, o_count = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current->board[i][j] == 'X') x_count++;
                if (current->board[i][j] == 'O') o_count++;
            }
        }
        char player = (x_count == o_count) ? 'X' : 'O';

        // Генерируем дочерние состояния
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

void evaluate_states_dfs(GameState* state, char player) {
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
        evaluate_states_dfs(state->children[i], player == 'X' ? 'O' : 'X');

        if (player == 'X') {
            state->x_steps = std::min(state->x_steps, state->children[i]->x_steps + 1);
            state->draw_steps = std::min(state->draw_steps, state->children[i]->draw_steps + 1);
        }
        else {
            state->o_steps = std::min(state->o_steps, state->children[i]->o_steps + 1);
            state->draw_steps = std::min(state->draw_steps, state->children[i]->draw_steps + 1);
        }
    }
}

void save_to_file(const char* filename) {
    FILE* f = fopen(filename, "wb");
    for (int i = 0; i < state_count; i++) {
        fwrite(all_states[i], sizeof(GameState), 1, f);
    }
    fclose(f);
}}