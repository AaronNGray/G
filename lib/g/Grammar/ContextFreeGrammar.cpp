//
//	g/Grammar/Grammar.cpp
//
//  Property and Copyright (c) 2016, 2017 Aaron Nathaniel Gray
//

#include "g/Grammar/ContextFreeGrammar.h"
#include "g/Actions.h"
#include "nonstd/Utils.h"
#include <sstream>
#include <iostream>

namespace G {
namespace Grammar {

ContextFreeGrammar::Error ContextFreeGrammar::ERROR;
ContextFreeGrammar::Epsilon ContextFreeGrammar::EPSILON;
ContextFreeGrammar::End ContextFreeGrammar::END;

void ContextFreeGrammar::CheckGrammar() {
    if (!startSymbol)
        setStartSymbol(getDefaultStartSymbol());
    if (!isAugmentedGrammar())
        AugmentGrammar();
    if (!startSymbol)
        SetStartProduction();
}

ContextFreeGrammar::NonTerminal* ContextFreeGrammar::getDefaultStartSymbol() {
    return productions[0]->getLHS();
}

bool ContextFreeGrammar::isAugmentedGrammar() {
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

void ContextFreeGrammar::AugmentGrammar() {
    if (!isAugmentedGrammar()) {
        NonTerminal* newStartSymbol = newNonTerminal(newIdentifier("S'"));
        addNonTerminal(newStartSymbol);
        Production* production = newProduction(newNamedSymbols({ newNamedSymbol(startSymbol), newNamedSymbol(getEnd()) }), true);
        addRule(newRule(newStartSymbol, newProductions(production)));
        setStartSymbol(newStartSymbol);
    }
}

void ContextFreeGrammar::SetStartProduction() {
    if (startSymbol) {
        Rule* startRule = getRule(startSymbol);

        if (startRule->getProductions().size() == 1) {
            Production* startProduction = startRule->getProductions()[0];
            startProduction->setStart();
        }
    }
}

//
//
//

void ContextFreeGrammar::GeneratePrecedences() {
    for (auto rule : rules)
        for (auto production : *rule)
            production->GeneratePrecedenceAndAsscoiativity();
}

// set precedence of production to precedence of rightmost terminal
void ContextFreeGrammar::Production::GeneratePrecedenceAndAsscoiativity() {
    for (auto symbol = crbegin(); symbol != crend(); ++symbol)
        if ((*symbol)->isTerminal()) {
            setPrecedence((*symbol)->asTerminal()->getPrecedence());
            setAssociativity((*symbol)->asTerminal()->getAssociativity());
            return;
        }
}

ContextFreeGrammar::NamedSymbols* ContextFreeGrammar::NamedSymbols::clone() {
	return new NamedSymbols();	// TODO: Implement ContextFreeGrammar::clone(NamedSymbols*) as and do memory allocation
}


std::string ContextFreeGrammar::Terminal::toString() const {
    if (value != "")
        return "\"" + value + "\"";
    else
        return name;
}

std::string ContextFreeGrammar::NamedSymbols::toString() const {
    std::stringstream ss;

    for (auto namedSymbol : getNamedSymbols())
        ss << namedSymbol->toString() << " ";

    return ss.str();
}

std::string ContextFreeGrammar::Production::toString() const {
    std::stringstream ss;
    ss << getLHS()->toString() << ": " << getRHS().toString();
    return ss.str();
}

std::string ContextFreeGrammar::Rule::toString() const {
    std::stringstream ss;

    ss << lhs->toString() << " -> ";

    for (auto production : *productions) {
        if (production == *productions->cbegin())
            ss << "    ";
        else
            ss << "  | ";

        ss << production->toString() << std::endl;
    }

    return ss.str();
}

void ContextFreeGrammar::dump(std::ostream& os) {
    for (auto production : productions)
        production->dump(os);
}

void ContextFreeGrammar::Rule::dump(std::ostream& os) {
    //os << lhs->getName() << " : " << lhs->getType() << " =" << std::endl;
    productions->dump(os);
}

void ContextFreeGrammar::Productions::dump(std::ostream& os) {
    for (auto production : getProductions())
        production->dump(os);
}

void ContextFreeGrammar::Production::dump(std::ostream& os) {
    os << rule->getLHS()->getName() << " : " << getType() << " =" << std::endl;
    for (size_t attribute = 1; attribute < attributes.size(); ++attribute)
        os << attributes[attribute] << " : " << types[attribute] << std::endl;
}

//
//  ContextFreeGrammar - compare()
//

bool ContextFreeGrammar::Identifier::compare(const Identifier* rhs) const {
	return getValue() == rhs->getValue();
}

bool ContextFreeGrammar::StringLiteral::compare(const StringLiteral* rhs) const {
	return getValue() == rhs->getValue();
}

bool ContextFreeGrammar::Terminal::compare(const Symbol* rhs) const {
	return rhs->isTerminal() &&
		getName() == rhs->getName() &&
		getPrecedence() == ((Terminal*)rhs)->getPrecedence() &&
		getAssociativity() == ((Terminal*)rhs)->getAssociativity() &&
		isFinal() == ((Terminal*)rhs)->isFinal();
}
bool ContextFreeGrammar::NonTerminal::compare(const Symbol* rhs) const {
    std::string lhs_name = getName();
    std::string rhs_name = rhs->getName();

    return rhs->isNonTerminal() && lhs_name == rhs_name;
    // return rhs->isNonTerminal() && getName() == rhs->getName();
}

bool ContextFreeGrammar::Epsilon::compare(const Symbol* rhs) const {
	return rhs->isEpsilon();
}
bool ContextFreeGrammar::End::compare(const Symbol* rhs) const {
	return rhs->isEnd();
}

bool ContextFreeGrammar::NamedSymbol::compare(const NamedSymbol* rhs) const {
	bool test = ((name == rhs->name) || (name && rhs->name && name->getName() == rhs->name->getName()))
        && symbol->compare(rhs->symbol);
    return test;
}

bool ContextFreeGrammar::NamedSymbols::compare(const NamedSymbols* rhs) const {
	for (auto l = cbegin(), r = rhs->cbegin(); l != cend(); ++l, ++r)
		if (!(*l)->compare(*r))
			return false;
	return true;
}

bool ContextFreeGrammar::Terminals::compare(const Terminals* rhs) const {
    for (auto l = cbegin(), r = rhs->cbegin(); l != cend(); ++l, ++r)
        if (!(*l)->compare(*r))
            return false;
    return true;
}
bool ContextFreeGrammar::NonTerminals::compare(const NonTerminals* rhs) const {
    for (auto l = cbegin(), r = rhs->cbegin(); l != cend(); ++l, ++r)
        if (!(*l)->compare(*r))
            return false;
    return true;
}

bool compare(const ContextFreeGrammar::Production* lhs, const ContextFreeGrammar::Production* rhs) {
    return lhs->compare(rhs);
}
bool ContextFreeGrammar::Production::compare(const Production* rhs) const {
	if (rule->getLHS()->getName() != rhs->rule->getLHS()->getName())
		return false;
    for (auto l = cbegin(), r = rhs->cbegin(); l != cend(); ++l, ++r) {
        bool tester = (*l)->compare(*r);
        if (!tester)
            return false;
    }
	return true;
}
bool ContextFreeGrammar::Productions::compare(const Productions* rhs) const {
	for (auto l = cbegin(), r = rhs->cbegin(); l != cend(); ++l, ++r)
		if (!(*l)->compare(*r))
			return false;
	return true;
}

bool ContextFreeGrammar::Rule::compare(const Rule* rhs) const {
	return lhs->getName() == rhs->lhs->getName() && productions->compare(rhs->productions);
}

bool ContextFreeGrammar::Rules::compare(const Rules* rhs) const {
    for (auto l = cbegin(), r = rhs->cbegin(); l != cend(); ++l, ++r)
        if (!(*l)->compare(*r))
            return false;
    return true;
}

bool compare(const ContextFreeGrammar* lhs, const ContextFreeGrammar* rhs) {
    bool terminals = lhs->getTerminals().compare(&rhs->getTerminals());
    bool nonTerminals = lhs->getNonTerminals().compare(&rhs->getNonTerminals());
    bool rules = lhs->getRules().compare(&rhs->getRules());

    bool grammar =
        terminals
        && nonTerminals
        && rules;

	return grammar;
}

} // end namespace G
} // end namespace Grammar

// End g/Grammar/Grammar.cpp
