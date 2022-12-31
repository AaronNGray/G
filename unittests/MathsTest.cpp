//
//  UnitTests/MathsTest.cpp
//
//  Property and Copyright (c) 2022 Aaron Nathaniel Gray
//

#include "nonstd/maths.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(Utils, log_ceiling_test) {
    EXPECT_TRUE(nonstd::log_ceiling(5, 10) == 2);
    EXPECT_TRUE(nonstd::log_ceiling(77, 10) == 3);
}
