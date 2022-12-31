//
//  g/ParserGenerator/LR1.h - LR1 State And table Generation header.
//
//  Property and Copyright (c) 2016, 2017 Aaron Nathaniel Gray
//

#pragma once

#include "g/ParserGenerator/LR/LR.h"
#include "nonstd/set.h"
#include "nonstd/map.h"
#include "nonstd/deque.h"
#include "nonstd/bitset.h"
#include "g/Table.h"
#include <iostream>
#include <deque>
//#include <map>
#include <initializer_list>
#include <cassert>

namespace G {
namespace ParserGenerator {

class LR1 : public LR {
public:
    LR1(ContextFreeGrammar* grammar, bool rowCompressed = true, unsigned debug = 0) : LR(grammar, rowCompressed, debug) {}
    ~LR1() {}

	struct Item : public LR::Item {
		Item() {}
		Item(Item* item) : LR::Item(item) {}
		Item(ContextFreeGrammar::Production* production) : LR::Item(production) {}
		Item(ContextFreeGrammar::Production* production, unsigned int position) : LR::Item(production, position) {}
		Item(ContextFreeGrammar::Production* production, Lookaheads lookaheads) : LR::Item(production), lookaheads(lookaheads) {}
		Item(ContextFreeGrammar::Production* production, unsigned int position, Lookaheads lookaheads) : LR::Item(production, position), lookaheads(lookaheads) {}

		Lookaheads& getLookaheads() { return lookaheads; }

		bool hasMove() const { return position < production->size(); }
		Item Move();

		bool isReduction() { return !hasMove(); }

		std::string toString() const;
		std::string toString(ContextFreeGrammar*, int indent = 0) const;

		friend bool operator < (const Item& lhs, const Item& rhs) {
			return lhs.production < rhs.production && lhs.position < rhs.position && lhs.lookaheads < rhs.lookaheads;
		}
		friend bool operator == (const Item& lhs, const Item& rhs) {
			return lhs.production == rhs.production && lhs.position == rhs.position && lhs.lookaheads == rhs.lookaheads;
		}
		friend bool operator != (const Item& lhs, const Item& rhs) {
			return !(lhs == rhs);
		}

		Lookaheads lookaheads;
	};

	struct Items : public set<Item> {
		Items() : set<Item>() {}
		Items(Item& item) : set<Item>() { insert(item); }
		Items(Item&& item) : set<Item>() { insert(item); }
		Items(std::initializer_list<Item> items) : set<Item>(items) {}

		void insert(Item& item) { set<Item>::insert(item); }
		void insert(Item&& item) { set<Item>::insert(item); }

		const Items& getItems() const { return *this; }

		Items MergeLookaheads();
		void MergeLookaheads(const LR1::Item item);

		size_t hasReductions() {
			size_t reductions = 0;
			for (auto item : getItems())
				if (item.isReduction())
					++reductions;
			return reductions;
		}
		bool isStart() {
			bool start = false;
			for (auto item : getItems())
				start |= item.isFinal();
			return start;
		}

		std::string toString() const;
		std::string toString(ContextFreeGrammar* grammar, int indent = 0) const;

		friend bool operator == (const Items& lhs, const Items& rhs);
	};

	struct State;
	struct Reduction {
		Reduction(Item* item) : item(item) {}
		Item* item;

		Item* getItem() { return item; }

		bitset& getLookaheads() { return item->getLookaheads(); }
		ContextFreeGrammar::NonTerminal* getLHS() { return item->getLHS(); }
		ContextFreeGrammar::Production* getProduction() { return item->production; }
	};

	struct Conflict {
	};
	struct ShiftReduceConflict : public Conflict {
		ShiftReduceConflict(bitset symbols, State* state, Items* items) : symbols(symbols), state(state), items(items) {}

		bitset symbols;
		State* state;
		Items* items;
	};
	struct ReduceReduceConflict : public Conflict {
		ReduceReduceConflict(Item* item) : item(item) {}
		Item* item;
	};

	struct State : public LR::State {
		State() : LR::State(0), production(nullptr), reduceReduceConflictItems(nullptr) {}
		State(unsigned int index) : LR::State(index), production(nullptr), reduceReduceConflictItems(nullptr) {}
		State(unsigned int index, Items items) : LR::State(index), items(items), production(nullptr), reduceReduceConflictItems(nullptr) {}
		~State() {}

		void addShift(ContextFreeGrammar::Symbol* symbol, State* state) {
			assert(state != nullptr);
			shifts[symbol] = state;
		}
		void addReduction(Item* item) {
			reductions.push_back(item);
		}

		bool isReduction() {
			return items[0].isReduction();
		}
		bool hasReduction() {
			return items.hasReductions() != 0;
		}
		bool isAccept() {
			return items[0].isStart();
		}
		bool isLookahead(ContextFreeGrammar::Terminal* terminal) {
			return getLookaheads()[terminal->getIndex()];
		}

		bool isStart() { return items.isStart(); }
		size_t hasReductions() { return items.hasReductions(); }

		bitset& getLookaheads() {
			return items[0].getLookaheads(); // TODO: Check !
		}

		void GenerateActions(ContextFreeGrammar* grammar);

		void printShifts(std::ostream &os);
		void printReductions(std::ostream &os, ContextFreeGrammar* grammar);

		operator Items& () { return items; }

		typedef Items::iterator iterator;
		typedef Items::const_iterator const_iterator;

		iterator begin() { return items.begin(); }
		iterator end() { return items.end(); }
		const_iterator begin() const { return items.begin(); }
		const_iterator end() const { return items.end(); }
		const_iterator cbegin() { return items.cbegin(); }
		const_iterator cend() { return items.cend(); }

