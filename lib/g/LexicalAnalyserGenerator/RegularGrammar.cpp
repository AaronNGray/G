//
//  g/LexicalAnalyserGenerator/RegularGrammar.cpp - Regular Grammar to DFA methods
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/LexicalAnalyserGenerator/CharacterClass.h"
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include <typeinfo>

namespace G {
namespace LexicalAnalyserGenerator {

//
// clone()
//

RegularGrammar::RE *RegularGrammar::CharacterClass::clone() const {
    return RegularGrammar::newCharacterClass(characterClass);
}
RegularGrammar::RE *RegularGrammar::End::clone() const {
    return RegularGrammar::newEnd(action);
}
RegularGrammar::RE *RegularGrammar::Sequence::clone() const {
    RegularGrammar::RE *_re1 = re1->clone();
    RegularGrammar::RE *_re2 = re2->clone();
    return RegularGrammar::newSequence(_re1, _re2);
}
RegularGrammar::RE *RegularGrammar::Selection::clone() const {
    RegularGrammar::RE *_re1 = re1->clone();
    RegularGrammar::RE *_re2 = re2->clone();
    return RegularGrammar::newSelection(_re1, _re2);
}
RegularGrammar::RE *RegularGrammar::Kleene::clone() const {
    return RegularGrammar::newKleene(re->clone());
}
RegularGrammar::RE *RegularGrammar::Optional::clone() const {
    return RegularGrammar::newOptional(re->clone());
}

//
// void index()
//

void RegularGrammar::Leaf::index(RegularGrammar* regularGrammar) {
    position = regularGrammar->positionIndex;
    regularGrammar->leafFromPos[regularGrammar->positionIndex++] = this;
}
void RegularGrammar::Sequence::index(RegularGrammar* regularGrammar) {
    re1->index(regularGrammar);
    re2->index(regularGrammar);
}
void RegularGrammar::Selection::index(RegularGrammar* regularGrammar) {
    re1->index(regularGrammar);
    re2->index(regularGrammar);
}
void RegularGrammar::Kleene::index(RegularGrammar* regularGrammar) {
    re->index(regularGrammar);
}
void RegularGrammar::Optional::index(RegularGrammar* regularGrammar) {
    re->index(regularGrammar);
}

//
// bitset firstpos()
//

bitset RegularGrammar::Leaf::firstpos() const {
    return bitset::SingletonSet(position);
}
bitset RegularGrammar::Sequence::firstpos() const {
    if (re1->nullable())
        return Union(re1->firstpos(), re2->firstpos());
    else
        return re1->firstpos();
}
bitset RegularGrammar::Selection::firstpos() const {
    return Union(re1->firstpos(), re2->firstpos());
}
bitset RegularGrammar::Kleene::firstpos() const {
    return re->firstpos();
}
bitset RegularGrammar::Optional::firstpos() const {
    return re->firstpos();
}

//
// followpos()
//

void RegularGrammar::CharacterClass::followpos(RegularGrammar* parent, bitset&& rest) {
    parent->pos.push_back(rest);
}
void RegularGrammar::End::followpos(RegularGrammar* parent, bitset&& rest) {
    parent->pos.push_back(bitset::EmptySet());
}
void RegularGrammar::Sequence::followpos(RegularGrammar* parent, bitset&& rest) {
    re1->followpos(parent, re2->nullable() ? Union(re2->firstpos(), rest) : re2->firstpos());
    re2->followpos(parent, std::move(rest));
}
void RegularGrammar::Selection::followpos(RegularGrammar* parent, bitset&& rest) {
    re1->followpos(parent, std::move(rest));
    re2->followpos(parent, std::move(rest));
}
void RegularGrammar::Kleene::followpos(RegularGrammar* parent, bitset&& rest) {
    re->followpos(parent, Union(re->firstpos(), rest));
}
void RegularGrammar::Optional::followpos(RegularGrammar* parent, bitset&& rest) {
    re->followpos(parent, std::move(rest));
}

//
//
//

bool compare(const RegularGrammar* lhs, const RegularGrammar* rhs) {
	return lhs->root->compare(rhs->root);
}

bool RegularGrammar::CharacterClass::compare(const RegularGrammar::RE* rhs) const {
	bool cc = G::LexicalAnalyserGenerator::compare(characterClass, ((const CharacterClass*)rhs)->characterClass);
	if (!cc) {
		std::cout << "characterClass.toString() = " << characterClass.toString() << "  " << characterClass.getRanges().size() << std::endl;
		std::cout << "((const CharacterClass*)rhs)->characterClass.toString() = " << ((const CharacterClass*)rhs)->characterClass.toString() << "  " << ((const CharacterClass*)rhs)->characterClass.getRanges().size() << std::endl;

		std::cout << characterClass.getRanges()[0].getUpper() << std::endl;
		std::cout << characterClass.getRanges()[0].getLower() << std::endl;

		std::cout << ((const CharacterClass*)rhs)->characterClass.getRanges()[0].getUpper() << std::endl;
		std::cout << ((const CharacterClass*)rhs)->characterClass.getRanges()[0].getLower() << std::endl;

		std::cout << characterClass.getNegated() << std::endl;
		std::cout << ((const CharacterClass*)rhs)->characterClass.getNegated() << std::endl;

	}

	bool test = (getTypeName() == rhs->getTypeName()) && cc;
	return test;
}
bool RegularGrammar::Sequence::compare(const RegularGrammar::RE* rhs) const {
	bool test = (getTypeName() == rhs->getTypeName()) && re1->compare(((const Sequence*)rhs)->re1) && re2->compare(((const Sequence*)rhs)->re2);
	return test;
}
bool RegularGrammar::Selection::compare(const RegularGrammar::RE* rhs) const {
	bool test = (getTypeName() == rhs->getTypeName()) && re1->compare(((const Selection*)rhs)->re1) && re2->compare(((const Selection*)rhs)->re2);
	return test;
}
bool RegularGrammar::Optional::compare(const RegularGrammar::RE* rhs) const {
	bool test = (getTypeName() == rhs->getTypeName()) && re->compare(((const Optional*)rhs)->re);
	return test;
}
bool RegularGrammar::Kleene::compare(const RegularGrammar::RE* rhs) const {
	bool test = (getTypeName() == rhs->getTypeName()) && re->compare(((const Kleene*)rhs)->re);
	return test;
}
bool RegularGrammar::End::compare(const RE* rhs) const {
	bool test = getTypeName() == rhs->getTypeName();
	return test;
}

//
//
//

void RegularGrammar::diag() {
    std::cout << std::endl << prettyPrint() << std::endl << std::endl;

    std::cout << std::endl << "positions: " << positionIndex << std::endl;
    std::cout << std::endl << "Starting positions: " << std::endl;
    std::cout << std::endl << firstpos().toString() << std::endl;

    std::cout << std::endl << "Positions" << std::endl;
    for (unsigned int position = 0; position < getNumberOfPositions(); ++position) {
        std::cout << position << " : " << getPosition(position).toString() << std::endl;
    }

    std::cout << std::endl << "Leaf from Position" << std::endl;
    for (auto li = leafFromPos.begin(); li != leafFromPos.end(); ++li)
        std::cout << li->first << " = " << li->second->toString(this) << std::endl;
}

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End RegularGrammar.cpp
