//
//	g/ParserGenerator/LR1/Output.cpp
//
//  Property and Copyright (c) 2016, 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"
#include <iostream>

namespace G {
namespace ParserGenerator {

void LR1::Output(std::ostream &output) const {
	// Output
	for (auto production : grammar->getProductions()) {
		output << production->getIndex() << " = " << production->toString() << nonstd::endl;
	}
	output << nonstd::endl;

//	AnalyseStates(output);

	output << nonstd::endl;

	output << states.toString(grammar, 4) << nonstd::endl;

	output << nonstd::endl;

	PrintTables(output);    // TODO: Incorrect printout bug !!!
}

void LR1::OutputIncludesHXX(std::ostream &output, std::string className) const {
	vector<std::string> includes = {
		"runtime/lexer/Lexer.h",
		"runtime/parser/" + className + ".h",
		"runtime/Stack.h",
		"runtime/Pairs.h",
	};
	OutputIncludes(output, includes);
	output << "#include <string.h>";
}


void LR1::OutputCodeHXX(std::ostream &output, std::string className) const {

	output << "\t" << "virtual State getStates() {" << nonstd::endl;
	output << "\t\t" << "return " << states.size() << ";" << nonstd::endl;
	output << "\t" << "}" << nonstd::endl;

	output << "\t" << "virtual Action nextState(State state, Input input) {" << nonstd::endl;
	if (rowCompressed) {
		output << "\t\t" << "auto cell = ShiftReduce_states[state - 1];" << nonstd::endl;
		output << "\t\t" << "return cell ? cell->lookup(input) : Action(Action::Function::Error);" << nonstd::endl;
	}
	else
		output << "\t\t" << "return ShiftReduce_states[state - 1].lookup(input);" << nonstd::endl;
	output << "\t" << "}" << nonstd::endl;

	output << "\t" << "virtual State nextGoto(State state, NonTerminal lhs) {" << nonstd::endl;
	if (rowCompressed) {
		output << "\t\t" << "auto cell = Goto_states[state - 1];" << nonstd::endl;
		output << "\t\t" << "return cell ? cell->lookup(lhs) : 0;" << nonstd::endl;
	}
	else
		output << "\t\t" << "return Goto_states[state - 1].lookup(lhs);" << nonstd::endl;
	output << "\t" << "}" << nonstd::endl;

	output << "\t" << "virtual int getAcceptAction(size_t production) {" << nonstd::endl;
	output << "\t\t" << "return ActionMap[production];" << nonstd::endl;
	output << "\t" << "}" << nonstd::endl;

	output << "\t" << "virtual void dispatch(int action) {" << nonstd::endl;
	output << "\t\t" << "(this->*Actions[action])();" << nonstd::endl;
	output << "\t" << "}" << nonstd::endl;

	output << "\t" << "virtual size_t getNumberOfRHSSymbols(unsigned production) {" << nonstd::endl;
	output << "\t\t" << "return rhsSymbols[production];" << nonstd::endl;
	output << "\t" << "}" << nonstd::endl;

	output << "\t" << "virtual NonTerminal getLHSSymbolIndex(unsigned production) {" << nonstd::endl;
	output << "\t\t" << "return production2lhs[production];" << nonstd::endl;
	output << "\t" << "}" << nonstd::endl;

	output << "\t" << "virtual size_t getNumberOfTerminals() {" << nonstd::endl;
	output << "\t\t" << "return " << grammar->getNumberOfTerminalSymbols() << ";" << nonstd::endl;
	output << "\t" << "}" << nonstd::endl;

	output << "\t" << "virtual std::string getTerminalName(size_t index) {" << nonstd::endl;
	output << "\t\t" << "return (index >= 0 && index < getNumberOfTerminals()) ? Terminals[index] : \"<\" + std::to_string(index) + \">\";" << nonstd::endl;
	output << "\t" << "}" << nonstd::endl;

	output << "\t" << "virtual std::string getNonTerminalName(size_t index) {" << nonstd::endl;
	output << "\t\t" << "return NonTerminals[index - 1];" << nonstd::endl;
	output << "\t" << "}" << nonstd::endl;

	output << "\t" << "virtual void reportError(State state, Input input);" << nonstd::endl;

	output << nonstd::endl;

	output << "\t" << "static const char* Terminals[" << grammar->getTerminals().size() << "];" << nonstd::endl;
	output << "\t" << "static const char* NonTerminals[" << grammar->getNonTerminals().size() << "];" << nonstd::endl;

	output << "\t" << "enum Terminal {" << nonstd::endl;
	for (size_t terminal = 0, terminals = grammar->getTerminals().size(); terminal < terminals; ++terminal) {
		if (terminal < terminals - 1)
			output << "\t\t" << grammar->getTerminals()[terminal]->getName() << "," << nonstd::endl;
		else
			output << "\t\t" << grammar->getTerminals()[terminal]->getName() << nonstd::endl;
	}

	output << "\t" << "};" << nonstd::endl;

	//    output << "\t" << "static size_t production[" << lr1->states.size() << "];" << nonstd::endl;
	output << "\t" << "static size_t rhsSymbols[" << grammar->getProductions().size() << "];" << nonstd::endl;
	output << "\t" << "static NonTerminal production2lhs[" << grammar->getProductions().size() << "];" << nonstd::endl;

	output << "\t" << "static int ActionMap[" << grammar->getProductions().size() << "];" << nonstd::endl;
}


void LR1::OutputCodeCXX(std::ostream &output, std::string className) const {

	output << "const char* " << className << "::Terminals[" << grammar->getNumberOfTerminals() << "] = {" << nonstd::endl;
	for (size_t terminal = 0, terminals = grammar->getNumberOfTerminals(); terminal < terminals; ++terminal) {
		if (terminal < terminals - 1)
			output << "\t" << "\"" << grammar->getTerminals()[terminal]->getName() << "\"" << "," << nonstd::endl;
		else
			output << "\t" << "\"" << grammar->getTerminals()[terminal]->getName() << "\"" << nonstd::endl;
	}
	output << "};" << nonstd::endl;

	output << "const char* " << className << "::NonTerminals[" << grammar->getNumberOfNonTerminals() << "] = {" << nonstd::endl;
	for (size_t nonterminal = 0, nonterminals = grammar->getNumberOfNonTerminals(); nonterminal < nonterminals; ++nonterminal) {
		if (nonterminal < nonterminals - 1)
			output << "\t" << "\"" << grammar->getTerminals()[nonterminal]->getName() << "\"" << "," << nonstd::endl;
		else
			output << "\t" << "\"" << grammar->getTerminals()[nonterminal]->getName() << "\"" << nonstd::endl;
	}
	output << "};" << nonstd::endl;

	output << "size_t " << className << "::rhsSymbols[" << grammar->getProductions().size() << "] = {" << nonstd::endl;
	for (size_t production = 0, productions = grammar->getProductions().size(); production < productions; ++production)
		if (production < productions - 1)
			output << "\t" << grammar->getProductions()[production]->size() << "," << nonstd::endl;
		else
			output << "\t" << grammar->getProductions()[production]->size() << nonstd::endl;
	output << "};" << nonstd::endl;

	output << className << "::NonTerminal " << className << "::production2lhs[" << grammar->getProductions().size() << "] = {" << nonstd::endl;
	for (size_t production = 0, productions = grammar->getProductions().size(); production < productions; ++production) {
		output << "\t" << grammar->getProductions()[production]->getLHS()->getIndex();
		if (production < productions - 1)
			output << "," << nonstd::endl;		// TODO: do for all
	}
	output << "};" << nonstd::endl;

	output << "int " << className << "::ActionMap[" << grammar->getProductions().size() << "] = {" << nonstd::endl;
	auto productions = grammar->getProductions();
	for (size_t production = 0; production < productions.size(); ++production) {
		auto action = productions[production]->getAction();
		output << "\t" << action;
		if (production < productions.size())
			output << ",";
		else
			output << " ";
		output << " // " << production << nonstd::endl;
	}
	output << "};" << nonstd::endl;
}

void LR1::OutputTerminals(std::ostream& output) const {
	std::cout << "Terminals:" << nonstd::endl;
	for (auto terminal : grammar->getTerminals())
		std::cout << "\t" << terminal->getIndex() << ": " << terminal->getName() << nonstd::endl;
}
void LR1::OutputNonTerminals(std::ostream& output) const {
	std::cout << "NonTerminals:" << nonstd::endl;
	for (auto nonTerminal : grammar->getNonTerminals())
		std::cout << "\t" << nonTerminal->getIndex() << ": " << nonTerminal->getName() << std::endl;
}

void LR1::OutputStates(std::ostream& output) const {
	std::cout << "States:" << nonstd::endl;
	for (auto state : states)
		output << state->toString(grammar, 4) << nonstd::endl << nonstd::endl;
}


} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/Output.cpp
