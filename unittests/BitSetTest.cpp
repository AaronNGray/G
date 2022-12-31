//
//  PG/UnitTests/BitSetTest.cpp
//
//  Property and Copyright (c) 2022 Aaron Nathaniel Gray
//

#include "nonstd/bitset.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace nonstd;

TEST(bitset, SetAndClearBit) {
	bitset bs;

	bs.set(1);

	EXPECT_FALSE(bs[0]);
	EXPECT_TRUE(bs[1]);
	EXPECT_FALSE(bs[2]);

	bs.clear(1);
	EXPECT_FALSE(bs[1]);
}

TEST(bitset, InvertBit) {
	bitset bs;

	EXPECT_FALSE(bs[1]);

	bs.invert(1);

	EXPECT_TRUE(bs[1]);
}

TEST(bitset, SetAll) {
	bitset bs;

	bs.setAll();

	EXPECT_TRUE(bs[0]);
	EXPECT_TRUE(bs[1]);
	EXPECT_TRUE(bs[2]);
}

TEST(bitset, ClearAll) {
	bitset bs;

	bs.clearAll();
	EXPECT_FALSE(bs[0]);
	EXPECT_FALSE(bs[1]);
	EXPECT_FALSE(bs[2]);
}

TEST(bitset, InvertAll) {
	{
		bitset bs;

		EXPECT_FALSE(bs[0]);
		EXPECT_FALSE(bs[1]);
		EXPECT_FALSE(bs[2]);

		bs.invertAll();

		EXPECT_TRUE(bs[0]);
		EXPECT_TRUE(bs[1]);
		EXPECT_TRUE(bs[2]);
	}
	{
		bitset bs(128);

		for (size_t i = 1; i < 128; i += 2)
			bs.set(i);

		bs.invertAll();

		for (size_t i = 0; i < 128; i += 2)
			EXPECT_TRUE(bs.get(i) == true);

		for (size_t i = 1; i < 128; i += 2)
			EXPECT_TRUE(bs.get(i) == false);

	}
}

TEST(bitset, size) {
	bitset bs;

	EXPECT_EQ(bs.size(), 0);

	bs.set(99);

	EXPECT_EQ(bs.size(), 100);
}

TEST(bitset, isEmpty) {
	bitset bs;

	EXPECT_TRUE(bs.isEmpty());

	bs.set(1);

	EXPECT_FALSE(bs.isEmpty());
}

TEST(bitset, empty) {
	bitset bs;

	bs.setAll();

	bs.set(1);

	bs.empty();

	EXPECT_TRUE(bs.isEmpty());
}


TEST(bitset, Empty) {
	EXPECT_TRUE(bitset::Empty.isEmpty());
}

TEST(bitset, SingletonSet) {
	bitset bs = bitset::SingletonSet(1);

	bool b = bs.get(1);

	EXPECT_TRUE(b);

	EXPECT_TRUE(bitset::SingletonSet(97).get(97));
}

TEST(bitset, Initializer) {
	bitset bs({ 0, 2 });

	EXPECT_TRUE(bs[0] == true);
	EXPECT_TRUE(bs[1] == false);
	EXPECT_TRUE(bs[2] == true);
	EXPECT_TRUE(bs[3] == false);
}

TEST(bitset, Clone) {
	bitset bs(128);

	for (size_t i = 0; i < 128; i += 2) // set all even members
		bs.set(i);

	bitset bs2 = bs;
	
	for (size_t i = 0; i < 128; ++i)
		EXPECT_TRUE(bs.get(i) == bs2.get(i));
}

TEST(bitset, Equal) {
	bitset bs(128);

	for (size_t i = 0; i < 128; i += 2) // set all even members
		bs.set(i);

	bitset bs2 = bs;

	EXPECT_TRUE(bs == bs2);
}

TEST(bitset, NotEqual) {
	bitset bs(128);

	for (size_t i = 0; i < 128; i += 2) // set all even members
		bs.set(i);

	bitset bs2(128);

	for (size_t i = 1; i < 128; i += 2) // set all even members
		bs2.set(i);

	EXPECT_TRUE(bs != bs2);
}

TEST(bitset, Subset) {
	bitset bs(128);

	for (size_t i = 16; i < 112; ++i)
		bs.set(i);

	bitset bs2(128);

	for (size_t i = 32; i < 96; ++i) // create subset
		bs2.set(i);

	EXPECT_TRUE(bs.Subset(bs2));
	EXPECT_TRUE(Subset(bs, bs2));
}

