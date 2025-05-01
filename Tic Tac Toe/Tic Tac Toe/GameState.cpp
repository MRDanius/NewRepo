//#define _CRT_SECURE_NO_WARNINGS
//#include "GameState.h"
//#include <queue>
//#include <cstdio>
//#include <cstring>
//#include <algorithm>
//#include <iostream>
//GameState** all_states = nullptr;
//int state_count = 0;
//const int MAX_STATES = 5478;
//
//// Создание состояния
//GameState* create_state(const char board[3][3], int id) {
//    GameState* state = new GameState();
//    memcpy(state->board, board, 9);
//    state->x_steps = INT_MAX;
//    state->o_steps = INT_MAX;
//    state->draw_steps = INT_MAX;
//    state->child_ids = nullptr;
//    state->children_count = 0;
//    state->id = id;
//    return state;
//}
//
//// Проверка победы
//bool is_win(const char board[3][3], char player) {
//    for (int i = 0; i < 3; i++) {
//        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
//        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
//    }
//    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
//        (board[0][2] == player && board[1][1] == player && board[2][0] == player);
//}
//
//// Проверка ничьей
//bool is_draw(const char board[3][3]) {
//    for (int i = 0; i < 3; i++)
//        for (int j = 0; j < 3; j++)
//            if (board[i][j] == ' ') return false;
//    return true;
//}
//
//// Генерация всех состояний
//void generate_all_states() {
//    all_states = new GameState * [MAX_STATES];
//    char empty[3][3] = { {' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '} };
//    all_states[0] = create_state(empty, 0);
//    state_count = 1;
//
//    std::queue<GameState*> q;
//    q.push(all_states[0]);
//
//    while (!q.empty() && state_count < MAX_STATES) {
//        GameState* curr = q.front();
//        q.pop();
//
//        if (is_win(curr->board, 'X') || is_win(curr->board, 'O') || is_draw(curr->board))
//            continue;
//
//        // Определение текущего игрока
//        int x = 0, o = 0;
//        for (int i = 0; i < 3; i++) {
//            for (int j = 0; j < 3; j++) {
//                if (curr->board[i][j] == 'X') x++;
//                if (curr->board[i][j] == 'O') o++;
//            }
//        }
//        char player = (x == o) ? 'X' : 'O';
//
//        // Генерация потомков
//        curr->child_ids = new int[9];
//        curr->children_count = 0;
//
//        for (int i = 0; i < 3; i++) {
//            for (int j = 0; j < 3; j++) {
//                if (curr->board[i][j] == ' ') {
//                    char new_board[3][3];
//                    memcpy(new_board, curr->board, 9);
//                    new_board[i][j] = player;
//
//                    // Поиск существующего состояния
//                    bool found = false;
//                    for (int k = 0; k < state_count; k++) {
//                        if (memcmp(all_states[k]->board, new_board, 9) == 0) {
//                            curr->child_ids[curr->children_count++] = k;
//                            found = true;
//                            break;
//                        }
//                    }
//
//                    // Добавление нового состояния
//                    if (!found) {
//                        GameState* child = create_state(new_board, state_count);
//                        all_states[state_count] = child;
//                        curr->child_ids[curr->children_count++] = state_count;
//                        q.push(child);
//                        state_count++;
//                    }
//                }
//            }
//        }
//    }
//}
//
//// Оценка состояний
//void evaluate_states(GameState* state) {
//    if (is_win(state->board, 'X')) {
//        state->x_steps = 0;
//        state->o_steps = state->draw_steps = INT_MAX;
//        return;
//    }
//    if (is_win(state->board, 'O')) {
//        state->o_steps = 0;
//        state->x_steps = state->draw_steps = INT_MAX;
//        return;
//    }
//    if (is_draw(state->board)) {
//        state->draw_steps = 0;
//        state->x_steps = state->o_steps = INT_MAX;
//        return;
//    }
//
//    for (int i = 0; i < state->children_count; i++) {
//        GameState* child = all_states[state->child_ids[i]];
//        if (child->x_steps == INT_MAX) evaluate_states(child);
//        state->x_steps = std::min(state->x_steps, child->x_steps + 1);
//        state->o_steps = std::min(state->o_steps, child->o_steps + 1);
//        state->draw_steps = std::min(state->draw_steps, child->draw_steps + 1);
//    }
//}
//
//// Сохранение в текстовый файл
//void save_to_file(const char* filename) {
//    FILE* f = fopen(filename, "w");
//    fprintf(f, "%d\n", state_count);
//
//    for (int i = 0; i < state_count; i++) {
//        GameState* s = all_states[i];
//        for (int r = 0; r < 3; r++)
//            for (int c = 0; c < 3; c++)
//                fprintf(f, "%c", s->board[r][c]);
//        fprintf(f, "\n%d %d %d %d\n", s->x_steps, s->o_steps, s->draw_steps, s->children_count);
//
//        if (s->children_count > 0) {
//            for (int j = 0; j < s->children_count; j++)
//                fprintf(f, "%d ", s->child_ids[j]);
//            fprintf(f, "\n");
//        }
//    }
//    fclose(f);
//}
//
//// Загрузка из текстового файла
//void load_from_file(const char* filename) {
//    FILE* f = fopen(filename, "r");
//
//    fscanf(f, "%d\n", &state_count);
//    all_states = new GameState * [state_count];
//    if (!f) {
//        std::cerr << "Ошибка открытия файла: " << filename << "\n";
//        return;
//    }
//    for (int i = 0; i < state_count; i++) {
//        all_states[i] = new GameState();
//        char board_str[10];
//        fgets(board_str, 10, f);
//
//        for (int r = 0; r < 3; r++)
//            for (int c = 0; c < 3; c++)
//                all_states[i]->board[r][c] = board_str[r * 3 + c];
//
//        fscanf(f, "%d %d %d %d\n",
//            &all_states[i]->x_steps,
//            &all_states[i]->o_steps,
//            &all_states[i]->draw_steps,
//            &all_states[i]->children_count
//        );
//
//        if (all_states[i]->children_count > 0) {
//            all_states[i]->child_ids = new int[all_states[i]->children_count];
//            for (int j = 0; j < all_states[i]->children_count; j++)
//                fscanf(f, "%d ", &all_states[i]->child_ids[j]);
//            fscanf(f, "\n");
//        }
//    }
//    fclose(f);
//}
//
//// Инициализация состояний
//void initialize_states() {
//    load_from_file("states.txt");
//    if (state_count == 0) {
//        generate_all_states();
//        evaluate_states(all_states[0]);
//        save_to_file("states.txt");
//    }
//}
//
//// Очистка памяти
//void free_memory() {
//    for (int i = 0; i < state_count; i++) {
//        delete[] all_states[i]->child_ids;
//        delete all_states[i];
//    }
//    delete[] all_states;
//    state_count = 0;
//}

