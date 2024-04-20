#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__

#include "sudoku.h"
#include <memory>

class Solver
{
private:
    std::unique_ptr<SudokuGame> game;

public:
    Solver(const std::string &filename);
    Solver(std::unique_ptr<SudokuGame> game);
    Solver(Solver &&other);

    virtual void solve() = 0;
    virtual ~Solver();
};

#endif