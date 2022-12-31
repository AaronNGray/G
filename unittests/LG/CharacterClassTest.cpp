//
//	CharacterClassesTest.cpp
//
//  Copyright (c) 2015-2016 Aaron Nathaniel Gray under the MIT License
//

#include "gtest/gtest.h"
#include "g/LexicalAnalyserGenerator/CharacterClass.h"
#include "g/LexicalAnalyserGenerator/Lowers.h"

using namespace G::LexicalAnalyserGenerator;

TEST(CharacterClassTest, CharacterTest) {
    CharacterClass characterClass('c');

    //std::cout << characterClass.toString() << std::endl;

    ASSERT_TRUE(characterClass.getRanges().size() == 1);
    ASSERT_TRUE(characterClass.getRanges()[0].getLower() == 'c');
    ASSERT_TRUE(characterClass.getRanges()[0].getUpper() == 'c');
}

TEST(CharacterClassTest, RangeTest) {
    CharacterClass characterClass(Range('A', 'C'));

    //std::cout << characterClass.toString() << std::endl;

    ASSERT_TRUE(characterClass.getRanges().size() == 1);
    ASSERT_TRUE(characterClass.getRanges()[0].getLower() == 'A');
    ASSERT_TRUE(characterClass.getRanges()[0].getUpper() == 'C');
}

TEST(CharacterClassTest, ReverseRangeTest) {
    CharacterClass characterClass(Range('C', 'A'));

    //std::cout << characterClass.toString() << std::endl;

    ASSERT_TRUE(characterClass.getRanges().size() == 1);
    ASSERT_TRUE(characterClass.getRanges()[0].getLower() == 'A');
    ASSERT_TRUE(characterClass.getRanges()[0].getUpper() == 'C');
}


TEST(CharacterClassTest, bug1) {
    Ranges ranges;

    ranges.add(Char('\\'));
    ranges.add(Char('\n'));
    ranges.add(Char(']'));
    ranges.add(Char('-'));

    CharacterClass cc(ranges, true);

    Lowers lowers = Lowers(cc.getRanges());

    //std::cout << lowers.toString() << std::endl;

    std::vector<unsigned int> result = { '\0', '\x0A', '\x0B', '-', '.', '\\', '^' };

    ASSERT_TRUE(std::equal(result.begin(), result.end(), lowers.getLowers().begin()));
}

TEST(CharacterClassTest, bug1_0) {
    Ranges ranges;

    ranges.add(Char('-'));
    ranges.add(Char(']'));
    ranges.add(Char('\n'));
    ranges.add(Char('\\'));

    CharacterClass cc(ranges, true);

    Lowers lowers = Lowers(cc.getRanges());

    //std::cout << lowers.toString() << std::endl;

    std::vector<unsigned int> result = { '\0', '\x0A', '\x0B', '-', '.', '\\', '^' };

    ASSERT_TRUE(std::equal(result.begin(), result.end(), lowers.getLowers().begin()));
}
