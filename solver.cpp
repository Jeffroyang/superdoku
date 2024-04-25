#include "solver.hpp"

Solver::Solver() : game(std::make_unique<SudokuGame>()) {}

Solver::Solver(const std::string &sudokuStr)
    : game(std::make_unique<SudokuGame>(sudokuStr))
{
}

Solver::Solver(const Solver &other)
    : game(other.game ? std::make_unique<SudokuGame>(*other.game) : nullptr)
{
}

Solver::Solver(Solver &&other)
    : game(std::move(other.game))
{
}

Solver &Solver::operator=(const Solver &other)
{
    if (this != &other)
    {
        game = other.game ? std::make_unique<SudokuGame>(*other.game) : nullptr;
    }
    return *this;
}

Solver &Solver::operator=(Solver &&other)
{
    if (this != &other)
    {
        game = std::move(other.game);
    }
    return *this;
}

SudokuGame Solver::getGame() const
{
    return *game;
}

Solver::~Solver() {}