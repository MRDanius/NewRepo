#pragma once


struct GameState {
    char board[3][3];     // Текущее состояние доски
    int x_steps;          // Шаги до победы X
    int o_steps;          // Шаги до победы O
    int draw_steps;       // Шаги до ничьей
    GameState** children; // Дочерние состояния
    int children_count;   // Количество дочерних состояний
};

// Прототипы функций
GameState* create_state(const char board[3][3]);
void delete_state_tree(GameState* root);
bool is_win(const char board[3][3], char player);
bool is_draw(const char board[3][3]);
bool is_terminal(const char board[3][3]);
void generate_all_states();
void save_to_file(const char* filename);



