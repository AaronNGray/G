//
//	bitset.h
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

#include "nonstd/vector.h"

namespace nonstd {

class bitset;
bool Compare(const bitset& bs1, const bitset& bs2);
bitset Union(const bitset& bs1, const bitset& bs2);
bitset Intersection(const bitset& bs1, const bitset& bs2);

class bitset
{
public:
    bitset(size_t bits = 0, bool complement = false) : sizeInBits(bits), complement(complement), data(NULL) {
        sizeInWords = (sizeInBits + sizeOfWord - 1) / sizeOfWord;
        data = new WORD[sizeInWords];

        for (size_t i = 0; i < sizeInWords; ++i)
            data[i] = 0;
    }
    bitset(bitset& bs) : bitset(bs.sizeInBits, bs.complement) {
        sizeInWords = (sizeInBits + sizeOfWord - 1) / sizeOfWord;
        data = new WORD[sizeInWords];

        for (size_t i = 0; i < sizeInWords; ++i)
            data[i] = bs.data[i];
    }
    bitset(const bitset& bs) : bitset(bs.sizeInBits, bs.complement) {
        sizeInWords = (sizeInBits + sizeOfWord - 1) / sizeOfWord;
        data = new WORD[sizeInWords];

        for (size_t i = 0; i < sizeInWords; ++i)
            data[i] = bs.data[i];
    }
/*
    bitset(const std::initializer_list<bool> bil) : bitset(bil.size()) {
        size_t i = 0;
        for (auto bi = bil.begin(); bi != bil.end(); ++bi, ++i)
            set(i, *bi);
    }
*/
    bitset(const std::initializer_list<size_t> il) : bitset() { // signed in instead of unsigned !
        expand(*(il.end() - 1));
        for (auto i = il.begin(); i != il.end(); ++i)
            set(*i);
    }

    ~bitset() {
        delete data;
    }

    static bitset SingletonSet(size_t element);
    static bitset EmptySet();
    static bitset Empty;  // The Empty Set

    bitset clone();

    bitset& set(const size_t b, bool v = true);
    bitset& clear(const size_t b);
    bitset& invert(const size_t b);

    bitset& setAll(bool value = true);
    bitset& clearAll();
    bitset& invertAll();

    bool get(const size_t b) const;

    bitset& empty();
    bool isEmpty() const;
    size_t size() const;

    void expand(const size_t bits);
    void compress();

    size_t getSizeOfWord() { return sizeOfWord; }

    std::string toString() const;
    std::string toString(std::vector<std::string> names) const;
    std::string toBoolArrayString() const;
    std::string toBitString() const;

    //

    class reference {
        friend class bitset;
    public:
        reference(reference& r) : bs(r.bs), pos(r.pos) {}
        reference(const reference& r) : bs(r.bs), pos(r.pos) {}
        reference(bitset& _bitset, size_t _pos) : bs(_bitset), pos(_pos) {}

        ~reference() {}

        reference& operator = (bool val) {
            bs.set(pos, val);
            return *this;
        }

        reference& operator = (const reference& bitref) {
            bs.set(pos, bitref.get());
            return *this;
        }

        reference& invert() {
            bs.invert(pos);
            return *this;
        }

        bool operator ~ () const {
            return !bs.get(pos);
        }

        operator bool() const {
            return bs.get(pos);
        }

        bool isElement() const {
            return bs.get(pos);
        }
        /*
        operator size_t () {
            return index();
        }
        */
        size_t index() {
            return pos;
        }
        bool value() const {
            return bs.get(pos);
        }
        bool get() const {
            return bs.get(pos);
        }
        void set(bool value = true) {
            bs.set(pos, value);
        }
        void clear() {
            bs.clear(pos);
        }

        bool operator * () {
            return (bs.get(pos));
        }

        friend inline bool operator == (reference& r1, reference& r2) {
            assert(&r1.bs == &r2.bs);
            return (r1.pos == r2.pos);
        }
        friend inline bool operator != (reference& r1, reference& r2) {
            assert(&r1.bs == &r2.bs);
            return (r1.pos != r2.pos);
        }

    protected:
        bitset& bs;
        size_t pos;
    };

