# Superdoku
By Jeffrey Yang (yjeffrey) and Jerry Wang (jwang01)

Our project implements various sudoku solvers in C++, with an exploration of 3 different algorithms. 

The objective of Sudoku is to fill an **9** by **9** grid with digits from 1 to **9** such that each row, column, and subgrid contains exactly one occurence of each digit. There are a variety of known techniques for solving Sudoku found [here](https://en.wikipedia.org/wiki/Sudoku_solving_algorithms). We have implemented algorithms for backtracking, ac3, and exact cover solvers.

## Usage
1. Run make to compile the different sudoku solvers and also the main file.
2. For each of the executables `backtrack_solver`, `constraint_solver`, and `exact_cover_solver`: 
    - Run `./executable <sudoku file> [-p]` to solve the puzzles in each sudoku file. `[-p]` indicates whether or not you want the Sudoku game to be printed.
3. We compiled the main program using `-O3` optimization and you can benchmark the runtime of the different algorithms. main is ran using `./main <sudoku file> <solver_type> [-p]`. Below are some examples:
    - `./main puzzles/easy_list.txt backtrack`
    - `./main puzzles/hard_list.txt constraint`
    - `./main puzzles/hard_list.txt exactcover`

## Results
Exact cover solver on a single hard puzzle with 17 givens:

![Screenshot 2024-04-25 at 11 12 29 PM](https://github.com/Jeffroyang/superdoku/assets/82118995/f2aa244c-481b-45b2-a04e-0d39a2548652)

<img width="861" alt="Screenshot 2024-04-25 at 11 07 04 PM" src="https://github.com/Jeffroyang/superdoku/assets/82118995/a1909b9b-425b-49a6-ab6f-5165566c02f9">

## Source Files
- `sudoku.cpp` implements the core sudoku logic and allows us to print the sudoku game to the terminal
- `backtrack_solver.cpp` implements the backtrack solver for our Sudoku game
- `constraint_solver.cpp` implements the AC-3 solver for our Sudoku game
- `exact_cover.cpp` implements Knuth's Algorithm X using Dancing Links to solve the Exact Cover problem
- `exact_cover_solver.cpp` reduces the Sudoku puzzle to an exact cover problem and solves the puzzles using the implementation in `exact_cover.cpp`
- `main.cpp` shows off our copy/move constructors and copy/move assignments. It also provides a way for us to measure the runtime of our different solvers.

## C++ Features
1. Object Oriented Programming: We represent our Sudoku Game, Sudoku Solvers, and Exact Cover as objects.
2. Class hierarchy: We have an abstract Solver class for Sudoku. The solvers for our 3 different solvers will implement the Solver class and provide their methods for `void solve()`
3. Standard Template Library (STL): We use arrays and vectors to represent the grids and subgrids in our Sudoku board.
4. File IO: We allow users to input Sudoku puzzles using files and output solutions visually in the terminal.

