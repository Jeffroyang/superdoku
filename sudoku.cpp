#include "sudoku.hpp"
#include <fstream>
#include <iostream>

SudokuGame::SudokuGame()
{
    for (size_t row = 0; row < GRID_SIZE; row++)
    {
        for (size_t col = 0; col < GRID_SIZE; col++)
        {
            grid[row][col] = '.';
        }
    }
}

SudokuGame::SudokuGame(const std::string &filename)
    : SudokuGame()
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    if (file.fail())
    {
        throw std::invalid_argument("Error opening File");
    }

    for (size_t row = 0; row < GRID_SIZE; row++)
    {
        for (size_t col = 0; col < GRID_SIZE; col++)
        {
            if (file.eof())
            {
                throw std::invalid_argument("Error reading value from file");
            }
            char val;
            file >> val;
            if (!update(row, col, val))
            {
                throw std::invalid_argument("Invalid initial grid");
            }
        }
    }

    file.close();
}

SudokuGame::SudokuGame(const std::array<std::array<char, GRID_SIZE>, GRID_SIZE> &grid)
{
    for (size_t row = 0; row < GRID_SIZE; row++)
    {
        for (size_t col = 0; col < GRID_SIZE; col++)
        {
            if (!update(row, col, grid[row][col]))
            {
                throw std::invalid_argument("Invalid initial grid");
            }
        }
    }
}

void SudokuGame::verifyArgs(int row, int col, char val) const
{
    if (row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE)
    {
        throw std::invalid_argument("Invalid row or column");
    }
    if (val != '.' && (val < '1' || val > '9'))
    {
        throw std::invalid_argument("Invalid value");
    }
}

bool SudokuGame::update(int row, int col, char value)
{
    verifyArgs(row, col, value);
    if (!canPlace(row, col, value))
    {
        return false;
    }
    grid[row][col] = value;
    return true;
}

bool SudokuGame::columnCheck(int col, char value) const
{
    return std::find_if(grid.begin(), grid.end(), [col, value](const std::array<char, GRID_SIZE> &row)
                        { return row[col] == value; }) == grid.end();
}

bool SudokuGame::rowCheck(int row, char value) const
{
    return std::find(grid[row].begin(), grid[row].end(), value) == grid[row].end();
}

bool SudokuGame::squareCheck(int row, int col, char value) const
{
    size_t rowStart = (row / 3) * 3, colStart = (col / 3) * 3;
    size_t rowEnd = rowStart + 3, colEnd = colStart + 3;

    for (size_t r = rowStart; r < rowEnd; r++)
    {
        for (size_t c = colStart; c < colEnd; c++)
        {
            if (grid[r][c] == value)
            {
                return false;
            }
        }
    }
    return true;
}

bool SudokuGame::canPlace(int row, int col, char value) const
{
    verifyArgs(row, col, value);
    bool undoingMove = value == '.';

    bool emptyCell = grid[row][col] == '.';
    bool noConflicts = emptyCell && columnCheck(col, value) && rowCheck(row, value) && squareCheck(row, col, value);

    return undoingMove || noConflicts;
}

bool SudokuGame::gameOver() const
{
    for (size_t row = 0; row < GRID_SIZE; row++)
    {
        for (size_t col = 0; col < GRID_SIZE; col++)
        {
            if (grid[row][col] == '.')
            {
                return false;
            }
        }
    }
    return true;
}

bool SudokuGame::operator==(const SudokuGame &game) const
{
    for (size_t row = 0; row < GRID_SIZE; row++)
    {
        for (size_t col = 0; col < GRID_SIZE; col++)
        {
            if (grid[row][col] != game.grid[row][col])
            {
                return false;
            }
        }
    }
    return true;
}

const std::array<char, GRID_SIZE> &SudokuGame::operator[](int row) const
{
    return grid[row];
}

std::ostream &operator<<(std::ostream &out, SudokuGame game)
{
    out << "+-------+-------+-------+\n";
    for (size_t row = 0; row < GRID_SIZE; row++)
    {
        out << "|";
        for (size_t col = 0; col < GRID_SIZE; col++)
        {
            out << " " << game.grid[row][col];
            if (col % 3 == 2)
            {
                out << " |";
            }
        }
        out << "\n";
        if (row % 3 == 2)
        {
            out << "+-------+-------+-------+\n";
        }
    }
    return out;
}