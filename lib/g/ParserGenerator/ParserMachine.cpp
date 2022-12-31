//
//	g/ParserGenerator/ParserMachine.cpp - Parser Machine methods
//
//  Property and Copyright (c) 2018-2022 Aaron Nathaniel Gray
//

#include "g/Grammar/ContextFreeGrammar.h"
#include "g/ParserGenerator/ParserMachine.h"
#include "g/Actions.h"
#include "nonstd/Utils.h"

namespace G {
namespace ParserGenerator {

	bool compare(const ParserMachine* lhs, const ParserMachine* rhs) {
		bool grammar = compare(lhs->grammar, rhs->grammar);

		bool result = grammar;

		return result;
	}
}
}

// End g/ParserGenerator/ParserMachine.cpp - Parser Machine methods
