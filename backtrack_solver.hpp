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

    void solve() override;
};
