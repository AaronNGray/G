//
//	g/ParserGenerator/LR0/FIRST.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR0/LR0.h"

namespace G {
namespace ParserGenerator {

//

bitset LR0::FIRST(Item item) {
	bitset first;
	ContextFreeGrammar::Production& production = *item.production;

	if (production.size() != 0) {

		size_t position = item.position;

		for (; position < production.size(); ++position) {
			first |= production[position]->getFirstSet();
			if (!production[position]->nullable())
				break;
		}
	}

	first &= ~ContextFreeGrammar::getEpsilon()->getFirstSet(); // clear epsilon

	return first;
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR0/FIRST.cpp

// TODO: look at making item.production a reference.