    class const_reference {
        friend class bitset;
    public:
        const_reference(const const_reference& r) : bs(r.bs), pos(r.pos) {}
        const_reference(const bitset& _bitset, size_t _pos) : bs(_bitset), pos(_pos) {}

        ~const_reference() {}

        //        const_reference& operator = (const const_reference&) = delete; // TODO: warning C4626: 'bitset::const_reference': assignment operator was implicitly defined as deleted

        bool operator ~ () const {
            return !bs.get(pos);
        }

        operator bool() const {
            return bs.get(pos);
        }

        bool isElement() const {
            return bs.get(pos);
        }

        operator size_t () const {
            return index();
        }
        size_t index() const {
            return pos;
        }
        bool value() const {
            return bs.get(pos);
        }
        bool get() const {
            return bs.get(pos);
        }

        bool operator * () {
            return (bs.get(pos));
        }

        friend inline bool operator == (const_reference& r1, const_reference& r2) {
            assert(&r1.bs == &r2.bs);
            return (r1.pos == r2.pos);
        }
        friend inline bool operator != (const_reference& r1, const_reference& r2) {
            assert(&r1.bs == &r2.bs);
            return (r1.pos != r2.pos);
        }

    protected:
        const bitset& bs;
        size_t pos;
    };

    class iterator {
    public:
        iterator(bitset& _bitset, size_t _pos) : bs(_bitset), pos(_pos) {}
        iterator(iterator& r) : bs(r.bs), pos(r.pos) {}
        iterator(const iterator& r) : bs(r.bs), pos(r.pos) {}
        iterator(reference& it) : bs(it.bs), pos(it.pos) {}
        iterator(const reference& it) : bs(it.bs), pos(it.pos) {}

        iterator& operator = (iterator it) {
            bs = it.bs;
            pos = it.pos;
            return *this;
        }
        iterator& operator = (const reference& bitref) {
            bs.set(pos, bitref.get());
            return *this;
        }
        iterator& invert() {
            bs.invert(pos);
            return *this;
        }
        reference operator -> () {
            return reference(bs, pos);
        }
        bool operator * () {
            return bs.get(pos);
        }

        operator size_t () {
            return index();
        }
        size_t index() {
            return pos;
        }

        operator bool() const {
            return bs.get(pos);
        }

        bool isElement() const {
            return bs.get(pos);
        }

        bool value() const {
            return (bs.get(pos));
        }
        bool get() const {
            return (bs.get(pos));
        }
        void set(bool value = true) {
            bs.set(pos, value);
        }
        void clear() {
            bs.clear(pos);
        }

        iterator operator ++ () { // should these return C++ references ???
            ++pos;
            return *this;
        }
        iterator operator -- () {
            --pos;
            return *this;
        }
        iterator operator ++ (int) {
            iterator save(*this);
            ++pos;
            return save;
        }
        iterator operator -- (int) {
            iterator save(*this);
            --pos;
            return save;
        }

        friend inline bool operator == (iterator& i1, iterator& i2) {
            assert(&i1.bs == &i2.bs);
            return (i1.pos == i2.pos);
        }
        friend inline bool operator != (iterator& i1, iterator& i2) {
            assert(&i1.bs == &i2.bs);
            return (i1.pos != i2.pos);
        }

    protected:
        bitset& bs;
        size_t pos;
    };

    class const_iterator {
    public:
        const_iterator(const bitset& _bitset, size_t _pos) : bs(_bitset), pos(_pos) {}
        const_iterator(const const_iterator& r) : bs(r.bs), pos(r.pos) {}
        const_iterator(const reference& it) : bs(it.bs), pos(it.pos) {}

        const_reference operator -> () {
            return const_reference(bs, pos);
        }
        bool operator * () {
            return bs.get(pos);
        }

        operator size_t () {
            return index();
        }
        size_t index() {
            return pos;
        }

        operator bool() const {
            return bs.get(pos);
        }

        bool isElement() const {
            return bs.get(pos);
        }

        bool value() const {
            return (bs.get(pos));
        }
        bool get() const {
            return (bs.get(pos));
        }

