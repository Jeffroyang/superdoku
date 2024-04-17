#ifndef __GRID_HPP__
#define __GRID_HPP__

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <set>
#include <vector>

#define GRID_SIZE 9

class Grid {
private:
    std::array<std::array<int, GRID_SIZE>, GRID_SIZE> grid;
    std::set<std::pair<int, int>> currentCoords;

public:
    Grid() {for_each(grid.begin(), grid.end(), [](std::array<int, GRID_SIZE>& g) {std::fill(g.begin(), g.end(), 0);});}
    Grid(std::array<std::array<int, GRID_SIZE>, GRID_SIZE> grid) {setGrid(grid);}

    void setGrid(std::array<std::array<int, GRID_SIZE>, GRID_SIZE> grid) {
        currentCoords.clear();
        for (int row = 0; row < GRID_SIZE; row++) for (int col = 0; col < GRID_SIZE; col++) {
            int currCell = grid.at(row).at(col);
            if (currCell < 0 || currCell > 9) throw std::invalid_argument("Cell value should be in the range from 0 to 9");
            this->grid.at(row).at(col) = currCell;
            if (currCell != 0) currentCoords.insert(std::make_pair(row, col));
        }
    }

    void importGridFromFile(std::string filename) {
        std::ifstream file;
        file.open(filename, std::ios::in);
        if (file.fail()) throw std::invalid_argument("Error opening File");

        std::array<std::array<int, GRID_SIZE>, GRID_SIZE> grid;

        for (int row = 0; row < GRID_SIZE; row++) for (int col = 0; col < GRID_SIZE; col++) {
            file >> grid.at(row).at(col);
            if (file.eof()) throw std::invalid_argument("Error reading value from file");
        }
        file.close();
        setGrid(grid);
    }

    void update(std::pair<int, int> coord, int value) {
        if (value < 0 || value > 9) throw std::invalid_argument("Cell value should be in the range from 0 to 9");
        grid.at(coord.first).at(coord.second) = value;
    }

    int get(std::pair<int, int> coord) const { return grid.at(coord.first).at(coord.second); }

    bool columnCheck(std::pair<int, int> coord, int value) const {
        int currRow = 0;
        return std::any_of(grid.begin(), grid.end(),
            [=, &currRow] (std::array<int, GRID_SIZE> row) -> bool {
                return (row.at(coord.second) == value) && (coord.first != currRow++);
            }
        );
    }

    bool rowCheck(std::pair<int, int> coord, int value) const {
        int currCol = 0;
        return std::any_of(grid.at(coord.first).begin(), grid.at(coord.first).end(),
            [=, &currCol] (int cell) -> bool {
                return (cell == value) && (coord.second != currCol++);
            }
        );
    }

    bool squareCheck(std::pair<int, int> coord, int value) const {
        int rowStart = (coord.first/3)*3, colStart = (coord.second/3)*3;
        int rowEnd = (rowStart+2), colEnd = (colStart+2);

        for (int row = rowStart; row <= rowEnd; row++) for (int col = colStart; col <= colEnd; col++) {
            if ((std::make_pair(row, col) != coord) && (grid.at(row).at(col) == value)) return true;
        }
        return false;
    }

    bool coordGiven(std::pair<int, int> coord) const {
        auto element_found = std::find(currentCoords.begin(), currentCoords.end(), coord);
        return element_found != currentCoords.end();
    }

    std::vector<int> getPossibleValues(std::pair<int, int> coord) {
        std::vector<int> values(GRID_SIZE);
        std::iota (values.begin(), values.end(), 1);
        std::vector<int> filtered(GRID_SIZE);

        auto it = std::copy_if(values.begin(), values.end(), filtered.begin(),
            [this, coord] (int value) -> bool {
                return !(this->columnCheck(coord, value) || this->rowCheck(coord, value) || this->squareCheck(coord, value));
            }
        );

        filtered.resize(std::distance(filtered.begin(), it));
        return filtered;
    }

    bool operator== (const Grid& grid) const {
        for (int row = 0; row < GRID_SIZE; row++) for (int col = 0; col < GRID_SIZE; col++) {
            auto coord = std::make_pair(row, col);
            if (get(coord) != grid.get(coord)) return false;
        }
        return true;
    }

    friend std::ostream& operator<< (std::ostream& out, Grid grid);
};

std::ostream& operator<< (std::ostream& out, Grid grid) {
    out << "+-------+-------+-------+\n";
    for (int row = 0; row < GRID_SIZE; row++) {
        out << "|";
        for (int col = 0; col < GRID_SIZE; col++) {
            out << " " << grid.grid[row][col];
            if (col%3 == 2) out << " |";
        }
        out << "\n";
        if (row%3 == 2) out << "+-------+-------+-------+\n";
    }
    return out;
}

#endif