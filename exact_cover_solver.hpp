#pragma once
#include "solver.hpp"
#include "exact_cover.hpp"

class ExactCoverSolver : public Solver
{
private:
    ExactCover ec;

    void initExactCover();

public:
    ExactCoverSolver(const std::string &filename);

    ExactCoverSolver(const Solver &other);

    ExactCoverSolver(Solver &&other);

    ExactCoverSolver &operator=(const Solver &other);

    ExactCoverSolver &operator=(Solver &&other);

    void solve(bool printGame) override;
};