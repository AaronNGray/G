//
//	g/Grammar/FIRST.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/Grammar/ContextFreeGrammar.h"

namespace G {
namespace Grammar {

bitset ContextFreeGrammar::Production::FIRST() {
	if (rhs->size() == 0)
		return ContextFreeGrammar::getEpsilon()->getBitset();
	else {
		bitset first;
		for (auto symbol : *rhs) {
			if (symbol->isTerminal())
				first |= symbol->getIndex();
			else
				first |= symbol->getFirstSet();
		}
		return first;
	}
}

} // end namespace G
} // end namespace Grammar

// End g/Grammar/FIRST.cpp
