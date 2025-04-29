#define _CRT_SECURE_NO_WARNINGS
#include "GameState.h"
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>

GameState** all_states = nullptr;
int state_count = 0;
const int MAX_STATES = 5478;

GameState* create_state(const char board[3][3], int id) {
    GameState* state = new GameState();
    memcpy(state->board, board, 9);
    state->x_steps = INT_MAX;
    state->o_steps = INT_MAX;
    state->draw_steps = INT_MAX;
    state->child_ids = nullptr;
    state->children_count = 0;
    state->id = id;
    return state;
}

bool is_win(const char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player);
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
    all_states = new GameState * [MAX_STATES];
    char empty_board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    GameState* root = create_state(empty_board, 0);
    all_states[state_count++] = root;

    std::queue<GameState*> q;
    q.push(root);

    while (!q.empty() && state_count < MAX_STATES) {
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

        current->child_ids = new int[9];
        current->children_count = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current->board[i][j] == ' ') {
                    char new_board[3][3];
                    memcpy(new_board, current->board, 9);
                    new_board[i][j] = player;

                    bool exists = false;
                    for (int k = 0; k < state_count; k++) {
                        if (memcmp(all_states[k]->board, new_board, 9) == 0) {
                            current->child_ids[current->children_count++] = k;
                            exists = true;
                            break;
                        }
                    }

                    if (!exists) {
                        GameState* child = create_state(new_board, state_count);
                        all_states[state_count++] = child;
                        current->child_ids[current->children_count++] = child->id;
                        q.push(child);
                    }
                }
            }
        }
    }
}

void evaluate_states(GameState* state) {
    if (!state || is_terminal(state->board)) return;

    for (int i = 0; i < state->children_count; i++) {
        GameState* child = all_states[state->child_ids[i]];
        evaluate_states(child);

        if (child->x_steps != INT_MAX)
            state->x_steps = std::min(state->x_steps, child->x_steps + 1);
        if (child->o_steps != INT_MAX)
            state->o_steps = std::min(state->o_steps, child->o_steps + 1);
        if (child->draw_steps != INT_MAX)
            state->draw_steps = std::min(state->draw_steps, child->draw_steps + 1);
    }
}

void save_to_file(const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) return;

    fwrite(&state_count, sizeof(int), 1, f);
    for (int i = 0; i < state_count; i++) {
        GameState* s = all_states[i];
        fwrite(s, sizeof(GameState), 1, f);
        fwrite(s->child_ids, sizeof(int), s->children_count, f);
    }
    fclose(f);
}

void load_from_file(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) return;

    fread(&state_count, sizeof(int), 1, f);
    all_states = new GameState * [state_count];

    for (int i = 0; i < state_count; i++) {
        all_states[i] = new GameState();
        fread(all_states[i], sizeof(GameState), 1, f);
        all_states[i]->child_ids = new int[all_states[i]->children_count];
        fread(all_states[i]->child_ids, sizeof(int), all_states[i]->children_count, f);
    }
    fclose(f);
}

void initialize_states() {
    load_from_file("states.bin");
    if (state_count == 0) {
        generate_all_states();
        evaluate_states(all_states[0]);
        save_to_file("states.bin");
    }
}

void free_memory() {
    for (int i = 0; i < state_count; i++) {
        delete[] all_states[i]->child_ids;
        delete all_states[i];
    }
    delete[] all_states;
    state_count = 0;
}