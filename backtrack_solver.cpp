#include "solver.h"
#include <iostream>

class BacktrackingSolver : public Solver
{
public:
    BacktrackingSolver() = default;

    BacktrackingSolver(const std::string &filename) : Solver(filename) {}

    bool solve() override
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
                if (solve())
                {
                    std::cout << "Sudoku puzzle solved successfully!" << std::endl;
                    std::cout << *game << std::endl;
                    return true;
                }

                game->update(row, col, '.');
            }
        }

        return false;
    }

private:
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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <sudoku filename>" << std::endl;
    }

    BacktrackingSolver solver(argv[1]);
    if (!solver.solve())
    {
        std::cout << "No solution found!" << std::endl;
    }

    return 0;
}
