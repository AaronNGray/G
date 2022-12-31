//
//  g/LexicalAnalyserGenerator/Lowers.cpp - Equivalence Classes Lowers
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/LexicalAnalyserGenerator/Lowers.h"

namespace G {
namespace LexicalAnalyserGenerator {

void Lowers::add(const Ranges& ranges) {
    if (!ranges.size()) {
        lowers.push_back(0);
        return;
    }
    else {
        unsigned int lower = ranges[0].getLower();

        if (ranges[0].getLower() != 0) {
            lowers.push_back(0);
            push_back(lower);
        }
        else
            push_back(0);

        lower = ranges[0].getUpper() + 1;

        for (size_t r = 1; r < ranges.size(); ++r) {
            if (lower != ranges[r].getLower()) {
                push_back(lower);
                push_back(ranges[r].getLower());
            }
            lower = ranges[r].getUpper() + 1;
        }
        push_back(ranges[ranges.size() - 1].getUpper() + 1);
    }
}

static std::string toString(unsigned int c) {
    std::ostringstream os;
    if (c < 32 || c > 126)
        os << "\\" << (int)c;
    else
        os << (unsigned char)c;
    return os.str();
}

std::string Lowers::toString() const {
    std::ostringstream ss;
    ss << "{";
    for (auto i = cbegin(); i != cend(); ++i) {
        ss << "'" << LexicalAnalyserGenerator::toString(*i) << "'";
        if (i != cend() - 1)
            ss << ", ";
    }
    ss << "}";
    return ss.str();
}

CharacterClass Lowers::getCharacterClass(const bitset& classes, bool negate) const {
    return CharacterClass(getRanges(classes, false), negate);
}

Ranges Lowers::getRanges(const bitset& classes, bool negate) const {
    Ranges rs;

    size_t lower = 0;
    for (bitset::const_iterator ci = classes.cbegin(); ci != classes.cend() && lower < lowers.size(); ++ci, ++lower) {
        if (ci.isElement() ^ negate) {
            unsigned int upper = (lower + 1 < lowers.size()) ? lowers[lower + 1] : 128;
            rs.add(Range(lowers[lower], upper - 1));
        }
    }

    return rs;
}

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/Lowers.cpp - Equivalence Classes Lowers
