#include "solver.h"
#include <iostream>

class ConstraintSolver : public Solver
{
private:
public:
    ConstraintSolver() = default;

    ConstraintSolver(const std::string &filename) : Solver(filename) {}

    void solve() override
    {
        // std::queue currQueue;

        return;
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <sudoku filename>" << std::endl;
    }

    ConstraintSolver solver(argv[1]);
    solver.solve();

    return 0;
}