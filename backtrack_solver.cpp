#include "solver.h"
#include <iostream>

class BacktrackingSolver : public Solver
{
public:
    BacktrackingSolver() = default;

    BacktrackingSolver(const std::string &filename) : Solver(filename) {}

    void solve() override
    {
        if (solveSudoku())
        {
            std::cout << "Sudoku puzzle solved successfully!" << std::endl;
            std::cout << *game << std::endl;
        }
        else
        {
            std::cout << "No solution found for the given Sudoku puzzle." << std::endl;
        }
    }

private:
    bool solveSudoku()
    {
        int row, col;

        if (!findEmptyLocation(row, col))
        {
            return true;
        }
        for (char num = '1'; num <= '9'; num++)
        {
            if (game->canPlace(row, col, num))
            {
                game->update(row, col, num);
                if (solveSudoku())
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
};

int main()
{
    BacktrackingSolver solver("sudoku.txt");
    solver.solve();
    return 0;
}
