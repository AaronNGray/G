//
//	g/ParserGenerator/LR1/Generate.cpp - Generate LR1 Machine
//
//  Property and Copyright (c) 2017-2022 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"

namespace G {
namespace ParserGenerator {

void LR1::Generate() {

	// Generate States
	GenerateStates();
	GenerateStateProductions();

	size_t conflicts = CheckReductionsPerState();

	if (conflicts)
		std::cout << "total reduce/reduce conflicts: " << conflicts << nonstd::endl;

	// Generate actions and Resolve Conflicts
	GenerateActions();

	// Generate Shift Reduce Table
	GenerateShiftReduceTable();

	// Generate Goto Table
	GenerateGotoTable();
	GenerateAcceptStates(); // TODO: remove
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/Generate.cpp - Generate LR1 Machine
