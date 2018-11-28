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
    test.shortest_path_to_origin(result, dest_row, dest_col);
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(result.front() == Pair(2, 2));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
    EXPECT_TRUE(result.front() == Pair(2, 1));
    EXPECT_TRUE(test.map[result.front().row_idx][result.front().col_idx].cleaned == true);
    result.pop_front();
}

TEST(Map, detect_direction){
    Map test(3, 3, 14);
    char input[9] = {'0', '0', '0', '0', '0', '0', 'R', '0', '0'};
    test.read_map(input);
    EXPECT_EQ(test.direction, UNDEF);
    Pair last_cell(1, 0);
    test.detect_direction(last_cell);
    EXPECT_EQ(test.direction, UP);
}






#endif
