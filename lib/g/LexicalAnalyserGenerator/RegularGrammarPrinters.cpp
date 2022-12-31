//
//  g/LexicalAnalyserGenerator/RegularGrammarPrinters.cpp - Regular Grammar Printers
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include <sstream>
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "nonstd/Utils.h"

namespace G {
namespace LexicalAnalyserGenerator {

// toString(RegularGrammar *root)

std::string RegularGrammar::CharacterClass::toString(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << "CharacterClass('" << characterClass.toString() << "')";

    return ss.str();
}


std::string RegularGrammar::End::toString(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << "End(";
    ss << position;

    ss << ", ";

    if (!root->pos[position].isEmpty())
        ss << root->pos[position].toString();
    else
        ss << "<empty>";

    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Sequence::toString(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << "Sequence(";
    ss << re1->toString(root);
    ss << ", ";
    ss << re2->toString(root);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Selection::toString(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << "Selection(";
    ss << re1->toString(root);
    ss << ", ";
    ss << re2->toString(root);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Kleene::toString(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << "Kleene(";
    ss << re->toString(root);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Optional::toString(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << "Optional(";
    ss << re->toString(root);
    ss << ")";
    return ss.str();
}

// toRE(RegularGrammar *root)

std::string RegularGrammar::CharacterClass::toRE(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << root->getCharacterClassFromPos(position).toString();
    return ss.str();
}

std::string RegularGrammar::End::toRE(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << "#";
    return ss.str();
}

std::string RegularGrammar::Sequence::toRE(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << "(";
    ss << re1->toRE(root);
    ss << re2->toRE(root);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Selection::toRE(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << "(";
    ss << re1->toRE(root);
    ss << "|";
    ss << re2->toRE(root);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Kleene::toRE(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << re->toRE(root);
    ss << "*";
    return ss.str();
}

std::string RegularGrammar::Optional::toRE(const RegularGrammar *root) const {
    std::stringstream ss;
    ss << re->toRE(root);
    ss << "?";
    return ss.str();
}

//

// prettyPrint()

std::string RegularGrammar::CharacterClass::prettyPrint(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
	ss << "CharacterClass('" << characterClass.toString() << "'";

	if (position != -1) {
		ss << ", " << position << ", ";

		if (!root->pos[position].isEmpty())
			ss << root->pos[position].toString();
		else
			ss << "<empty>";
	};
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::End::prettyPrint(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
    ss << "End(";

	if (position != -1) {
		ss << position << ", ";

		if (!root->pos[position].isEmpty())
			ss << root->pos[position].toString();
		else
			ss << "<empty>";
	};
	ss << ")";
    return ss.str();
}

std::string RegularGrammar::Sequence::prettyPrint(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
    ss << "Sequence(" << nonstd::endl;
    ss << re1->prettyPrint(root, indent);
    ss << ", " << nonstd::endl;
    ss << re2->prettyPrint(root, indent) << nonstd::endl;
    ss << Indent(indent);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Selection::prettyPrint(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
    ss << "Selection(" << nonstd::endl;
    ss << re1->prettyPrint(root, indent);
    ss << ", " << nonstd::endl;
    ss << re2->prettyPrint(root, indent) << nonstd::endl;
    ss << Indent(indent);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Kleene::prettyPrint(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
    ss << "Kleene(" << nonstd::endl;
    ss << re->prettyPrint(root, indent) << nonstd::endl;
    ss << Indent(indent);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Optional::prettyPrint(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
    ss << "Optional(" << nonstd::endl;
    ss << re->prettyPrint(root, indent) << nonstd::endl;
    ss << Indent(indent);
    ss << ")";
    return ss.str();
}

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/RegularGrammarPrinters.cpp - Regular Grammar Printers
