#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

class cell{
public:
    char type;
    bool cleaned;
    int distance;
};
class pair{
public:
    pair(const int & row, const int & col){
        row_idx = row;
        col_idx = col;
    }
    int row_idx;
    int col_idx;
};
void read_map(cell * map, const int & row, const int & column, int & R_row, int & R_col){
    for (int i = 0; i < row; i ++){
        for (int j = 0; j < column; j ++){
            std::cin >> map[i * column + j].type;
            map[i * column + j].cleaned = (map[i * column + j].type == '0')? false: true;
            map[i * column + j].distance = -1;
            if (map[i * column + j].type == 'R'){
                R_row = i;
                R_col = j;
            }
        }
    }
}
bool isValid(cell * map, const int & row, const int & column, const int & row_idx, const int & col_idx){
    return (map[row_idx * column + col_idx].type != '1') && (map[row_idx * column + col_idx].type != '1') &&
           (row_idx < row) && (row_idx > 0) && (col_idx < column) && (col_idx > 0);
}
void find_distance(cell * map, const int & row, const int & column, const int & R_row, const int & R_col){
    std::queue<pair> q;
    q.push(pair(R_row, R_col));
    map[R_row * column + R_col].distance = 0;
    while(!q.empty()){
        pair v = q.front();
        int distance = map[v.row_idx * column + v.col_idx].distance + 1; 
        q.pop();
        if (isValid(map, row, column, v.row_idx + 1, v.col_idx) && map[(v.row_idx + 1) * column + v.col_idx].distance == -1){
            q.push(pair(v.row_idx + 1, v.col_idx));
            map[(v.row_idx + 1) * column + v.col_idx].distance = distance;
        }
        if (isValid(map, row, column, v.row_idx - 1, v.col_idx) && map[(v.row_idx - 1) * column + v.col_idx].distance == -1){
            q.push(pair(v.row_idx - 1, v.col_idx));
            map[(v.row_idx - 1) * column + v.col_idx].distance = distance;
        }
        if (isValid(map, row, column, v.row_idx, v.col_idx - 1) && map[v.row_idx * column + v.col_idx - 1].distance == -1){
            q.push(pair(v.row_idx, v.col_idx - 1));
            map[v.row_idx * column + v.col_idx - 1].distance = distance;
        }
        if (isValid(map, row, column, v.row_idx, v.col_idx + 1) && map[v.row_idx * column + v.col_idx + 1].distance == -1){
            q.push(pair(v.row_idx, v.col_idx + 1));
            map[v.row_idx * column + v.col_idx + 1].distance = distance;
        }
    }

}

int main(void){
    int row, column, battery;
    int R_row, R_col;
    std::cin >> row;
    std::cin >> column;
    std::cin >> battery;
    cell map[row][column];
    std::cout << row << " " << column << " " << battery << '\n';
    read_map(&map[0][0], row, column, R_row, R_col);
    find_distance(&map[0][0], row, column, R_row, R_col);
    for (int i = 0; i < row; i ++){
        for (int j = 0; j < column; j ++){
            std::cout << map[i][j].type << ' ';
        }
        std::cout << '\n';
    }
    for (int i = 0; i < row; i ++){
        for (int j = 0; j < column; j ++){
            std::cout << map[i][j].distance << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
