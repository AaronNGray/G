//
//  g/LexicalAnalyserGenerator/LexicalContext.cpp
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "g/LexicalAnalyserGenerator/LexicalMachine.h"
#include "g/LexicalAnalyserGenerator/LexicalContext.h"
#include "g/LexicalAnalyserGenerator/DFA.h"

#include "nonstd/Utils.h"

namespace G {
namespace LexicalAnalyserGenerator {

void LexicalContext::addEquivalenceSets() {
    for (unsigned int position = 0; position < regularGrammar->getNumberOfPositions(); ++position)
        if (!regularGrammar->isEnd(position))
            addEquivalenceSet(regularGrammar->getCharacterClassFromPos(position), position);
}

void LexicalContext::addEquivalenceSet(CharacterClass& cc, unsigned int position) {
    positionToSet[position] = machine->addEquivalenceSet(cc);
}

void LexicalContext::Index() {
    regularGrammar->Index();
}

void LexicalContext::GenerateFollowPos() {
    regularGrammar->followpos();
}

void LexicalContext::Generate(DFA* dfa) {
    startState = dfa->GenerateRG2DFA(this);
}

void LexicalContext::Dump(std::ostream &output, unsigned indent) const {
	indent += 4;
	output << Indent(indent) << "name = " << name << std::endl;
	output << Indent(indent) << "className = " << className << std::endl;
	output << Indent(indent) << "compressed = " << compressed << std::endl;
	output << Indent(indent) << "regularGrammar = " << regularGrammar->toString() << std::endl;

	output << Indent(indent) << "positionToSet = {" << std::endl;
	for (auto i = positionToSet.begin(), e = positionToSet.end(); i != e; ++i)
		output << Indent(indent + 4) << i->first << " = " << i->second << std::endl;
	output << Indent(indent) << "}" << std::endl;
}

bool compare(const LexicalContext* lhs, const LexicalContext* rhs) {

	//std::cout << "Context: " << lhs->name << std::endl;
	bool name = (lhs->name == rhs->name);
	bool className = (lhs->className == rhs->className);
	bool regularGrammar = compare(lhs->regularGrammar, rhs->regularGrammar);
	bool positionToSet = (lhs->positionToSet == rhs->positionToSet);
	bool startState = (lhs->startState == rhs->startState);
	bool compressed = (lhs->compressed == rhs->compressed);

	bool result =
		name &&
		className &&
		regularGrammar &&
		positionToSet &&
		startState &&
		compressed;

	if (!result) {
		std::cout << "\t\t" "name: " << nonstd::generateBoolean(name) << nonstd::endl;
		std::cout << "\t\t" "className: " << nonstd::generateBoolean(className) << nonstd::endl;

		std::cout << "\t\t" "regularGrammar: " << nonstd::generateBoolean(regularGrammar) << nonstd::endl;
		if (!regularGrammar) {
			std::cout << lhs->regularGrammar->prettyPrint(16);
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << rhs->regularGrammar->prettyPrint(16);
			std::cout << std::endl;
			std::cout << std::endl;
		}

		std::cout << "\t\t" "compressed" << nonstd::generateBoolean(compressed) << nonstd::endl;
		std::cout << "\t\t" "positionToSet" << nonstd::generateBoolean(positionToSet) << nonstd::endl;
		std::cout << "\t\t" "startState" << nonstd::generateBoolean(startState) << nonstd::endl;
		std::cout << "\t\t" "compressed" << nonstd::generateBoolean(compressed) << nonstd::endl;
	}

	return result;
}

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/LexicalContext.cpp
