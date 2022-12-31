//
//	g/ParserGenerator/LR1/GenerateAcceptStates.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"

namespace G {
namespace ParserGenerator {

void LR1::GenerateAcceptStates() {
    acceptTable.resize(states.size());
    for (auto state : states) {
//		std::cout << state->index << " " << state->production->getIndex() << " " << state->production->getAction()->getAction() << (state->production->getAction() ? state->production->getAction()->getIndex() : -1) << std::endl;
        if (state->isReduction() && state->production->getAction())
            acceptTable[state->index] = state->production->getAction();
        else
            acceptTable[state->index] = -1;
    }
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/GenerateAcceptStates.cpp