        const_iterator operator ++ () { // should these return C++ references ???
            ++pos;
            return *this;
        }
        const_iterator operator -- () {
            --pos;
            return *this;
        }
        const_iterator operator ++ (int) {
            const_iterator save(*this);
            ++pos;
            return save;
        }
        const_iterator operator -- (int) {
            const_iterator save(*this);
            --pos;
            return save;
        }

        friend inline bool operator == (const_iterator& i1, const_iterator& i2) {
            assert(&i1.bs == &i2.bs);
            return (i1.pos == i2.pos);
        }
        friend inline bool operator != (const_iterator& i1, const_iterator& i2) {
            assert(&i1.bs == &i2.bs);
            return (i1.pos != i2.pos);
        }

    protected:
        const bitset& bs;
        size_t pos;
    };

    reference operator [](size_t pos) {
        return reference(*this, pos);
    }

    iterator begin() {
        return iterator(*this, 0);
    }
    iterator end() {
        return iterator(*this, size());
    }

    const_iterator cbegin() const {
        return const_iterator(*this, 0);
    }
    const_iterator cend() const {
        return const_iterator(*this, size());
    }

    iterator first() { return next(begin()); }
    iterator last() { return prev(end()); }

    iterator next(iterator i) {
        for (; i != end(); ++i)
            if (i.isElement())
                return i;
        return i;
    }
    iterator prev(iterator i) {
        for (; i != end(); --i)
            if (i.isElement())
                return i;
        return i;
    }

    bitset Negate();

    bool Subset(const bitset& sub) const;
    bool Subset(const bitset* sub) const;

    friend bool Subset(const bitset& bs1, const bitset& bs2);
    friend bool Subset(const bitset* bs1, const bitset* bs2);

    bool Compare(const bitset& bs);
    bool Compare(const bitset* bs);

    friend bool Compare(const bitset& bs1, const bitset& bs2);
    friend bool Compare(const bitset* bs1, const bitset* bs2);

    bitset& Union(const bitset& bs);
    bitset* Union(const bitset* bs);

    friend bitset Union(const bitset& bs1, const bitset& bs2);
    friend bitset* Union(const bitset* bs1, const bitset* bs2);

    bitset& Intersection(const bitset& bs);
    bitset* Intersection(const bitset* bs);

    friend bitset Intersection(const bitset& bs1, const bitset& bs2);
    friend bitset* Intersection(const bitset* bs1, const bitset* bs2);

    bitset& Difference(const bitset& bs);
    bitset* Difference(const bitset* bs);

    friend bitset Difference(const bitset& bs1, const bitset& bs2);
    friend bitset* Difference(const bitset* bs1, const bitset* bs2);

    bitset& operator = (const bitset& bs);

    bool operator == (const bitset& bs) {
        return ::nonstd::Compare(*this, bs);
    }
    bool operator != (const bitset& bs) {
        return !nonstd::Compare(*this, bs);
    }

    bool operator < (const bitset& bs) const;

    bitset operator |= (const bitset& bs) {
        return Union(bs);
    }
    bitset operator |= (bitset& bs) {
        return Union(bs);
    }
    bitset operator |= (unsigned int element) {
        set(element);
        return *this;
    }

    bitset operator &= (const bitset& bs) {
        return Intersection(bs);
    }
    bitset operator &= (bitset& bs) {
        return Intersection(bs);
    }

    bitset operator ~ () {
        return Negate();
    }

    bitset operator ! () {
        return Negate();
    }

    friend bitset operator | (const bitset& lhs, const bitset& rhs) {
        return nonstd::Union(lhs, rhs);
    }
    friend bitset operator & (const bitset& lhs, const bitset& rhs) {
        return nonstd::Intersection(lhs, rhs);
    }

    friend bool operator == (const bitset& lhs, const bitset& rhs) {
        return nonstd::Compare(lhs, rhs);
    }
    friend bool operator != (const bitset& lhs, const bitset& rhs) {
        return !nonstd::Compare(lhs, rhs);
    }

private:
    typedef unsigned int WORD;

    size_t sizeInBits;
    size_t sizeInWords;
    enum { sizeOfWord = sizeof(WORD) * 8 };

    bool complement;
    WORD* data;
};

};

// TODO: Deal with empty bitsets in operations !

// End bitset.h
