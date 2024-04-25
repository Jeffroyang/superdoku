#pragma once
#include "solver.hpp"
#include "exact_cover.hpp"

class ExactCoverSolver : public Solver
{
private:
    ExactCover ec;

public:
    ExactCoverSolver(const std::string &filename);

    void solve() override;
};