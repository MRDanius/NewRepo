#pragma once


#include <climits>

struct GameState {
    char board[3][3];     // Текущее состояние доски
    int x_steps;          // Шаги до победы X
    int o_steps;          // Шаги до победы O
    int draw_steps;       // Шаги до ничьей
    int* child_ids;       // Массив ID дочерних состояний
    int children_count;   // Количество потомков
    int id;               // Уникальный идентификатор
};

extern GameState** all_states;  // Глобальный массив всех состояний
extern int state_count;         // Общее количество состояний

// Прототипы функций
void initialize_states();
void save_to_file(const char* filename);
void load_from_file(const char* filename);
bool is_win(const char board[3][3], char player);
bool is_draw(const char board[3][3]);
bool is_terminal(const char board[3][3]);
void evaluate_states(GameState* state);
void free_memory();

