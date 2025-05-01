//#pragma once
//#include <climits>
//
//struct GameState {
//    char board[3][3];     // ��������� �����
//    int x_steps;          // ���� �� ������ X
//    int o_steps;          // ���� �� ������ O
//    int draw_steps;       // ���� �� ������
//    int* child_ids;       // ID �������� ���������
//    int children_count;   // ���������� ��������
//    int id;               // ���������� ID
//};
//
//extern GameState** all_states; // ��� ���������
//extern int state_count;        // ���������� ���������
//
//void initialize_states();      // ������������� ������� ���������
//void save_to_file(const char* filename); // ���������� � ����
//void load_from_file(const char* filename); // �������� �� �����
//void free_memory();            // ������������ ������
#pragma once
#include <climits>

struct GameState {
    char board[3][3];
    int x_steps;    // ���� �� ������ X
    int o_steps;    // ���� �� ������ O
    int draw_steps; // ���� �� ������
    int* child_ids; // ID �������� ���������
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