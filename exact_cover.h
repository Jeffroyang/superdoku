#pragma once
#include <vector>
#include <cstddef>
#include <memory>

class ExactCover
{
private:
    struct Node
    {
        Node *left, *right, *up, *down;
        // pointers to start of row and column
        Node *row, *column;
        // count is only used for column nodes to keep track of the number of nodes in the column
        size_t count;

        size_t rowNum;

        Node();
    };

    Node *root;

    std::vector<Node *> nodes;

    std::vector<Node *> rows;

    size_t cols;

    size_t numRows;

    std::vector<size_t> solution;

    bool isSolved;

    void unlink(Node *node);

    void cover(Node *column);

    void uncover(Node *column);

    Node *findColumnWithLeastNodes();

    bool search();

public:
    // cols is the number of constraints, constraints are 1-indexed
    ExactCover(size_t cols);

    // constraints represent the columns that need to be set to 1
    // columns are 1-indexed
    void addRow(const std::vector<size_t> &subset);

    void initRows(const std::vector<size_t> &rows);

    // finds a single solution to the exact cover problem
    std::vector<size_t> solve();

    ~ExactCover();
};