#define _CRT_SECURE_NO_WARNINGS
#include "GameState.h"
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

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
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

bool is_draw(const char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

void generate_all_states() {
    if (state_count >= MAX_STATES) return;

    all_states = new GameState * [MAX_STATES];
    char empty_board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    all_states[0] = create_state(empty_board, 0);
    state_count = 1;

    std::queue<GameState*> q;
    q.push(all_states[0]);

    while (!q.empty() && state_count < MAX_STATES) {
        GameState* current = q.front();
        q.pop();

        if (is_win(current->board, 'X') || is_win(current->board, 'O') || is_draw(current->board)) {
            continue;
        }

        int x_cnt = 0, o_cnt = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current->board[i][j] == 'X') x_cnt++;
                if (current->board[i][j] == 'O') o_cnt++;
            }
        }
        char player = (x_cnt == o_cnt) ? 'X' : 'O';

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
                        all_states[state_count] = child;
                        current->child_ids[current->children_count++] = state_count;
                        q.push(child);
                        state_count++;
                    }
                }
            }
        }
    }
}

void evaluate_states(GameState* state) {
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
        int child_id = state->child_ids[i];
        if (child_id < 0 || child_id >= state_count) continue;

        GameState* child = all_states[child_id];
        if (child->x_steps == INT_MAX) evaluate_states(child);

        state->x_steps = std::min(state->x_steps, child->x_steps + 1);
        state->o_steps = std::min(state->o_steps, child->o_steps + 1);
        state->draw_steps = std::min(state->draw_steps,
            (child->draw_steps != INT_MAX) ? child->draw_steps + 1 : INT_MAX);
    }
}

void save_to_file(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    fprintf(f, "%d\n", state_count);
    for (int i = 0; i < state_count; i++) {
        GameState* s = all_states[i];
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                fprintf(f, "%c", s->board[r][c]);
            }
        }
        fprintf(f, "\n%d %d %d %d\n", s->x_steps, s->o_steps, s->draw_steps, s->children_count);
        if (s->children_count > 0) {
            for (int j = 0; j < s->children_count; j++) {
                fprintf(f, "%d ", s->child_ids[j]);
            }
            fprintf(f, "\n");
        }
    }
    fclose(f);
}

void load_from_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        std::cerr << "File not found: " << filename << ". Generating new..." << std::endl;
        generate_all_states();
        evaluate_states(all_states[0]);
        save_to_file(filename);
        return;
    }

    fscanf(f, "%d\n", &state_count);
    all_states = new GameState * [state_count];

    for (int i = 0; i < state_count; i++) {
        all_states[i] = new GameState();
        char board_str[10];
        fgets(board_str, 10, f);

        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                all_states[i]->board[r][c] = board_str[r * 3 + c];
            }
        }

        fscanf(f, "%d %d %d %d\n",
            &all_states[i]->x_steps,
            &all_states[i]->o_steps,
            &all_states[i]->draw_steps,
            &all_states[i]->children_count);

        if (all_states[i]->children_count > 0) {
            all_states[i]->child_ids = new int[all_states[i]->children_count];
            for (int j = 0; j < all_states[i]->children_count; j++) {
                fscanf(f, "%d ", &all_states[i]->child_ids[j]);
            }
        }
    }
    fclose(f);
}

void initialize_states() {
    load_from_file("states.txt");
}

void free_memory() {
    for (int i = 0; i < state_count; i++) {
        delete[] all_states[i]->child_ids;
        delete all_states[i];
    }
    delete[] all_states;
    state_count = 0;
}