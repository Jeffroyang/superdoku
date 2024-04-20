
#include "solver.h"

Solver::Solver() = default;

Solver::Solver(const std::string &filename)
{
    game = std::make_unique<SudokuGame>(filename);
}

Solver::Solver(Solver &&other)
{
    game = std::move(other.game);
}

Solver::~Solver() = default;