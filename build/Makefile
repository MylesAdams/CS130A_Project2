#variables
FLAGS=-c -std=c++11 -O2

all: main

main: main.o AVLTree.o TwoFiveTree.o
	g++ -o main main.o AVLTree.o TwoFiveTree.o

main.o: ../src/main.cpp
	g++ $(FLAGS) ../src/main.cpp

AVLTree.o: ../src/AVLTree.cpp
	g++ $(FLAGS) ../src/AVLTree.cpp

TwoFiveTree.o: ../src/TwoFiveTree.cpp
	g++ $(FLAGS) ../src/TwoFiveTree.cpp

clean:
	rm -rf *o main *~ ../sort.txt
