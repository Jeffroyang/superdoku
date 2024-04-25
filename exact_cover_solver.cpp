#include "exact_cover_solver.hpp"
#include <iostream>
#include <fstream>

ExactCoverSolver::ExactCoverSolver(const std::string &filename) : Solver(filename), ec(GRID_SIZE * GRID_SIZE * 4)
{
    initExactCover();
}

ExactCoverSolver::ExactCoverSolver(const Solver &other) : Solver(other), ec(GRID_SIZE * GRID_SIZE * 4)
{
    initExactCover();
}

ExactCoverSolver::ExactCoverSolver(Solver &&other) : Solver(other), ec(GRID_SIZE * GRID_SIZE * 4)
{
    initExactCover();
}

ExactCoverSolver &ExactCoverSolver::operator=(const Solver &other)
{
    Solver::operator=(other);
    initExactCover();
    return *this;
}

ExactCoverSolver &ExactCoverSolver::operator=(Solver &&other)
{
    Solver::operator=(other);
    initExactCover();
    return *this;
}

void ExactCoverSolver::initExactCover()
{
    // add options for each cell
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            for (int num = 1; num <= GRID_SIZE; num++)
            {
                size_t valConstraint = row * GRID_SIZE + col + 1;
                size_t rowConstraint = GRID_SIZE * GRID_SIZE + row * GRID_SIZE + num;
                size_t colConstraint = 2 * GRID_SIZE * GRID_SIZE + col * GRID_SIZE + num;
                size_t boxRow = row / 3;
                size_t boxCol = col / 3;
                size_t boxConstraint = 3 * GRID_SIZE * GRID_SIZE + (boxRow * 3 + boxCol) * GRID_SIZE + num;
                ec.addRow({valConstraint, rowConstraint, colConstraint, boxConstraint});
            }
        }
    }

    // add initial covers
    std::vector<size_t> initialRows;
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            auto val = (*game)[row][col];
            if (val != '.')
            {
                auto idx = row * GRID_SIZE * GRID_SIZE + col * GRID_SIZE + val - '0' - 1;
                initialRows.push_back(idx);
            }
        }
    }
    ec.initRows(initialRows);
}

void ExactCoverSolver::solve(bool printGame)
{
    if (printGame)
    {
        std::cout << "Initial game:" << std::endl;
        std::cout << *game << std::endl;
    }

    auto solution = ec.solve();

    if (solution.size() != GRID_SIZE * GRID_SIZE)
    {
        std::cout << "No solution found" << std::endl;
    }
    else
    {
        std::cout << "Solution found" << std::endl;
        for (const auto &row : solution)
        {
            char val = row % GRID_SIZE + 1 + '0';
            size_t updateRow = row / (GRID_SIZE * GRID_SIZE);
            size_t updateCol = row % (GRID_SIZE * GRID_SIZE) / GRID_SIZE;
            game->update(updateRow, updateCol, val);
        }
        if (printGame)
        {
            std::cout << *game << std::endl;
        }
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
        ExactCoverSolver solver(line);
        solver.solve(printGame);
        count++;
        std::cout << "Puzzle #" << count << " solved" << std::endl;
    }
}
#endif