#include "constraint_solver.cpp"
#include "backtrack_solver.cpp"

int main(int argc, char *argv[])
{
    ConstraintSolver solver1(argv[1]);
    BacktrackingSolver solver2(solver1);
}