		size_t size() const { return items.size(); }

		Item& operator [] (size_t index) { return items[index]; }
		const Item& operator [] (size_t index) const { return items[index]; }

		friend bool operator == (State& lhs, State& rhs) {
			return lhs.items == rhs.items;
		}

		bool hasConflicts() {
			return hasShiftReduceConflicts() || hasReduceReduceConflicts();
		}
		Lookaheads shiftReduceConflictsSymbols() const;
		Lookaheads reduceReduceConflictSymbols() const;
		bool hasShiftReduceConflicts() const;
		bool hasReduceReduceConflicts() const;
		vector<LR1::Item*>* CalculateReduceReduceConflictItems() const;
		vector<LR1::Item*>* getReduceReduceConflictItems();
		unsigned numberOfShiftReduceConflicts() const;
		unsigned numberOfReduceReduceConflicts() const;
		void AnalyseState(std::ostream &os, ContextFreeGrammar* grammar);

		std::string toString(ContextFreeGrammar* grammar, int i) const;

		ContextFreeGrammar::Production* production;	// TODO: change to reductions productions action.

		struct compSymbols {
			bool operator()(ContextFreeGrammar::Symbol* a, ContextFreeGrammar::Symbol* b) const { return a->getName() < b->getName(); }
		};

		Items items;
		std::map<ContextFreeGrammar::Symbol*, State*, compSymbols> shifts; // TODO: Rename as shifts
		vector<Item*> reductions;

		vector<Item*>* reduceReduceConflictItems;
	};

	template<template <class T> class C = set>
	struct States : public C<State*> {
		States() : states(1) {}
		C<State*>& getStates() { return *this; }
		const C<State*>& getStates() const { return *this; }

		State* newState(Items items) {
			return new State(states++, items);
		}

		State* find(Items& items) {
			auto sp = std::find_if(C<State*>::cbegin(), C<State*>::cend(), [items](State* sp) { return items == *sp; });
			if (sp != C<State*>::cend())
				return *sp;
			else
				return nullptr;
		}

		size_t getNumberOfStates() const { return states; }

		std::string toString(ContextFreeGrammar* grammar, int i) const;

		unsigned states;
	};

    size_t getNumberOfStates() const { return states.getNumberOfStates(); }

    static bitset FIRST(Item item);
    static bitset FIRST(ContextFreeGrammar::Production& production, size_t position);

	virtual void Generate();

	void GenerateStates();
    void GenerateStateProductions();
    void GenerateActions();

	virtual void AnalyseStates(std::ostream &os);

	void GenerateShiftReduceTable();
    void GenerateGotoTable();
    size_t CheckReductionsPerState();
    void GenerateAcceptStates();

	void PrintTables(std::ostream &os) const;

	virtual void Output(std::ostream &os) const;
	virtual void OutputIncludesHXX(std::ostream &os, std::string className) const;

	virtual void OutputCodeHXX(std::ostream &os, std::string className) const;
	virtual void OutputCodeCXX(std::ostream &os, std::string className) const;

	virtual void OutputTablesHXX(std::ostream &os, std::string className) const;
	virtual void OutputTablesCXX(std::ostream &os, std::string className) const;

	virtual void OutputTerminals(std::ostream& os) const;
	virtual void OutputNonTerminals(std::ostream& os) const;

	virtual void OutputStates(std::ostream& os) const;

	void OutputShiftReduceTable(std::ostream &os);
    void OutputGotoTable(std::ostream &os);

    void OutputShiftReduceTableHXX(std::ostream &os, std::string className) const;
    void OutputShiftReduceTableCXX(std::ostream &os, std::string className) const;
    void OutputGotoTableHXX(std::ostream &os, std::string className) const;
    void OutputGotoTableCXX(std::ostream &os, std::string className) const;

	virtual Items Closure(const Items& I);
	virtual Items Closure(const Items&& I) { return Closure(I); };
	Items Closure(Item& I) { return Closure(Items(I)); }
    Items Goto(Items&, ContextFreeGrammar::Symbol* symbol);

	virtual bool compare(const Machine* rhs) const;

	bool hasConflicts();
	unsigned numberOfShiftReduceConflicts();
	unsigned numberOfReduceReduceConflicts();

	unsigned shiftReduceConflicts;
	unsigned reduceReduceConflicts;

    Items items;
    States<set> states;

	static Machine* Create(ContextFreeGrammar* grammar, bool rowCompressed, unsigned debug) { return new LR1(grammar, rowCompressed, debug); }
	static std::string Name;
};

/*
template<>
std::string LR1::States<>::toString(ContextFreeGrammar* grammar, int i) const {
    std::stringstream ss;
    int s = 0;
    for (auto state : getStates()) {
        ss << state->index << " : {" << std::endl;
        ss << state->toString(grammar, i);
        ss << "}" << std::endl;
    }
    return ss.str();
}
*/

bool is_member(std::deque<LR1::Item>& items, LR1::Item item);

inline std::string AsString(LR1::ACTION value) {
    std::string s = value.toString();
    return s;
}

inline std::string AsString(LR1::GOTO value) {
    std::string s = value.toString();
    return s;
}

inline std::string AsCXXString(LR1::ACTION value) {
    std::string s = value.toCXXString();
    return s;
}

inline std::string AsCXXString(LR1::GOTO value) {
    std::string s = value.toCXXString();
    return s;
}

} // end namespace ParserGenerator
} // end namespce G

// End lib/ParserGenerator/LR1.h - LR1 State And table Generation header.
