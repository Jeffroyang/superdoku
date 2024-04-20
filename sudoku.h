#ifndef __SUDOKU_HPP__
#define __SUDOKU_HPP__
#define GRID_SIZE 9

#include <array>
#include <cstdint>
#include <string>
#include <vector>

class SudokuGame
{
private:
    // grid containing numbers '1' to '9' and empty cells '.'
    std::array<std::array<char, GRID_SIZE>, GRID_SIZE> grid;

    // potentially get rid of this if we always have well-formed input
    void verifyCoords(int row, int col) const;

    // check if the value can be placed in the given column
    bool columnCheck(int col, char value) const;

    // check if the value can be placed in the given row
    bool rowCheck(int row, char value) const;

    // check if the value can be placed in the given square
    bool squareCheck(int row, int col, char value) const;

public:
    // create sudoku game given a file
    SudokuGame(const std::string &filename);

    // loads grid from 2D vector
    SudokuGame(const std::array<std::array<char, GRID_SIZE>, GRID_SIZE> &grid);

    // update grid with value at coord
    // returns bool indicating whether the update was successful
    bool update(int row, int col, char value);

    // check if the value can be placed at the given coord
    bool canPlace(int row, int col, char value) const;

    // check if the game is over
    bool gameOver() const;

    // reads the value at the given row and column
    const std::array<char, GRID_SIZE> &operator[](int row) const;

    bool operator==(const SudokuGame &grid) const;

    friend std::ostream &operator<<(std::ostream &out, SudokuGame game);
};

#endif
