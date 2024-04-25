#include "backtrack_solver.hpp"
#include <iostream>
#include <fstream>

BacktrackingSolver::BacktrackingSolver(const std::string &sudokuStr)
    : Solver(sudokuStr) {}

BacktrackingSolver::BacktrackingSolver(const Solver &other) : Solver(other) {}

BacktrackingSolver::BacktrackingSolver(Solver &&other) : Solver(other) {}

BacktrackingSolver &BacktrackingSolver::operator=(const Solver &other)
{
    Solver::operator=(other);
    return *this;
}

BacktrackingSolver &BacktrackingSolver::operator=(Solver &&other)
{
    Solver::operator=(other);
    return *this;
}

bool BacktrackingSolver::solveHelper()
{
    int row, col;

    if (!findEmptyLocation(row, col))
    {
        return true;
    }
    for (char num = '1'; num <= '9'; num++)
    {
        if (game->update(row, col, num))
        {
            if (solveHelper())
            {
                return true;
            }
            game->update(row, col, '.');
        }
    }

    return false;
}

bool BacktrackingSolver::findEmptyLocation(int &row, int &col) const
{
    for (row = 0; row < GRID_SIZE; row++)
    {
        for (col = 0; col < GRID_SIZE; col++)
        {
            if ((*game)[row][col] == '.')
            {
                return true;
            }
        }
    }
    return false;
}

void BacktrackingSolver::solve(bool printGame)
{
    if (printGame)
    {
        std::cout << "Initial game:" << std::endl;
        std::cout << *game << std::endl;
    }

    if (solveHelper())
    {
        std::cout << "Solution found:" << std::endl;
        if (printGame)
        {
            std::cout << *game << std::endl;
        }
    }
    else
    {
        std::cout << "No solution found" << std::endl;
    }
}

#ifndef MAIN
#define MAIN
int main(int argc, char *argv[])
{
    if (argc < 2 || argc >= 4)
    {
        std::cout << "Usage: " << argv[0] << " <sudoku filename> [-p]" << std::endl;
    }

    // check for print option
    bool printGame = false;
    if (argc == 3)
    {
        if (std::string(argv[2]) == "-p")
        {
            printGame = true;
        }
    }

    std::fstream file(argv[1]);
    std::string sudokuStr;

    // each line of the file is a sudoku puzzle
    std::string line;

    int count = 0;
    while (std::getline(file, line))
    {
        BacktrackingSolver solver(line);
        solver.solve(printGame);
        count++;
        std::cout << "Puzzle #" << count << " solved" << std::endl;
    }
}
#endif