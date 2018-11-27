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
    bool isValid(const int & row_idx, const int & col_idx){
               if((row_idx < row) && (row_idx >= 0) && (col_idx < column) && (col_idx >= 0)){
                   if ((map[row_idx][col_idx].type != '1') && (map[row_idx][col_idx].type != 'R')){
                       return true;
                   }
                   else{
                       return false;
                   }
               }
               else{
                   return false;
               }
    }
    ~Map(){
        delete origin;
        for (int i = 0; i < row; i ++){
            delete [] map[i];
        }
        delete map;
    }
    int row;
    int column;
    Pair *origin;
    Cell ** map;
};




#endif
