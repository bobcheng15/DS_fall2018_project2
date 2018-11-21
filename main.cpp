#include <iostream>
#include <fstream>
#include <string>
#include <queue>


class cell{
public:
    char type;
    bool cleaned;
};
void read_map(cell * map, const int & row, const int & column){
    for (int i = 0; i < row; i ++){
        for (int j = 0; j < column; j ++){
            std::cin >> map[i * column + j].type;
            map[i * column + j].cleaned = (map[i * column + j].type == '0')? false: true;
        }
    }
}




int main(void){
    int row, column, battery;
    std::cin >> row;
    std::cin >> column;
    std::cin >> battery;
    cell map[row][column];
    std::cout << row << " " << column << " " << battery << '\n';
    read_map(&map[0][0], row, column);
    for (int i = 0; i < row; i ++){
        for (int j = 0; j < column; j ++){
            std::cout << map[i][j].type << ' ';
        }
        std::cout << '\n';
    }
    for (int i = 0; i < row; i ++){
        for (int j = 0; j < column; j ++){
            std::cout << map[i][j].cleaned << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
