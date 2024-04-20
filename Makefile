all: a.out

a.out: sudoku.cpp
	g++-10 -g -Wall -Werror -std=c++20 sudoku.cpp

clean:
	rm a.out
