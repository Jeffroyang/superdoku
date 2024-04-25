#include "exact_cover_solver.hpp"
#include <iostream>

ExactCoverSolver::ExactCoverSolver(const std::string &filename) : Solver(filename), ec(GRID_SIZE * GRID_SIZE * 4)
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

ExactCoverSolver::ExactCoverSolver(const Solver &other) : Solver(other), ec(GRID_SIZE * GRID_SIZE * 4)
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

ExactCoverSolver::ExactCoverSolver(Solver &&other) : Solver(other), ec(GRID_SIZE * GRID_SIZE * 4)
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

void ExactCoverSolver::solve()
{
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

        std::cout << *game << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <sudoku filename>" << std::endl;
    }

    ExactCoverSolver solver(argv[1]);
    solver.solve();

    return 0;
}
