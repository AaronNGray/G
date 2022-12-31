//
//  g/LexicalAnalyserGenerator/Lowers.h - Equivalence Classes Lowers
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/bitset.h"
#include "nonstd/vector.h"
#include "g/LexicalAnalyserGenerator/Ranges.h"
#include "g/LexicalAnalyserGenerator/CharacterClass.h"

namespace G {
namespace LexicalAnalyserGenerator {

using namespace nonstd;

class Lowers {
public:
    Lowers() {}
    Lowers(const Ranges& rs) { add(rs); }
    Lowers(const std::initializer_list<unsigned int>& il) {
        for (auto i = il.begin(); i != il.end(); ++i)
            lowers.push_back(*i);
    }

    void add(const Ranges& ranges);
    void push_back(unsigned int lower) { lowers.push_back(lower); }

    typedef std::vector<unsigned int> value_type;

    typedef std::vector<unsigned int>::iterator iterator;
    typedef std::vector<unsigned int>::const_iterator const_iterator;

    iterator begin() { return lowers.begin(); }
    iterator end() { return lowers.end(); }
    const_iterator cbegin() const { return lowers.cbegin(); }
    const_iterator cend() const { return lowers.cend(); }
    size_t size() { return lowers.size(); }

    unsigned int operator [] (size_t index) { return lowers[index]; }

    std::string toString() const;

    Ranges getRanges(const bitset& classes, bool negate = false) const;
    CharacterClass getCharacterClass(const bitset& classes, bool negate = false) const;

    friend bool operator == (Lowers& ll, Lowers& lr);

    std::vector<unsigned int>& getLowers() { return lowers; }
private:
    std::vector<unsigned int> lowers;
};

inline bool operator == (Lowers& ll, Lowers& lr) {
    return std::equal(ll.begin(), ll.end(), lr.begin());
}

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/Lowers.h - Equivalence Classes Lowers
