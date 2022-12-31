//
//	g/ParserGenerator/LR1/OutputTables.cpp
//
//  Property and Copyright (c) 2016, 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"
#include "nonstd/deque.h"
#include "nonstd/Utils.h"

#include <map>
#include <deque>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace G {
namespace ParserGenerator {

// TODO: Change relevant Output functions to Print ???

void LR1::PrintTables(std::ostream &os) const {
	os << "        ";
	for (size_t terminal = 1; terminal < grammar->getNumberOfTerminalSymbols(); ++terminal) {
		os << std::setw(8) << grammar->getTerminals()[terminal]->toString(); //.substr(8);
	}
	os << "        ";
	for (size_t nonTerminal = 0; nonTerminal < grammar->getNumberOfNonTerminalSymbols(); ++nonTerminal) {
		os << std::setw(8) << grammar->getNonTerminals()[nonTerminal]->toString(); //.substr(8);
	}
	os << std::endl;

	for (size_t state = 1; state < getNumberOfStates(); ++state) {
		os << std::setw(8) << state;
		os << shiftReduceTable->OutputRow(state, 1, grammar->getNumberOfTerminalSymbols() - 1);
		os << "        ";
		os << gotoTable->OutputRow(state, 1, grammar->getNumberOfNonTerminalSymbols());
		os << std::endl;
	}
	os << std::endl;
}

void LR1::OutputShiftReduceTable(std::ostream &os) {

}

void LR1::OutputGotoTable(std::ostream &os) {

}

//
//
//

void LR1::OutputTablesHXX(std::ostream &os, std::string className) const {
	OutputShiftReduceTableHXX(os, className);
	OutputGotoTableHXX(os, className);
}

void LR1::OutputTablesCXX(std::ostream &os, std::string className) const {
	OutputShiftReduceTableCXX(os, className);
	OutputGotoTableCXX(os, className);
}

void LR1::OutputShiftReduceTableHXX(std::ostream &os, std::string className) const {
	os << shiftReduceTable->OutputPairsHXX(className, "ShiftReduce", "Action") << std::endl;
}
void LR1::OutputShiftReduceTableCXX(std::ostream &os, std::string className) const {
	os << shiftReduceTable->OutputPairsCXX(className, "ShiftReduce", className + "::Action") << std::endl;
}
void LR1::OutputGotoTableHXX(std::ostream &os, std::string className) const {
	os << gotoTable->OutputPairsHXX(className, "Goto", "State") << std::endl;
}
void LR1::OutputGotoTableCXX(std::ostream &os, std::string className) const {
	os << gotoTable->OutputPairsCXX(className, "Goto", "State") << std::endl;
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/OutputTables.cpp
