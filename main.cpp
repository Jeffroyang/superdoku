#include "constraint_solver.hpp"
#include "backtrack_solver.hpp"
#include "exact_cover_solver.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <sudoku_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string line;
    std::getline(file, line);

    ConstraintSolver solver1(line);
    std::cout << "Solver 1: Regular Constructor" << std::endl;
    std::cout << solver1.getGame() << std::endl;

    // copy constructor
    BacktrackingSolver solver2(solver1);
    std::cout << "Solver 2: Copy Constructor" << std::endl;
    std::cout << solver2.getGame() << std::endl;

    // move constructor
    ExactCoverSolver solver3(std::move(solver2));
    std::cout << "Solver 3: Move Constructor" << std::endl;
    std::cout << solver3.getGame() << std::endl;

    // copy assignment
    BacktrackingSolver solver4 = solver3;
    std::cout << "Solver 4: Copy Assignment" << std::endl;
    std::cout << solver4.getGame() << std::endl;

    // move assignment
    ConstraintSolver solver5 = std::move(solver4);
    std::cout << "Solver 5: Move Assignment" << std::endl;
    std::cout << solver5.getGame() << std::endl;

    return 0;
}