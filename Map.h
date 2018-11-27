#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "Cell.h"
class Map{
public:
    Map(const int & input_row, const int & input_column){
        row = input_row;
        column = input_column;
        map = new Cell *[row];
        for (int i = 0; i < row; i++){
            map[i] = new Cell[column];
        }


    }
    void read_map(char * input){
        int idx = 0;
        for (int i = 0; i < row; i ++){
            for (int j = 0; j < column; j ++){
                map[i][j].type = input[idx];
                map[i][j].cleaned = (map[i][j].type == '0')? false: true;
                map[i][j].distance = -1;
                map[i][j].dest_distance = -1;
                if (map[i][j].type == 'R'){
                    origin = new Pair(i, j);
                }
                idx ++;
            }
        }
    }
    int row;
    int column;
    Pair *origin;
    Cell ** map;
};




#endif
