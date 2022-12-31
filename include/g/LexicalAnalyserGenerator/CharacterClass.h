//
//  CharacterClass.h
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <vector>
#include "nonstd/bitset.h"
#include "g/LexicalAnalyserGenerator/Ranges.h"

#include "g/Logger.h"

namespace G {
namespace LexicalAnalyserGenerator {

class CharacterClass {
    friend class EquivalenceSet;
public:
    CharacterClass() : negative(false) {}
    CharacterClass(const char c, bool negate = false) : ranges(Range(c)), negative(negate) {}
    CharacterClass(const Range r, bool negate = false) : ranges(r), negative(negate) {}
    CharacterClass(const Ranges& rs, bool negate = false) : ranges(rs), negative(negate) { normalize(); }
    CharacterClass(const Ranges* rs, bool negate = false) : ranges(*rs), negative(negate) { normalize(); }
    CharacterClass(const CharacterClass &cc, bool negate) : ranges(cc.ranges), negative(negate) {}
    CharacterClass(const CharacterClass &cc) : ranges(cc.ranges), negative(cc.negative) {}

    CharacterClass(const std::initializer_list<Range>& ril, bool negate = false) : negative(negate) {
        for (auto ri = ril.begin(); ri != ril.end(); ++ri)
            ranges.add(*ri);
    }
    CharacterClass(const std::initializer_list<char>& cil, bool negate = false) : negative(negate) {
        for (auto ci = cil.begin(); ci != cil.end(); ++ci)
            ranges.add(*ci);
    }

    void sortOnLowers() {
        ranges.sortOnLowers();
    }

    void normalize() {
        sortOnLowers();
        if (!check())
            ranges.normalize();
    }
    bool check() const {
        return ranges.check();
    }

    void negate() { negative = true; }
    bool getNegated() const { return negative; }

    const Ranges& getRanges() const { return ranges; }

    std::string toString() const;
    std::string toSource() const;

    static CharacterClass Null;

	friend bool compare(const CharacterClass& lhs, const CharacterClass& rhs);

private:
    Ranges ranges;
	bool negative;
};

inline bool compare(const CharacterClass& lhs, const CharacterClass& rhs) {
	return (lhs.ranges == rhs.ranges) && (lhs.negative == rhs.negative);
}

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// TODO: remove g/Logger.h dependency, use exception mechanism !

// End CharacterClass.h
