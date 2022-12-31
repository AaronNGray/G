//
//  PG/UnitTests/FirstSetTest.cpp
//
//  Copyright (c) 2016 Aaron Nathaniel Gray under the MIT License
//

#include "lib/ParserGenerator/Grammar.h"
#include "lib/Actions.h"
#include "gtest/gtest.h"

Actions *actions; // TODO: remove this !

TEST(FirstSet, basic_firstset_test) {
    Grammar* grammar = new Grammar;

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
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(C), grammar->newNamedSymbol(C) }))
        })
    ));

    grammar->addProduction(grammar->newProduction(C,
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(c), grammar->newNamedSymbol(C) })),
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(d) }))
        })
    ));

    grammar->GenerateFirstSets();

    bitset expected_result;
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("c"))->getIndex());
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("d"))->getIndex());

    std::cout << (grammar->getNonTerminal(grammar->newIdentifier("S"))->getFirstSet()).toString() << std::endl;
    std::cout << "expected_result = " << expected_result.toString() << std::endl;

    EXPECT_TRUE((grammar->getNonTerminal(grammar->newIdentifier("S"))->getFirstSet()) == expected_result);
    EXPECT_TRUE((grammar->getNonTerminal(grammar->newIdentifier("C"))->getFirstSet()) == expected_result);


    delete grammar;
}

TEST(FirstSet, augmented_firstset_test) {
    Grammar* grammar = new Grammar;

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
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(C), grammar->newNamedSymbol(C) }))
        })
    ));

    grammar->addProduction(grammar->newProduction(C,
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(c), grammar->newNamedSymbol(C) })),
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(d) }))
        })
    ));

    grammar->CheckGrammar();
    grammar->GenerateFirstSets();

    bitset expected_result;
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("c"))->getIndex());
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("d"))->getIndex());

    std::cout << (grammar->getNonTerminal(grammar->newIdentifier("S"))->getFirstSet()).toString(grammar->getTerminalNamesAsVector()) << std::endl;
    std::cout << "expected_result = " << expected_result.toString(grammar->getTerminalNamesAsVector()) << std::endl;

    std::cout << "startSymbol = " << grammar->getStartSymbol()->getFirstSet().toString(grammar->getTerminalNamesAsVector()) << std::endl;

    EXPECT_TRUE(grammar->getStartSymbol()->getFirstSet() == expected_result);
    EXPECT_TRUE(S->getFirstSet() == expected_result);
    EXPECT_TRUE(C->getFirstSet() == expected_result);

    delete grammar;
}
