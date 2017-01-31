all:
	g++ main.cpp solver.cpp clause.cpp atom.cpp -o solver.o
basic:
	g++ main.cpp solver_basic.cpp clause.cpp atom.cpp -o solver_basic.o
