//
//  g/Generator/DFA.cpp
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/Generator/DFA.h"

#include "nonstd/Utils.h"

#include <deque>
#include <iomanip>
#include <cassert>

namespace G {
namespace Generator {

static std::string generateType(unsigned int values, bool _signed = false) {
	if (values < (_signed ? (unsigned)128 : (unsigned)254))
		return _signed ? "signed char" : "unsigned char";
	else
		return _signed ? "signed short" : "unsigned short";
}

void DFA::OutputDFACXX(std::ostream &os, std::string className) {
	os << generateType(getNumberOfStates(), true) << " " << className << "::dfa[" << getNumberOfStates() << "][" << getNumberOfInputs() << "]" << " = {" << std::endl;

	os << "//        ";
	for (unsigned int ec = 0; ec < getNumberOfInputs(); ++ec)
		os << std::setw(5) << ec;
	os << std::endl;

	for (int state = 0; state < getNumberOfStates(); ++state) {
		os << "/* " << std::setw(3) << state + 1 << " */ {";

		for (unsigned int ec = 0; ec < getNumberOfInputs(); ++ec) {
			os << std::setw(4) << (signed int)(*table)[state][ec] << ((ec != getNumberOfInputs() - 1) ? "," : "");
		}
		os << " }" << ((state != getNumberOfStates() - 1) ? "," : " ") << "  // " << state + 1 << std::endl;
	}
	os << "};" << std::endl << std::endl;
}

void DFA::OutputAcceptCXX(std::ostream &os, std::string className) {
	os << generateType(getNumberOfStates(), true) << " " << className << "::accept[" << getNumberOfStates() << "] = {" << std::endl;

	for (size_t state = 0; state < accept.size(); ++state) {
		os << "\t" << accept[state] << ((state != getNumberOfStates() - 1) ? "," : " ") << "  // " << state << std::endl;
	}
	os << "};" << std::endl;
}

void DFA::OutputH(std::ostream &os, std::string className) {

}

void DFA::OutputDFA(std::ostream &os) {
	for (size_t c = 0; c < getNumberOfInputs(); ++c)
		os << std::setw(6) << c;

	os << std::endl;

	for (int state = 0; state < getNumberOfStates(); ++state) {
		os << std::setw(5) << std::left << state + 1;
		for (size_t ec = 0; ec < getNumberOfInputs(); ++ec) {
			os << std::setw(6) << (signed int)(*table)[state][ec];
		}
	}
}

void DFA::OutputAccept(std::ostream &os) {
	for (size_t state = 0; state < accept.size(); ++state)
		os << "\t" << state << "\t" << accept[state] << std::endl;
}

bool compare(const DFA* lhs, const DFA* rhs) {
	bool inputs = (lhs->inputs == rhs->inputs);
	bool states = (lhs->states == rhs->states);
	bool table = compare(lhs->table, rhs->table);
	bool accept = (lhs->accept == rhs->accept);

	bool result =
		inputs &&
		states &&
		table &&
		accept;

	if (!result) {
		std::cout << "\t\t    " "inputs: ";
		std::cout << nonstd::generateBoolean(inputs) << nonstd::endl;

		std::cout << "\t\t    " "states: ";
		std::cout << nonstd::generateBoolean(states) << nonstd::endl;

		std::cout << "\t\t    " "table: ";
		std::cout << nonstd::generateBoolean(table) << nonstd::endl;

		std::cout << "\t\t    " "accept: ";
		std::cout << nonstd::generateBoolean(accept) << nonstd::endl;

		std::cout << "\t    " << nonstd::generateBoolean(result) << nonstd::endl;
	}

	return result;
}

} // end namespace Generator
} // end namespace G

// End g/Generator/DFA.cpp
