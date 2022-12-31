//
//  PG/UnitTests/FIRSTTests.cpp
//
//  Copyright (c) 2016 Aaron Nathaniel Gray under the MIT License
//

#include "g/ParserGenerator/Grammar.h"
#include "g/ParserGenerator/LR1.h"
#include "gtest/gtest.h"


TEST(FIRST, basic_FIRST_test) {
    Grammar* grammar = new Grammar;

    // S: C C {};
    // C: c C | d {};

    Grammar::Terminal* c = grammar->newTerminal(grammar->newIdentifier("c"), grammar->newStringLiteral("c"));
    Grammar::Terminal* d = grammar->newTerminal(grammar->newIdentifier("d"), grammar->newStringLiteral("d"));
    Grammar::NonTerminal* S = grammar->newNonTerminal(grammar->newIdentifier("S"));
    Grammar::NonTerminal* C = grammar->newNonTerminal(grammar->newIdentifier("C"));

    grammar->addTerminal(c);
    grammar->addTerminal(d);
    grammar->addNonTerminal(S);
    grammar->addNonTerminal(C);

    grammar->addProduction(grammar->newProduction(S,
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({
                grammar->newNamedSymbol(C),
                grammar->newNamedSymbol(C)
            }))
        })
    ));

    grammar->addProduction(grammar->newProduction(C,
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({
                grammar->newNamedSymbol(c),
                grammar->newNamedSymbol(C)
            })),
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(d) }))
        })
    ));

    grammar->GenerateFirstSets();

    {
        LR1::Item testItem((*grammar->getProduction(C))[0], 0, bitset::EmptySet());
        bitset testBitset = LR1::FIRST(testItem);

        EXPECT_TRUE(testBitset == c->getFirstSet());
    }
    {
        LR1::Item testItem((*grammar->getProduction(C))[0], 1, bitset::EmptySet());
        bitset testBitset = LR1::FIRST(testItem);
        bitset expected_result;
        expected_result.set(grammar->getTerminal(grammar->newIdentifier("c"))->getIndex());
        expected_result.set(grammar->getTerminal(grammar->newIdentifier("d"))->getIndex());

//        std::cout << testBitset.toString() << std::endl;
        EXPECT_TRUE(testBitset == expected_result);
    }
    delete grammar;
}

TEST(FIRST, epsilon_closure_test) {
    Grammar* grammar = new Grammar;

    //  S: A
    //  A: a | epsilon

    Grammar::Terminal* a = grammar->newTerminal(grammar->newIdentifier("a"), grammar->newStringLiteral("a"));
    Grammar::NonTerminal* S = grammar->newNonTerminal(grammar->newIdentifier("S"));
    Grammar::NonTerminal* A = grammar->newNonTerminal(grammar->newIdentifier("A"));

    grammar->addTerminal(a);
    grammar->addNonTerminal(S);
    grammar->addNonTerminal(A);

    grammar->addProduction(grammar->newProduction(S,
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({
                grammar->newNamedSymbol(A)
            }))
        })
    ));

    grammar->addProduction(grammar->newProduction(A,
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(a) })),
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getEpsilon()) }))
        })
    ));

    grammar->GenerateFirstSets();

    {
        LR1::Item testItem((*grammar->getProduction(A))[0], 0, bitset::EmptySet());
        bitset testBitset = LR1::FIRST(testItem);

        EXPECT_TRUE(testBitset == a->getFirstSet());
    }

    {
        LR1::Item testItem((*grammar->getProduction(A))[1], 0, bitset::EmptySet());
        bitset testBitset = LR1::FIRST(testItem);

        std::cout << testBitset.toString() << std::endl;

        EXPECT_TRUE(testBitset == bitset::EmptySet());
    }

    {
        LR1::Item testItem((*grammar->getProduction(A))[1], 0, grammar->getEnd()->getFirstSet());
        bitset testBitset = LR1::FIRST(testItem);

        std::cout << testBitset.toString() << std::endl;

        EXPECT_TRUE(testBitset == grammar->getEnd()->getFirstSet());
    }

    delete grammar;
}

TEST(FIRST, hidden_closure_test) {
    Grammar* grammar = new Grammar;

    //  S: A
    //  A: B b
    //  B: a | epsilon

    Grammar::Terminal* a = grammar->newTerminal(grammar->newIdentifier("a"), grammar->newStringLiteral("a"));
    Grammar::Terminal* b = grammar->newTerminal(grammar->newIdentifier("b"), grammar->newStringLiteral("b"));
    Grammar::NonTerminal* S = grammar->newNonTerminal(grammar->newIdentifier("S"));
    Grammar::NonTerminal* A = grammar->newNonTerminal(grammar->newIdentifier("A"));
    Grammar::NonTerminal* B = grammar->newNonTerminal(grammar->newIdentifier("B"));

    grammar->addTerminal(a);
    grammar->addTerminal(b);
    grammar->addNonTerminal(S);
    grammar->addNonTerminal(A);
    grammar->addNonTerminal(B);

    grammar->addProduction(grammar->newProduction(S,
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({
                grammar->newNamedSymbol(A)
            }))
        })
    ));

    grammar->addProduction(grammar->newProduction(A,
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(B), grammar->newNamedSymbol(b) }))
        })
    ));

    grammar->addProduction(grammar->newProduction(B,
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(a) })),
                grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getEpsilon()) }))
        })
    ));

    grammar->GenerateFirstSets();

    {
        LR1::Item testItem((*grammar->getProduction(A))[0], 0, grammar->getEnd()->getFirstSet());
        bitset testBitset = LR1::FIRST(testItem);

        std::cout << testBitset.toString() << std::endl;

        bitset expected_result;
        expected_result.set(grammar->getTerminal(grammar->newIdentifier("a"))->getIndex());
        expected_result.set(grammar->getTerminal(grammar->newIdentifier("b"))->getIndex());

        EXPECT_TRUE(testBitset == expected_result);
    }

    delete grammar;
}
