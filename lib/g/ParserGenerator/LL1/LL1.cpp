//
//	g/ParserGenerator/LL1/LL1.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LL1/LL1.h"

namespace G {
namespace ParserGenerator {

std::string LL1::Name = "LL(1)";

void LL1::GenerateStatesAndTransitions() {
    for (auto nonTerminal : getNonTerminals()) {
        State* state = new State(nonTerminal);
        for (auto production : getProductions()) {
            for (auto terminal : getTerminals())
                state->transitions.insert(std::pair<Terminal*, Production*>(terminal, production));
        }
    }
}

bool LL1::CheckForConflicts() {
    for (auto state : states)
        for (auto terminal : getTerminals())
            if (state->transitions.count(terminal) > 1)
				for (auto iterator = state->transitions.find(terminal); iterator->first == terminal; ++iterator)
				conflicts.push_back(new Conflict(state, terminal, iterator->second));

    return conflicts.size() != 0;
}

void LL1::GenerateDFA() {
	dfa = new Generator::DFA(getNumberOfTerminals());

	for (auto production : getProductions()) {
		NonTerminal* nonTerminal = production->getLHS();
		bitset selectSet = production->getSelectSet();
		for (bitset::iterator terminal = selectSet.begin(), end = selectSet.end(); terminal != end; ++terminal)
			dfa->getTable()[nonTerminal->getIndex()][terminal.index()] = production->getIndex();
	}
}

void LL1::GeneratePushTable() {
	for (auto production : getProductions()) {
		ContextFreeGrammar::NamedSymbols rhsSymbols = production->getRHS();
		for (unsigned index = 0; index < rhsSymbols.size(); ++index) {
			ContextFreeGrammar::Symbol* symbol = rhsSymbols[index]->getSymbol();
			pushTable[production->getIndex()][index] =
				symbol->isTerminal() ? LL1::Symbol(LL1::Symbol::Terminal, symbol->getIndex())
				                     : LL1::Symbol(LL1::Symbol::NonTerminal, symbol->getIndex());
		}
	}
}

void LL1::AnalyseStates(std::ostream &os) {
}

std::string LL1::State::toString(ContextFreeGrammar* grammar, int i) const { // TODO: Move to LL1/toString.cpp
	std::stringstream ss;

	return ss.str();
}

bool LL1::compare(const Machine* rhs) const {
	return false;		// TODO: !!!
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LL1/LL1.cpp
