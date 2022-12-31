//
//	g/Grammar/FollowSets.cpp
//
//  Property and Copyright (c) 2016, 2017 Aaron Nathaniel Gray
//

#include "g/Grammar/ContextFreeGrammar.h"
#include <sstream>

namespace G {
namespace Grammar {

void ContextFreeGrammar::GenerateFollowSets() {
    bool change;
    do {
        change = false;
        for (auto rule : rules) {
            bitset F = rule->getFollowSet();
            for (auto production : *rule) {
                auto rhs = production->getRHS();
                for (auto symbol = rhs.begin(), end = rhs.end(); symbol != end; ++symbol) {
                    if ((symbol != end) && (*symbol)->isNonTerminal()) {
                        auto nonterminal = (*symbol)->asNonTerminal();
                        for (auto y = symbol + 1; y != end; ++y) {

                            if ((*y)->isTerminal()) {
                                nonterminal->getFollowSet() |= (*y)->getIndex();
                                break;
                            }
                            else {
                                nonterminal->getFollowSet() |= (*y)->getFirstSet();
                                if (!(*y)->nullable())
                                    break;
                            }
                        } // end for y
                    }
                } // end if is non terminal
            } // end for production

            if (F != rule->getFollowSet())
                change = true;
        } // end for production
    } while (change);

    for (auto rule : rules) {
        bitset F = rule->getFollowSet();

        for (auto production : getProductions()) {
            auto rhs = production->getRHS();
            for (auto symbol = rhs.rbegin(), begin = rhs.rend(); symbol != begin; ++symbol) {
                if ((*symbol)->isNonTerminal())
                    (*symbol)->asNonTerminal()->getFollowSet() |= rule->getFollowSet();

                if (!(*symbol)->nullable())
                    break;
            } // end for production
        } // end for production
    }
}

std::string ContextFreeGrammar::PrintFollowSets() {
    std::stringstream ss;
    for (auto rule : rules)
        ss << rule->getLHS()->getName() << " = " << rule->getFollowSet().toString(terminalNames) << std::endl;
    return ss.str();
}

} // end namespace G
} // end namespace Grammar

// End g/Grammar/FollowSets.cpp
