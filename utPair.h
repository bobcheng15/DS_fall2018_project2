#ifndef UTPAIR_H_INCLUDED
#define UTPAIR_H_INCLUDED
#include "Pair.h"
TEST(Pair, testPairConstructor){
    Pair test(0, 1);
    EXPECT_EQ(test.row_idx, 0);
    EXPECT_EQ(test.col_idx, 1);
}


TEST(Pair, equalOperatorOverload){
    Pair test1(12, 12);
    Pair test2(12, 12);
    Pair test3(12, 13);
    EXPECT_TRUE(test1 == test2);
    EXPECT_FALSE(test1 == test3);
}





#endif
