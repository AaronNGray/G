//
//	g/Grammar/FirstSets.cpp
//
//  Property and Copyright (c) 2016, 2017 Aaron Nathaniel Gray
//

#include "g/Grammar/ContextFreeGrammar.h"
#include <sstream>

namespace G {
namespace Grammar {

void ContextFreeGrammar::GenerateFirstSets() {
    bool change;

    do {
        change = false;

		for (auto rule : rules) {
            bitset F;

            for (auto production : getProductions()) {

                if (production->nullable())
                    F |= EPSILON;
                else {
					NamedSymbols rhs = production->getRHS();
                    for (auto symbol = rhs.begin(); symbol != rhs.end(); ++symbol) {

                        if ((*symbol)->isTerminal())
                            F |= (*symbol)->getIndex();
                        else
                            F |= (*symbol)->getFirstSet();
                        if (!(*symbol)->nullable())
                            break;
                    }
                } // end production nullable

            } // end for production

			if (F != rule->getFirstSet()) {
				rule->setFirstSet(F);
                change = true;
            }
        } // end for production

    } while (change);
}

std::string ContextFreeGrammar::PrintFirstSets() {
    std::stringstream ss;
    for (auto rule : rules) {
        ss << rule->getLHS()->getName() << " = " << rule->getFirstSet().toString(terminalNames) << std::endl;
    }
    return ss.str();
}

} // end namespace G
} // end namespace Grammar

// End g/Grammar/FirstSets.cpp