TEST(bitset, Union_Reference) {
	bitset bs(128);

	for (size_t i = 16; i < 64; ++i)
		bs.set(i);

	bitset bs2(128);

	for (size_t i = 64; i < 112; ++i)
		bs2.set(i);

	bitset bs3 = Union(bs, bs2);

	for (size_t i = 0; i < 15; ++i)
		EXPECT_TRUE(bs3.get(i) == false);

	for (size_t i = 16; i < 112; ++i) // create subset
		EXPECT_TRUE(bs3.get(i) == true);

	for (size_t i = 112; i < 128; ++i)
		EXPECT_TRUE(bs3.get(i) == false);
}

TEST(bitset, Union_Pointer) {
	bitset* bs = new bitset(128);

	for (size_t i = 16; i < 64; ++i)
		bs->set(i);

	bitset* bs2 = new bitset(128);

	for (size_t i = 64; i < 112; ++i)
		bs2->set(i);

	bitset* bs3 = Union(bs, bs2);

	for (size_t i = 0; i < 15; ++i)
		EXPECT_TRUE(bs3->get(i) == false);

	for (size_t i = 16; i < 112; ++i) // create subset
		EXPECT_TRUE(bs3->get(i) == true);

	for (size_t i = 112; i < 128; ++i)
		EXPECT_TRUE(bs3->get(i) == false);
}

TEST(bitset, Intersection_Reference) {
	bitset bs(128);

	for (size_t i = 16; i < 96; ++i)
		bs.set(i);

	bitset bs2(128);

	for (size_t i = 64; i < 112; ++i)
		bs2.set(i);

	bitset bs3 = Intersection(bs, bs2);

	for (size_t i = 0; i < 64; ++i)
		EXPECT_TRUE(bs3.get(i) == false);

	for (size_t i = 64; i < 96; ++i) // create subset
		EXPECT_TRUE(bs3.get(i) == true);

	for (size_t i = 96; i < 128; ++i)
		EXPECT_TRUE(bs3.get(i) == false);
}

TEST(bitset, Intersection_Reference_2) {
	bitset bs(128);

	for (size_t i = 0; i < 128; i += 2)
		bs.set(i);

	bitset bs2(128);

	for (size_t i = 1; i < 128; i += 2)
		bs2.set(i);

	bitset bs3 = Intersection(bs, bs2);

	EXPECT_TRUE(bs3.isEmpty());

	bs2.invertAll();

	bitset bs4 = Intersection(bs, bs2);

	EXPECT_TRUE(bs2 == bs4);
}

TEST(bitset, Intersection_Pointer) {
	bitset* bs = new bitset(128);

	for (size_t i = 16; i < 96; ++i)
		bs->set(i);

	bitset* bs2 = new bitset(128);

	for (size_t i = 64; i < 112; ++i)
		bs2->set(i);

	bitset* bs3 = Intersection(bs, bs2);

	for (size_t i = 0; i < 64; ++i)
		EXPECT_TRUE(bs3->get(i) == false);

	for (size_t i = 64; i < 96; ++i) // create subset
		EXPECT_TRUE(bs3->get(i) == true);

	for (size_t i = 96; i < 128; ++i)
		EXPECT_TRUE(bs3->get(i) == false);
}

TEST(bitset, Intersection_Pointer_2) {
	bitset* bs = new bitset(128);

	for (size_t i = 0; i < 128; i += 2)
		bs->set(i);

	bitset* bs2 = new bitset(128);

	for (size_t i = 1; i < 128; i += 2)
		bs2->set(i);

	bitset* bs3 = Intersection(bs, bs2);

	EXPECT_TRUE(bs3->isEmpty());

	bs2->invertAll();

	bitset* bs4 = Intersection(bs, bs2);

	EXPECT_TRUE(*bs2 == *bs4);
}

TEST(bitset, Operator_Intersection_Equals_Reference) {
    bitset bs(128);

    for (size_t i = 16; i < 96; ++i)
        bs.set(i);

    bitset bs2(128);

    for (size_t i = 64; i < 112; ++i)
        bs2.set(i);

    bs.Intersection(bs2);

    for (size_t i = 0; i < 64; ++i)
        EXPECT_TRUE(bs.get(i) == false);

    for (size_t i = 64; i < 96; ++i) // create subset
        EXPECT_TRUE(bs.get(i) == true);

    for (size_t i = 96; i < 128; ++i)
        EXPECT_TRUE(bs.get(i) == false);
}

