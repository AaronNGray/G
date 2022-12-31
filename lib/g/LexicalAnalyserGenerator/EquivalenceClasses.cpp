//
//  g/LexicalAnalyserGenerator/EquivalenceClasses.cpp - Equivalence Classes
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//
//  Algorithm abstract from Robert Grainger
//

#include "g/LexicalAnalyserGenerator/EquivalenceClasses.h"
#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include "nonstd/bitset.h"

namespace G {
namespace LexicalAnalyserGenerator {

EquivalenceClasses::EquivalenceClasses(const std::vector<Ranges>& rss) : EquivalenceSets() {
    for (auto rsi = rss.cbegin(); rsi != rss.cend(); ++rsi) {
        Ranges rs(*rsi);
        rs.normalize();
        add(rs, false);
    }
}

struct Position {
    Position(
        EquivalenceSet* set,
        EquivalenceSet::iterator begin,
        EquivalenceSet::iterator position,
        EquivalenceSet::iterator end,
        bitset::iterator sets,
        bool open
	) : index(indexIndex++), set(set), begin(begin), position(position), end(end), sets(sets), open(open) {}

	Position(std::vector<EquivalenceSet*>::iterator si) :
        Position(*si, (*si)->begin(), (*si)->begin(), (*si)->end(), (*si)->getSets().begin(), (*si)->getNegated()) {}

    int index;
    EquivalenceSet* set;
    EquivalenceSet::iterator begin;
    EquivalenceSet::iterator position;
    EquivalenceSet::iterator end;
    bitset::iterator sets;
    bool open;
    static int indexIndex;
};

int Position::indexIndex = 0;

struct Positions {
    Positions(std::vector<EquivalenceSet*>& sets) {
        // initialize all positions to first values
        for (std::vector<EquivalenceSet*>::iterator si = sets.begin(); si != sets.end(); ++si)
            positions.push_back(Position(si));
    }

    typedef std::vector<Position>::iterator iterator;

    iterator begin() { return positions.begin(); }
    iterator end() { return positions.end(); }
    size_t size() const { return positions.size(); }

    unsigned int findLowest() {
        unsigned int lowest = 0xFFFF;
        // find lowest first value
        for (Positions::iterator p = begin(); p != end(); ++p)
            if (p->position != p->end)
                lowest = std::min(lowest, *p->position);

        return lowest;
    }

    void moveForward(unsigned int lowest) {
        // iterate lowest first values forward
        for (Positions::iterator p = begin(); p != end(); ++p)
            if (p->position != p->end && *p->position == lowest)
                ++(p->position);
    }

    bool finished() {
        // have we finnished yet ?
        bool finished = true;
        for (Positions::iterator p = begin(); p != end(); ++p)
            finished &= (p->position == p->end);
        return finished;
    }

    void reset() {
        // reset all positions to back first values
        for (Positions::iterator p = begin(); p != end(); ++p)
            p->position = p->begin;
    }

    bitset generateInitialClassState() {
        // set class 'state' bitset
        bitset state(positions.size());
        bitset::iterator si = state.begin();
        for (Positions::iterator pi = positions.begin(); pi != positions.end(); ++pi, ++si)
            si.set(!pi->open);
        return state;
    }

    std::vector<Position> positions;
};

void EquivalenceSets::GenerateLowers() {
	// initialize all positions
	Positions positions(sets);

	// Generate Lowers
	do {
		// find lowest first value
		unsigned int lowest = positions.findLowest();

		// iterate lowest first values forward
		positions.moveForward(lowest);

		// append lowest value onto lowers vector
		lowers.push_back(lowest);

	} while (!positions.finished()); // have we finnished yet ?
}

void EquivalenceClasses::Generate() {

	// Generate Lowers
	GenerateLowers();

	// initialize all positions
	Positions positions(sets);

	// generate initial class 'state' bitset
    bitset state = positions.generateInitialClassState();

    unsigned int InputIndex = 0;
    unsigned int ColumnIndex = 0;
    std::map<bitset, unsigned int> stateToColumnIndex;

    // generate classes bitsets
    for (std::vector<unsigned int>::iterator l = lowers.begin(); l != lowers.end(); ++l, ++InputIndex) {
        unsigned int lower = *l;

        // set classes 'state' bitsets for the lowers
        bitset::iterator si = state.begin();

        // move through lowers generating classes bitsets
        for (Positions::iterator p = positions.begin(); p != positions.end(); ++p, ++si) {
            if (p->position != p->end && *p->position == lower) {
                si.invert();
                ++p->position;
            }
            p->sets.set(si.get());
            ++(p->sets);
        }

        // compress sets to classes based on unique state bitsets
        if (stateToColumnIndex.find(state) == stateToColumnIndex.end()) {
            stateToColumnIndex[state] = ColumnIndex;
            columnIndexToInputIndex[ColumnIndex] = InputIndex;
            ++ColumnIndex;
        }

        // output equivalence classes
        if (columnToInput[stateToColumnIndex[state]] == 0)
            columnToInput[stateToColumnIndex[state]] = InputIndex;
        inputIndexToColumnIndex[InputIndex] = stateToColumnIndex[state];
    }

    // Generate classes
    for (auto set : sets) {
        bitset classmap;
        for (unsigned int ci = 0; ci < columnToInput.size(); ++ci)
            classmap.set(ci, set->getSets()[columnToInput[ci]].get());

        classes.push_back(new EquivalenceClass(classmap));
    }

    inputs = InputIndex;
    columns = ColumnIndex;
}

bool compare(const EquivalenceClasses& lhs, const EquivalenceClasses& rhs) {
	return true;
}

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/EquivalenceClasses.cpp - Equivalence Classes
