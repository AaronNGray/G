//
//  g/LexicalAnalyserGenerator/toString.cpp - EquivalenceClasses to string
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/LexicalAnalyserGenerator/EquivalenceClasses.h"
#include <iostream>
#include <vector>
#include <map>
#include "nonstd/bitset.h"

namespace G {
namespace LexicalAnalyserGenerator {

static std::string toString(unsigned int c) {
    std::ostringstream os;
    if (c < 32 || c > 126)
        os << "\\" << (int)c;
    else
        os << (unsigned char)c;
    return os.str();
}

std::string EquivalenceSets::toString() const {
    std::ostringstream os;
    unsigned int i = 0;
    for (auto esi = cbegin(); esi != cend(); ++esi, ++i) {
        os << i << "\t" << (*esi)->toString(lowers) << std::endl;
    }

    return os.str();
}

std::string EquivalenceSets::toString2() const {
    std::ostringstream os;
    unsigned int i = 0;
    for (auto esi = cbegin(); esi != cend(); ++esi, ++i) {
        os << i << "\t" << (*esi)->toString() << std::endl;
    }

    return os.str();
}


std::string EquivalenceClasses::toString() {
    std::ostringstream os;
    os << "Equivalence Sets:" << std::endl << std::endl;
    os << EquivalenceSets::toString() << std::endl;

    os << "Lowers:" << std::endl << std::endl;
    auto l = lowers.cbegin();
    os << "{ " << "'" << LexicalAnalyserGenerator::toString(*l++) << "'";
    for (; l != lowers.cend(); ++l)
        os << ", " << "'" << LexicalAnalyserGenerator::toString(*l) << "'";
    os << "}" << std::endl << std::endl;

    os << lowers.toString() << std::endl;

    os << "InputIndexToColumnIndex:" << std::endl;

    for (unsigned int i = 0; i < inputIndexToColumnIndex.size(); ++i)
        os << i << ": " << inputIndexToColumnIndex[i] << std::endl;


    os << std::endl;
    os << "columnIndexToInputIndex:" << std::endl;
    for (unsigned int i = 0; i < columnIndexToInputIndex.size(); ++i)
        os << i << ": " << columnIndexToInputIndex[i] << std::endl;
    os << std::endl;

    os << "columnToInput:" << std::endl;
    for (unsigned int i = 0; i < columnToInput.size(); ++i)
        os << i << ": " << columnToInput[i] << std::endl;
    os << std::endl;


    os << "Equivalence Classes:" << std::endl << std::endl;

    unsigned int i = 0;
    for (auto eci = cbegin(); eci != cend(); ++eci, ++i) {
        os << i << "\t" << (*eci)->toString(lowers) << std::endl;
    }

    return os.str();
}

std::string EquivalenceSet::toString() const {
    std::ostringstream os;
    auto l = lowers.cbegin();
    os << "{ " << "'" << LexicalAnalyserGenerator::toString(*l++) << "'";
    for (; l != lowers.cend(); ++l)
        os << ", " << "'" << LexicalAnalyserGenerator::toString(*l) << "'";
    os << "}";

    // TODO: negative

    return os.str();
}

std::string EquivalenceSet::toString(const Lowers& lowers) const {
    return sets.toBoolArrayString() + "\t" + lowers.getCharacterClass(sets).toString();
}

std::string EquivalenceClass::toString(const Lowers& lowers) const {
    return classes.toBoolArrayString(); // "\t" + lowers.getCharacterClass(classes).toString();
}


static std::string toString(const std::vector<unsigned int> lowers) {
    std::ostringstream ss;
    ss << "{";
    for (auto i = lowers.cbegin(); i != lowers.cend(); ++i) {
        ss << "'" << LexicalAnalyserGenerator::toString(*i) << "'";
        if (i != lowers.cend() - 1)
            ss << ", ";
    }
    ss << "}";
    return ss.str();
}

Ranges* EquivalenceSet::getRanges() {
    auto ranges = new Ranges;
    unsigned int last = 0;
    auto l = lowers.begin();
    last = *l++;
    for (auto e = lowers.end(); l != e; ++l) {
        ranges->add(Range(last, (*l) - 1));
        last = *l;
    }
    return ranges;
}

Ranges& EquivalenceClasses::getRanges() const {
    Ranges& ranges = *new Ranges;
    unsigned int last = 0;
    auto l = lowers.cbegin();
    last = *l++;
    for (auto e = lowers.cend(); l != e; ++l) {
        ranges.add(Range(last, (*l) - 1));
        last = *l;
    }
    return ranges;
}

std::string EquivalenceClasses::print() const {
    std::ostringstream os;
    auto l = lowers.cbegin();
    os << "{ " << *l++;
    for (; l != lowers.cend(); ++l)
        os << ", " << *l;
    os << "}\n";
    return os.str();
}

std::string EquivalenceClasses::diag() {
    std::ostringstream os;
    os << "EquivalenceClasses::diag()" << std::endl;
    os << "classes.size() = " << classes.size() << std::endl;
    os << "lowers = " << lowers.toString() << std::endl << std::endl;

    os << "sets: " << std::endl;
    for (auto esi = sets.begin(); esi != sets.end(); ++esi)
        os << (*esi)->diag();
    os << std::endl;

    os << "lowers = " << lowers.toString() << std::endl << std::endl;
    os << std::endl;
    os << "classes: " << std::endl;
    for (auto eci = classes.begin(); eci != classes.end(); ++eci)
        os << (*eci)->diag();
    os << std::endl;

    os << "inputIndexToColumnIndex[]: " << std::endl;
    for (auto i = inputIndexToColumnIndex.begin(); i != inputIndexToColumnIndex.end(); ++i)
        os << i->first << " = " << i->second << std::endl;

    return os.str();
}

std::string EquivalenceSet::diag() {
    std::ostringstream os;
    //os << "index = " << getIndex() << std::endl;
    os << "negative = " << (negative ? "true" : "false") << std::endl;
    os << "lowers = " << lowers.toString() << std::endl;
    os << "sets = " << sets.toString() << std::endl;
    return os.str();
}

std::string EquivalenceClass::diag() {
    std::ostringstream os;
    os << "index = " << getIndex() << std::endl;
    os << "classes = " << classes.toString() << std::endl;
    return os.str();
}

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/toString.cpp - EquivalenceClasses to string
