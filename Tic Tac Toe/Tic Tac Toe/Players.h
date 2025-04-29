#pragma once


#include "GameState.h"  // ���������!

class Game; // ��������������� ����������

struct Cell {
    int row;
    int col;
};

class Player {
public:
    char symbol;
    virtual ~Player() {}
    virtual Cell getMove(const Game& game) = 0;
    virtual void setSymbol(char s) { symbol = s; }
};

class HumanPlayer : public Player {
public:
    Cell getMove(const Game& game) override;
};

class BotPlayer : public Player {
public:
    enum Mode { NORMAL, PROLONG };
    enum Difficulty { EASY, MEDIUM, HARD };

    BotPlayer(Mode mode, Difficulty diff);
    ~BotPlayer();
    Cell getMove(const Game& game) override;

private:
    Mode mode;
    Difficulty difficulty;

    // ������������ ����������:
    GameState* find_current_state(const Game& game) const; // �������� GameState*
    int calculate_score(const GameState* state) const;      // �������� GameState*
};
