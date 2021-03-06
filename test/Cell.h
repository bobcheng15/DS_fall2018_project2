#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED
#include "Pair.h"
class Cell{
public:
    Cell(const char & input){
        type = input;
        cleaned = false;
        distance = -1;
        dest_distance = -1;
        src_pair = new Pair(- 1, -1);
    }
    Cell(){
        type = '0';
        cleaned = false;
        distance = -1;
        dest_distance = -1;
        src_pair = new Pair(-1, -1);
    }
    ~Cell(){
        delete src_pair;
    }
    char type;
    bool cleaned;
    int distance;
    int dest_distance;
    Pair * src_pair;
};
#endif
