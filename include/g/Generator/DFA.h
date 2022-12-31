//
//  g/Generator/DFA.h - compile time Determinate Finite Automata class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <set>
#include <map>
#include <iostream>

#include "nonstd/bitset.h"
#include "g/Table.h"

namespace G {
namespace Generator {

class DFA {
	DFA();
public:
	DFA(unsigned int inputs) : inputs(inputs), states(1) {
		table = new Table<size_t, unsigned int, 0, PairedArray<unsigned int, unsigned int>>(inputs);
	}

	int getNumberOfStates() { return states; } // TODO: - 1
	unsigned int getNumberOfInputs() { return inputs; }

	int newState() { return states++; }

	Table<size_t, unsigned int, 0, PairedArray<unsigned int, unsigned int>>& getTable() { return *table; }

	void OutputDFACXX(std::ostream &os, std::string className);
	void OutputAcceptCXX(std::ostream &os, std::string className);
	void OutputH(std::ostream &os, std::string className);
	void OutputDFA(std::ostream &os);
	void OutputAccept(std::ostream &os);

	friend bool compare(const DFA* lhs, const DFA* rhs);

protected:
	unsigned int inputs;
	signed int states;

	Table<size_t, unsigned int, 0, PairedArray<unsigned int, unsigned int>>* table; // TODO: Check if 0 based
	std::map<signed int, signed int> accept;
};

} // end namespace Generator
} // end namespace G

// End g/Generator/DFA.h - compile time Determinate Finite Automata class
