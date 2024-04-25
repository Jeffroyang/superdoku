#include "constraint_solver.hpp"

using namespace std;

ConstraintSolver::ConstraintSolver(array<array<vector<int>, GRID_SIZE>, GRID_SIZE> other_board) : board(other_board) {}

bool ConstraintSolver::is_solved() {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (board[row][col].size() != 1) return false;
        }
    }
    return true;
}

void ConstraintSolver::populate_grid() {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (board[row][col].size() == 1) game->update(row, col, (board[row][col][0] + '0'));
        }
    }
}

deque<pair<pair<int, int>, pair<int, int>>> ConstraintSolver::get_arcs() {
    deque<pair<pair<int, int>, pair<int, int>>> arcs;
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            // Create arcs for each 3x3 subgrid
            for (int i = (row/3)*3; i < (row/3)*3 + 3; i++) {
                for (int j = (col/3)*3; j < (col/3)*3 + 3; j++) {
                    if (i != row || j != col) {
                        if (board[i][j].size() == 1) {
                            arcs.push_back(make_pair(make_pair(row, col), make_pair(i, j)));
                        }
                    }
                }
            }
            // Create arcs for each row
            for (int i = 0; i < GRID_SIZE; i++) {
                if (i < (row/3)*3 || i >= (row/3)*3 + 3) {
                    if (board[i][col].size() == 1) {
                        arcs.push_back(make_pair(make_pair(row, col), make_pair(i, col)));
                    }
                }
            }
            // Create arcs for each column
            for (int j = 0; j < GRID_SIZE; j++) {
                if (j < (col/3)*3 || j >= (col/3)*3 + 3) {
                    if (board[row][j].size() == 1) {
                        arcs.push_back(make_pair(make_pair(row, col), make_pair(row, j)));
                    }
                }
            }
        }
    }
    return arcs;
}

void ConstraintSolver::ac3_successors(deque<pair<pair<int, int>, pair<int, int>>>& queue, pair<int, int> start, pair<int, int> end) {
    int row = start.first, col = start.second;
    // Create arcs for each 3x3 subgrid
    for (int i = (row/3)*3; i < (row/3)*3 + 3; i++) {
        for (int j = (col/3)*3; j < (col/3)*3 + 3; j++) {
            if (i != row || j != col) {
                if (i != end.first && j != end.second) {
                    queue.push_back(make_pair(make_pair(i, j), start));
                }
            }
        }
    }
    // Create arcs for each row
    for (int i = 0; i < GRID_SIZE; i++) {
        if (i < (row/3)*3 || i >= (row/3)*3 + 3) {
            if (i != end.first && col != end.second) {
                queue.push_back(make_pair(make_pair(i, col), start));
            }
        }
    }
    // Create arcs for each column
    for (int j = 0; j < GRID_SIZE; j++) {
        if (j < (col/3)*3 || j >= (col/3)*3 + 3) {
            if (row != end.first && j != end.second) {
                queue.push_back(make_pair(make_pair(row, j), start));
            }
        }
    }
}

bool ConstraintSolver::remove_inconsistent(pair<int, int> cell1, pair<int, int> cell2) {
    if (board[cell2.first][cell2.second].size() == 1) {
        auto iter = find(board[cell1.first][cell1.second].begin(), board[cell1.first][cell1.second].end(), board[cell2.first][cell2.second][0]);
        if (iter != board[cell1.first][cell1.second].end()) {
            board[cell1.first][cell1.second].erase(iter);
            return true;
        }
    }
    return false;
}

void ConstraintSolver::infer_ac3() {
    deque<pair<pair<int, int>, pair<int, int>>> queue;
    for (auto element : get_arcs()) {
        queue.push_back(element);
    }
    while (!queue.empty()) {
        pair<int, int> start = queue.front().first;
        pair<int, int> end = queue.front().second;
        queue.pop_front();
        if (is_solved()) return;
        if (remove_inconsistent(start, end)) {
            ac3_successors(queue, start, end);
        }
    }
}

bool ConstraintSolver::in_arcs(int value, int row, int col) {
    bool rows = false, cols = false, blocks = false;
    // Create arcs for each 3x3 subgrid
    for (int i = (row/3)*3; i < (row/3)*3 + 3; i++) {
        for (int j = (col/3)*3; j < (col/3)*3 + 3; j++) {
            if (i != row || j != col) {
                if (find(board[i][j].begin(), board[i][j].end(), value) != board[i][j].end()) {
                    blocks = true;
                }
            }
        }
    }
    // Create arcs for each row
    for (int i = 0; i < GRID_SIZE; i++) {
        if (i != row) {
            if (find(board[i][col].begin(), board[i][col].end(), value) != board[i][col].end()) {
                rows = true;
            } 
        }
    }
    // Create arcs for each column
    for (int j = 0; j < GRID_SIZE; j++) {
        if (j != col) {
            if (find(board[row][j].begin(), board[row][j].end(), value) != board[row][j].end()) {
                cols = true;
            }
        }
    }
    return blocks && rows && cols;
}

