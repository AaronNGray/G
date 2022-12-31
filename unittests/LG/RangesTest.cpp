//
//	RangesTest.cpp
//
//  Copyright (c) 2015-2016 Aaron Nathaniel Gray under the MIT License
//

#include "gtest/gtest.h"
#include "g/LexicalAnalyserGenerator/Ranges.h"
#include <assert.h>

using namespace G::LexicalAnalyserGenerator;

/*
TEST(RangesTest, ExceptionInvalidRange) {
    bool caught = false;
    try {
        Range range('b', 'a');
    }
    catch (ExceptionInvalidRange) {
        caught = true;
    };

    ASSERT_TRUE(caught);
}

TEST(RangesTest, NotExceptionInvalidRange) {
    bool caught = false;
    try {
        Range range('a', 'b');
    }
    catch (ExceptionInvalidRange) {
        caught = true;
    };

    ASSERT_TRUE(!caught);
}
*/
TEST(RangesTest, compareLowers) {
    ASSERT_TRUE(Range::compareLowers(Range('a', 'm'), Range('n', 'z')));
}

TEST(RangesTest, overlapped_Overlapped) {
    ASSERT_TRUE(Range::overlapped(Range('a', 'n'), Range('m', 'z')));
    ASSERT_TRUE(Range::overlapped(Range('m', 'z'), Range('a', 'n')));
}

TEST(RangesTest, overlapped_NonOverlapped) {
    ASSERT_FALSE(Range::overlapped(Range('a', 'm'), Range('n', 'z')));
}

TEST(RangesTest, Check_InOrder) {
    Ranges ranges;

    ranges.add(Range('a', 'd'));
    ranges.add(Char('e'));
    ranges.add(Char('f'));
    ranges.add(Range('g', 'z'));

    ASSERT_TRUE(ranges.check());
}


TEST(RangesTest, Check_Overlap) {
    Ranges ranges;

    ranges.add(Range('a', 'g'));
    ranges.add(Range('h', 'z'));

    ASSERT_TRUE(ranges.check());
}

TEST(RangesTest, Sort_InOrder) {
    Ranges ranges;

    ranges.add(Range('a', 'd'));
    ranges.add(Char('e'));
    ranges.add(Char('f'));
    ranges.add(Range('g', 'z'));

    ranges.sortOnLowers();

    ASSERT_TRUE(ranges.check());
}

TEST(RangesTest, Sort_OutOfOrder) {
    Ranges ranges;

    ranges.add(Range('g', 'z'));
    ranges.add(Char('f'));
    ranges.add(Char('e'));
    ranges.add(Range('a', 'd'));

    ranges.sortOnLowers();

    ASSERT_TRUE(ranges.check());
}

TEST(RangesTest, ArrayAccess) {
    Ranges ranges;

    ranges.add(Range('a', 'd'));
    ranges.add(Char('e'));
    ranges.add(Char('f'));
    ranges.add(Range('g', 'z'));

    Range r = ranges[0];
}


TEST(RangeTest, Equal) {
    Range range1('a', 'z');
    Range range2('a', 'z');

    ASSERT_TRUE(range1 == range2);
}

TEST(RangeTest, NotEqual) {
    Range range1('a', 'z');
    Range range2('n', 'z');

    ASSERT_TRUE(range1 != range2);
}

TEST(RangeTest, Character255) {

    unsigned char c = '\xFF';

    ASSERT_TRUE(Range(0, 255) == Range(0, '\xFF'));
}

TEST(RangeTest, initializer_list) {
    Ranges newline = { Range('\n', '\n'), Range('\r', '\r') };
}