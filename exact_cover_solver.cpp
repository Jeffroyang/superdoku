#include "solver.h"
#include <iostream>

class ExactCoverSolver : public Solver
{

public:
    ExactCoverSolver() = default;

    ExactCoverSolver(const std::string &filename) : Solver(filename) {}

    void solve() override
    {
        return;
    }
};

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
