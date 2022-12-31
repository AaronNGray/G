//
//  g/LexicalAnalyserGenerator/toSource.cpp - Regular Grammar AST to source code
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include <sstream>
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "nonstd/Utils.h"

namespace G {
namespace LexicalAnalyserGenerator {

std::string RegularGrammar::toSource(int indent) const {
    std::stringstream ss;
    ss << "new RegularGrammar(" + nonstd::endl + root->toSource(this, indent) + nonstd::endl;
	ss << Indent(indent) << ")" + nonstd::endl;
    return ss.str();
}

std::string RegularGrammar::CharacterClass::toSource(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
    ss << "RegularGrammar::newCharacterClass(" << characterClass.toSource() << ")";
    return ss.str();
}

std::string RegularGrammar::End::toSource(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent) << "RegularGrammar::newEnd(" << action << ")";
    return ss.str();
}

std::string RegularGrammar::Sequence::toSource(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
    ss << "RegularGrammar::newSequence(" << nonstd::endl;
    ss << re1->toSource(root, indent);
    ss << "," << nonstd::endl;
    ss << re2->toSource(root, indent);
    ss << nonstd::endl;
    ss << Indent(indent);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Selection::toSource(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
    ss << "RegularGrammar::newSelection(" << nonstd::endl;
    ss << re1->toSource(root, indent);
    ss << "," << nonstd::endl;
    ss << re2->toSource(root, indent);
    ss << nonstd::endl;
    ss << Indent(indent);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Kleene::toSource(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
    ss << "RegularGrammar::newKleene(" << nonstd::endl;
    ss << re->toSource(root, indent);
    ss << nonstd::endl;
    ss << Indent(indent);
    ss << ")";
    return ss.str();
}

std::string RegularGrammar::Optional::toSource(const RegularGrammar *root, int indent) const {
    indent += 2;
    std::stringstream ss;
    ss << Indent(indent);
    ss << "RegularGrammar::newOptional(" << nonstd::endl;
    ss << re->toSource(root, indent);
    ss << nonstd::endl;
    ss << Indent(indent);
    ss << ")";
    return ss.str();
}

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End LexicalAnalyserGenerator/toSource.cpp