void ConstraintSolver::infer_improved() {
    bool reduced = true;
    while (reduced) {
        reduced = false;
        infer_ac3();
        if (is_solved()) return;
        for (int row = 0; row < GRID_SIZE; row++) {
            for (int col = 0; col < GRID_SIZE; col++) {
                if (board[row][col].size() > 1) {
                    for (auto val : board[row][col]) {
                        if (!in_arcs(val, row, col)) {
                            board[row][col] = {val};
                            reduced = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}

bool ConstraintSolver::is_solvable() {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (board[row][col].empty()) return false;
        }
    }
    return true;
}

pair<int, int> ConstraintSolver::cell_choice() {
    unsigned int min = GRID_SIZE + 1;
    pair<int, int> next_cell = make_pair(-1, -1);
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (board[row][col].size() < min && board[row][col].size() > 1) {
                if (board[row][col].size() == 2) return make_pair(row, col);
                next_cell = make_pair(row, col);
                min = board[row][col].size();
            }
        }
    }
    return next_cell;
}

vector<array<array<vector<int>, GRID_SIZE>, GRID_SIZE>> ConstraintSolver::guess_successors(pair<int, int> next_cell) {
    array<array<vector<int>, GRID_SIZE>, GRID_SIZE> board_copy;
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            board_copy[row][col] = board[row][col];
        }
    }
    vector<array<array<vector<int>, GRID_SIZE>, GRID_SIZE>> output;
    vector<int> potential_cand = board[next_cell.first][next_cell.second];
    for (auto i : potential_cand) {
        board_copy[next_cell.first][next_cell.second] = {i};
        array<array<vector<int>, GRID_SIZE>, GRID_SIZE> result_board;
        for (int row = 0; row < GRID_SIZE; row++) {
            for (int col = 0; col < GRID_SIZE; col++) {
                result_board[row][col] = board_copy[row][col];
            }
        }
        output.push_back(result_board);
    }
    return output;
}

void ConstraintSolver::infer_with_guessing() {
    deque<ConstraintSolver> stack;
    stack.push_back(ConstraintSolver(board));
    while (!stack.empty()) {
        ConstraintSolver frontier = stack.back();
        stack.pop_back();
        frontier.infer_improved();
        if (frontier.is_solved()) {
            this->board = frontier.board;
            return;
        }
        if (frontier.is_solvable()) {
            pair<int, int> next_cell = frontier.cell_choice();
            if (next_cell.first != -1 && next_cell.second != -1) {
                for (auto new_p : frontier.guess_successors(next_cell)) {
                    stack.push_back(ConstraintSolver(new_p));
                }
            }
        }
    }
}

ConstraintSolver::ConstraintSolver(const string &filename) : Solver(filename) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if ((*game)[row][col] == '.') {
                for (int i = 0; i < GRID_SIZE; i++) {
                    board[row][col].push_back(i+1);
                }
            } else {
                board[row][col].push_back((*game)[row][col] - '0');
            }
        }
    }
}

ConstraintSolver::ConstraintSolver(const ConstraintSolver& other) : board(other.board) {}

ConstraintSolver::ConstraintSolver(const Solver &other) : Solver(other) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if ((*game)[row][col] == '.') {
                for (int i = 0; i < GRID_SIZE; i++) {
                    board[row][col].push_back(i+1);
                }
            } else {
                board[row][col].push_back((*game)[row][col] - '0');
            }
        }
    }
}

ConstraintSolver::ConstraintSolver(Solver &&other) : Solver(other) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if ((*game)[row][col] == '.') {
                for (int i = 0; i < GRID_SIZE; i++) {
                    board[row][col].push_back(i+1);
                }
            } else {
                board[row][col].push_back((*game)[row][col] - '0');
            }
        }
    }
}

void ConstraintSolver::solve()
{
    infer_with_guessing();
    populate_grid();
    std::cout << "Solution found:" << std::endl;
    cout << *game << endl;
}

#ifndef MAIN
#define MAIN
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <sudoku filename>" << endl;
    }

    ConstraintSolver solver(argv[1]);
    solver.solve();

    return 0;
}
#endif