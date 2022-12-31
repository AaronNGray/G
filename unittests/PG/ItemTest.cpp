//
//  PG/UnitTests/ItemTest.cpp
//
//  Copyright (c) 2016 Aaron Nathaniel Gray under the MIT License
//

#include "lib/ParserGenerator/LR1.h"
#include "gtest/gtest.h"

TEST(Items, walking_items_test) {
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

    grammar->GenerateFirstSets();

    LR1 lr1(grammar);

    Grammar::Rule* startRule = grammar->getRules(grammar->getNonTerminal(grammar->newIdentifier("S")))->getRule(0);
    LR1::Items items = LR1::Items(LR1::Item(startRule, Grammar::END));

    std::cout << "start items = " << items.toString() << std::endl;

    while (items.size() != 0) {
        LR1::Items closureItems = lr1.Closure(items);
        std::cout << "closureItems" << closureItems.toString() << std::endl;

        items.clear();

        for (auto item : closureItems) {
            if (item.isNext())
                items.insert(item.next());
        }
        std::cout << "item = " << items.toString() << std::endl;

//        getc(stdin);
    }

    delete grammar;
}
