//
//	EquivalenceClassesTest.cpp
//
//  Copyright (c) 2015-2016 Aaron Nathaniel Gray under the MIT License
//

#include "gtest/gtest.h"
#include "g/LexicalAnalyserGenerator/EquivalenceClasses.h"

using namespace G::LexicalAnalyserGenerator;

extern bool debug;

TEST(EquivalenceSets, copy_constructor) {
    Ranges ranges = { Range('a', 'a'), Range('b', 'b') };
    EquivalenceSet es1(0, ranges);

    EquivalenceSet es2(es1);

    EXPECT_TRUE(es1 == es2);
}

TEST(EquivalenceClasses, SingleCharacter) {

    std::vector<Ranges> classes = {
        { Char('a') }
    };

    EquivalenceClasses ecs(classes);
    ecs.Generate();

    if (debug)
        ecs.diag();

    auto lowers = ecs.getLowers();

    if (debug)
        for (auto l = lowers.cbegin(); l != lowers.cend(); ++l)
            std::cout << "'" << Range::printChar(*l) << "', " << std::endl;

    std::vector<unsigned int> result = {
        (unsigned int) '\0',
        (unsigned int) 'a',
        (unsigned int) 'b'
    };

    EXPECT_TRUE(std::equal(result.begin(), result.end(), ecs.getLowers().begin()));
}

TEST(EquivalenceClasses, TwoCharacterClasses) {

    std::vector<Ranges> classes = {
        { Range('a', 'a') },
        { Range('b', 'b') },
    };

    EquivalenceClasses ecs(classes);
    ecs.Generate();

    if (debug)
        ecs.diag();

    auto lowers = ecs.getLowers();

    if (debug)
        for (auto l = lowers.cbegin(); l != lowers.cend(); ++l)
            std::cout << "'" << Range::printChar(*l) << "', " << std::endl;

    std::vector<unsigned int> result = {
        (unsigned int) '\0',
        (unsigned int) 'a',
        (unsigned int) 'b',
        (unsigned int) 'c'
    };

    EXPECT_TRUE(std::equal(result.begin(), result.end(), ecs.getLowers().begin()));
}

static std::string toString(unsigned int c) {
    std::ostringstream os;
    if (c < 32 || c > 126)
        os << "\\" << (int)c;
    else
        os << (unsigned char)c;
    return os.str();
}

TEST(EquivalenceClasses, Generate_getLowers) {

    std::vector<Ranges> classes = {
        { Range(0, 255) },
        { Range('0', '0') },
        { Range('0', '1') },
        { Range('0', '7') },
        { Range('0', '9') },
        { Range('0', '9'), Range('a', 'f'), Range('A', 'F') },
        { Range('e', 'e'), Range('E', 'E') },
        { Range('a', 'z'), Range('A', 'Z') }
    };

    EquivalenceClasses ecs(classes);
    ecs.Generate();

    if (debug)
        for (auto l = ecs.getLowers().cbegin(); l != ecs.getLowers().cend(); ++l)
            std::cout << "'" << ::toString(*l) << "', " << std::endl;

    std::vector<unsigned int> result = {
        (unsigned int) 0,
        (unsigned int) '0',
        (unsigned int) '1',
        (unsigned int) '2',
        (unsigned int) '8',
        (unsigned int) ':',
        (unsigned int) 'A',
        (unsigned int) 'E',
        (unsigned int) 'F',
        (unsigned int) 'G',
        (unsigned int) '[',
        (unsigned int) 'a',
        (unsigned int) 'e',
        (unsigned int) 'f',
        (unsigned int) 'g',
        (unsigned int) '{',
        (unsigned int) 256
    };

    EXPECT_TRUE(std::equal(result.begin(), result.end(), ecs.getLowers().begin()));
}

TEST(EquivalenceClasses, Generate_getRanges) {

    std::vector<Ranges> classes = {
        { Range(0, 255) },
        { Range('0', '0') },
        { Range('0', '1') },
        { Range('0', '7') },
        { Range('0', '9') },
        { Range('0', '9'), Range('a', 'f'), Range('A', 'F') },
        { Range('e', 'e'), Range('E', 'E') },
        { Range('a', 'z'), Range('A', 'Z') }
    };

    EquivalenceClasses ecs(classes);
    ecs.Generate();

    Ranges result = {
        Range('\0', '/'),
        Range('0', '0'),
        Range('1', '1'),
        Range('2', '7'),
        Range('8', '9'),
        Range(':', '@'),
        Range('A', 'D'),
        Range('E', 'E'),
        Range('F', 'F'),
        Range('G', 'Z'),
        Range('[', '`'),
        Range('a', 'd'),
        Range('e', 'e'),
        Range('f', 'f'),
        Range('g', 'z'),
        Range('{', '\xFF')
    };

    EXPECT_TRUE(Compare(result, ecs.getRanges()));
}

