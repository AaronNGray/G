//
//	g/ParserGenerator/LR1/Analyse.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"
#include "nonstd/deque.h"
#include "nonstd/Utils.h"

#include <string>
#include <map>
#include <deque>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace G {
namespace ParserGenerator {


size_t LR1::CheckReductionsPerState() {
	size_t conflicts = 0;
	for (auto state : states) {
		size_t reductions = (*state).hasReductions();
		if (reductions > 1) {
			conflicts += reductions - 1;
		}
	}
	return conflicts;
}

//
//
//

Lookaheads LR1::State::shiftReduceConflictsSymbols() const {
	bitset shiftSymbols;
	for (auto shift : shifts)
		shiftSymbols.set(shift.first->getIndex());
	bitset reduceSymbols;
	for (auto reduction : reductions)
		reduceSymbols.Union(reduction->getLookaheads());

	return Intersection(shiftSymbols, reduceSymbols);
}

Lookaheads LR1::State::reduceReduceConflictSymbols() const {
	bitset reduceSymbols;
	for (auto first = reductions.begin(); first != reductions.end(); ++first)
		for (auto second = first + 1; second != reductions.end(); ++second)
			reduceSymbols |= (*first)->getLookaheads() & (*second)->getLookaheads();

	return reduceSymbols;
}

bool LR1::State::hasShiftReduceConflicts() const {
	return !shiftReduceConflictsSymbols().isEmpty();
}

bool LR1::State::hasReduceReduceConflicts() const {
	return !reduceReduceConflictSymbols().isEmpty();
}

vector<LR1::Item*>* LR1::State::CalculateReduceReduceConflictItems() const {
	vector<LR1::Item*>* rs = new vector<LR1::Item*>;
	bitset reduceSymbols = reduceReduceConflictSymbols();
	for (auto reduction = reductions.begin(); reduction != reductions.end(); ++reduction)
		if (!(reduceSymbols & (*reduction)->getLookaheads()).isEmpty())
			rs->push_back(*reduction);

	return rs;
}

vector<LR1::Item*>* LR1::State::getReduceReduceConflictItems() {
	if (reduceReduceConflictItems)
		return reduceReduceConflictItems;
	else {
		reduceReduceConflictItems = CalculateReduceReduceConflictItems();
		return reduceReduceConflictItems;
	}
}

unsigned LR1::State::numberOfShiftReduceConflicts() const {
	return shiftReduceConflictsSymbols().size();
}
unsigned LR1::State::numberOfReduceReduceConflicts() const {
	return (reduceReduceConflictItems != nullptr) ? reduceReduceConflictItems->size() : 0;
}

bool LR1::hasConflicts() {
	return numberOfShiftReduceConflicts() != 0 || (numberOfReduceReduceConflicts() != 0);
}

unsigned LR1::numberOfShiftReduceConflicts() {
	shiftReduceConflicts = 0;
	for (auto state : states)
		shiftReduceConflicts += state->numberOfShiftReduceConflicts();
	return shiftReduceConflicts;
}

unsigned LR1::numberOfReduceReduceConflicts() {
	reduceReduceConflicts = 0;
	for (auto state : states)
		reduceReduceConflicts += state->numberOfReduceReduceConflicts();

	return reduceReduceConflicts;
}

void LR1::AnalyseStates(std::ostream &os) {
	if (hasConflicts()) {
		os << "Conflicts: " << nonstd::endl;
		for (auto state : states)
			state->AnalyseState(os, grammar);
	}
}

void LR1::State::AnalyseState(std::ostream &os, ContextFreeGrammar* grammar) {
	if (hasConflicts()) {
		os << "State: " << getIndex() << nonstd::endl;
		if (numberOfShiftReduceConflicts())
			os << numberOfShiftReduceConflicts() << " Shift/Reduce conflicts" << nonstd::endl;
		if (numberOfReduceReduceConflicts())
			os << numberOfReduceReduceConflicts() << " Reduce/Reduce conflicts" << nonstd::endl;
		if (hasShiftReduceConflicts()) {
			os << "\t" << "Shifts:" << nonstd::endl;
			printShifts(os);
		}
		if (hasReduceReduceConflicts()) {
			os << "\t" << "Reductions:" << nonstd::endl;
			printReductions(os, grammar);
		}
		else if (hasShiftReduceConflicts()) {
			os << "\t" << "Reduction:" << nonstd::endl;
			os << "\t\t" << reductions[0]->toString(grammar) << nonstd::endl;
		}
	}
}

void LR1::State::printShifts(std::ostream &os) {
	for (auto shift = shifts.begin(); shift != shifts.end(); ++shift)
		os << "\t\t" << (*shift).first->toString() << " : " << (*shift).second->getIndex() << nonstd::endl;
}
void LR1::State::printReductions(std::ostream &os, ContextFreeGrammar* grammar) {
	for (auto reduction : reductions)
		os << "\t\t" << reduction->toString(grammar) << nonstd::endl;
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/Analyse.cpp
