#include "constraint_solver.hpp"
#include "backtrack_solver.hpp"
#include "exact_cover_solver.hpp"

#include <iostream>
#include <fstream>
#include <chrono>

enum class SolverType
{
    BACKTRACK,
    CONSTRAINT,
    EXACTCOVER
};

void testConstructors(const std::string &fileName)
{
    std::ifstream file(fileName);
    std::string line;
    std::getline(file, line);
    file.close();

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
}

int main(int argc, char *argv[])
{
    testConstructors(argv[1]);

    if (argc < 3 || argc > 5)
    {
        std::cerr << "Usage: " << argv[0] << " <sudoku_file> <solver> [-p]" << std::endl;
        return 1;
    }

    // check for print option
    bool printGame = false;
    if (argc == 4)
    {
        if (std::string(argv[2]) == "-p")
        {
            printGame = true;
        }
    }

    SolverType solverType;
    if (std::string(argv[2]) == "backtrack")
    {
        solverType = SolverType::BACKTRACK;
    }
    else if (std::string(argv[2]) == "constraint")
    {
        solverType = SolverType::CONSTRAINT;
    }
    else if (std::string(argv[2]) == "exactcover")
    {
        solverType = SolverType::EXACTCOVER;
    }
    else
    {
        std::cerr << "Invalid solver type" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string sudokuStr;

    int count = 0;
    auto start = std::chrono::steady_clock::now();
    while (std::getline(file, sudokuStr))
    {
        auto puzzle_start = std::chrono::steady_clock::now();
        switch (solverType)
        {
        case SolverType::BACKTRACK:
        {
            BacktrackingSolver solver(sudokuStr);
            solver.solve(printGame);
            break;
        }
        case SolverType::CONSTRAINT:
        {
            ConstraintSolver solver(sudokuStr);
            solver.solve(printGame);
            break;
        }
        case SolverType::EXACTCOVER:
        {
            ExactCoverSolver solver(sudokuStr);
            solver.solve(printGame);
            break;
        }
        default:
            break;
        }
        count++;
        auto puzzle_end = std::chrono::steady_clock::now();
        std::cout << "Puzzle #" << count << " solved in "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(puzzle_end - puzzle_start).count()
                  << " ns" << std::endl;
    }
    auto end = std::chrono::steady_clock::now(); // end timing
    std::cout << "Total time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    return 0;
}