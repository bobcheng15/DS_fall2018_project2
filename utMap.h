#ifndef UTMAP_H_INCLUDED
#define UTMAP_H_INCLUDED
#include "Map.h"
#include <queue>
TEST(Map, MapConstructor){
    Map test (2, 2, 14);
    EXPECT_EQ(test.row, 2);
    EXPECT_EQ(test.column, 2);
    EXPECT_EQ(test.battery, 14);
    char input[4] = {'1', '1', '1', 'R'};
    test.read_map(input);
    EXPECT_TRUE(test.map[0][0].type == '1');
    EXPECT_TRUE(test.map[0][1].type == '1');
    EXPECT_TRUE(test.map[1][0].type == '1');
    EXPECT_TRUE(test.map[1][1].type == 'R');
    EXPECT_TRUE(*(test.origin) == Pair(1, 1));
    EXPECT_EQ(test.direction, UNDEF);
}

TEST(Map, isValid){
    Map test(2, 2, 14);
    char input[4] = {'1', '0', '0', 'R'};
    test.read_map(input);
    EXPECT_EQ(test.map[0][0].type, '1');
    EXPECT_FALSE(test.isValid(0 , 0));
    EXPECT_TRUE(test.isValid(0, 1));
    EXPECT_TRUE(test.isValid(1, 0));
    EXPECT_FALSE(test.isValid(1, 1));
    EXPECT_FALSE(test.isValid(-1, 0));
    EXPECT_FALSE(test.isValid(0, -1));
    EXPECT_FALSE(test.isValid(-1, 1));
    EXPECT_FALSE(test.isValid(0, 2));

}
TEST(Map, find_distance){
    Map test(2, 2, 14);
    char input[4] = {'0', '0', '0', 'R'};
    test.read_map(input);
    test.find_distance();
    EXPECT_EQ(test.map[0][0].distance, 2);
    EXPECT_EQ(test.map[0][1].distance, 1);
    EXPECT_EQ(test.map[1][0].distance, 1);
    EXPECT_EQ(test.map[1][1].distance, 0);
}

TEST(Map, find_distance2){
    Map test(3, 3, 14);
    char input[9] = {'0', '0', '0', '1', '1', '0', 'R', '0', '0'};
    test.read_map(input);
    test.find_distance();
    EXPECT_EQ(test.map[0][0].distance, 6);
    EXPECT_EQ(test.map[0][1].distance, 5);
    EXPECT_EQ(test.map[0][2].distance, 4);
    EXPECT_EQ(test.map[1][0].distance, -1);
    EXPECT_EQ(test.map[1][1].distance, -1);
    EXPECT_EQ(test.map[1][2].distance, 3);
    EXPECT_EQ(test.map[2][0].distance, 0);
    EXPECT_EQ(test.map[2][1].distance, 1);
    EXPECT_EQ(test.map[2][2].distance, 2);
}

TEST(Map, find_distance3){
    Map test(3, 3, 14);
    char input[9] = {'0', '0', '0', '0', '0', '0', 'R', '0', '0'};
    test.read_map(input);
    test.find_distance();
    EXPECT_EQ(test.map[0][0].distance, 2);
    EXPECT_EQ(test.map[0][1].distance, 3);
    EXPECT_EQ(test.map[0][2].distance, 4);
    EXPECT_EQ(test.map[1][0].distance, 1);
    EXPECT_EQ(test.map[1][1].distance, 2);
    EXPECT_EQ(test.map[1][2].distance, 3);
    EXPECT_EQ(test.map[2][0].distance, 0);
    EXPECT_EQ(test.map[2][1].distance, 1);
    EXPECT_EQ(test.map[2][2].distance, 2);
}

TEST(Map, shortest_path_to_origin){
    Map test(3, 3, 14);
    char input[9] = {'0', '0', '0', '1', '1', '0', 'R', '0', '0'};
    test.read_map(input);
    test.find_distance();
    std::deque<Pair> result;
    int row_idx = 0;
    int col_idx = 0;
    test.shortest_path_to_origin(result, row_idx, col_idx);
    EXPECT_TRUE(result.front() == Pair(0, 0));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(0, 1));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(0, 2));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(1, 2));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(2, 2));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(2, 1));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
}

