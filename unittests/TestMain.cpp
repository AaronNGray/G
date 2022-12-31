//
//  PG/UnitTests/TestMain.cpp
//
//  Property and Copyright (c) 2022 Aaron Nathaniel Gray
//

#include "gtest/gtest.h"

bool debug = false;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
#ifdef PAUSE
    std::cout << "Press RETURN key to exit !";
    getc(stdin);
#endif
    return ret;
}