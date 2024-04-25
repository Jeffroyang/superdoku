all: a.out b.out c.out d.out

a.out: backtrack_solver.cpp sudoku.cpp solver.cpp
	g++-10 -g -Wall -Werror -std=c++20 backtrack_solver.cpp sudoku.cpp solver.cpp -o a.out

b.out: constraint_solver.cpp sudoku.cpp solver.cpp
	g++-10 -g -Wall -Werror -std=c++20 constraint_solver.cpp sudoku.cpp solver.cpp -o b.out

c.out: exact_cover_solver.cpp sudoku.cpp solver.cpp exact_cover.cpp
	g++-10 -g -Wall -Werror -std=c++20 exact_cover_solver.cpp sudoku.cpp solver.cpp exact_cover.cpp -o c.out

d.out: backtrack_solver.cpp constraint_solver.cpp exact_cover_solver.cpp sudoku.cpp solver.cpp exact_cover.cpp
	g++-10 -g -Wall -Werror -std=c++20 main.cpp backtrack_solver.cpp constraint_solver.cpp exact_cover_solver.cpp sudoku.cpp solver.cpp exact_cover.cpp -DMAIN -o d.out

clean:
	rm *.out
