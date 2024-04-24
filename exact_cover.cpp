#include "exact_cover.h"
#include <iostream>
#include <unordered_set>

ExactCover::Node::Node() : left(this), right(this), up(this), down(this), row(this), column(this), count(0), rowNum(0)
{
}

ExactCover::ExactCover(size_t cols) : root(nullptr), nodes(), rows(), numRows(0), solution(), isSolved(false)
{

    // add root node to the end of the nodes vector
    nodes.emplace_back(new Node());
    root = nodes.back();

    // add column nodes
    for (size_t i = 0; i < cols; i++)
    {
        nodes.emplace_back(new Node());
        auto prev = nodes.at(nodes.size() - 2);
        auto node = nodes.back();
        prev->right = node;
        node->left = prev;

        node->right = root;
        root->left = node;
    }
}

void ExactCover::addRow(const std::vector<size_t> &subset)
{
    // setup row node
    nodes.emplace_back(new Node());
    auto rowStart = nodes.back();
    rowStart->rowNum = numRows++;
    rows.emplace_back(rowStart);

    for (const auto &col : subset)
    {
        auto prev = nodes.back();
        nodes.emplace_back(new Node());
        auto node = nodes.back();
        auto columnNode = nodes.at(col);

        // seek to the end of the column
        auto current = columnNode;
        while (current->down != columnNode)
        {
            current = current->down;
        }

        // link meta nodes
        node->column = columnNode;
        node->row = rowStart;
        columnNode->count++;

        // link new node vertically
        current->down = node;
        columnNode->up = node;
        node->up = current;
        node->down = columnNode;

        // link new node horizontally
        prev->right = node;
        node->left = prev;
        node->right = rowStart;
        rowStart->left = node;

        // set row number
        node->rowNum = rowStart->rowNum;
    }
}

void ExactCover::initRows(const std::vector<size_t> &rows)
{
    // find all the columns that need to be covered
    std::unordered_set<Node *> columns;
    for (const auto &row : rows)
    {
        solution.push_back(row);
        auto node = this->rows.at(row);
        for (auto current = node->right; current != node; current = current->right)
        {
            columns.insert(current->column);
        }
    }

    // cover all the columns
    for (const auto &column : columns)
    {
        cover(column);
    }
}

void ExactCover::cover(Node *column)
{
    // remove column from header list
    column->right->left = column->left;
    column->left->right = column->right;

    // cover all rows in the column
    for (auto row = column->down; row != column; row = row->down)
    {
        for (auto node = row->right; node != row; node = node->right)
        {
            node->down->up = node->up;
            node->up->down = node->down;
            node->column->count--;
        }
    }
}

void ExactCover::uncover(Node *column)
{
    // uncover all rows in the column
    for (auto row = column->up; row != column; row = row->up)
    {
        for (auto node = row->left; node != row; node = node->left)
        {
            node->column->count++;
            node->down->up = node;
            node->up->down = node;
        }
    }

    // add column back to header list
    column->right->left = column;
    column->left->right = column;
}

ExactCover::Node *ExactCover::findColumnWithLeastNodes()
{
    size_t min = SIZE_MAX;
    Node *minColumn = nullptr;

    for (auto column = root->right; column != root; column = column->right)
    {
        if (column->count < min)
        {
            min = column->count;
            minColumn = column;
        }
    }
    return minColumn;
}

bool ExactCover::search()
{
    // partial solution is complete if there are no columns left
    if (root->right == root)
    {
        return true;
    }

    auto column = findColumnWithLeastNodes();
    cover(column);
    // try each row in the column
    for (auto row = column->down; row != column; row = row->down)
    {
        solution.push_back(row->rowNum);

        // cover all columns that have a 1 in the current row
        for (auto node = row->right; node != row; node = node->right)
        {
            cover(node->column);
        }

        if (search())
        {
            return true;
        }

        // backtrack
        solution.pop_back();
        for (auto node = row->left; node != row; node = node->left)
        {
            uncover(node->column);
        }
    }
    uncover(column);
    return false;
}

std::vector<size_t> ExactCover::solve()
{
    // if the problem has already been solved, return the solution
    if (isSolved)
    {
        return solution;
    }
    else
    {
        isSolved = search();
    }
    return solution;
}

ExactCover::~ExactCover()
{
    for (auto node : nodes)
    {
        delete node;
    }
}