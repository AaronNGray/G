//
//	g/Grammar/GenerateGrammar.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include <g/Grammar/ContextFreeGrammar.h>
#include <nonstd/Utils.h>

namespace G {
namespace Grammar {

std::string ContextFreeGrammar::GenerateGrammar() const {
	std::string os;
	for (auto rule : getRules()) {
		os += rule->GenerateGrammar();
	}
	return os;
}

std::string ContextFreeGrammar::Rule::GenerateGrammar() const {
	return productions->GenerateGrammar();
}

std::string ContextFreeGrammar::Productions::GenerateGrammar() const {
	std::string os;

	for (auto production : getProductions()) {
		os += production->GenerateGrammar();
		os += nonstd::endl;
	}

	return os;
}

std::string ContextFreeGrammar::Production::GenerateGrammar() const {
	return "production " + getLHS()->GenerateGrammar() + " = " + getRHS().GenerateGrammar() + ";";
}

std::string ContextFreeGrammar::NamedSymbols::GenerateGrammar() const {
	std::string os;

	for (auto symbol : getNamedSymbols())
		os += symbol->GenerateGrammar() + " ";

	return os;
}

std::string ContextFreeGrammar::NamedSymbol::GenerateGrammar() const {
	std::string os;

	if (name)
		os += name->getValue() + std::string(":");

	os += symbol->GenerateGrammar();

	return os;
}

std::string ContextFreeGrammar::NonTerminal::GenerateGrammar() const {
	return getName();
}

std::string ContextFreeGrammar::Terminal::GenerateGrammar() const {
	return ((value != "") ? ("\"" + value + "\""): name);
}

} // end namespace G
} // end namespace Grammar

// End g/Grammar/GenerateGrammar.cpp
