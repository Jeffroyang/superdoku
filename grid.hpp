#ifndef __GRID_HPP__
#define __GRID_HPP__

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <set>
#include <vector>

class Grid
{
private:
    size_t n;

    std::vector<std::vector<uint32_t>> grid;

    std::set<std::pair<uint32_t, uint32_t>> currentCoords;

public:
    // create empty n x n grid
    Grid(uint32_t n = 9);

    // loads grid from 2D vector
    Grid(std::vector<std::vector<uint32_t>> grid, uint32_t n = 9);

    // set grid from 2D vector and validates the grid
    void setGrid(std::vector<std::vector<uint32_t>> grid);

    // load grid from file
    void importGridFromFile(std::string filename);

    // update grid with value at coord
    void update(std::pair<uint32_t, uint32_t> coord, uint32_t value);

    // get value at coord
    uint32_t get(std::pair<uint32_t, uint32_t> coord) const;

    bool columnCheck(std::pair<uint32_t, uint32_t> coord, uint32_t value) const;

    bool rowCheck(std::pair<uint32_t, uint32_t> coord, uint32_t value) const;

    bool squareCheck(std::pair<uint32_t, uint32_t> coord, uint32_t value) const;

    bool coordGiven(std::pair<uint32_t, uint32_t> coord) const;

    std::vector<uint32_t> getPossibleValues(std::pair<uint32_t, uint32_t> coord);

    bool operator==(const Grid &grid) const;

    friend std::ostream &operator<<(std::ostream &out, Grid grid);
};

#endif