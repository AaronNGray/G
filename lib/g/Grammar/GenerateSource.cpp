//
//	lib/Grammar/GenerateSource.cpp
//
//  Copyright (c) 2017 Aaron Nathaniel Gray under the MIT License
//

#include <string>

#include "g/Grammar/ContextFreeGrammar.h"
#include "nonstd/Utils.h"

namespace G {
namespace Grammar {

void ContextFreeGrammar::GenerateSourceH(std::string name, std::ostream& output) const {
}

std::string GenerateAssociativity(ContextFreeGrammar::Associativity associativity ) {
	switch (associativity) {
		case ContextFreeGrammar::None:
			return "ContextFreeGrammar::None";
		case ContextFreeGrammar::Left:
			return "ContextFreeGrammar::Left";
		case ContextFreeGrammar::Right:
			return "ContextFreeGrammar::Right";
		default:
			throw;
	}
}

void ContextFreeGrammar::GenerateSourceCXX(std::string name, std::ostream& output) const {

	output << "ContextFreeGrammar* " << name << "_bootstrap() {" << std::endl;
	output << "\tContextFreeGrammar* " << name << "_ContextFreeGrammar = new ContextFreeGrammar(\"" << name << "\");" << nonstd::endl;
	output << nonstd::endl;

	for (auto terminal : terminals)
		if (!(terminal->isEpsilon() || terminal->isEnd()))
			output << "\tContextFreeGrammar::Terminal *" << terminal->getName() << " = "
				   << name << "_ContextFreeGrammar->addTerminal("
				   << "\"" << terminal->getName() << "\","
				   << (terminal->hasType() ? ("\"" + terminal->getType() + "\"") : "\"\"") << ", "
				   << (terminal->hasValue() ? ("\"" + terminal->getValue() + "\"") : "\"\"") << ", "
				   << GenerateAssociativity(terminal->getAssociativity()) << ", "
				   << terminal->getPrecedence() << ", "
				   << (terminal->isFinal() ? "true" : "false")
				   << ");" << nonstd::endl;
	output << nonstd::endl;
	output << "\tContextFreeGrammar::Terminal *EPSILON = " << name << "_ContextFreeGrammar->getTerminal(\"EPSILON\");" << nonstd::endl;
	output << "\tContextFreeGrammar::Terminal *END = " << name << "_ContextFreeGrammar->getTerminal(\"END\");" << nonstd::endl;
	output << nonstd::endl;

	for (auto nonTerminal : nonTerminals)
		output << "\tContextFreeGrammar::NonTerminal *" << generateSymbolString(nonTerminal->getName()) << " = "
		       << name << "_ContextFreeGrammar->addNonTerminal(\"" << nonTerminal->getName()
		       << "\"" << (nonTerminal->hasType() ? (", \"" + nonTerminal->getType()) + "\"" : "")
			   << ");" << nonstd::endl;
	output << nonstd::endl;

	if (getStartSymbol())
		output << "\t" << name << "_ContextFreeGrammar->setStartSymbol(" << generateSymbolString(getStartSymbol()->getName()) << ");" << nonstd::endl;

	for (auto rule : rules) {
		output << rule->GenerateSource(name);
	}
/*
	output << "\t" << "Actions bootstrapActions = ";
	output << "\t" << getActions()->Generate(0) << ";" << nonstd::endl;
	output << nonstd::endl;
*/
	output << "\t" << name << "_ContextFreeGrammar->setActions(&bootstrapActions);" << nonstd::endl;
	output << nonstd::endl;

	output << "\t" << "return " << name << "_ContextFreeGrammar;" << nonstd::endl;
	output << "}";
}

std::string ContextFreeGrammar::Rule::GenerateSource(std::string name) const {
	return "\t" + name + "_ContextFreeGrammar->addRule(" + generateSymbolString(getLHS()->getName()) + ", " + productions->GenerateSource(name) + ");" + nonstd::endl;
}

std::string ContextFreeGrammar::Productions::GenerateSource(std::string name) const {
	std::string os;

	os += "{" + nonstd::endl;

	for (auto production = begin(); production != end(); ++production) {
		os += "\t\t" + (*production)->GenerateSource(name);
		if (production != clast())	os += ",";
		os += nonstd::endl;
	}

	os += "\t}";
	return os;
}

std::string ContextFreeGrammar::Production::GenerateSource(std::string name) const {

	if (!getRHS().isEpsilon())
		return name + "_ContextFreeGrammar->addProduction(" + getRHS().GenerateSource(name) + ", " + std::to_string(getAction()) + ")";
	else
		return name + "_ContextFreeGrammar->addProduction({}, " + std::to_string(getAction()) + ")";
}

std::string ContextFreeGrammar::NamedSymbols::GenerateSource(std::string name) const {
	std::string os;

	os += "{" + nonstd::endl;
	for (auto namedSymbol = begin(); namedSymbol != end(); ++namedSymbol) {
		os += "\t\t\t" + (*namedSymbol)->GenerateSource(name);
		if (namedSymbol != clast()) os += "," + nonstd::endl;
	}
	os += nonstd::endl;
	os += "\t\t}";

	return os;
}

std::string ContextFreeGrammar::NamedSymbol::GenerateSource(std::string grammarName) const {
	return  grammarName + "_ContextFreeGrammar->newNamedSymbol(" + ((name != nullptr) ? "\"" + name->getValue() + "\", " : "") + symbol->GenerateSource(grammarName) + ")";
}

std::string ContextFreeGrammar::NonTerminal::GenerateSource(std::string grammarName) const {
	return name;
}

std::string ContextFreeGrammar::Terminal::GenerateSource(std::string grammarName) const {
	return name;
}

} // end namespace Grammar
} // end namespace G

// End lib/Grammar/GenerateSource.cpp
