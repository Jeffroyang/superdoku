#pragma once
#include "sudoku.hpp"
#include <memory>

class Solver
{
protected:
    std::unique_ptr<SudokuGame> game;

public:
    Solver();
    Solver(const std::string &sudokuStr);
    Solver(Solver &&other);
    Solver(const Solver &other);

    Solver &operator=(const Solver &other);
    Solver &operator=(Solver &&other);

    // returns a copy of the game
    SudokuGame getGame() const;

    virtual void solve(bool printGame) = 0;
    virtual ~Solver();
};