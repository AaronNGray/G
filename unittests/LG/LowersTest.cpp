//
//	LowersTest.cpp
//
//  Copyright (c) 2015-2016 Aaron Nathaniel Gray under the MIT License
//

#include "gtest/gtest.h"
#include "g/LexicalAnalyserGenerator/Lowers.h"
#include <algorithm>

using namespace G::LexicalAnalyserGenerator;

TEST(LowersTest, LowersRangeTest) {
    Ranges ranges;

    ranges.add(Range('A', 'Z'));
    ranges.add(Range('a', 'z'));

    ranges.normalize();

    Lowers lowers(ranges);

    //std::cout << lowers.toString() << std::endl;

    std::vector<unsigned int> result = { '\0', 'A', '[', 'a', '{' };

    ASSERT_TRUE(std::equal(result.begin(), result.end(), lowers.getLowers().begin()));
}

TEST(LowersTest, LowersConsecutiveRangeTest) {
    Ranges ranges;

    ranges.add(Range('A', 'M'));
    ranges.add(Range('N', 'Z'));

    ranges.normalize();

    Lowers lowers(ranges);

    std::vector<unsigned int> result = { '\0', 'A', '[' };

    //  for (auto l = lowers.cbegin(); l != lowers.cend(); ++l)
    //    std::cout << "'" << (char) *l << "', " << std::endl;

    ASSERT_TRUE(std::equal(result.begin(), result.end(), lowers.getLowers().begin()));
}

TEST(LowersTest, LowersConsecutiveRangeTest2) {
    Ranges ranges;

    ranges.add(Range('A', 'M'));
    ranges.add(Range('N', 'Z'));
    ranges.add(Range('a', 'm'));
    ranges.add(Range('n', 'z'));

    ranges.normalize();

    Lowers lowers(ranges);

    std::vector<unsigned int> result = { '\0', 'A', '[', 'a', '{' };

    ASSERT_TRUE(std::equal(result.begin(), result.end(), lowers.getLowers().begin()));
}

TEST(LowersTest, LowersTest) {
    Ranges ranges;

    ranges.add(Range('g', 'z'));
    ranges.add(Char('f'));
    ranges.add(Char('e'));
    ranges.add(Range('a', 'd'));

    ranges.normalize();

    Lowers lowers(ranges);

    std::vector<unsigned int> result = { '\0', 'a', '{' };

    ASSERT_TRUE(std::equal(result.begin(), result.end(), lowers.getLowers().begin()));
}

TEST(LowersTest, LowersTest_AdjacentValues) {
    Ranges ranges;
    ranges.add(Char('A'));
    ranges.add(Char('B'));
    Lowers lowers(ranges);

    std::vector<unsigned int> result = { '\0', 'A', 'C' };

    ASSERT_TRUE(std::equal(lowers.getLowers().begin(), lowers.getLowers().end(), result.begin()));
}

TEST(LowersTest, LowersTest_AdjacentRanges) {
    Ranges ranges;
    ranges.add(Range('A', 'B'));
    ranges.add(Range('C', 'D'));

    Lowers lowers(ranges);

    std::vector<unsigned int> result = { '\0', 'A', 'E' };

    ASSERT_TRUE(std::equal(lowers.getLowers().begin(), lowers.getLowers().end(), result.begin()));
}

