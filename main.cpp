#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#define UNDEF 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
class pair{
public:
    pair(const int & row, const int & col){
        row_idx = row;
        col_idx = col;
    }
    pair(){
        row_idx = 1001;
        col_idx = 1001;
    }
    int row_idx;
    int col_idx;
};

class cell{
public:
    char type;
    bool cleaned;
    int distance;
    int dest_distance;
    pair dest_pair;
};

void read_map(cell * map, const int & row, const int & column, int & R_row, int & R_col){
    for (int i = 0; i < row; i ++){
        for (int j = 0; j < column; j ++){
            std::cin >> map[i * column + j].type;
            map[i * column + j].cleaned = (map[i * column + j].type == '0')? false: true;
            map[i * column + j].distance = -1;
            map[i * column + j].dest_distance = -1;
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

bool isValid_path(cell * map, const int & row, const int & column, const int & row_idx, const int & col_idx){
    return (map[row_idx * column + col_idx].type != '1') && (row_idx < row) && (row_idx >= 0) && (col_idx < column) && (col_idx >= 0);
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
            //std::cout << v.row_idx + 1 << " " << v.col_idx << '\n';
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

void find_dest_distance(cell * map, const int & row, const int & column, const int & src_row, const int & src_col, const int & dest_row, const int & dest_col){
    std::queue<pair> q;
    q.push(pair(src_row, src_col));
    map[src_row * column + src_col].dest_distance = 0;
    map[src_row * column + src_col].dest_pair = pair(dest_row, dest_col);
    while(!q.empty()){
        std::cout << "done\n";
        pair v = q.front();
        int distance = map[v.row_idx * column + v.col_idx].dest_distance + 1;
        q.pop();
        if (v.row_idx == dest_row && v.col_idx == dest_col) {
            std::cout << "break";
            break;
        }
        if (isValid(map, row, column, v.row_idx + 1, v.col_idx) && map[(v.row_idx + 1) * column + v.col_idx].dest_pair.row_idx != dest_row && map[(v.row_idx + 1) * column + v.col_idx].dest_pair.col_idx != dest_col){
            q.push(pair(v.row_idx + 1, v.col_idx));
            map[(v.row_idx + 1) * column + v.col_idx].dest_distance = distance;
            map[(v.row_idx + 1) * column + v.col_idx].dest_pair = pair(dest_row, dest_col);

        }
        if (isValid(map, row, column, v.row_idx - 1, v.col_idx) && map[(v.row_idx - 1) * column + v.col_idx].dest_pair.row_idx != dest_row && map[(v.row_idx - 1) * column + v.col_idx].dest_pair.col_idx != dest_col){
            q.push(pair(v.row_idx - 1, v.col_idx));
            map[(v.row_idx - 1) * column + v.col_idx].dest_distance = distance;
            map[(v.row_idx - 1) * column + v.col_idx].dest_pair = pair(dest_row, dest_col);

        }
        if (isValid(map, row, column, v.row_idx, v.col_idx - 1) && map[v.row_idx * column + v.col_idx - 1].dest_pair.row_idx != dest_row && map[v.row_idx * column + v.col_idx - 1].dest_pair.col_idx != dest_col){
            q.push(pair(v.row_idx, v.col_idx - 1));
            map[v.row_idx * column + v.col_idx - 1].dest_distance = distance;
            map[v.row_idx * column + v.col_idx - 1].dest_pair = pair(dest_row, dest_col);
        }
        if (isValid(map, row, column, v.row_idx, v.col_idx + 1) &&map[v.row_idx * column + v.col_idx + 1].dest_pair.row_idx != dest_row && map[v.row_idx * column + v.col_idx + 1].dest_pair.col_idx != dest_col){
            q.push(pair(v.row_idx, v.col_idx + 1));
            map[v.row_idx * column + v.col_idx + 1].dest_distance = distance;
            map[v.row_idx * column + v.col_idx + 1].dest_pair = pair(dest_row, dest_col);
        }
    }
    std::cout << "exit\n";
}

void shortest_path(std::deque<pair> & result, cell * map, const int & row, const int & column, const int & src_row, const int & src_col, const int & dest_row, const int & dest_col){
    pair cur_cell = pair(src_row, src_col);
    int distance = map[cur_cell.row_idx * column + cur_cell.col_idx].distance;
    result.push_back(cur_cell);
    std::cout << cur_cell.row_idx << " " << cur_cell.col_idx << '\n';
    std::cout << dest_row << " " << dest_col << '\n';
    while (cur_cell.row_idx != dest_row || cur_cell.col_idx != dest_col){
        std::cout << "enterrrr\n";
        bool found = false;
        pair result_cell = pair(0 , 0);
        if (isValid_path(map, row, column, cur_cell.row_idx - 1, cur_cell.col_idx) && !found && map[(cur_cell.row_idx - 1) * column + cur_cell.col_idx].distance == distance - 1){
            std::cout << "entereddd\n";
            result_cell.row_idx = cur_cell.row_idx - 1;
            result_cell.col_idx = cur_cell.col_idx;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;

            }
        }
        if (isValid_path(map, row, column, cur_cell.row_idx + 1, cur_cell.col_idx) && !found && map[(cur_cell.row_idx + 1) * column + cur_cell.col_idx].distance == distance - 1){
            std::cout << "enteredsss\n";
            result_cell.row_idx = cur_cell.row_idx + 1;
            result_cell.col_idx = cur_cell.col_idx;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;
            }
        }
        if (isValid_path(map, row, column, cur_cell.row_idx, cur_cell.col_idx + 1) && !found && map[cur_cell.row_idx * column + cur_cell.col_idx + 1].distance == distance - 1){
            result_cell.row_idx = cur_cell.row_idx;
            result_cell.col_idx = cur_cell.col_idx + 1;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;
            }
        }
        if (isValid_path(map, row, column, cur_cell.row_idx, cur_cell.col_idx - 1) && !found && map[cur_cell.row_idx * column + cur_cell.col_idx - 1].distance == distance - 1){
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
        std::cout << cur_cell.row_idx << " " << cur_cell.col_idx << '\n';
        distance --;
    }
}
void shortest_dest_path(std::deque<pair> & result, cell * map, const int & row, const int & column, const int & src_row, const int & src_col, const int & dest_row, const int & dest_col){
    pair cur_cell = pair(src_row, src_col);
    std::cout << "enter" << src_row << " " << src_col << '\n';
    int distance = map[cur_cell.row_idx * column + cur_cell.col_idx].dest_distance;
    std::cout << distance << '\n';
    result.push_back(cur_cell);
    while (cur_cell.row_idx != dest_row || cur_cell.col_idx != dest_col){
        //std::cout << "done\n";
        //std::cout << cur_cell.row_idx << " " << cur_cell.col_idx << '\n';
        bool found = false;
        pair result_cell = pair(0 , 0);
        if (isValid(map, row, column, cur_cell.row_idx - 1, cur_cell.col_idx) && !found && map[(cur_cell.row_idx - 1) * column + cur_cell.col_idx].dest_distance == distance - 1 /*&& map[(cur_cell.row_idx - 1) * column + cur_cell.col_idx].dest_pair.row_idx == dest_row && map[(cur_cell.row_idx - 1) * column + cur_cell.col_idx].dest_pair.col_idx == dest_col*/){
            result_cell.row_idx = cur_cell.row_idx - 1;
            result_cell.col_idx = cur_cell.col_idx;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;

            }
        }
        if (isValid(map, row, column, cur_cell.row_idx + 1, cur_cell.col_idx) && !found && map[(cur_cell.row_idx + 1) * column + cur_cell.col_idx].dest_distance == distance - 1 /*&& map[(cur_cell.row_idx + 1) * column + cur_cell.col_idx].dest_pair.row_idx == dest_row && map[(cur_cell.row_idx + 1) * column + cur_cell.col_idx].dest_pair.col_idx == dest_col*/){
            result_cell.row_idx = cur_cell.row_idx + 1;
            result_cell.col_idx = cur_cell.col_idx;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;
            }
        }
        if (isValid(map, row, column, cur_cell.row_idx, cur_cell.col_idx + 1) && !found && map[cur_cell.row_idx * column + cur_cell.col_idx + 1].dest_distance == distance - 1 /*&& map[cur_cell.row_idx * column + cur_cell.col_idx + 1].dest_pair.row_idx == dest_row && map[cur_cell.row_idx * column + cur_cell.col_idx + 1].dest_pair.col_idx == dest_col*/){
            result_cell.row_idx = cur_cell.row_idx;
            result_cell.col_idx = cur_cell.col_idx + 1;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;
            }
        }
        if (isValid(map, row, column, cur_cell.row_idx, cur_cell.col_idx - 1) && !found && map[cur_cell.row_idx * column + cur_cell.col_idx - 1].dest_distance == distance - 1 /*&& map[cur_cell.row_idx * column + cur_cell.col_idx + 1].dest_pair.row_idx == dest_row && map[cur_cell.row_idx * column + cur_cell.col_idx + 1].dest_pair.col_idx == dest_col*/){
            result_cell.row_idx = cur_cell.row_idx;
            result_cell.col_idx = cur_cell.col_idx - 1;
            if (map[result_cell.row_idx * column + result_cell.col_idx].cleaned == false){
                found = true;
                map[result_cell.row_idx * column + result_cell.col_idx].cleaned = true;
            }
        }
        cur_cell.row_idx = result_cell.row_idx;
        cur_cell.col_idx = result_cell.col_idx;
        //std::cout << cur_cell.row_idx << " " << cur_cell.col_idx << '\n';
        result.push_back(result_cell);
        distance --;
    }
    std::cout << "exit\n";
}

