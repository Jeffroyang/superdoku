#include "grid.hpp"

Grid::Grid(uint32_t n)
    : n(n)
{
    grid = std::vector<std::vector<uint32_t>>(n, std::vector<uint32_t>(n, 0));
}

Grid::Grid(std::vector<std::vector<uint32_t>> grid, uint32_t n)
    : n(n)
{
    setGrid(grid);
}

void Grid::setGrid(std::vector<std::vector<uint32_t>> grid)
{
    if (grid.size() != n || grid.at(0).size() != n)
    {
        throw std::invalid_argument("Grid size should be n x n");
    }

    currentCoords.clear();
    for (uint32_t row = 0; row < n; row++)
        for (uint32_t col = 0; col < n; col++)
        {
            uint32_t currCell = grid.at(row).at(col);
            if (currCell < 0 || currCell > 9)
            {
                throw std::invalid_argument("Cell value should be in the range from 0 to 9");
            }
            this->grid.at(row).at(col) = currCell;
            if (currCell != 0)
            {
                currentCoords.insert(std::make_pair(row, col));
            }
        }
}

void Grid::importGridFromFile(std::string filename)
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    if (file.fail())
    {
        throw std::invalid_argument("Error opening File");
    }

    std::vector<std::vector<uint32_t>> grid(n, std::vector<uint32_t>(n, 0));
    for (uint32_t row = 0; row < n; row++)
    {
        for (uint32_t col = 0; col < n; col++)
        {
            if (file.eof())
            {
                throw std::invalid_argument("Error reading value from file");
            }
            file >> grid.at(row).at(col);
        }
    }

    file.close();
    setGrid(grid);
}

void Grid::update(std::pair<uint32_t, uint32_t> coord, uint32_t value)
{
    if (value <= 0 || value > n)
    {
        throw std::invalid_argument("Cell value should be in the range from 1 to n");
    }
    grid.at(coord.first).at(coord.second) = value;
}

uint32_t Grid::get(std::pair<uint32_t, uint32_t> coord) const
{
    return grid.at(coord.first).at(coord.second);
}

bool Grid::columnCheck(std::pair<uint32_t, uint32_t> coord, uint32_t value) const
{
    uint32_t currRow = 0;
    return std::any_of(grid.begin(), grid.end(),
                       [=, &currRow](const auto &row) -> bool
                       {
                           return (row.at(coord.second) == value) && (coord.first != currRow++);
                       });
}

bool Grid::rowCheck(std::pair<uint32_t, uint32_t> coord, uint32_t value) const
{
    uint32_t currCol = 0;
    return std::any_of(grid.at(coord.first).begin(), grid.at(coord.first).end(),
                       [=, &currCol](uint32_t cell) -> bool
                       {
                           return (cell == value) && (coord.second != currCol++);
                       });
}

bool Grid::squareCheck(std::pair<uint32_t, uint32_t> coord, uint32_t value) const
{
    uint32_t rowStart = (coord.first / 3) * 3, colStart = (coord.second / 3) * 3;
    uint32_t rowEnd = (rowStart + 2), colEnd = (colStart + 2);

    for (uint32_t row = rowStart; row <= rowEnd; row++)
    {
        for (uint32_t col = colStart; col <= colEnd; col++)
        {
            if ((std::make_pair(row, col) != coord) && (grid.at(row).at(col) == value))
            {
                return true;
            }
        }
    }
    return false;
}

bool Grid::coordGiven(std::pair<uint32_t, uint32_t> coord) const
{
    return currentCoords.find(coord) != currentCoords.end();
}

std::vector<uint32_t> Grid::getPossibleValues(std::pair<uint32_t, uint32_t> coord)
{
    std::vector<uint32_t> values(n);
    std::iota(values.begin(), values.end(), 1);
    std::vector<uint32_t> filtered(n);

    auto it = std::copy_if(values.begin(), values.end(), filtered.begin(),
                           [this, coord](uint32_t value) -> bool
                           {
                               return !(this->columnCheck(coord, value) || this->rowCheck(coord, value) || this->squareCheck(coord, value));
                           });

    filtered.resize(std::distance(filtered.begin(), it));
    return filtered;
}

bool Grid::operator==(const Grid &grid) const
{
    for (uint32_t row = 0; row < n; row++)
        for (uint32_t col = 0; col < n; col++)
        {
            auto coord = std::make_pair(row, col);
            if (get(coord) != grid.get(coord))
                return false;
        }
    return true;
}

std::ostream &operator<<(std::ostream &out, Grid grid)
{
    out << "+-------+-------+-------+\n";
    for (uint32_t row = 0; row < grid.n; row++)
    {
        out << "|";
        for (uint32_t col = 0; col < grid.n; col++)
        {
            out << " " << grid.grid[row][col];
            if (col % 3 == 2)
                out << " |";
        }
        out << "\n";
        if (row % 3 == 2)
            out << "+-------+-------+-------+\n";
    }
    return out;
}

int main()
{
    Grid grid;
    grid.importGridFromFile("grid.txt");
    std::cout << grid;
    return 0;
}