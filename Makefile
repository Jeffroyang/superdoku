all: backtrack_solver constraint_solver exact_cover_solver main

backtrack_solver: backtrack_solver.cpp sudoku.cpp solver.cpp
	g++-10 -Wall -Werror -std=c++20 backtrack_solver.cpp sudoku.cpp solver.cpp -o backtrack_solver

constraint_solver: constraint_solver.cpp sudoku.cpp solver.cpp
	g++-10 -Wall -Werror -std=c++20 constraint_solver.cpp sudoku.cpp solver.cpp -o constraint_solver

exact_cover_solver: exact_cover_solver.cpp sudoku.cpp solver.cpp exact_cover.cpp
	g++-10 -Wall -Werror -std=c++20 exact_cover_solver.cpp sudoku.cpp solver.cpp exact_cover.cpp -o exact_cover_solver

main: backtrack_solver.cpp constraint_solver.cpp exact_cover_solver.cpp sudoku.cpp solver.cpp exact_cover.cpp main.cpp
	g++-10 -Wall -Werror -std=c++20 -O3 -DNDEBUG main.cpp backtrack_solver.cpp constraint_solver.cpp exact_cover_solver.cpp sudoku.cpp solver.cpp exact_cover.cpp -DMAIN -o main

clean:
	rm -f backtrack_solver constraint_solver exact_cover_solver main
