//#pragma once
//#include "Cell.h"
//#include "GameState.h"
//
//class Game; // Forward declaration
//
//class Player {
//protected:
//    char symbol;
//public:
//    virtual ~Player() = default;
//    virtual Cell getMove(const Game& game) = 0;
//    void setSymbol(char s) { symbol = s; }
//    char getSymbol() const { return symbol; }
//};
//
//class HumanPlayer : public Player {
//public:
//    Cell getMove(const Game& game) override;
//};
//
//class BotPlayer : public Player {
//public:
//    enum Difficulty { RANDOM, EASY, HARD, PROLONG };
//
//    BotPlayer(Difficulty difficulty);
//    Cell getMove(const Game& game) override;
//
//private:
//    Difficulty difficulty;
//
//    GameState* findCurrentState(const Game& game) const;
//    int calculateScore(const GameState* state) const;
//};

#pragma once
#include "Cell.h"
#include "GameState.h"

class Game;

class Player {
protected:
    char symbol;
public:
    virtual ~Player() = default;
    virtual Cell getMove(const Game& game) = 0;
    void setSymbol(char s) { symbol = s; }
    char getSymbol() const { return symbol; }
};

class HumanPlayer : public Player {
public:
    Cell getMove(const Game& game) override;
};

class BotPlayer : public Player {
public:
    enum Difficulty { RANDOM, EASY, HARD, PROLONG };
    BotPlayer(Difficulty difficulty);
    Cell getMove(const Game& game) override;

private:
    Difficulty difficulty;
    GameState* findCurrentState(const Game& game) const;
    int calculateScore(const GameState* state) const;
};