#pragma once
#include "solver.hpp"
#include <iostream>
#include <deque>

class ConstraintSolver : public Solver
{
private:
    // Board that keeps track of all possible values each cell can take
    std::array<std::array<std::vector<int>, GRID_SIZE>, GRID_SIZE> board;

    // Private constructor that creates a board from a board representation
    ConstraintSolver(std::array<std::array<std::vector<int>, GRID_SIZE>, GRID_SIZE> other_board);

    // Checks if the board is solved
    bool is_solved();

    // Generate the value tracking-board from a sudoku puzzle
    void populate_grid();

    // Generate a deque of arc combinations between two points
    std::deque<std::pair<std::pair<int, int>, std::pair<int, int>>> get_arcs();

    // Given a queue, generate the arc successors with the given start and end coordinates
    void ac3_successors(std::deque<std::pair<std::pair<int, int>, std::pair<int, int>>>& queue, std::pair<int, int> start, std::pair<int, int> end);

    // Remove inconsistent arcs, return true if an arc has been removed
    bool remove_inconsistent(std::pair<int, int> cell1, std::pair<int, int> cell2);

    // Attempt to apply the AC-3 algorithm
    void infer_ac3();

    // Check if the value can be added with the arc constraints
    bool in_arcs(int value, int row, int col);

    // Apply the AC-3 Algorithm with tighter arc constraints
    void infer_improved();

    // Checks if the board is solvable
    bool is_solvable();

    // Return a coordinate pair with the lowest possible values
    std::pair<int, int> cell_choice();

    // Generate a board with a guessed cell choice
    std::vector<std::array<std::array<std::vector<int>, GRID_SIZE>, GRID_SIZE>> guess_successors(std::pair<int, int> next_cell);

    // Attempt to apply the improved AC-3 Algorithm with backtracking and guessing
    void infer_with_guessing();

public:
    // Constructor for a puzzle from a string
    ConstraintSolver(const std::string &filename);

    // Constructor for a puzzle from another ConstraintSolver
    ConstraintSolver(const ConstraintSolver& other);

    // Run the solver
    void solve() override;
};