#pragma once
#include "solver.hpp"
#include <iostream>

class BacktrackingSolver : public Solver
{
private:
    // recursive helper function to solve the puzzle
    bool solveHelper();

    // find an empty location in the puzzle
    bool findEmptyLocation(int &row, int &col) const;

public:
    BacktrackingSolver(const std::string &sudokuStr);

    BacktrackingSolver(Solver &&other);

    BacktrackingSolver(const Solver &other);

    BacktrackingSolver &operator=(const Solver &other);

    BacktrackingSolver &operator=(Solver &&other);

    void solve(bool printGame) override;
};
