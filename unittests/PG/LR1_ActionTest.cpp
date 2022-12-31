//
//  PG/UnitTests/LR1_ClosureTest.cpp
//
//  Copyright (c) 2016 Aaron Nathaniel Gray under the MIT License
//

#include "lib/ParserGenerator/LR1.h"
#include "gtest/gtest.h"

TEST(LR1_Action, EqualsTest) {
    LR1::ACTION a1(LR1::ACTION::Function::Reduce, 1);
    LR1::ACTION a2(LR1::ACTION::Function::Reduce, 1);

    EXPECT_TRUE(a1 == a2);
}

TEST(LR1_Action, NotEqualsTest) {
    LR1::ACTION a1(LR1::ACTION::Function::Reduce, 1);
    LR1::ACTION a2(LR1::ACTION::Function::Reduce, 2);

    EXPECT_TRUE(a1 != a2);
}
