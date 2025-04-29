#pragma once


struct GameState {
    char board[3][3];     // ������� ��������� �����
    int x_steps;          // ���� �� ������ X
    int o_steps;          // ���� �� ������ O
    int draw_steps;       // ���� �� ������
    GameState** children; // �������� ���������
    int children_count;   // ���������� �������� ���������
};

// ��������� �������
GameState* create_state(const char board[3][3]);
void delete_state_tree(GameState* root);
bool is_win(const char board[3][3], char player);
bool is_draw(const char board[3][3]);
bool is_terminal(const char board[3][3]);
void generate_all_states();
void save_to_file(const char* filename);



