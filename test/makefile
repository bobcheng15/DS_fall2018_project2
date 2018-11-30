all:main

main:main.o
	g++ -o main main.o -lgtest
main.o:main.cpp Cell.h utCell.h Pair.h utPair.h Map.h utMap.h
	g++ -std=c++11 -c main.cpp

clean:
	rm -f *.o main
