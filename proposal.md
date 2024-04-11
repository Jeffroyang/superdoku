## Description

Our project aims to develop a sudoku solver implemented in C++, with an exploration of different algorithms. The objective of Sudoku is to fill an 9 by 9 grid with digits from 1 to 9 such that each row, column, and subgrid contains exactly one occurence of each digit. There are a variety of known techniques for solving Sudoku found on https://en.wikipedia.org/wiki/Sudoku_solving_algorithms. Techniques include backtracking, stochastic search, constraint programming, exact cover, and relations and residuals. We plan to implement at least up to exact cover (relations and residuals time permitting).

## Libraries/Frameworks
1. Standard Template Library (STL): We will use arrays to represent the grids and subgrids in our Sudoku board. We will make sure of different containers as we explore the different algorithms.

## C++ Features
1. Class hierarchy: We will have a base class for Sudoku that represents the actual Sudoku game. This will be responsible for reading in Sudoku games, tracking internal state, and printing the final solution to the terminal. For each of the algorithms we implement, we will inherit from the base Sudoku class and add any metadata required.
2. File IO: We will allow users to input Sudoku puzzles using files and output solutions visually in the terminal.


## Division of Work
- Week 1: We will work together to come up with a reasonable implementation of the Sudoku class
- Week 2: Work separately on implementing the backtracking / stochastic search solutions. Measure runtimes of these two methods.
- Week 3: Work separately on implementing the Constraint programming / exact cover solutions. Compare runtimes for the four different methods.

## Time Estimates
- Week 1: Implement the Sudoku class, reading game from file, and writing to terminal.
- Week 2: Implement Backtracking and Stochastic search solutions
- Week 3: Implement Constraint programming and exact cover solutions