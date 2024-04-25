#pragma once
#include "solver.hpp"
#include "exact_cover.hpp"

class ExactCoverSolver : public Solver
{
private:
    ExactCover ec;

public:
    ExactCoverSolver(const std::string &filename);

    // Solver copy constructor
    ExactCoverSolver(const Solver &other);

    // Solver move constructor
    ExactCoverSolver(Solver &&other);

    void solve() override;
};