#ifndef UTMAP_H_INCLUDED
#define UTMAP_H_INCLUDED
#include "Map.h"
TEST(Map, MapConstructor){
    Map test (2, 2);
    EXPECT_EQ(test.row, 2);
    EXPECT_EQ(test.column, 2);
    char input[4] = {'1', '1', '1', 'R'};
    test.read_map(input);
    EXPECT_TRUE(test.map[0][0].type == '1');
    EXPECT_TRUE(test.map[0][1].type == '1');
    EXPECT_TRUE(test.map[1][0].type == '1');
    EXPECT_TRUE(test.map[1][1].type == 'R');
    EXPECT_TRUE(*(test.origin) == Pair(1, 1));

}





#endif
