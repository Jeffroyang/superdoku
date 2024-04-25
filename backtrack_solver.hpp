#pragma once
#include "solver.hpp"
#include <iostream>

class BacktrackingSolver : public Solver
{
private:
    bool solveHelper();

    bool findEmptyLocation(int &row, int &col) const;

public:
    BacktrackingSolver(const std::string &filename);

    BacktrackingSolver(Solver &&other);

    BacktrackingSolver(const Solver &other);

    void solve() override;
};
