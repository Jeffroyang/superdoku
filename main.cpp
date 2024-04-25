#include "constraint_solver.hpp"
#include "backtrack_solver.hpp"

int main(int argc, char *argv[])
{
    ConstraintSolver solver1(argv[1]);
    BacktrackingSolver solver2(solver1);
}