#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "Cell.h"
#include <queue>
#define UNDEF 1
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5
class Map{
public:
    Map(const int & input_row, const int & input_column, const int & input_battery){
        row = input_row;
        column = input_column;
        battery = input_battery;
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
    void find_distance(){
        std::queue<Pair> q;
        q.push(*origin);
        map[origin->row_idx][origin->col_idx].distance = 0;
        while(!q.empty()){
            Pair v = q.front();
            int distance = map[v.row_idx][v.col_idx].distance + 1;
            q.pop();
            if (isValid(v.row_idx + 1, v.col_idx) && map[v.row_idx + 1][v.col_idx].distance == -1){
                q.push(Pair(v.row_idx + 1, v.col_idx));
                map[v.row_idx + 1][v.col_idx].distance = distance;
            }
            if (isValid(v.row_idx - 1, v.col_idx) && map[v.row_idx - 1][v.col_idx].distance == -1){
                q.push(Pair(v.row_idx - 1, v.col_idx));
                map[v.row_idx - 1][v.col_idx].distance = distance;
            }
            if (isValid(v.row_idx, v.col_idx - 1) && map[v.row_idx][v.col_idx - 1].distance == -1){
                q.push(Pair(v.row_idx, v.col_idx - 1));
                map[v.row_idx][v.col_idx - 1].distance = distance;
            }
            if (isValid(v.row_idx, v.col_idx + 1) && map[v.row_idx][v.col_idx + 1].distance == -1){
                q.push(Pair(v.row_idx, v.col_idx + 1));
                map[v.row_idx][v.col_idx + 1].distance = distance;
            }
        }
    }
    void find_distance_to_src(const int & src_row, const int & src_col){
        std::queue<Pair> q;
        q.push(Pair(src_row, src_col));
        map[src_row][src_col].dest_distance = 0;
        map[src_row][src_col].src_pair->row_idx = src_row;
        map[src_row][src_col].src_pair->col_idx = src_col;
        while(!q.empty()){
            Pair v = q.front();
            int distance = map[v.row_idx][v.col_idx].dest_distance + 1;
            q.pop();
            if (isValid(v.row_idx + 1, v.col_idx) && !(*map[v.row_idx + 1][v.col_idx].src_pair == Pair(src_row, src_col))){
                map[v.row_idx + 1][v.col_idx].src_pair->row_idx = src_row;
                map[v.row_idx + 1][v.col_idx].src_pair->col_idx = src_col;
                q.push(Pair(v.row_idx + 1, v.col_idx));
                map[v.row_idx + 1][v.col_idx].dest_distance = distance;
            }
            if (isValid(v.row_idx - 1, v.col_idx) && !(*map[v.row_idx - 1][v.col_idx].src_pair == Pair(src_row, src_col))){
                map[v.row_idx - 1][v.col_idx].src_pair->row_idx = src_row;
                map[v.row_idx - 1][v.col_idx].src_pair->col_idx = src_col;
                q.push(Pair(v.row_idx - 1, v.col_idx));
                map[v.row_idx - 1][v.col_idx].dest_distance = distance;
            }
            if (isValid(v.row_idx, v.col_idx - 1) && !(*map[v.row_idx][v.col_idx - 1].src_pair == Pair(src_row, src_col))){
                map[v.row_idx][v.col_idx - 1].src_pair->row_idx = src_row;
                map[v.row_idx][v.col_idx - 1].src_pair->col_idx = src_col;
                q.push(Pair(v.row_idx, v.col_idx - 1));
                map[v.row_idx][v.col_idx - 1].dest_distance = distance;
            }
            if (isValid(v.row_idx, v.col_idx + 1) && !(*map[v.row_idx][v.col_idx + 1].src_pair == Pair(src_row, src_col))){
                map[v.row_idx][v.col_idx + 1].src_pair->row_idx = src_row;
                map[v.row_idx][v.col_idx + 1].src_pair->col_idx = src_col;
                q.push(Pair(v.row_idx, v.col_idx + 1));
                map[v.row_idx][v.col_idx + 1].dest_distance = distance;
            }
        }
    }
    void shortest_path_to_origin(std::deque<Pair> & result, int & src_row, const int & src_col){
        Pair cur_cell = Pair(src_row, src_col);
        result.push_back(cur_cell);
        map[src_row][src_col].cleaned = true;
        while (map[cur_cell.row_idx][cur_cell.col_idx].distance != 1){
            int distance = map[cur_cell.row_idx][cur_cell.col_idx].distance;
            bool found = false;
            Pair result_cell(-1, -1);
            if (isValid(cur_cell.row_idx - 1, cur_cell.col_idx) && !found && map[cur_cell.row_idx - 1][cur_cell.col_idx].distance == distance - 1){
                result_cell.row_idx = cur_cell.row_idx - 1;
                result_cell.col_idx = cur_cell.col_idx;
                if (map[result_cell.row_idx][result_cell.col_idx].cleaned == false){
                    found = true;
                    map[result_cell.row_idx][result_cell.col_idx].cleaned = true;

                }
            }
            if (isValid(cur_cell.row_idx + 1, cur_cell.col_idx) && !found && map[cur_cell.row_idx + 1][cur_cell.col_idx].distance == distance - 1){
                result_cell.row_idx = cur_cell.row_idx + 1;
                result_cell.col_idx = cur_cell.col_idx;
                if (map[result_cell.row_idx][result_cell.col_idx].cleaned == false){
                    found = true;
                    map[result_cell.row_idx][result_cell.col_idx].cleaned = true;
                }
            }
            if (isValid(cur_cell.row_idx, cur_cell.col_idx + 1) && !found && map[cur_cell.row_idx][cur_cell.col_idx + 1].distance == distance - 1){
                result_cell.row_idx = cur_cell.row_idx;
                result_cell.col_idx = cur_cell.col_idx + 1;
                if (map[result_cell.row_idx][result_cell.col_idx].cleaned == false){
                    found = true;
                    map[result_cell.row_idx][result_cell.col_idx].cleaned = true;
                }
            }
            if (isValid(cur_cell.row_idx, cur_cell.col_idx - 1) && !found && map[cur_cell.row_idx][cur_cell.col_idx - 1].distance == distance - 1){
                result_cell.row_idx = cur_cell.row_idx;
                result_cell.col_idx = cur_cell.col_idx - 1;
                if (map[result_cell.row_idx][result_cell.col_idx].cleaned == false){
                    found = true;
                    map[result_cell.row_idx][result_cell.col_idx].cleaned = true;
                }
            }
            cur_cell.row_idx = result_cell.row_idx;
            cur_cell.col_idx = result_cell.col_idx;
            result.push_back(result_cell);
        }
    }
    void shortest_path_to_dest(std::deque<Pair> & result, const int & dest_row, const int & dest_col){
        Pair cur_cell = Pair(dest_col, dest_row);
        while(map[cur_cell.row_idx][cur_cell.col_idx].dest_distance != 0){
            int distance = map[cur_cell.row_idx][cur_cell.col_idx].dest_distance;
            bool found = false;
            Pair result_cell(-1, -1);
            if (isValid(cur_cell.row_idx - 1, cur_cell.col_idx) && !found && map[cur_cell.row_idx - 1][cur_cell.col_idx].dest_distance == distance - 1){
                result_cell.row_idx = cur_cell.row_idx - 1;
                result_cell.col_idx = cur_cell.col_idx;
                if (map[result_cell.row_idx][result_cell.col_idx].cleaned == false){
                    found = true;
                    map[result_cell.row_idx][result_cell.col_idx].cleaned = true;

                }
            }
            if (isValid(cur_cell.row_idx + 1, cur_cell.col_idx) && !found && map[cur_cell.row_idx + 1][cur_cell.col_idx].dest_distance == distance - 1){
                result_cell.row_idx = cur_cell.row_idx + 1;
                result_cell.col_idx = cur_cell.col_idx;
                if (map[result_cell.row_idx][result_cell.col_idx].cleaned == false){
                    found = true;
                    map[result_cell.row_idx][result_cell.col_idx].cleaned = true;
                }
            }
            if (isValid(cur_cell.row_idx, cur_cell.col_idx + 1) && !found && map[cur_cell.row_idx][cur_cell.col_idx + 1].dest_distance == distance - 1){
                result_cell.row_idx = cur_cell.row_idx;
                result_cell.col_idx = cur_cell.col_idx + 1;
                if (map[result_cell.row_idx][result_cell.col_idx].cleaned == false){
                    found = true;
                    map[result_cell.row_idx][result_cell.col_idx].cleaned = true;
                }
            }
            if (isValid(cur_cell.row_idx, cur_cell.col_idx - 1) && !found && map[cur_cell.row_idx][cur_cell.col_idx - 1].dest_distance == distance - 1){
                result_cell.row_idx = cur_cell.row_idx;
                result_cell.col_idx = cur_cell.col_idx - 1;
                if (map[result_cell.row_idx][result_cell.col_idx].cleaned == false){
                    found = true;
                    map[result_cell.row_idx][result_cell.col_idx].cleaned = true;
                }
            }
            cur_cell.row_idx = result_cell.row_idx;
            cur_cell.col_idx = result_cell.col_idx;
            result.push_back(result_cell);
        }
    }
    void detect_direction(const Pair & input){
        if (input.row_idx == origin->row_idx - 1 && input.col_idx == origin->col_idx){
            direction = UP;
        }
        else if (input.row_idx == origin->row_idx + 1 && input.col_idx == origin->col_idx){
            direction = DOWN;
        }
        else if (input.row_idx == origin->row_idx && input.col_idx == origin->col_idx - 1){
            direction = LEFT;
        }
        else if (input.row_idx == origin->row_idx && input.col_idx == origin->col_idx + 1){
            direction = RIGHT;
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
    int battery;
    int direction = UNDEF;
};




#endif
