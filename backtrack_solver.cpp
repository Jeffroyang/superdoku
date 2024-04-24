#include "solver.h"
#include <iostream>

class BacktrackingSolver : public Solver
{
private:
    bool solveHelper()
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

    bool findEmptyLocation(int &row, int &col) const
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

public:
    BacktrackingSolver() = default;

    BacktrackingSolver(const std::string &filename) : Solver(filename) {}

    void solve() override
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
};

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
