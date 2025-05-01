//#pragma once
//#include <climits>
//
//struct GameState {
//    char board[3][3];     // Состояние доски
//    int x_steps;          // Шаги до победы X
//    int o_steps;          // Шаги до победы O
//    int draw_steps;       // Шаги до ничьей
//    int* child_ids;       // ID дочерних состояний
//    int children_count;   // Количество потомков
//    int id;               // Уникальный ID
//};
//
//extern GameState** all_states; // Все состояния
//extern int state_count;        // Количество состояний
//
//void initialize_states();      // Инициализация системы состояний
//void save_to_file(const char* filename); // Сохранение в файл
//void load_from_file(const char* filename); // Загрузка из файла
//void free_memory();            // Освобождение памяти
#pragma once
#include <climits>

struct GameState {
    char board[3][3];
    int x_steps;    // Шаги до победы X
    int o_steps;    // Шаги до победы O
    int draw_steps; // Шаги до ничьей
    int* child_ids; // ID дочерних состояний
    int children_count;
    int id;
};

extern GameState** all_states;
extern int state_count;

bool is_win(const char board[3][3], char player);
bool is_draw(const char board[3][3]);
void generate_all_states();
void evaluate_states(GameState* state);
void initialize_states();
void save_to_file(const char* filename);
void load_from_file(const char* filename);
void free_memory();