TEST(bitset, Difference_Reference) {
	bitset bs(128);

	for (size_t i = 16; i < 96; ++i)
		bs.set(i);

	bitset bs2(128);

	for (size_t i = 64; i < 112; ++i)
		bs2.set(i);

	bitset bs3 = Difference(bs, bs2);

	for (size_t i = 0; i < 16; ++i)
		EXPECT_TRUE(bs3.get(i) == false);

	for (size_t i = 16; i < 64; ++i)
		EXPECT_TRUE(bs3.get(i) == true);

	for (size_t i = 64; i < 96; ++i)
		EXPECT_TRUE(bs3.get(i) == false);

	for (size_t i = 96; i < 112; ++i)
		EXPECT_TRUE(bs3.get(i) == true);

	for (size_t i = 112; i < 128; ++i)
		EXPECT_TRUE(bs3.get(i) == false);
}

TEST(bitset, Difference_Pointer) {
	bitset* bs = new bitset(128);

	for (size_t i = 16; i < 96; ++i)
		bs->set(i);

	bitset* bs2 = new bitset(128);

	for (size_t i = 64; i < 112; ++i)
		bs2->set(i);

	bitset* bs3 = Difference(bs, bs2);

	for (size_t i = 0; i < 16; ++i)
		EXPECT_TRUE(bs3->get(i) == false);

	for (size_t i = 16; i < 64; ++i)
		EXPECT_TRUE(bs3->get(i) == true);

	for (size_t i = 64; i < 96; ++i)
		EXPECT_TRUE(bs3->get(i) == false);

	for (size_t i = 96; i < 112; ++i)
		EXPECT_TRUE(bs3->get(i) == true);

	for (size_t i = 112; i < 128; ++i)
		EXPECT_TRUE(bs3->get(i) == false);
}

TEST(bitset, initializer_list) {
    bitset test = { 1, 3, 5 };
    
    bitset result;

    result.set(1);
    result.set(3);
    result.set(5);

    //std::cout << test.toString() << std::endl;

    EXPECT_TRUE(test == result);
}

TEST(bitset, toString_1) {
	bitset bs({ 0, 2 });

	EXPECT_TRUE(bs.toString() == "{0, 2}");
}

TEST(bitset, toString_2) {
	bitset bs({ 1, 3 });

	EXPECT_TRUE(bs.toString() == "{1, 3}");
}


TEST(bitset, Bug1) {
	bitset test;
	test.Union(bitset::SingletonSet(97));
    test.Union(bitset::SingletonSet(98));
    test.Union(bitset::SingletonSet(99));
    test.Union(bitset::SingletonSet(101));

    EXPECT_TRUE(test.get(0) == false);
	EXPECT_TRUE(test.get(97) == true);
	EXPECT_TRUE(test.get(98) == true);
	EXPECT_TRUE(test.get(99) == true);
	EXPECT_TRUE(test.get(100) == false);
	EXPECT_TRUE(test.get(101) == true);
}

TEST(bitset, Bug2) {
	bitset alphabet;

	alphabet.set(98);
	alphabet.set(99);

	EXPECT_TRUE(alphabet.get(98) == true);
	EXPECT_TRUE(alphabet.get(99) == true);

	for (bitset::iterator i = alphabet.begin(), e = alphabet.end(); i != e; ++i) {
		EXPECT_TRUE((i.index() == 98) ? (i.get() == true) : true);
		EXPECT_TRUE((i.index() == 99) ? (i.get() == true) : true);
	}

	// Added friend bool operator == (reference&, reference&) as 'operator bool()' was being called on the comparison in the 'for' statement.
}

TEST(bitset, Bug3) {
    bitset test(35);
    bitset f = bitset::SingletonSet(5);

    test |= f;
    
    bitset result = { 5 };

    EXPECT_TRUE(test == result);
}

TEST(bitset, toStringTest2) {
	bitset test;

	test.Union(bitset::SingletonSet(97));
	test.Union(bitset::SingletonSet(98));
	test.Union(bitset::SingletonSet(99));
	test.Union(bitset::SingletonSet(101));

    EXPECT_TRUE(test.toString() == "{97, 98, 99, 101}");
}

