all: a.out

a.out: grid.cpp 
	g++-10 -g -Wall -Werror -std=c++20 grid.cpp

clean:
	rm a.out
