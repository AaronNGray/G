//
//	g/ParserGenerator/LR0/GenerateActions.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR0/LR0.h"
#include "nonstd/deque.h"
#include "nonstd/Utils.h"
#include <map>

namespace G {
namespace ParserGenerator {

void LR0::GenerateActions() {
	for (auto state : states)
		state->GenerateActions(grammar);
}

//

void LR0::State::GenerateActions(ContextFreeGrammar* grammar) {

	// select correct item to reduce by, checking all reduce-reduce conflicts
	std::map<size_t, ContextFreeGrammar::Production*> selectedReductions;

	if (reductions.size()) {
		for (auto terminal : grammar->getTerminals()) {
			ContextFreeGrammar::Production* selectedProduction = nullptr;

			for (auto item : reductions) {
				ContextFreeGrammar::Production* production = item->getProduction();
				size_t productionIndex = production->getIndex();

				if (selectedProduction == nullptr || productionIndex < selectedProduction->getIndex())
					selectedProduction = item->getProduction();
			}
			if (selectedProduction) {
				selectedReductions[terminal->getIndex()] = selectedProduction;
			}
		}
	}

	// generate action for lookahead, checking for shift/reduce conflicts
	for (auto terminal : grammar->getTerminals()) {
		size_t terminalIndex = terminal->getIndex();
		State* state = shifts[terminal->asSymbol()];
		ContextFreeGrammar::Production* production = selectedReductions[terminalIndex];

		// check if reduction avalable
		if (production) {
			// check if shift/reduce conflict
			if (state) {
				size_t stateIndex = state->getIndex();
				// shift/reduce conflict
				// if shift symbol has higher precedence than production precedence
				if (terminal->getPrecedence() > production->getPrecedence())
					// then shift
					setAction(terminal, ACTION(ACTION::Function::Shift, stateIndex));
				// else if equal then if the associativity of the production is left
				else if (production->getAssociativity() == ContextFreeGrammar::Associativity::Left)
					// then reduce
					setAction(terminal, ACTION(ACTION::Function::Reduce, production->getIndex()));
				else
					// else shift
					setAction(terminal, ACTION(ACTION::Function::Shift, stateIndex));
			}
			else
				// else reduction
				setAction(terminal, ACTION(ACTION::Function::Reduce, production->getIndex()));
		}
		else if (state) {
			// shift with no conflict
			setAction(terminal, ACTION(ACTION::Function::Shift, state->getIndex()));
		}
		// else Error
	} // end for terminal
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR0/GenerateActions.cpp

// TODO: Getting ACTION::Function::ERROR's coming through into Pair tables !!!
// TODO: Reintroduce State 0, do for folk of old working test3 version as verification !
// TODO: REDUCE 0 should not be masked by ACCEPT, reintroduce $end and $accept production - DONE
