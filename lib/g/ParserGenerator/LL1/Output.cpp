//
//	g/ParserGenerator/LL1/Output.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LL1/LL1.h"

namespace G {
namespace ParserGenerator {

void LL1::Output(std::ostream& os) const {
	std::cout << "test";
}

void LL1::OutputIncludesHXX(std::ostream &os, std::string className) const {

}

void LL1::OutputCodeHXX(std::ostream &os, std::string className) const {
}
void LL1::OutputCodeCXX(std::ostream &os, std::string className) const {
}

void LL1::OutputTablesHXX(std::ostream &os, std::string className) const {

}
void LL1::OutputTablesCXX(std::ostream &os, std::string className) const {

}

void LL1::OutputTerminals(std::ostream& output) const {
	std::cout << "Terminals:" << nonstd::endl;
	for (auto terminal : grammar->getTerminals())
		std::cout << "\t" << terminal->getIndex() << ": " << terminal->getName() << nonstd::endl;
}
void LL1::OutputNonTerminals(std::ostream& output) const {
	std::cout << "NonTerminals:" << nonstd::endl;
	for (auto nonTerminal : grammar->getNonTerminals())
		std::cout << "\t" << nonTerminal->getIndex() << ": " << nonTerminal->getName() << std::endl;
}

void LL1::OutputStates(std::ostream& output) const {
	std::cout << "States:" << nonstd::endl;
	for (auto state : states)
		output << state->toString(grammar, 4) << nonstd::endl << nonstd::endl; // TODO: LL1::State::toString()
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LL1/Output.cpp
