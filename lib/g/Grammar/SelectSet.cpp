//
//	g/Grammar/SelectSet.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/Grammar/ContextFreeGrammar.h"

namespace G {
namespace Grammar {

void ContextFreeGrammar::GenerateSelectSets() {
	for (auto rule : rules)
		rule->GenerateSelectSets();
}
/*
void Grammar::Rule::GenerateSelectSets() {
	for (auto production : *productions) {
		production->selectSet |= production->FIRST();
		if (production->nullable())
			production->selectSet |= getFollowSet();
		production->selectSet &= ~Grammar::getEpsilon()->getFirstSet();
	}
}
*/

void ContextFreeGrammar::Rule::GenerateSelectSets() {
	for (auto production : *productions)
		production->GenerateSelectSet(this);
}

void ContextFreeGrammar::Production::GenerateSelectSet(ContextFreeGrammar::Rule* rule) {
	selectSet |= FIRST();
	if (nullable())
		selectSet |= rule->getFollowSet();
	selectSet &= ~ContextFreeGrammar::getEpsilon()->getFirstSet();
}

} // end namespace G
} // end namespace Grammar

// End g/Grammar/SelectSet.cpp
