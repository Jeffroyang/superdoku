#pragma once
#include <vector>
#include <cstddef>
#include <memory>

class ExactCover
{
private:
    struct Node
    {
        // pointers to adjacent nodes
        Node *left, *right, *up, *down;

        // pointers to start of row and column
        Node *row, *column;

        // count is only used for column nodes to keep track of the number of nodes in the column
        size_t count;

        // row number is only used for row nodes to keep track of the row number
        size_t rowNum;

        Node();
    };

    // root node is a dummy node that points to the first column node
    Node *root;

    // nodes vector stores all nodes in the exact cover matrix
    std::vector<Node *> nodes;

    // rows vector stores the start of each row
    std::vector<Node *> rows;

    // number of rows in the exact cover matrix, used to assign row numbers
    size_t numRows;

    // solution stores the row numbers of the solution
    std::vector<size_t> solution;

    // isSolved is true if a solution has been found
    bool isSolved;

    // covers the column and all rows in the column
    void cover(Node *column);

    // uncovers the column and all rows in the column
    void uncover(Node *column);

    // finds the column with the least number of nodes
    Node *findColumnWithLeastNodes();

    // searches for a solution to the exact cover problem
    bool search();

public:
    // cols is the number of constraints, constraints are 1-indexed
    ExactCover(size_t cols);

    // constraints represent the columns that need to be set to 1
    // columns are 1-indexed
    void addRow(const std::vector<size_t> &subset);

    // rows is a vector of row numbers that are initially covered
    void initRows(const std::vector<size_t> &rows);

    // finds a single solution to the exact cover problem
    std::vector<size_t> solve();

    ~ExactCover();
};