TEST(Map, find_distance_to_src){
    Map test(3, 3, 14);
    char input[9] = {'0', '0', '0', '0', '0', '0', 'R', '0', '0'};
    test.read_map(input);
    test.find_distance();
    int row_idx = 1;
    int col_idx = 0;
    test.find_distance_to_src(row_idx, col_idx);
    EXPECT_EQ(test.map[0][0].dest_distance, 1);
    EXPECT_EQ(test.map[0][1].dest_distance, 2);
    EXPECT_EQ(test.map[0][2].dest_distance, 3);
    EXPECT_EQ(test.map[1][0].dest_distance, 0);
    EXPECT_EQ(test.map[1][1].dest_distance, 1);
    EXPECT_EQ(test.map[1][2].dest_distance, 2);
    EXPECT_EQ(test.map[2][0].dest_distance, -1);
    EXPECT_EQ(test.map[2][1].dest_distance, 2);
    EXPECT_EQ(test.map[2][2].dest_distance, 3);
    EXPECT_TRUE(*test.map[0][0].src_pair == Pair(1, 0));
    EXPECT_TRUE(*test.map[0][1].src_pair == Pair(1, 0));
    EXPECT_TRUE(*test.map[0][2].src_pair == Pair(1, 0));
    EXPECT_TRUE(*test.map[1][0].src_pair == Pair(1, 0));
    EXPECT_TRUE(*test.map[1][1].src_pair == Pair(1, 0));
    EXPECT_TRUE(*test.map[1][2].src_pair == Pair(1, 0));
    EXPECT_TRUE(*test.map[2][0].src_pair == Pair(-1, -1));
    EXPECT_TRUE(*test.map[2][1].src_pair == Pair(1, 0));
    EXPECT_TRUE(*test.map[2][2].src_pair == Pair(1, 0));
}

TEST(Map, shortest_path_to_dest){
    Map test(3, 3, 14);
    char input[9] = {'0', '0', '0', '0', '0', '0', 'R', '0', '0'};
    test.read_map(input);
    test.find_distance();
    int src_row = 1;
    int src_col = 0;
    int dest_row = 2;
    int dest_col = 2;
    test.find_distance_to_src(src_row, src_col);
    std::deque<Pair> result;
    test.shortest_path_to_dest(result, dest_row, dest_col);
    EXPECT_EQ(result.size(), 3);
    EXPECT_TRUE(result.front() == Pair(1, 2));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(1, 1));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(1, 0));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
}

TEST(Map, detect_direction){
    Map test(3, 3, 14);
    char input[9] = {'0', '0', '0', '0', 'R', '0', '0', '0', '0'};
    test.read_map(input);
    EXPECT_EQ(test.direction, UNDEF);
    Pair last_cell(0, 1);
    test.detect_direction(last_cell);
    EXPECT_EQ(test.direction, UP);
    last_cell.row_idx = 2;
    test.detect_direction(last_cell);
    EXPECT_EQ(test.direction, DOWN);
    last_cell.row_idx = 1;
    last_cell.col_idx = 0;
    test.detect_direction(last_cell);
    EXPECT_EQ(test.direction, LEFT);
    last_cell.col_idx = 2;
    test.detect_direction(last_cell);
    EXPECT_EQ(test.direction, RIGHT);
}

TEST(Map, path_finding_and_direction){
    Map test(3, 3, 14);
    char input[9] = {'0', '0', '0', '0', '0', '0', 'R', '0', '0'};
    test.read_map(input);
    test.find_distance();
    int src_row = 1;
    int src_col = 0;
    int dest_row = 2;
    int dest_col = 2;
    test.find_distance_to_src(src_row, src_col);
    std::deque<Pair> result;
    test.shortest_path_to_dest(result, dest_row, dest_col);
    EXPECT_EQ(result.size(), 3);
    EXPECT_TRUE(result.front() == Pair(1, 2));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(1, 1));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(1, 0));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    test.shortest_path_to_origin(result, dest_row, dest_col);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.front() == Pair(2, 2));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(2, 1));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_EQ(test.direction, RIGHT);
}

TEST(Map, outgoing_cell){
    Map test(3, 3, 14);
    char input[9] = {'0', '0', '0', '0', 'R', '0', '0', '0', '0'};
    test.read_map(input);
    test.direction = UP;
    Pair result = test.outgoing_cell();
    EXPECT_TRUE(result == Pair(0, 1));
    test.direction = DOWN;
    result = test.outgoing_cell();
    EXPECT_TRUE(result == Pair(2, 1));
    test.direction = LEFT;
    result = test.outgoing_cell();
    EXPECT_TRUE(result == Pair(1, 0));
    test.direction = RIGHT;
    result = test.outgoing_cell();
    EXPECT_TRUE(result == Pair(1, 2));
}

