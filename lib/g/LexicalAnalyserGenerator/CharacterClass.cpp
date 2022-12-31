//
//  g/LexicalAnalyserGenerator/CharacterClass.cpp
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/Logger.h"
#include "g/LexicalAnalyserGenerator/CharacterClass.h"
#include "g/StringLiteral.h"

namespace G {
namespace LexicalAnalyserGenerator {

CharacterClass CharacterClass::Null;

std::string CharacterClass::toString() const {
    std::ostringstream ss;
    if (getRanges().size() == 1 && getRanges()[0].getLower() == getRanges()[0].getUpper())
        ss << CharacterLiteral::toString(getRanges()[0].getLower());
    else {
        ss << "[";
        if (getNegated())
            ss << "^";
        for (auto ri = getRanges().cbegin(); ri != getRanges().cend(); ++ri) {
            if (ri->getLower() == ri->getUpper())
                ss << CharacterLiteral::toString(ri->getUpper());
            else
                ss << ri->toString();
        }
        ss << "]";
    }
    return ss.str();
}

std::string CharacterClass::toSource() const {
    std::ostringstream ss;
    if (getRanges().size() == 1 && getRanges()[0].getLower() == getRanges()[0].getUpper())
        ss << "CharacterClass( Char(" << CharacterLiteral::toSource(getRanges()[0].getLower()) << "))";
    else {
        ss << "CharacterClass( Ranges( {";
        for (auto ri = getRanges().cbegin(); ri != getRanges().cend(); ++ri) {
            if (ri->getLower() == ri->getUpper())
                ss << "Char(" << CharacterLiteral::toSource(ri->getUpper()) << ")";
            else {
                ss << ri->toSource();
            }
            if (ri != getRanges().clast())
                ss << ", ";
        }
        ss << "})";
        if (getNegated())
            ss << ", true";
        ss << ")";
    }
    return ss.str();
}
/*
bool compare(const CharacterClass* lhs, const CharacterClass* rhs) {
	return (lhs->ranges == rhs->ranges) && (lhs->negative == rhs->negative);
}
*/
}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/CharacterClass.cpp

// TODO: CharacterLiteral::toSource()
// TODO: StringLiteral::toSource()
