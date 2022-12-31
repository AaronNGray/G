//
//  PG/UnitTests/LR1_ClosureTest.cpp
//
//  Copyright (c) 2016 Aaron Nathaniel Gray under the MIT License
//

#include "lib/ParserGenerator/LR1.h"
#include "gtest/gtest.h"

TEST(LR1_Closure, basic_closure_test) {
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

    grammar->CheckGrammar();
    grammar->GenerateFirstSets();
    grammar->GenerateTerminalNamesAsVector();

    LR1 lr1(grammar, std::cout);

    LR1::Items startItems = LR1::Items(LR1::Item(grammar->getStartRule(), Grammar::getEnd()->getFirstSet()));

    LR1::Items closure = lr1.Closure(startItems);

    std::cout << closure.toString(grammar) << std::endl;

    bitset expected_result;
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("c"))->getIndex());
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("d"))->getIndex());

    LR1::Items result = {
        LR1::Item(grammar->getProduction("S'")->getRule(0), 0, Lookaheads( Grammar::getEnd()->getFirstSet() )),
        LR1::Item(grammar->getProduction("S")->getRule(0), 0, Lookaheads( Grammar::getEnd()->getFirstSet() )),
        LR1::Item(grammar->getProduction("C")->getRule(0), 0, Lookaheads(expected_result)),
        LR1::Item(grammar->getProduction("C")->getRule(1), 0, Lookaheads(expected_result))
    };

    EXPECT_TRUE(closure == result);

    delete grammar;
}

TEST(LR1_Closure, basic_closure_and_goto_test) {
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

    grammar->CheckGrammar();
    grammar->GenerateFirstSets();
    grammar->GenerateTerminalNamesAsVector();

    LR1 lr1(grammar, std::cout);

    LR1::Items startItems = LR1::Items(LR1::Item(grammar->getStartRule(), Grammar::getEnd()->getFirstSet()));

    LR1::Items items = lr1.Closure(startItems);

    std::cout << items.toString(grammar) << std::endl;

    LR1::Items result = {
        LR1::Item(grammar->getProduction("S'")->getRule(0), 0, Lookaheads(Grammar::getEnd()->getFirstSet())),
        LR1::Item(grammar->getProduction("S")->getRule(0), 0, Lookaheads(Grammar::getEnd()->getFirstSet())),
        LR1::Item(grammar->getProduction("C")->getRule(0), 0, Lookaheads({ 2, 3 })),
        LR1::Item(grammar->getProduction("C")->getRule(1), 0, Lookaheads({ 2, 3 }))
    };

    std::cout << "Grammar::getEnd()->getFirstSet() = " << Grammar::getEnd()->getFirstSet().toString() << std::endl;

    EXPECT_TRUE(items == result);

    std::cout << "{" << std::endl << items.toString(grammar) << std::endl << "}" << std::endl;

    for (auto item : items) {
        LR1::Items goto_items = lr1.Goto(LR1::Items(item), item.rightOfDot());

        std::cout << "{" << std::endl << goto_items.toString(grammar) << "}" << std::endl;
    }
    delete grammar;
}

std::string ItemsPrettyPrint(std::vector<LR1::Items>& itemSets, Grammar* grammar, int indent) {
    std::stringstream ss;
    for (auto items : itemSets) {
        ss << "{" << std::endl;
        for (auto item : items)
            ss << "\t" << item.toString(grammar) << std::endl;
        ss << "}" << std::endl;
    }
    return ss.str();
}


TEST(LR1_Closure, walking_closure_test) {
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

    grammar->CheckGrammar();
    grammar->GenerateFirstSets();
    grammar->GenerateTerminalNamesAsVector();

    LR1 lr1(grammar, std::cout);

    LR1::Items startItems = LR1::Items(LR1::Item(grammar->getStartRule(), Grammar::getEnd()->getFirstSet()));

    LR1::Items items = lr1.Closure(startItems);

    std::cout << items.toString(grammar) << std::endl;

    bitset expected_result;
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("c"))->getIndex());
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("d"))->getIndex());

    LR1::Items result = {
        LR1::Item(grammar->getProduction("S'")->getRule(0), 0, Lookaheads(Grammar::getEnd()->getFirstSet())),
        LR1::Item(grammar->getProduction("S")->getRule(0), 0, Lookaheads(Grammar::getEnd()->getFirstSet())),
        LR1::Item(grammar->getProduction("C")->getRule(0), 0, Lookaheads(expected_result)),
        LR1::Item(grammar->getProduction("C")->getRule(1), 0, Lookaheads(expected_result))
    };

    EXPECT_TRUE(items == result);

    std::vector<LR1::Items> itemSets;

    itemSets.push_back(items);

    for (auto item : items)
        itemSets.push_back(lr1.Goto(LR1::Items(item), item.rightOfDot()));

    std::cout << ItemsPrettyPrint(itemSets, grammar, 0);

    std::vector<LR1::Items> itemSets2;

    for (auto items : itemSets)
        for (auto item : items)
            if (item.hasNext())
                itemSets2.push_back(lr1.Goto(LR1::Items(item), item.rightOfDot()));


    std::cout << "itemsSets2 = " << std::endl;
    for (auto items : itemSets2) {
        std::cout << "{" << std::endl;
        for (auto item : items)
            std::cout << "\t" << item.toString(grammar) << std::endl;
        std::cout << "}" << std::endl;
    }

    delete grammar;
}

std::string ItemsPrettyPrint(std::set<LR1::Items>& itemSets, Grammar* grammar, int indent) {
    std::stringstream ss;
    for (auto items : itemSets) {
        ss << "{" << std::endl;
        for (auto item : items)
            ss << "\t" << item.toString(grammar) << std::endl;
        ss << "}" << std::endl;
    }
    return ss.str();
}

