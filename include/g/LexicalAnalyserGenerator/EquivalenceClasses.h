//
//  EquivalenceClasses.h - Equivalence set and Equivalence class classes
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//
//  Algorithm abstract from Robert Grainger
//

#pragma once

#include <vector>
#include <map>
#include <initializer_list>

#include "nonstd/bitset.h"
#include "g/LexicalAnalyserGenerator/Ranges.h"
#include "g/LexicalAnalyserGenerator/CharacterClass.h"
#include "g/LexicalAnalyserGenerator/Lowers.h"

namespace G {
namespace LexicalAnalyserGenerator {

class EquivalenceSet {
public:
    EquivalenceSet(unsigned int index) : index(index), negative(false), lowers(), sets() {}
    explicit EquivalenceSet(unsigned int index, const Range &range, bool negate = false) : index(index), negative(negate), lowers(range), sets() {}
    explicit EquivalenceSet(unsigned int index, const Ranges &ranges, bool negate = false) : index(index), negative(negate), lowers(ranges), sets() {}
    EquivalenceSet(unsigned int index, const CharacterClass& cc) : index(index), negative(cc.negative), lowers(cc.ranges), sets() {}
    EquivalenceSet(unsigned int index, const EquivalenceSet& es) : index(index), negative(es.negative), lowers(es.lowers), sets() {}
    EquivalenceSet(unsigned int index, const EquivalenceSet& es, bool negate) : index(index), negative(negate), lowers(es.lowers), sets() {}

    void add(unsigned int value) { lowers.push_back(value); }

    typedef std::vector<unsigned int>::iterator iterator;
    typedef std::vector<unsigned int>::const_iterator const_iterator;
    iterator begin() { return lowers.begin(); }
    iterator end() { return lowers.end(); }
    const_iterator cbegin() { return lowers.begin(); }
    const_iterator cend() { return lowers.end(); }

    Ranges* getRanges();

    bool getNegated() const { return negative; }

    bitset &getSets() { return sets; }
    void setSets(bitset& sets) { sets = sets; }

	operator bitset& () { return sets; }

    std::string toString(const Lowers& lowers) const;
    std::string toString() const;

    unsigned int getIndex() const { return index; }

    std::string diag();

    friend bool operator == (EquivalenceSet eql, EquivalenceSet eqr);
private:
    bool negative;
    Lowers lowers;
    unsigned int index;
    bitset sets;
};

inline bool operator == (EquivalenceSet eql, EquivalenceSet eqr) {
    return (
        (eql.lowers.size() == eqr.lowers.size()) &&
        (eql.negative == eqr.negative) &&
        (eql.lowers == eqr.lowers)
    );
}

//
//
//

class EquivalenceSets {
public:
    EquivalenceSets() : index(0), lowers() {}
    ~EquivalenceSets() {
        for (auto equivalenceSet : sets)
            delete equivalenceSet;
    }

    EquivalenceSet* newEquivalenceSet(const Ranges &ranges, bool negate = false) {
        return new EquivalenceSet(index++, ranges, negate);
    }

    EquivalenceSet* add(const Ranges& rs, bool negate = false) {
        EquivalenceSet* es = newEquivalenceSet(rs, negate);
        sets.push_back(es);
        return es;
    }
    unsigned int add(const CharacterClass& cc) {
        EquivalenceSet* es = new EquivalenceSet(index++, cc);
        sets.push_back(es);
        return sets.size() - 1;
    }
    EquivalenceSet* add(EquivalenceSet* es) {
        sets.push_back(es);
        return es;
    }

	void GenerateLowers();

    unsigned int getNumberOfClasses() { return lowers.size(); }
    std::vector<EquivalenceSet*>& getEquivalenceSets() { return sets; }

	EquivalenceSet& getEquivalenceSet(unsigned int set) { return *sets[set]; }
	unsigned int getNumberOfEquivalenceSets() { return sets.size(); }

    Lowers& getLowers() { return lowers; }

    std::string toString() const;
    std::string toString2() const;

