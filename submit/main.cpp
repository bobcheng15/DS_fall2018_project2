#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#define UNDEF 1
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5
class Pair{
public:
    Pair(const int & row, const int & col){
        row_idx = row;
        col_idx = col;
    }
    bool operator ==(const Pair & input){
        return (input.row_idx == row_idx) && (input.col_idx == col_idx);
    }
    int row_idx;
    int col_idx;

};
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
        direction = UNDEF;

    }
    void read_map(std::ifstream & input_file){
        int idx = 0;
        for (int i = 0; i < row; i ++){
            for (int j = 0; j < column; j ++){
                input_file >> map[i][j].type;
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
    void shortest_path_to_origin(std::deque<Pair> & result, const int & src_row, const int & src_col){
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
        detect_direction(result.back());
    }
    void shortest_path_to_dest(std::deque<Pair> & result, const int & dest_row, const int & dest_col){
        Pair cur_cell = Pair(dest_row, dest_col);

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
                // std::cout << "down " << cur_cell.row_idx + 1 << " " << cur_cell.col_idx << "\n";
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
    Pair outgoing_cell(){
        if (direction == UP){
            return Pair(origin->row_idx - 1, origin->col_idx);
        }
        else if (direction == DOWN){
            return Pair(origin->row_idx + 1, origin->col_idx);
        }
        else if (direction == LEFT){
            return Pair(origin->row_idx, origin->col_idx - 1);
        }
        else if (direction == RIGHT){
            return Pair(origin->row_idx, origin->col_idx + 1);
        }
        else{
            return Pair(-1, -1);
        }

    }

    bool valid_dest(const int & dest_row, const int & dest_col){
        if (map[dest_row][dest_col].dest_distance + map[dest_row][dest_col].distance + 1 > battery){
            return false;
        }
        else return true;
    }
    void change_outgoing_cell(std::queue<Pair> & result,const int & dest_row, const int & dest_col){
        std::queue<Pair> rotate_result;
        int cur_direction = direction;
        bool found = false;
        for (int i = 0; i < 3; i ++){
            //std::cout << direction << "\n";
            Pair new_src = rotate(true);
            rotate_result.push(new_src);
            if (new_src == Pair(-1, -1)){
                //std::cout << "done\n";
                break;
            }
            find_distance_to_src(new_src.row_idx, new_src.col_idx);
            if (valid_dest(dest_row, dest_col)){
                found = true;
                break;
            }
        }
        direction = cur_direction;
        //std::cout << rotate_result.size() << '\n';
        if (found){
            while(!rotate_result.empty()){
                std::deque<Pair> tmp_result;
                Pair src = outgoing_cell();
                find_distance_to_src(src.row_idx, src.col_idx);
                //std::cout << src.row_idx << " " <<src.col_idx << '\n';
                //std::cout << rotate_result.front().row_idx << " " << rotate_result.front().col_idx << '\n';
                shortest_path_to_dest(tmp_result, rotate_result.front().row_idx, rotate_result.front().col_idx);
                while (!tmp_result.empty()){
                    //std::cout << tmp_result.back().row_idx << " " <<tmp_result.back().col_idx << '\n';
                    result.push(tmp_result.back());
                    tmp_result.pop_back();
                }
                shortest_path_to_origin(tmp_result, rotate_result.front().row_idx, rotate_result.front().col_idx);
                while (!tmp_result.empty()){
                    std::cout << tmp_result.back().row_idx << " " <<tmp_result.back().col_idx << '\n';
                    result.push(tmp_result.back());
                    tmp_result.pop_back();
                }
                result.push(Pair(origin->row_idx, origin->col_idx));
                rotate_result.pop();
            }
        }
        else{
            //std::cout << "enter" << '\n';
            direction = cur_direction;
            //std::cout << direction << '\n';
            while(!rotate_result.empty()) rotate_result.pop();
            for (int i = 0; i < 3; i ++){
                Pair new_src = rotate(false);
                rotate_result.push(new_src);
                if (new_src == Pair(-1, -1)){
                    break;
                }
                find_distance_to_src(new_src.row_idx, new_src.col_idx);
                //std::cout << "now " << new_src.row_idx << " " << new_src.col_idx << '\n';
                //std::cout << map[dest_row][dest_col].dest_distance << "\n";

                if (valid_dest(dest_row, dest_col)){
                    found = true;
                    break;
                }
            }
            if (found){
                direction = cur_direction;
                while(!rotate_result.empty()){
                    std::deque<Pair> tmp_result;
                    Pair src = outgoing_cell();
                    find_distance_to_src(src.row_idx, src.col_idx);
                    shortest_path_to_dest(tmp_result, rotate_result.front().row_idx, rotate_result.front().col_idx);
                    while (!tmp_result.empty()){

                        result.push(tmp_result.back());
                        tmp_result.pop_back();
                    }
                    shortest_path_to_origin(tmp_result, rotate_result.front().row_idx, rotate_result.front().col_idx);
                    while (!tmp_result.empty()){
                        result.push(tmp_result.back());
                        tmp_result.pop_back();
                    }
                    result.push(Pair(origin->row_idx, origin->col_idx));
                    rotate_result.pop();
                }
            }
        }
    }
    Pair rotate(bool clockwise){
        switch (direction) {
            case UP:
                if (clockwise){
                    if (isValid(origin->row_idx, origin->col_idx + 1) && valid_dest(origin->row_idx, origin->col_idx + 1)){
                        direction = RIGHT;
                        return Pair(origin->row_idx, origin->col_idx + 1);
                    }
                    else return Pair(-1, -1);
                }
                else{
                    if (isValid(origin->row_idx, origin->col_idx - 1) && valid_dest(origin->row_idx, origin->col_idx - 1)){
                        direction = LEFT;
                        return Pair(origin->row_idx, origin->col_idx - 1);
                    }
                    else return Pair(-1, -1);
                }
                break;
            case DOWN:
                if (clockwise){
                    if (isValid(origin->row_idx, origin->col_idx - 1) && valid_dest(origin->row_idx, origin->col_idx - 1)){
                        direction = LEFT;
                        return Pair(origin->row_idx, origin->col_idx - 1);
                    }
                    else return Pair(-1, -1);
                }
                else{
                    if (isValid(origin->row_idx, origin->col_idx + 1) && valid_dest(origin->row_idx, origin->col_idx + 1)){
                        direction = RIGHT;
                        return Pair(origin->row_idx, origin->col_idx + 1);
                    }
                    else return Pair(-1, -1);
                }
                break;
            case LEFT:
                if (clockwise){
                    if (isValid(origin->row_idx - 1, origin->col_idx) && valid_dest(origin->row_idx - 1, origin->col_idx)){
                        direction = UP;
                        return Pair(origin->row_idx - 1, origin->col_idx);
                    }
                    else return Pair(-1, -1);
                }
                else{
                    if (isValid(origin->row_idx + 1, origin->col_idx) && valid_dest(origin->row_idx + 1, origin->col_idx)){
                        direction = DOWN;
                        return Pair(origin->row_idx + 1, origin->col_idx);
                    }
                    else return Pair(-1, -1);
                }
            case RIGHT:
                if (clockwise){
                    if (isValid(origin->row_idx + 1, origin->col_idx) && valid_dest(origin->row_idx + 1, origin->col_idx)){
                        direction = DOWN;
                        return Pair(origin->row_idx + 1, origin->col_idx);
                    }
                    else return Pair(-1, -1);
                }
                else{
                    if (isValid(origin->row_idx - 1, origin->col_idx) && valid_dest(origin->row_idx - 1, origin->col_idx)){
                        direction = UP;
                        return Pair(origin->row_idx - 1, origin->col_idx);
                    }
                    else return Pair(-1, -1);
                }
                break;
            default:
                return Pair(-1, -1);
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
    int direction;

};

int main(int argc, char** argv) {
    int row, column, battery;
    std::ifstream input_file;
    std::ofstream output_file;
    std::queue<Pair> result;
    std::deque<Pair> tmp_result;
    input_file.open("./" + std::string(argv[1]) + "/floor.data");
    output_file.open("./" + std::string(argv[1]) + "/final.path");
    input_file >> row;
    input_file >> column;
    input_file >> battery;
    Map floor(row, column, battery);
    floor.read_map(input_file);
    floor.find_distance();
    for (int i = 0; i < row; i ++){
        for (int j = 0; j < column; j ++){
            std::cout << i << " " << j << "\n";
            if (floor.isValid(i, j) && floor.map[i][j].cleaned == false){
                if (floor.direction == UNDEF){
                    floor.shortest_path_to_origin(tmp_result, i, j);
                    tmp_result.pop_front();
                    while(!tmp_result.empty()){
                        result.push(tmp_result.back());
                        tmp_result.pop_back();
                    }
                    floor.shortest_path_to_origin(tmp_result, i, j);
                    while(!tmp_result.empty()){
                        result.push(tmp_result.front());
                        tmp_result.pop_front();
                    }
                }
                else{
                    result.push(Pair(floor.origin->row_idx, floor.origin->col_idx));
                    Pair src = floor.outgoing_cell();
                    floor.find_distance_to_src(src.row_idx, src.col_idx);
                    if (!floor.valid_dest(i, j)){
                        std::cout << "enter\n";
                        floor.change_outgoing_cell(result, i, j);
                    }
                    floor.shortest_path_to_dest(tmp_result, i, j);
                    while (!tmp_result.empty()){
                        result.push(tmp_result.back());
                        tmp_result.pop_back();
                    }
                    floor.shortest_path_to_origin(tmp_result, i, j);
                    while(!tmp_result.empty()){
                        result.push(tmp_result.front());
                        tmp_result.pop_front();
                    }
                }
            }
        }
    }
    result.push(Pair(floor.origin->row_idx, floor.origin->col_idx));
    std::cout << "done\n";
    std::cout << result.size() << '\n';
    output_file << result.size() << '\n';
    while(!result.empty()){
        output_file << result.front().row_idx << " " << result.front().col_idx << '\n';
        result.pop();
    }
    return 0;
}
