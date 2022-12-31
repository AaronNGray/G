//
//  Ranges.h - Range and Ranges classes
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <initializer_list>

#include "nonstd/vector.h"
#include "g/StringLiteral.h"

namespace G {
namespace LexicalAnalyserGenerator {

class Range;

class ExceptionInvalidRange {
public:
    ExceptionInvalidRange(Range &r) {}
};

class ExceptionCrossedRanges {
public:
    ExceptionCrossedRanges() {}
};

class Range {
public:
    Range() : lower(0), upper(0) {}
    Range(const Range& range) : lower(range.lower), upper(range.upper) {}
    Range(unsigned char c) : lower(c), upper(c) {}
    Range(unsigned char l, unsigned char u) : lower(l), upper(u) {}

    unsigned int getLower() const { return lower; }
    unsigned int getUpper() const { return upper; }

    bool check() const {
        return upper >= lower;
    }

    void order() {
        if (upper >= lower)
            return;
        std::swap(lower, upper);
    }

    static bool compareLowers(const Range r1, const Range r2) {
        return (r1.lower < r2.lower);
    }

    static bool overlapped(const Range r1, const Range r2) {
        if (r1.lower < r2.lower)
            return (r1.upper > r2.lower);
        else if (r2.lower < r1.lower)
            return (r2.upper > r1.lower);
        else
            return true;
    }

    std::string print() const {
        std::ostringstream os;
        os << "Range('" << printChar(lower) << "', '" << printChar(upper) << "')";
        return os.str();
    }

    std::string toString() const {
        std::ostringstream os;
        os << "Range(" << (unsigned int)lower << ", " << (unsigned int)upper << ")";
        return os.str();
    }

    std::string toSource() const {
        std::ostringstream os;
        os << "Range(" << CharacterLiteral::toSource(lower) << ", " << CharacterLiteral::toSource(upper) << ")";
        return os.str();
    }

    static std::string printChar(unsigned int c) {
        std::ostringstream os;
        if (c < 32 || c > 126)
            os << "\\" << (int)c;
        else
            os << (unsigned char)c;
        return os.str();
    }

    friend class Char;
    friend bool operator == (const Range& r1, const Range& r2);
    friend bool operator != (const Range& r1, const Range& r2);
private:
    unsigned int lower;
    unsigned int upper;
};

inline bool operator == (const Range& r1, const Range& r2) {
    return ((r1.lower == r2.lower) && (r1.upper == r2.upper));
}

inline bool operator != (const Range& r1, const Range& r2) {
    return !(r1 == r2);
}

class Char : public Range {
public:
    Char(int c) : Range(c, c) {}

    std::string toSource() const {
        std::ostringstream os;
        os << "Char('" << CharacterLiteral::toSource(lower) << "')";
        return os.str();
    }
};

//
//
//

class Ranges {
public:
    Ranges() {}
    Ranges(Range r) {
        r.order();
        ranges.push_back(r);
    }
    Ranges(const Ranges& rs) {
        ranges.reserve(rs.size());
        for (auto ri = rs.cbegin(); ri != rs.cend(); ++ri)
            ranges.push_back(*ri);
        orderRanges();
    }
    Ranges(std::initializer_list<Range> rs) : ranges(rs) {
        orderRanges();
    }

    void add(Range r) {
        ranges.push_back(r);
    }
    void remove(const Range r) {
        auto i = std::find(ranges.begin(), ranges.end(), r);
        if (i != ranges.end())
            ranges.erase(i);
        else
            throw;
    }
    const size_t size() const {
        return ranges.size();
    }

    bool check() const {
        if (ranges.size()) {
            for (size_t i = 0, e = ranges.size(); i < e; ++i)
                if (!ranges[i].check())
                    return false;
        }
        return true;
    }

    void orderRanges() {
        for (auto ri = ranges.begin(); ri != ranges.end(); ++ri)
            ri->order();
    }

    void sortOnLowers() {
        std::sort(begin(), end(), Range::compareLowers);
    }
    void normalize() {
        sortOnLowers();

        auto r = begin();
        unsigned int upper = r->getUpper();

        for (++r; r != end(); ++r) {
            if (upper >= r->getUpper()) // total overlap
                remove(*r);
            else if (upper >= r->getUpper()) { // overlap
                upper = r->getUpper();
                remove(*r);
            }
        }
    }

    typedef std::vector<Range>::iterator iterator;
    typedef std::vector<Range>::const_iterator const_iterator;

    iterator begin() { return ranges.begin(); }
    iterator last() { return ranges.last(); }
    iterator end() { return ranges.end(); }
    const_iterator cbegin() const { return ranges.begin(); }
    const_iterator clast() const { return ranges.last(); }
    const_iterator cend() const { return ranges.end(); }

    const Range operator [](int index) const {
        return ranges[index];
    }

    friend bool Compare(const Ranges& rs1, const Ranges& rs2);
    friend bool Compare2(const Ranges& rs1, const Ranges& rs2);

	friend bool operator == (const Ranges& rs1, const Ranges& rs2);

	std::string toString() const;
    std::string toSource() const;

private:
    vector<Range> ranges;
};

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End Ranges.h - Range and Ranges classes
