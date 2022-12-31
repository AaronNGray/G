//
//	g/ParserGenerator/LR1/FIRST.cpp - Generate First Set
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"
#include <cassert>

namespace G {
namespace ParserGenerator {

bitset LR1::FIRST(Item item) {
    bitset first;
	ContextFreeGrammar::Production& production = *item.production;

    if (production.size() != 0) {

        size_t position = item.position;

        for (; position < production.size(); ++position) {
            first |= production[position]->getFirstSet();
            if (!production[position]->nullable())
                break;
        }

        if (position == production.size())
            first |= item.lookaheads;
    }
    else
        first |= item.lookaheads;

    first &= ~ContextFreeGrammar::getEpsilon()->getFirstSet(); // clear epsilon

    return first;
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/FIRST.cpp - Generate First Set

// TODO: look at making item.production a reference.