int main(void){
    int row, column, battery;
    int R_row, R_col;
    int direction = UNDEF;
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
                std::deque<pair> tmp_result;
                if (direction == UNDEF){
                    shortest_path(tmp_result, &map[0][0], row, column, i, j, R_row, R_col);
                }
                else {
                    result.push(pair(R_row, R_col));
                    switch (direction) {
                        int cr, cc;
                        case UP:
                            std::cout << "up\n";
                            find_dest_distance(&map[0][0], row, column, R_row - 1, R_col, i, j);
                            shortest_dest_path(tmp_result, &map[0][0], row, column, i, j, R_row - 1, R_col);
                            break;
                        case DOWN:
                            std::cout << "down\n";
                            find_dest_distance(&map[0][0], row, column, R_row + 1, R_col, i, j);
                            shortest_dest_path(tmp_result, &map[0][0], row, column, i, j, R_row + 1, R_col);
                            break;
                        case LEFT:
                            std::cout << "left\n";
                            find_dest_distance(&map[0][0], row, column, R_row, R_col - 1, i, j);
                            shortest_dest_path(tmp_result, &map[0][0], row, column, i, j, R_row, R_col - 1);
                            break;
                        case RIGHT:
                            std::cout << "right\n";
                            find_dest_distance(&map[0][0], row, column, R_row, R_col + 1, i, j);
                            for (cr = 0; cr < row; cr ++){
                                for (int cc = 0; cc < column; cc ++){
                                    std::cout << map[cr][cc].dest_distance << ' ';
                                }
                                std::cout << '\n';
                            }
                            shortest_dest_path(tmp_result, &map[0][0], row, column, i, j, R_row, R_col + 1);
                            break;
                    }
                }
                tmp_result.pop_front();
                while (!tmp_result.empty()){
                    result.push(tmp_result.back());
                    tmp_result.pop_back();

                }
                shortest_path(tmp_result, &map[0][0], row, column, i, j, R_row, R_col);
                tmp_result.pop_back();
                while (!tmp_result.empty()){
                    result.push(tmp_result.front());
                    tmp_result.pop_front();
                }
                if (result.front().row_idx == R_row - 1 && result.front().col_idx == R_col){
                    direction = UP;
                }
                else if (result.front().row_idx == R_row + 1 && result.front().col_idx == R_col){
                    direction = DOWN;
                }
                else if (result.front().row_idx == R_row && result.front().col_idx == R_col - 1){
                    direction = LEFT;
                }
                else{
                    direction = RIGHT;
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