TEST(LR1_Closure, walking_closure_test2) {
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

    grammar->CheckGrammar();
    grammar->GenerateFirstSets();
    grammar->GenerateTerminalNamesAsVector();

    LR1 lr1(grammar, std::cout);

    LR1::Items startItems = LR1::Items(LR1::Item(grammar->getStartRule(), Grammar::getEnd()->getFirstSet()));

    LR1::Items items = lr1.Closure(startItems);

    std::cout << items.toString(grammar) << std::endl;

    bitset expected_result;
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("c"))->getIndex());
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("d"))->getIndex());

    LR1::Items result = {
        LR1::Item(grammar->getProduction("S'")->getRule(0), 0, Lookaheads(Grammar::getEnd()->getFirstSet())),
        LR1::Item(grammar->getProduction("S")->getRule(0), 0, Lookaheads(Grammar::getEnd()->getFirstSet())),
        LR1::Item(grammar->getProduction("C")->getRule(0), 0, Lookaheads(expected_result)),
        LR1::Item(grammar->getProduction("C")->getRule(1), 0, Lookaheads(expected_result))
    };

    EXPECT_TRUE(items == result);

    set<LR1::Items> itemSets;

    itemSets.insert(items);

    for (auto item : items)
        itemSets.insert(lr1.Goto(LR1::Items(item), item.rightOfDot()));

    //

    std::cout << ItemsPrettyPrint(itemSets, grammar, 0);

    set<LR1::Items> itemSets2;

    for (auto items : itemSets)
        for (auto item : items)
            if (item.hasNext())
                itemSets2.insert(lr1.Goto(LR1::Items(item), item.rightOfDot()));


    std::cout << "itemsSets2 = " << std::endl;
    for (auto items : itemSets2) {
        std::cout << "{" << std::endl;
        for (auto item : items)
            std::cout << "\t" << item.toString(grammar) << std::endl;
        std::cout << "}" << std::endl;
    }

    delete grammar;
}

std::string ItemsPrettyPrint(std::deque<LR1::Items>& itemSets, Grammar* grammar, int indent) {
    std::stringstream ss;
    for (auto items : itemSets) {
        ss << "{" << std::endl;
        for (auto item : items)
            ss << "\t" << item.toString(grammar) << std::endl;
        ss << "}" << std::endl;
    }
    return ss.str();
}

TEST(LR1_Closure, unwinding_closure_and_goto_test) {
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

    grammar->CheckGrammar();
    grammar->GenerateFirstSets();
    grammar->GenerateTerminalNamesAsVector();

    LR1 lr1(grammar, std::cout);

    LR1::Items startItems = LR1::Items(LR1::Item(grammar->getStartRule(), Grammar::getEnd()->getFirstSet()));

    LR1::Items items = lr1.Closure(startItems);

    std::cout << items.toString(grammar) << std::endl;

    bitset expected_result;
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("c"))->getIndex());
    expected_result.set(grammar->getTerminal(grammar->newIdentifier("d"))->getIndex());

    LR1::Items result = {
        LR1::Item(grammar->getProduction("S'")->getRule(0), 0, Lookaheads(Grammar::getEnd()->getFirstSet())),
        LR1::Item(grammar->getProduction("S")->getRule(0), 0, Lookaheads(Grammar::getEnd()->getFirstSet())),
        LR1::Item(grammar->getProduction("C")->getRule(0), 0, Lookaheads(expected_result)),
        LR1::Item(grammar->getProduction("C")->getRule(1), 0, Lookaheads(expected_result))
    };

    EXPECT_TRUE(items == result);

    std::deque<LR1::Items> T;
    set<LR1::Items> E;

    T.push_back(items);

    //

    std::cout << ItemsPrettyPrint(T, grammar, 0);

    while (!T.empty()) {
        LR1::Items items = T.front(); T.pop_front();
        E.insert(items);

        for (auto item : items)
            if (item.hasNext()) {
                LR1::Items items = lr1.Goto(LR1::Items(item), item.rightOfDot());
                if (!E.is_member(items))
                    T.push_back(items);
            }
    }

    std::cout << "E = " << std::endl;
    for (auto items : E) {
        std::cout << "{" << std::endl;
        for (auto item : items)
            std::cout << "\t" << item.toString(grammar) << std::endl;
        std::cout << "}" << std::endl;
    }

    delete grammar;
}

TEST(LR1_Closure, epsilon_closure_test) {
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

    grammar->CheckGrammar();
    grammar->GenerateFirstSets();
    grammar->GenerateFollowSets();
    grammar->GenerateTerminalNamesAsVector();

    LR1 lr1(grammar, std::cout);

    LR1::Items startItems = LR1::Items(LR1::Item(grammar->getStartRule(), Grammar::getEnd()->getFirstSet()));

    LR1::Items closure = lr1.Closure(startItems);

    std::cout << closure.toString(grammar) << std::endl;

    LR1::Item s1(grammar->getProduction("S")->getRule(0), 0, Lookaheads(Grammar::getEnd()->getFirstSet()));
    LR1::Item a1(grammar->getProduction("A")->getRule(0), 0, Lookaheads(Grammar::getEnd()->getFirstSet()));
    LR1::Item a2(grammar->getProduction("A")->getRule(1), 0, Lookaheads(Grammar::getEnd()->getFirstSet()));

    LR1::Items result = {
        s1,
        a1,
        a2
    };

    EXPECT_TRUE(closure == result);

    delete grammar;
}
