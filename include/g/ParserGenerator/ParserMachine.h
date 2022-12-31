//
//  g/ParserGenerator/ParserMachine.h - Parser Machine header
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include "g/Grammar/ContextFreeGrammar.h"
#include "nonstd/Utils.h"

namespace G {
namespace ParserGenerator {

using namespace G::Grammar;

class ParserMachine {
public:
	ParserMachine() {}
	ParserMachine(std::string name, ContextFreeGrammar* grammar, Actions* actions) : grammar(grammar), actions(actions) {}
	ParserMachine(std::string name, ContextFreeGrammar* grammar, std::initializer_list<Action> actions) : grammar(grammar), actions(actions) {}

	ContextFreeGrammar* grammar;
	Actions actions;

	bool compare(const ParserMachine* lhs, const ParserMachine* rhs);

}; // End class ParserMachine

} // end namespace ParserGenerator
} // end namespace G

// End g/ParserGenerator/ParserMachine.h - Parser Machine header
