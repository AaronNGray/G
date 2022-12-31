//
//  nonstd/bitset.cpp
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include <sstream>
#include <iostream>
#include "nonstd/bitset.h"

namespace nonstd {

bitset bitset::Empty;  // The Empty Set

bitset bitset::SingletonSet(size_t element) {
    bitset newset;
    newset.set(element);
    return std::move(newset);
}

bitset bitset::EmptySet() {
    bitset bs;
    return bs;
}

bitset& bitset::set(size_t element, bool v) {
    expand(element);

    size_t word = element / sizeOfWord;
    size_t bit = element % sizeOfWord;

    WORD value = ((WORD)1) << bit;
    data[word] = (data[word] &= ~value) | ((v ^ complement) ? value : 0);

    return *this;
}

bitset& bitset::setAll(bool value) {
    for (size_t i = 0; i < sizeInWords; ++i)
        data[i] = 0;

    complement = value;

    return *this;
}

bitset& bitset::clear(size_t element) {
    expand(element);

    size_t word = element / sizeOfWord;
    size_t bit = element % sizeOfWord;

    WORD value = ((WORD)1) << bit;
    data[word] = (data[word] & ~value) | (complement ? value : 0);

    return *this;
}

bitset& bitset::clearAll() {
    for (size_t i = 0; i < sizeInWords; ++i)
        data[i] = 0;

    complement = false;

    return *this;
}

bitset& bitset::invert(size_t element) {
    expand(element);

    size_t word = element / sizeOfWord;
    size_t bit = element % sizeOfWord;

    WORD value = ((WORD)1) << bit;
    data[word] = data[word] ^ value;

    return *this;
}

bitset& bitset::invertAll() {
    complement = !complement;

    return *this;
}

bool bitset::get(const size_t element) const {
    if (element < size())
        return (((data[element / sizeOfWord] >> (element % sizeOfWord)) & 1) != 0) ? !complement : complement;
    else
        return complement;
}

bitset& bitset::empty() {
    sizeInBits = 0;
    sizeInWords = 0;
    complement = false;
    if (sizeInWords != 0)
        delete data;

    return *this;
}

bool bitset::isEmpty() const {
    if (size() == 0)
        return !complement;
    else {
        WORD zero = 0;
        bitset::WORD comp = complement ? ((bitset::WORD)-1) : 0;
        for (size_t i = 0; i < sizeInWords; ++i)
            zero |= data[i] ^ comp;
        return (zero == 0);
    }
}

size_t bitset::size() const {
    return sizeInBits;
}


void bitset::expand(size_t element) {
    if (element + 1 >= sizeInBits) {
        size_t bits = element + 1;

        size_t newSizeInWords = (bits + sizeOfWord - 1) / sizeOfWord;

        if (newSizeInWords > sizeInWords) {
            WORD* newData = new WORD[newSizeInWords];
            size_t i = 0;

            for (; i < sizeInWords; ++i)
                newData[i] = data[i];

            for (; i < newSizeInWords; ++i)
                newData[i] = 0;

            if (data)
                delete data;

            data = newData;

            sizeInWords = newSizeInWords;
        }
        sizeInBits = bits;
    }
}

void bitset::compress() {}

bitset& bitset::operator = (const bitset& bs) {
    sizeInBits = bs.sizeInBits;
    sizeInWords = bs.sizeInWords;
    complement = bs.complement;

    if (data)
        delete data;

    data = new WORD[sizeInWords];

    for (size_t i = 0; i < sizeInWords; ++i)
        data[i] = bs.data[i];

    return *this;
}

bitset bitset::clone() {
    bitset bs(*this);
    return std::move(bs);
}

std::string bitset::toString() const {
    std::stringstream ss;
    ss << "{";

    bool first = true;
    for (size_t i = 0; i < sizeInBits; ++i) {
        if (get(i)) {
            if (!first)
                ss << ", ";
            first = false;
            ss << i;
        }
    }

    ss << "}";
    return ss.str();
}

std::string bitset::toString(std::vector<std::string> names) const {
    std::stringstream ss;
    ss << "{";

    bool first = true;
    for (size_t i = 0; i < sizeInBits; ++i) {
        if (get(i)) {
            if (!first)
                ss << ", ";
            first = false;
            if (i < names.size())
                ss << names[i];
            else
                ss << i;
        }
    }
    ss << "}";
    return ss.str();
}

std::string bitset::toBoolArrayString() const {
    std::stringstream ss;
    ss << "{";

    bool first = true;
    for (size_t i = 0; i < sizeInBits; ++i) {
        if (!first)
            ss << ", ";
        ss << (get(i) ? "1" : "0");
    }

    ss << "}";
    return ss.str();
}

std::string bitset::toBitString() const {
    std::stringstream ss;
    for (size_t i = 0; i < sizeInBits; ++i)
        ss << (get(i) ? "1" : "0");
    return ss.str();
}

bitset bitset::Negate() {
    bitset bs(*this);
    bs.complement ^= true;
    return std::move(bs);
}


bool bitset::Subset(const bitset& sub) const {
    WORD v = 0;

    bitset::WORD comp = complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD subcomp = sub.complement ? ((bitset::WORD)-1) : 0;

    for (size_t i = 0; i < std::min(sizeInWords, sub.sizeInWords); ++i)
        v |= (~(data[i] ^ comp)) & (sub.data[i] ^ subcomp);

    return (v == 0);
}

bool bitset::Subset(const bitset* sub) const {
    WORD v = 0;

    bitset::WORD comp = complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD subcomp = sub->complement ? ((bitset::WORD)-1) : 0;

    for (size_t i = 0; i < std::min(sizeInWords, sub->sizeInWords); ++i)
        v |= (~(data[i] ^ comp)) & (sub->data[i] ^ subcomp);

    return (v == 0);
}

bool Subset(const bitset& bs1, const bitset& bs2) {
    bitset::WORD v = 0;

    bitset::WORD comp1 = bs1.complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs2.complement ? ((bitset::WORD)-1) : 0;

    for (size_t i = 0; i < std::min(bs1.sizeInWords, bs2.sizeInWords); ++i)
        v |= (~(bs1.data[i] ^ comp1)) & (bs2.data[i] ^ comp2);

    return (v == 0);

}

bool Subset(const bitset* bs1, const bitset* bs2) {
    bitset::WORD v = 0;

    bitset::WORD comp1 = bs1->complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs2->complement ? ((bitset::WORD)-1) : 0;

    for (size_t i = 0; i < std::min(bs1->sizeInWords, bs2->sizeInWords); ++i)
        v |= (~(bs1->data[i] ^ comp1)) & (bs2->data[i] ^ comp2);

    return (v == 0);
}

bool Compare(const bitset& bs1, const bitset& bs2) {
    size_t lenMin = std::min(bs1.sizeInWords, bs2.sizeInWords);
    size_t lenMax = std::max(bs1.sizeInWords, bs2.sizeInWords);

    bitset::WORD comp1 = bs1.complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs2.complement ? ((bitset::WORD)-1) : 0;

    size_t i = 0;
    for (; i < lenMin; ++i)
        if ((bs1.data[i] ^ comp1) != (bs2.data[i] ^ comp2))
            return false;

    if (bs1.sizeInWords > bs2.sizeInWords) {
        for (; i < lenMax; ++i)
            if (bs1.data[i] != 0 && bs1.complement == bs2.complement)
                return false;
    }
    else if (bs1.sizeInWords < bs2.sizeInWords) {
        for (; i < lenMax; ++i)
            if (bs2.data[i] != 0 && bs1.complement == bs2.complement)
                return false;
    }
    return true;
}

bool Compare(const bitset* bs1, const bitset* bs2) {
    size_t lenMin = std::min(bs1->sizeInWords, bs2->sizeInWords);
    size_t lenMax = std::max(bs1->sizeInWords, bs2->sizeInWords);

    bitset::WORD comp1 = bs1->complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs2->complement ? ((bitset::WORD)-1) : 0;

    size_t i = 0;
    for (; i < lenMin; ++i)
        if ((bs1->data[i] ^ comp1) != (bs2->data[i] ^ comp2))
            return false;

    if (bs1->sizeInWords > bs2->sizeInWords) {
        for (; i < lenMax; ++i)
            if (bs1->data[i] != 0 && bs1->complement == bs2->complement)
                return false;
    }
    else if (bs1->sizeInWords < bs2->sizeInWords)
        for (; i < lenMax; ++i)
            if (bs2->data[i] != 0 && bs1->complement == bs2->complement)
                return false;

    return true;
}

bitset& bitset::Union(const bitset& bs) {
    size_t lenMin = std::min(sizeInWords, bs.sizeInWords);
    size_t lenMax = std::max(sizeInWords, bs.sizeInWords);

    bitset::WORD comp = complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs.complement ? ((bitset::WORD)-1) : 0;

    if (bs.sizeInBits == 0) return *this;
    size_t bits = std::max(sizeInBits, bs.sizeInBits);
    expand(bits - 1);

    if (sizeInWords > bs.sizeInWords) {
        size_t i = 0;
        for (; i < lenMin; ++i)
            data[i] = (data[i] ^ comp) | (bs.data[i] ^ comp2);
        for (; i < lenMax; ++i)
            data[i] = data[i] ^ comp;
    }
    else if (sizeInWords < bs.sizeInWords) {
        size_t i = 0;
        for (; i < lenMin; ++i)
            data[i] = (data[i] ^ comp) | (bs.data[i] ^ comp2);
        for (; i < lenMax; ++i)
            data[i] = bs.data[i] ^ comp2;
    }
    else
        for (size_t i = 0; i < lenMax; ++i)
            data[i] = (data[i] ^ comp) | (bs.data[i] ^ comp2);

    complement = false;
    return *this;
}

bitset* bitset::Union(const bitset* bs) {
    size_t lenMin = std::min(sizeInWords, bs->sizeInWords);
    size_t lenMax = std::max(sizeInWords, bs->sizeInWords);

    bitset::WORD comp = complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs->complement ? ((bitset::WORD)-1) : 0;

    if (bs->sizeInBits == 0) return this;
    size_t bits = std::max(sizeInBits, bs->sizeInBits);
    expand(bits - 1);

    if (sizeInWords > bs->sizeInWords) {
        size_t i = 0;
        for (; i < lenMin; ++i)
            data[i] = (data[i] ^ comp) | (bs->data[i] ^ comp2);
        for (; i < lenMax; ++i)
            data[i] = bs->data[i] ^ comp;
    }
    else if (sizeInWords < bs->sizeInWords) {
        size_t i = 0;
        for (; i < lenMin; ++i)
            data[i] = (data[i] ^ comp) | (bs->data[i] ^ comp2);
        for (; i < lenMax; ++i)
            data[i] = bs->data[i] ^ comp2;
    }
    else {
        for (size_t i = 0; i < lenMin; ++i)
            data[i] = (data[i] ^ comp) | (bs->data[i] ^ comp2);
    }
    complement = false;

    return this;
}

bitset Union(const bitset& bs1, const bitset& bs2) {
    size_t lenMin = std::min(bs1.sizeInWords, bs2.sizeInWords);
    size_t lenMax = std::max(bs1.sizeInWords, bs2.sizeInWords);

    bitset bs(std::max(bs1.sizeInBits, bs2.sizeInBits));

    bitset::WORD comp1 = bs1.complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs2.complement ? ((bitset::WORD)-1) : 0;

    if (bs1.sizeInWords > bs2.sizeInWords) {
        size_t i = 0;
        for (; i < lenMin; ++i)
            bs.data[i] = (bs1.data[i] ^ comp1) | (bs2.data[i] ^ comp2);
        for (; i < lenMax; ++i)
            bs.data[i] = bs1.data[i] ^ comp1;
    }
    else if (bs1.sizeInWords < bs2.sizeInWords) {
        size_t i = 0;
        for (; i < lenMin; ++i)
            bs.data[i] = (bs1.data[i] ^ comp1) | (bs2.data[i] ^ comp2);
        for (; i < lenMax; ++i)
            bs.data[i] = bs2.data[i] ^ comp2;
    }
    else {
        for (size_t i = 0; i < lenMin; ++i)
            bs.data[i] = (bs1.data[i] ^ comp1) | (bs2.data[i] ^ comp2);
    }
    return std::move(bs);
}

bitset* Union(const bitset* bs1, const bitset* bs2) {
    size_t lenMin = std::min(bs1->sizeInWords, bs2->sizeInWords);
    size_t lenMax = std::max(bs1->sizeInWords, bs2->sizeInWords);

    bitset* bs = new bitset(std::max(bs1->sizeInBits, bs2->sizeInBits));

    bitset::WORD comp1 = bs1->complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs2->complement ? ((bitset::WORD)-1) : 0;

    size_t i = 0;
    for (; i < lenMin; ++i)
        bs->data[i] = (bs1->data[i] ^ comp1) | (bs2->data[i] ^ comp2);

    if (bs1->sizeInWords > bs2->sizeInWords)
        for (; i < lenMax; ++i)
            bs->data[i] = bs1->data[i] ^ comp1;
    else if (bs1->sizeInWords < bs2->sizeInWords)
        for (; i < lenMax; ++i)
            bs->data[i] = bs2->data[i] ^ comp2;

    return bs;
}

bitset Intersection(const bitset& bs1, const bitset& bs2) {
    size_t len = std::min(bs1.sizeInWords, bs2.sizeInWords);
    size_t bits = std::min(bs1.sizeInBits, bs2.sizeInBits);

    bitset bs(bits);

    bitset::WORD comp1 = bs1.complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs2.complement ? ((bitset::WORD)-1) : 0;

    size_t i = 0;
    for (; i < len; ++i)
        bs.data[i] = (bs1.data[i] ^ comp1) & (bs2.data[i] ^ comp2);

    return std::move(bs);
}

bitset* Intersection(const bitset* bs1, const bitset* bs2) {
    size_t len = std::min(bs1->sizeInWords, bs2->sizeInWords);
    size_t bits = std::min(bs1->sizeInBits, bs2->sizeInBits);

    bitset* bs = new bitset(bits);

    bitset::WORD comp1 = bs1->complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs2->complement ? ((bitset::WORD)-1) : 0;

    size_t i = 0;
    for (; i < len; ++i)
        bs->data[i] = (bs1->data[i] ^ comp1) & (bs2->data[i] ^ comp2);

    return bs;
}

bitset& bitset::Intersection(const bitset& bs) {
    size_t len = std::min(sizeInWords, bs.sizeInWords);
    size_t bits = std::min(sizeInBits, bs.sizeInBits);

    bitset::WORD comp = complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs.complement ? ((bitset::WORD)-1) : 0;

    size_t i = 0;
    for (; i < len; ++i)
        data[i] = (data[i] ^ comp) & (bs.data[i] ^ comp2);

    return *this;
}
bitset* bitset::Intersection(const bitset* bs) {
    size_t len = std::min(sizeInWords, bs->sizeInWords);
    size_t bits = std::min(sizeInBits, bs->sizeInBits);

    bitset::WORD comp = complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs->complement ? ((bitset::WORD)-1) : 0;

    size_t i = 0;
    for (; i < len; ++i)
        data[i] = (data[i] ^ comp) & (bs->data[i] ^ comp2);

    return this;
}


bitset Difference(const bitset& bs1, const bitset& bs2) {
    size_t lenMin = std::min(bs1.sizeInWords, bs2.sizeInWords);
    size_t lenMax = std::max(bs1.sizeInWords, bs2.sizeInWords);

    size_t bits = std::max(bs1.sizeInBits, bs2.sizeInBits);

    bitset bs(bits);

    bitset::WORD comp1 = bs1.complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs2.complement ? ((bitset::WORD)-1) : 0;

    size_t i = 0;
    for (; i < lenMin; ++i)
        bs.data[i] = (bs1.data[i] ^ comp1) ^ (bs2.data[i] ^ comp2);

    if (bs1.sizeInWords > bs2.sizeInWords)
        for (; i < lenMax; ++i)
            bs.data[i] = bs1.data[i] ^ comp1;
    else if (bs1.sizeInWords < bs2.sizeInWords)
        for (; i < lenMax; ++i)
            bs.data[i] = bs2.data[i] ^ comp2;

    return bs;
}

bitset* Difference(const bitset* bs1, const bitset* bs2) {
    size_t lenMin = std::min(bs1->sizeInWords, bs2->sizeInWords);
    size_t lenMax = std::max(bs1->sizeInWords, bs2->sizeInWords);

    size_t bits = std::max(bs1->sizeInBits, bs2->sizeInBits);

    bitset* bs = new bitset(bits);

    bitset::WORD comp1 = bs1->complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs2->complement ? ((bitset::WORD)-1) : 0;

    size_t i = 0;
    for (; i < lenMin; ++i)
        bs->data[i] = (bs1->data[i] ^ comp1) ^ (bs2->data[i] ^ comp2);

    if (bs1->sizeInWords > bs2->sizeInWords)
        for (; i < lenMax; ++i)
            bs->data[i] = bs1->data[i] ^ comp1;
    else if (bs1->sizeInWords < bs2->sizeInWords)
        for (; i < lenMax; ++i)
            bs->data[i] = bs2->data[i] ^ comp2;

    return bs;
}

bool bitset::operator < (const bitset& bs) const {
    size_t lenMin = std::min(sizeInWords, bs.sizeInWords);
    size_t lenMax = std::max(sizeInWords, bs.sizeInWords);

    bitset::WORD comp1 = complement ? ((bitset::WORD)-1) : 0;
    bitset::WORD comp2 = bs.complement ? ((bitset::WORD)-1) : 0;

    for (size_t i = 0; i < lenMin; ++i) {
        WORD d1 = data[i] ^ comp1;
        WORD d2 = bs.data[i] ^ comp2;
        if (d1 < d2)
            return true;
        else if (d1 > d2)
            return false;
    }

    if (sizeInWords > bs.sizeInWords) {
        bool greaterthan = false;
        for (size_t i = lenMin; i < lenMax; ++i)
            greaterthan |= ((data[i] != 0) & (complement == bs.complement));
        return !greaterthan;
    }
    else if (sizeInWords < bs.sizeInWords) {
        bool lessthan = false;
        for (size_t i = lenMin; i < lenMax; ++i)
            lessthan |= ((bs.data[i] != 0) & (complement == bs.complement));
        return lessthan;
    }

    return false;
}

} // end namespace nonstd

// End bitset.cpp
