//
//	g/Grammar/ExtendedGrammar.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/Grammar/ExtendedGrammar.h"
#include "g/Actions.h"
#include "nonstd/Utils.h"
#include <sstream>
#include <iostream>

namespace G {
namespace Grammar {

//ExtendedGrammar::Error ExtendedGrammar::ERROR;
//ExtendedGrammar::Epsilon ExtendedGrammar::EPSILON;
//ExtendedGrammar::End ExtendedGrammar::END;

ContextFreeGrammar *ExtendedGrammar::lower() {
	ContextFreeGrammar* grammar = new ContextFreeGrammar(name, getActions());
	LowerContext* context = new LowerContext(grammar, this);

	for (auto terminal : getTerminals())
		if (!terminal->isPseudoTerminal() && !terminal->isEnd())
			addTerminal(grammar->newTerminal(terminal));

	for (auto nonTerminal : getNonTerminals())
		addNonTerminal(grammar->newNonTerminal(nonTerminal));

	grammar->setStartSymbol(getStartSymbol());

	for (auto rule : getRules()) {
		ContextFreeGrammar::Rule* grammar_rule = grammar->newRule(rule->getLHS());

		for (auto production : rule->getProductions()) {
			production->lower(context);
		}
	}

	return grammar;
}

/*
Grammar::Rule* ExtendedGrammar::Rule::lower(LowerContext* context) {

}
*/

void ExtendedGrammar::Production::lower(LowerContext* context) {
	if (rhs->hasOptional()) {
		vector<NamedSymbols*> leftHandSides;
		leftHandSides.push_back(new NamedSymbols());

		for (auto namedFactor : rhs->getNamedFactors()) {
			auto namedSymbol = namedFactor->lower(context);
			if (namedFactor->isOptional()) {
				for (auto iterator = leftHandSides.begin(), end = leftHandSides.end(); iterator != end; ++iterator) {
					auto clone = (*iterator)->clone();
					clone->add(namedSymbol);
					leftHandSides.push_back(clone);
				}
			}
			else
				for (auto lhs : leftHandSides)
					lhs->add(namedSymbol);
		}
		for (auto lhs : leftHandSides)
			context->grammar->newProduction(lhs, rhs);
	}
}

ContextFreeGrammar::NamedSymbols* ExtendedGrammar::NamedFactors::lower(LowerContext* context) {
	ContextFreeGrammar::NamedSymbols* namedSymbols = context->grammar->newNamedSymbols();

	for (auto namedFactor : getNamedFactors())
		namedSymbols->add(namedFactor->lower(context));

	return namedSymbols;
}

bool ExtendedGrammar::NamedFactors::hasOptional() {
	bool containsOptional = false;

	for (auto namedFactor : getNamedFactors())
		containsOptional |= namedFactor->isOptional();

	return containsOptional;
}

ContextFreeGrammar::NamedSymbol* ExtendedGrammar::NamedFactor::lower(LowerContext* context) {
	return context->grammar->newNamedSymbol(context->grammar->newSymbol(context->grammar->newIdentifier("")));
}

ContextFreeGrammar::NonTerminal* ExtendedGrammar::Factor::lower(LowerContext* context) {
	return context->grammar->newNonTerminal(context->grammar->newIdentifier(""));
}

ContextFreeGrammar::NonTerminal* ExtendedGrammar::OptionalRepetition::lower(LowerContext* context) {
	return context->grammar->newNonTerminal(context->grammar->newIdentifier(""));
}
ContextFreeGrammar::NonTerminal* ExtendedGrammar::Repetition::lower(LowerContext* context) {
	return context->grammar->newNonTerminal(context->grammar->newIdentifier(""));
}

ContextFreeGrammar::NonTerminal* ExtendedGrammar::Optional::lower(LowerContext* context) {
	return context->grammar->newNonTerminal(context->grammar->newIdentifier(""));
}
ContextFreeGrammar::NonTerminal* ExtendedGrammar::Selection::lower(LowerContext* context) {
	return context->grammar->newNonTerminal(context->grammar->newIdentifier(""));
}
ContextFreeGrammar::NonTerminal* ExtendedGrammar::Sequence::lower(LowerContext* context) {
	return context->grammar->newNonTerminal(context->grammar->newIdentifier(""));
}

/*
void ExtendedGrammar::CheckGrammar() {
	if (!startSymbol)
		setStartSymbol(getDefaultStartSymbol());
	if (!isAugmentedGrammar())
		AugmentGrammar();
	if (!startSymbol)
		SetStartProduction();
}

ExtendedGrammar::NonTerminal* ExtendedGrammar::getDefaultStartSymbol() {
	return productions[0]->getLHS();
}

bool ExtendedGrammar::isAugmentedGrammar() {
	if (startSymbol) {
		Rule* startRule = getRule(startSymbol);

		if (startRule->getProductions().size() == 1) {
			Production* startProduction = startRule->getProductions()[0];
			return (startProduction->size() == 2)
				&& startProduction->isStart()
				&& ((*startProduction)[1] == getEnd());
		}
		return false;
	}
	return false;
}

void ExtendedGrammar::AugmentGrammar() {
	if (!isAugmentedGrammar()) {
		NonTerminal* newStartSymbol = newNonTerminal(newIdentifier("S'"));
		addNonTerminal(newStartSymbol);
		Production* production = newProduction(newNamedSymbols({ newNamedSymbol(startSymbol), newNamedSymbol(getEnd()) }), true);
		addRule(newRule(newStartSymbol, newProductions(production)));
		setStartSymbol(newStartSymbol);
	}
}

void ExtendedGrammar::SetStartProduction() {
	if (startSymbol) {
		Rule* startRule = getRule(startSymbol);

		if (startRule->getProductions().size() == 1) {
			Production* startProduction = startRule->getProductions()[0];
			startProduction->setStart();
		}
	}
}
*/

} // end namespace G
} // end namespace Grammar

// End g/Grammar/ExtendedGrammar.cpp