    typedef std::vector<EquivalenceSet*>::iterator iterator;
    typedef std::vector<EquivalenceSet*>::const_iterator const_iterator;
    iterator begin() { return sets.begin(); }
    iterator end() { return sets.end(); }
    const_iterator cbegin() const { return sets.cbegin(); }
    const_iterator cend() const { return sets.cend(); }
    size_t size() const { return sets.size(); }
    EquivalenceSet& operator [] (unsigned int index) { return *sets[index]; }

protected:
    unsigned int index;
    Lowers lowers;
    std::vector<EquivalenceSet*> sets;
};

//

class EquivalenceClass {
public:
    EquivalenceClass() : classes(), index(0) {}
    EquivalenceClass(bitset classes) : classes(classes), index(0) {}

    typedef bitset::iterator iterator;
    typedef bitset::const_iterator const_iterator;
    iterator begin() { return classes.begin(); }
    iterator end() { return classes.end(); }
    const_iterator cbegin() { return classes.cbegin(); }
    const_iterator cend() { return classes.cend(); }

    std::string toString() const;
    std::string toString(const Lowers& lowers) const;

    bitset &getClasses() { return classes; }
    void setClasses(bitset& _classes) { classes = _classes; }

	operator bitset& () { return classes; }

	Ranges& getRanges(std::vector<unsigned int> &lowers);
    Ranges& getRanges2(std::vector<unsigned int> &lowers);

    unsigned int getIndex() { return index; }

    std::string diag();

    friend bool operator == (EquivalenceClass eql, EquivalenceClass eqr);

private:
    bitset classes;
    unsigned int index;
};

inline bool operator == (EquivalenceClass eql, EquivalenceClass eqr) {
    return eql.classes == eqr.classes;
}

//

class EquivalenceClasses : public EquivalenceSets {
public:
    EquivalenceClasses(unsigned int values = 128) : values(values), inputs(0), columns(0), EquivalenceSets() {}
    EquivalenceClasses(const std::vector<Ranges>& rss);
    ~EquivalenceClasses() {
        for (auto equivalenceClass : classes)
            delete equivalenceClass;
    }

	EquivalenceSets& getEquivalenceSets() { return *this; }

	void Generate();

    std::string toString();

    std::string diag();
    std::string print() const;
    std::string printRanges();

    Lowers& getLowers() { return lowers; }
    Ranges& getRanges() const;

    typedef std::vector<EquivalenceClass*>::iterator iterator;
    typedef std::vector<EquivalenceClass*>::const_iterator const_iterator;
    iterator begin() { return classes.begin(); }
    iterator end() { return classes.end(); }
    const_iterator cbegin() const { return classes.cbegin(); }
    const_iterator cend() const { return classes.cend(); }
    size_t size() const { return classes.size(); }
    EquivalenceClass& operator [] (unsigned int index) { return *classes[index]; }

    size_t getNumberOfEquivalenceSets() { return sets.size(); }
    size_t getNumberOfEquivalenceClasses() { return classes.size(); }

    size_t getNumberOfColumns() const {
        return columns;
    }
    size_t getNumberOfInputs() const {
        return inputs;
    }

    unsigned int getClassIndexFromSetIndex(unsigned int index) {
        return index;
    }
    unsigned int getInputFromColumn(unsigned int input) {
        return columnToInput[input];
    }
    unsigned int getClassIndexToSetIndex(unsigned int classIndex) {
        return classIndex;
    }
    unsigned int getInputIndexFromColumnIndex(unsigned int columnIndex) {
        return inputIndexToColumnIndex[columnIndex];
    }
    std::map<unsigned int, unsigned int>& getinputIndexToColumnIndex() {
        return inputIndexToColumnIndex;
    }

	friend bool compare(const EquivalenceClasses& lhs, const EquivalenceClasses& rhs);

private:
    unsigned int values;
    size_t columns;
    size_t inputs;

    std::vector<EquivalenceClass*> classes;

    std::map<unsigned int, unsigned int> inputIndexToColumnIndex;
    std::map<unsigned int, unsigned int> columnIndexToInputIndex;
    std::map<unsigned int, unsigned int> columnToInput;
};

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End EquivalenceClasses.h - Equivalence set and Equivalence class classes
