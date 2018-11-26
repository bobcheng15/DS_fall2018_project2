#ifndef UTCELL_H_INCLUDED
#define UTCELL_H_INCLUDED
#include "Cell.h"
#include "Pair.h"
TEST(Cell, testCellConstructor){
    Cell test('1');
    EXPECT_EQ(test.type, '1');
    EXPECT_EQ(test.cleaned, false);
    EXPECT_EQ(test.distance, -1);
    EXPECT_EQ(test.dest_distance, -1);
    EXPECT_TRUE(*(test.dest_pair) == Pair(-1, -1));
}


#endif
