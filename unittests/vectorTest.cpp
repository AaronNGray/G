//
//  PG/UnitTests/vectorTest.cpp
//
//  Property and Copyright (c) 2022 Aaron Nathaniel Gray
//

#include "nonstd/vector.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(vector, resize_base0Test) {
    vector<int> v;

    v.resize(10);
	v[0] = 0;
	v[1] = 1;
    v[2] = 2;
    v[3] = 3;
    v[4] = 4;
    v[5] = 5;
    v[6] = 6;
    v[7] = 7;
    v[8] = 8;
    v[9] = 9;

	EXPECT_TRUE(v.size() == 10);

	for (unsigned i = v.base(); i < v.base() + v.size(); ++i)
		EXPECT_TRUE(v[i] == i);
}

TEST(vector, resize_base1Test) {
	vector<int, 1> v;

	v.resize(10);
	v[1] = 1;
	v[2] = 2;
	v[3] = 3;
	v[4] = 4;
	v[5] = 5;
	v[6] = 6;
	v[7] = 7;
	v[8] = 8;
	v[9] = 9;
	v[10] = 10;

	std::cout << v.toString() << std::endl;

	EXPECT_TRUE(v.size() == 10);

	for (unsigned i = v.base(); i < v.base() + v.size(); ++i)
		EXPECT_TRUE(v[i] == i);
}
