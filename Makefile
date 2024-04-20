all: a.out

a.out: backtrack_solver.cpp sudoku.cpp solver.cpp
	g++-10 -g -Wall -Werror -std=c++20 backtrack_solver.cpp sudoku.cpp solver.cpp

clean:
	rm a.out
