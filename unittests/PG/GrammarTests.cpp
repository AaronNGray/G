//
//  PG/UnitTests/GrammarTest.cpp
//
//  Copyright (c) 2016 Aaron Nathaniel Gray under the MIT License
//

#include "lib/ParserGenerator/Grammar.h"
#include "gtest/gtest.h"

TEST(Grammar, test_end) {
    Grammar* grammar = new Grammar;

    EXPECT_TRUE(grammar->getEnd()->isFinal());
}

// TODO: Test *::nullable()'s
// TODO: Test *::isNullable()'s

TEST(Grammar, basic_grammar_test) {
    Grammar* grammar =  new Grammar;

    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("c"), grammar->newStringLiteral("c")));
    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("d"), grammar->newStringLiteral("d")));

    grammar->addNonTerminal(grammar->newNonTerminal(grammar->newIdentifier("S")));
    grammar->addNonTerminal(grammar->newNonTerminal(grammar->newIdentifier("C")));

    grammar->addProduction(grammar->newProduction(grammar->newIdentifier("S"),
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getNonTerminal(grammar->newIdentifier("C"))), grammar->newNamedSymbol(grammar->getNonTerminal(grammar->newIdentifier("C"))) }))
        })
    ));

    grammar->addProduction(grammar->newProduction(grammar->newIdentifier("C"),
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getTerminal(grammar->newIdentifier("c"))), grammar->newNamedSymbol(grammar->getNonTerminal(grammar->newIdentifier("C"))) })),
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getTerminal(grammar->newIdentifier("d"))) }))
        })
    ));

    std::cout << grammar->prettyPrint() << std::endl;
}

TEST(Grammar, augmented_grammar_test) {
    Grammar* grammar = new Grammar;

    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("c"), grammar->newStringLiteral("c")));
    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("d"), grammar->newStringLiteral("d")));

    grammar->addNonTerminal(grammar->newNonTerminal(grammar->newIdentifier("S")));
    grammar->addNonTerminal(grammar->newNonTerminal(grammar->newIdentifier("C")));

    grammar->addProduction(grammar->newProduction(grammar->newIdentifier("S"),
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getNonTerminal(grammar->newIdentifier("C"))), grammar->newNamedSymbol(grammar->getNonTerminal(grammar->newIdentifier("C"))) }))
        })
    ));

    grammar->addProduction(grammar->newProduction(grammar->newIdentifier("C"),
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getTerminal(grammar->newIdentifier("c"))), grammar->newNamedSymbol(grammar->getNonTerminal(grammar->newIdentifier("C"))) })),
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getTerminal(grammar->newIdentifier("d"))) }))
        })
    ));

    grammar->CheckGrammar();

    EXPECT_TRUE(grammar->getNonTerminal(grammar->newIdentifier("S'")) != nullptr);

    std::cout << grammar->prettyPrint() << std::endl;
}

TEST(Grammar, basic_firstset_test) {
    Grammar* grammar = new Grammar;

    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("c"), grammar->newStringLiteral("c")));
    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("d"), grammar->newStringLiteral("d")));

    grammar->addNonTerminal(grammar->newNonTerminal(grammar->newIdentifier("S")));
    grammar->addNonTerminal(grammar->newNonTerminal(grammar->newIdentifier("C")));

    grammar->addProduction(grammar->newProduction(grammar->newIdentifier("S"),
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getNonTerminal(grammar->newIdentifier("C"))), grammar->newNamedSymbol(grammar->getNonTerminal(grammar->newIdentifier("C"))) }))
        })
    ));

    grammar->addProduction(grammar->newProduction(grammar->newIdentifier("C"),
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getTerminal(grammar->newIdentifier("c"))), grammar->newNamedSymbol(grammar->getNonTerminal(grammar->newIdentifier("C"))) })),
            grammar->newRule(grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getTerminal(grammar->newIdentifier("d"))) }))
        })
    ));

    grammar->CheckGrammar();
    grammar->GenerateFirstSets();

    bitset expected_result;
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("c"))->getIndex());
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("d"))->getIndex());

    EXPECT_TRUE((grammar->getNonTerminal(grammar->newIdentifier("S'"))->getFirstSet()) == expected_result);
    EXPECT_TRUE((grammar->getNonTerminal(grammar->newIdentifier("S"))->getFirstSet()) == expected_result);
    EXPECT_TRUE((grammar->getNonTerminal(grammar->newIdentifier("C"))->getFirstSet()) == expected_result);

    delete grammar;
}

