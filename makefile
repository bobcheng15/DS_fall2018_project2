all:main

main:main.o
	g++ -o main main.o -lgtest
main.o:main.cpp cell.h ut_cell.h
	g++ -std=c++11 -c main.cpp

clean:
	rm -f *.o main
