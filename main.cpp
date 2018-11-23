#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <deque>

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
    return (map[row_idx * column + col_idx].type != '1') && (map[row_idx * column + col_idx].type != 'R') &&
           (row_idx < row) && (row_idx >= 0) && (col_idx < column) && (col_idx >= 0);
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
            std::cout << v.row_idx + 1 << " " << v.col_idx << '\n';
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
void shortest_path(std::deque<pair> & result, cell * map, const int & row, const int & column, const int & src_row, const int & src_col, const int & dest_row, const int & dest_col){
    pair cur_cell = pair(src_row, src_col);
    int distance = map[cur_cell.row_idx * column + cur_cell.col_idx].distance;
    result.push_back(cur_cell);
    while (cur_cell.row_idx != dest_row && cur_cell.col_idx != dest_col){
        //std::cout << cur_cell.row_idx << " " << cur_cell.col_idx << '\n';
        bool found = false;
        pair result_cell = pair(0 , 0);
        if (!found && map[(cur_cell.row_idx - 1) * column + cur_cell.col_idx].distance == distance - 1){
            result_cell.row_idx = cur_cell.row_idx - 1;
            result_cell.col_idx = cur_cell.col_idx;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;

            }
        }
        if (!found && map[(cur_cell.row_idx + 1) * column + cur_cell.col_idx].distance == distance - 1){
            result_cell.row_idx = cur_cell.row_idx + 1;
            result_cell.col_idx = cur_cell.col_idx;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;
            }
        }
        if (!found && map[cur_cell.row_idx * column + cur_cell.col_idx + 1].distance == distance - 1){
            result_cell.row_idx = cur_cell.row_idx;
            result_cell.col_idx = cur_cell.col_idx + 1;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;
            }
        }
        if (!found && map[cur_cell.row_idx * column + cur_cell.col_idx - 1].distance == distance - 1){
            result_cell.row_idx = cur_cell.row_idx;
            result_cell.col_idx = cur_cell.col_idx - 1;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;
            }
        }
        cur_cell.row_idx = result_cell.row_idx;
        cur_cell.col_idx = result_cell.col_idx;
        result.push_back(result_cell);
    }
    result.push_back(pair(dest_row, dest_col));
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
    std::queue<pair> result;
    for (int i = 0; i < row; i ++){
        for (int j = 0; j < column; j ++){
            if (map[i][j].type == '0' && map[i][j].cleaned == false){
                std::cout << i << " " << j << '\n';
                std::deque<pair> tmp_result;
                shortest_path(tmp_result, &map[0][0], row, column, i, j, R_row, R_col);

                while (!tmp_result.empty()){
                    result.push(tmp_result.back());
                    tmp_result.pop_back();
                }
                tmp_result.pop_front();
                shortest_path(tmp_result, &map[0][0], row, column, i, j, R_row, R_col);
                while (!tmp_result.empty()){
                    result.push(tmp_result.front());
                    tmp_result.pop_front();
                }
            }
        }
    }
    std::cout << result.size() << '\n';
    while (!result.empty()){
        std::cout << result.front().row_idx << " " << result.front().col_idx << '\n';
        result.pop();
    }
    // for (int i = 0; i < row; i ++){
    //     for (int j = 0; j < column; j ++){
    //         std::cout << map[i][j].type << ' ';
    //     }
    //     std::cout << '\n';
    // }
    // for (int i = 0; i < row; i ++){
    //     for (int j = 0; j < column; j ++){
    //         std::cout << map[i][j].distance << ' ';
    //     }
    //     std::cout << '\n';
    // }
    return 0;
}