TEST(Grammar, expression_grammar_firstset_test) {
    Grammar* grammar = new Grammar;

    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("OPEN_PARENTHSIS"), grammar->newStringLiteral("(")));
    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("CLOSE_PARENTHSIS"), grammar->newStringLiteral(")")));
    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("PLUS"), grammar->newStringLiteral("+")));
    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("MULT"), grammar->newStringLiteral("*")));
    grammar->addTerminal(grammar->newTerminal(grammar->newIdentifier("NUMBER")));

    grammar->addNonTerminal(grammar->newNonTerminal(grammar->newIdentifier("Expr")));
    grammar->addNonTerminal(grammar->newNonTerminal(grammar->newIdentifier("Term")));
    grammar->addNonTerminal(grammar->newNonTerminal(grammar->newIdentifier("Factor")));

    grammar->addProduction(grammar->newProduction(grammar->newIdentifier("Expr"),
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({
                grammar->newNamedSymbol(grammar->getNonTerminal("Expr")),
                grammar->newNamedSymbol(grammar->getTerminal("PLUS")),
                grammar->newNamedSymbol(grammar->getNonTerminal("Term"))
            })),
            grammar->newRule(grammar->newNamedSymbols({
                grammar->newNamedSymbol(grammar->getNonTerminal("Term"))
            }))
        })
    ));
    grammar->addProduction(grammar->newProduction(grammar->newIdentifier("Term"),
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({
                grammar->newNamedSymbol(grammar->getNonTerminal("Term")),
                grammar->newNamedSymbol(grammar->getTerminal("MULT")),
                grammar->newNamedSymbol(grammar->getNonTerminal("Factor"))
            })),
            grammar->newRule(grammar->newNamedSymbols({
                grammar->newNamedSymbol(grammar->getNonTerminal("Factor"))
            }))
        })
     ));

    grammar->addProduction(grammar->newProduction(grammar->newIdentifier("Factor"),
        grammar->newRules({
            grammar->newRule(grammar->newNamedSymbols({
                grammar->newNamedSymbol(grammar->getTerminal("OPEN_PARENTHSIS")),
                grammar->newNamedSymbol(grammar->getNonTerminal("Expr")),
                grammar->newNamedSymbol(grammar->getTerminal("CLOSE_PARENTHSIS")),
            })),
            grammar->newRule(grammar->newNamedSymbols({
                grammar->newNamedSymbol(grammar->getTerminal("NUMBER"))
            }))
        })
    ));

    grammar->CheckGrammar();

    std::cout << grammar->prettyPrint() << std::endl;

    grammar->GenerateFirstSets();
    grammar->GenerateTerminalNamesAsVector();

    size_t first_open_parenthsis = grammar->getTerminal("OPEN_PARENTHSIS")->getIndex();
    size_t first_close_parenthsis = grammar->getTerminal("CLOSE_PARENTHSIS")->getIndex();
    size_t first_plus = grammar->getTerminal("PLUS")->getIndex();
    size_t first_mult = grammar->getTerminal("MULT")->getIndex();
    size_t first_number = grammar->getTerminal("NUMBER")->getIndex();

    bitset expected_result;
    expected_result.set(grammar->getTerminal("OPEN_PARENTHSIS")->getIndex());
    expected_result.set(grammar->getTerminal("NUMBER")->getIndex());

    EXPECT_TRUE((grammar->getNonTerminal("S'")->getFirstSet()) == expected_result);
    EXPECT_TRUE((grammar->getNonTerminal("Expr")->getFirstSet()) == expected_result);
    EXPECT_TRUE((grammar->getNonTerminal("Term")->getFirstSet()) == expected_result);
    EXPECT_TRUE((grammar->getNonTerminal("Factor")->getFirstSet()) == expected_result);

    delete grammar;
}

