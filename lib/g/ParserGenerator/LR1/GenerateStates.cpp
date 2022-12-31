//
//	g/ParserGenerator/LR1/GenerateStates.cpp
//
//  Property and Copyright (c) 2016, 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"
#include "nonstd/deque.h"
#include "nonstd/Utils.h"

namespace G {
namespace ParserGenerator {

void LR1::GenerateStates() {
	States<deque> T;

	// Initial start seed state T <- { Closure({[S' -> $, $]}) }
	Items start(Closure(Item(grammar->getStartProduction(), grammar->getEnd()->getFirstSet())));
	State* state = states.newState(start);
	T.push_back(state);

	assert((state->items.size()));

	// while T is not empty
	while (!T.empty()) {
		// get a state from T
		State* state = T.pop_front();
		states.insert(state);

		// iterate through items collecting symbols and reductions
		ContextFreeGrammar::Symbols symbols;

		for (State::iterator item = state->begin(); item != state->end(); ++item) {
			// shift or reduction ?
			if (item->hasMove()) {
				ContextFreeGrammar::Symbol* symbol = item->rightOfDot();

				if (!symbols.exists(symbol))
					symbols.push_back(symbol);
			}
			else
				state->addReduction(&*item);
		}

		// process shifts propogating new states
		for (auto symbol : symbols)
		{
			// J <- Goto(I, X)
			Items J = Goto(*state, symbol);
			State* S;

			// if J is not empty and J is not in T and J is not in States
			// States <- States U { I -> J }
			if (!(S = T.find(J)) && !(S = states.find(J))) {
				S = states.newState(J);
				T.push_back(S);
			}

			state->addShift(symbol, S);
		} // end for symbol : symbols

	} // end while T is not empty
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/GenerateStates.cpp
