#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>

#define GRID_SIZE 9

class SudokuGame
{
private:
    // grid containing numbers '1' to '9' and empty cells '.'
    std::array<std::array<char, GRID_SIZE>, GRID_SIZE> grid;

    // verify that the row, column, and value are valid
    void verifyArgs(int row, int col, char val) const;

    // check if the value can be placed in the given column
    bool columnCheck(int col, char value) const;

    // check if the value can be placed in the given row
    bool rowCheck(int row, char value) const;

    // check if the value can be placed in the given square
    bool squareCheck(int row, int col, char value) const;

    // check if the value can be placed at the given coord
    bool canPlace(int row, int col, char value) const;

public:
    // create empty sudoku game
    SudokuGame();

    // create sudoku game given a string
    // format: row 1 || row 2 || ... || row 9
    SudokuGame(const std::string &);

    // loads grid from 2D vector
    SudokuGame(const std::array<std::array<char, GRID_SIZE>, GRID_SIZE> &grid);

    SudokuGame(const SudokuGame &other);

    SudokuGame(SudokuGame &&other);

    SudokuGame &operator=(const SudokuGame &other);

    SudokuGame &operator=(SudokuGame &&other);

    // update grid with value at coord
    // returns bool indicating whether the update was successful
    bool update(int row, int col, char value);

    // check if the game is over
    bool gameOver() const;

    // reads the value at the given row and column
    const std::array<char, GRID_SIZE> &operator[](int row) const;

    bool operator==(const SudokuGame &grid) const;

    friend std::ostream &operator<<(std::ostream &out, SudokuGame game);
};