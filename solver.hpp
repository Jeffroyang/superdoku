#pragma once
#include "sudoku.hpp"
#include <memory>

class Solver
{
protected:
    std::unique_ptr<SudokuGame> game;

public:
    Solver();
    Solver(const std::string &filename);
    Solver(Solver &&other);
    Solver(const Solver &other);

    virtual void solve() = 0;
    virtual ~Solver();
};