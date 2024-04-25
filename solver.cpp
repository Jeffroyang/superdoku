#include "solver.hpp"

Solver::Solver() = default;

Solver::Solver(const std::string &filename)
{
    game = std::make_unique<SudokuGame>(filename);
}

Solver::Solver(Solver &&other)
{
    game = std::move(other.game);
}

Solver::Solver(const Solver &other)
{
    game = std::make_unique<SudokuGame>(*other.game);
}

Solver::~Solver() = default;