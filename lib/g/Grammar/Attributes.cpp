//
//	g/ParserGenerator/FirstSets.cpp
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

#include "g/Grammar/ContextFreeGrammar.h"
#include "g/Actions.h"
#include "nonstd/Utils.h"
#include <sstream>

namespace G {
namespace Grammar {

void ContextFreeGrammar::GenerateAttributes(Actions* actions, bool isUnion) {
    for (auto rule : getRules())
        rule->GenerateAttributes(actions, isUnion);
}

void ContextFreeGrammar::Rule::GenerateAttributes(Actions* actions, bool isUnion) {
    productions->GenerateAttributes(actions, isUnion);
}

void ContextFreeGrammar::Productions::GenerateAttributes(Actions* actions, bool isUnion) {
    for (auto production : getProductions())
        production->GenerateAttributes(actions, isUnion);
}

void ContextFreeGrammar::Production::GenerateAttributes(Actions* actions, bool isUnion) {
	if (action != -1) {
		size_t attribute = 1;
		for (auto namedSymbol : getRHS()) {
			attributes[attribute] = namedSymbol->getName();
			types[attribute] = namedSymbol->getType(); // TODO: solve
			++attribute;
		}
		actions->SubstituteAttributes((*actions)[action], attributes, types, isUnion, getType(), size());
	}
}

std::string ContextFreeGrammar::Production::GenerateAttributeEnum(int i) {
    std::stringstream ss;

    ss << Indent(i) << "enum attributes {" << std::endl;

    for (size_t attribute = 1; attribute < attributes.size(); ++attribute)
        ss << Indent(i + 4) << attributes[attribute] << " = " << attribute << ";" << std::endl;

    ss << Indent(i) << "};" << std::endl;

    return ss.str();
}

} // end namespace G
} // end namespace Grammar

// End g/ParserGenerator/FirstSets.cpp
