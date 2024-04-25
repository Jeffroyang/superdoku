#include "backtrack_solver.hpp"

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

BacktrackingSolver::BacktrackingSolver(const std::string &filename) {}

BacktrackingSolver::BacktrackingSolver(const Solver &other) : Solver(other) {}

BacktrackingSolver::BacktrackingSolver(Solver &&other) : Solver(other) {}

void BacktrackingSolver::solve()
{
    if (solveHelper())
    {
        std::cout << "Solution found:" << std::endl;
        std::cout << *game << std::endl;
    }
    else
    {
        std::cout << "No solution found" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <sudoku filename>" << std::endl;
    }

    BacktrackingSolver solver(argv[1]);
    solver.solve();

    return 0;
}