TEST(Map, valid_dest){
    Map test(3, 3, 4);
    char input[9] = {'0', '0', '0', '0', 'R', '0', '0', '0', '0'};
    test.read_map(input);
    int src_row = 0;
    int src_col = 1;
    int dest_row = 2;
    int dest_col = 1;
    test.find_distance();
    test.find_distance_to_src(src_row, src_col);
    EXPECT_FALSE(test.valid_dest(dest_row, dest_col));
    dest_row = 1;
    dest_col = 2;
    EXPECT_TRUE(test.valid_dest(dest_row, dest_col));
}

TEST(Map, rotate){
    Map test(3, 3, 6);
    char input[9] = {'0', '0', '0', '0', 'R', '1', '0', '0', '0'};
    test.read_map(input);
    test.direction = UP;
    int src_row = 0;
    int src_col = 1;
    test.find_distance_to_src(src_row, src_col);
    EXPECT_TRUE(test.rotate(true) == Pair(-1, -1));
    test.direction = UP;
    EXPECT_TRUE(test.rotate(false) == Pair(1, 0));
    src_row = 1;
    src_col = 0;
    test.direction = LEFT;
    test.find_distance_to_src(src_row, src_col);
    EXPECT_TRUE(test.rotate(true) == Pair(0, 1));
    test.direction = LEFT;
    EXPECT_TRUE(test.rotate(false) == Pair(2, 1));
    src_row = 2;
    src_col = 1;
    test.direction = DOWN;
    test.find_distance_to_src(src_row, src_col);
    EXPECT_TRUE(test.rotate(true) == Pair(1, 0));
    test.direction = DOWN;
    EXPECT_TRUE(test.rotate(false) == Pair(-1, -1));
}
TEST(Map, shortest_path_to_dest2){
    Map test(3, 3, 4);
    char input[9] = {'0', '0', '0', '0', 'R', '0', '0', '0', '0'};
    test.read_map(input);
    int src_row = 0;
    int src_col = 1;
    test.find_distance_to_src(src_row, src_col);
    int dest_row = 1;
    int dest_col = 2;
    std::deque<Pair> result;
    for (int i = 0; i < 3; i ++){
        for (int j = 0; j < 3; j ++){
            std::cout << test.map[i][j].dest_distance << " ";
        }
        std::cout << '\n';
    }
    //std::cout << test.map[dest_row][dest_col].dest_distance << '\n';
    test.shortest_path_to_dest(result, dest_row, dest_col);
    EXPECT_EQ(result.size(), 2);
    std::cout << test.map[1][2].dest_distance << '\n';
    std::cout << result.front().row_idx << " " << result.front().col_idx << '\n';
    std::cout << test.map[result.front().row_idx][result.front().col_idx].dest_distance << '\n';
    std::cout << test.map[0][2].dest_distance << "\n";
    EXPECT_TRUE(result.front() == Pair(0, 2));
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(0, 1));
    result.pop_front();

}
TEST(Map, change_outgoing_cell){
    Map test(3, 3, 4);
    char input[9] = {'0', '0', '0', '0', 'R', '0', '0', '0', '0'};
    test.read_map(input);
    test.find_distance();
    int src_row = 0;
    int src_col = 1;
    test.find_distance_to_src(src_row, src_col);
    test.direction = UP;
    std::queue<Pair> result;
    int dest_row = 2;
    int dest_col = 0;
    test.change_outgoing_cell(result, dest_row, dest_col);
    std::cout << result.size() << '\n';
    EXPECT_EQ(result.size(), 8);
    EXPECT_TRUE(result.front() == Pair(0, 1));
    result.pop();
    EXPECT_TRUE(result.front() == Pair(0, 2));
    result.pop();
    EXPECT_TRUE(result.front() == Pair(1, 2));
    result.pop();
    EXPECT_TRUE(result.front() == Pair(1, 1));
    result.pop();
    EXPECT_TRUE(result.front() == Pair(1, 2));
    result.pop();
    EXPECT_TRUE(result.front() == Pair(2, 2));
    result.pop();
    EXPECT_TRUE(result.front() == Pair(2, 1));
    result.pop();
    EXPECT_TRUE(result.front() == Pair(1, 1));
    result.pop();
}


#endif
