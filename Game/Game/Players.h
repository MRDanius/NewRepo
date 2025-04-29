#pragma once


#include "Game.h"
#include "GameState.h"
#include <iostream>


class Game; // Предварительное объявление класса Game

struct Cell {
    int row;
    int col;
};

class Player {
public:
    char symbol;
    virtual ~Player() {}
    virtual Cell getMove(const Game& game) = 0; // Исправлен тип параметра
};

class HumanPlayer : public Player {
public:
    Cell getMove(const Game& game) override;
};

class BotPlayer : public Player {
public:
    enum Mode { NORMAL, PROLONG };
    enum Difficulty { EASY, MEDIUM, HARD };

    BotPlayer(Mode mode, Difficulty difficulty);
    ~BotPlayer();
    Cell getMove(const Game& game) override;

private:
    Mode bot_mode;
    Difficulty bot_difficulty;
    GameState* state_tree;

    void build_state_tree(GameState* root);
    void evaluate_states(GameState* state, char current_player);
    int calculate_score(GameState* state);
};



