//
//  g/ParserGenerator/LR0.h - LR0 State And table Generation header.
//
//  Property and Copyright (c) 2016, 2017 Aaron Nathaniel Gray
//

#pragma once

#include "g/ParserGenerator/LR/LR.h"
#include "nonstd/set.h"
#include "nonstd/deque.h"
#include "nonstd/bitset.h"
#include "g/Table.h"
#include "nonstd/maths.h"
#include <iostream>
#include <deque>
#include <map>
#include <initializer_list>

namespace G {
namespace ParserGenerator {

class LR0 : public LR {
public:
	LR0(ContextFreeGrammar* grammar, std::ostream& output, bool rowCompressed = true, unsigned debug = 0) : LR(grammar), rowCompressed(rowCompressed), output(output), debug(debug) {}
	~LR0() {}

	struct Item {
		Item() {}
		Item(Item* item) : production(item->production), position(item->position) {}
		Item(ContextFreeGrammar::Production* production) : production(production), position(0) {}
		Item(ContextFreeGrammar::Production* production, unsigned int position) : production(production), position(position) {}

		Item& operator = (const Item& i) = default;

		size_t size() { return production->size(); }

		ContextFreeGrammar::Production* getProduction() { return production; }

		ContextFreeGrammar::Symbol* rightOfDot() {
			return production->getSymbol(position);
		}

		bool isNullable() { return (position == 0) ? true : (position < size()) ? production->getRHS()[position]->nullable() : true; } // TODO: fix or remove
		bool hasMove() const;

		bool isReduction() { return !hasMove(); }
		bool isStart() { return production[0].isStart(); }
		bool isFinal() { return (position == production->size()) && production->isStart(); }

		ContextFreeGrammar::Symbol* getRightOfDot() { return (position != production->size()) ? production->getSymbol(position) : ContextFreeGrammar::getEpsilon(); }
		ContextFreeGrammar::NonTerminal* getLHS() { return production->getLHS(); }

		Item Move();

		std::string toString() const;
		std::string toString(ContextFreeGrammar*, int indent = 0) const;

		ContextFreeGrammar::Production* production;
		unsigned int position;

		friend bool operator < (const Item& lhs, const Item& rhs) {
			return lhs.production < rhs.production && lhs.position < rhs.position;
		}
		friend bool operator == (const Item& lhs, const Item& rhs) {
			return lhs.production == rhs.production && lhs.position == rhs.position;
		}
		friend bool operator != (const Item& lhs, const Item& rhs) {
			return !(lhs == rhs);
		}
	};

	struct Items : public set<Item> {
		Items() : set<Item>() {}
		Items(Item& item) : set<Item>() { insert(item); }
		Items(Item&& item) : set<Item>() { insert(item); }
		Items(std::initializer_list<Item> items) : set<Item>(items) {}

		Items& getItems() { return *this; }

		Items MergeLookaheads();
		void MergeLookaheads(const LR0::Item item);

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

		ContextFreeGrammar::NonTerminal* getLHS() { return item->getLHS(); }
		ContextFreeGrammar::Production* getProduction() { return item->production; }
	};

	struct State {
		State(unsigned int index) : index(index) {}
		State(unsigned int index, Items items) : index(index), items(items) {}
		~State() {}

		void addShift(ContextFreeGrammar::Symbol* symbol, State* state) {
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
		bool isShift(ContextFreeGrammar::Terminal* terminal) {
			return shifts[terminal] != nullptr;
		}

		bool isStart() { return items.isStart(); } // TODO: is this semantically correct or should it be 'hasStart()' ?
		size_t hasReductions() { return items.hasReductions(); }

		size_t getIndex() { return index; }

		unsigned numberOfShifts() {
			return shifts.size();
		}
		unsigned numberOfReductions() {
			return reductions.size();
		}

		bool hasConflicts() {
			return hasShiftReduceConflicts() || hasReduceReduceConflicts();
		}
		bool hasShiftReduceConflicts() {
			return numberOfShifts() > 0 && numberOfReductions() > 0;
		}
		bool hasReduceReduceConflicts() {
			return numberOfReductions() > 1;
		}

		unsigned numberOfShiftReduceConflicts() {
			return numberOfShifts() * numberOfReductions();
		}
		unsigned numberOfReduceReduceConflicts() {
			return nonstd::additionalFactorial(numberOfReductions());
		}

		void AnalyseState(std::ostream &os, ContextFreeGrammar* grammar);

		void GenerateActions(ContextFreeGrammar* grammar);
		void setAction(ContextFreeGrammar::Terminal* terminal, ACTION action) {
			actions[terminal] = action;
		}

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

		void printShifts(std::ostream &os);
		void printReductions(std::ostream &os, ContextFreeGrammar* grammar);

		std::string toString(ContextFreeGrammar* grammar, int i) const;

		size_t index;
		ContextFreeGrammar::Production* production;
		bool final;
		Items items;
		std::map<ContextFreeGrammar::Symbol*, State*> shifts;
		std::map<ContextFreeGrammar::Terminal*, ACTION> actions;
		vector<Item*> reductions;
	};

	template<template <class T> class C = set>
	struct States : public C<State*> {
		States() : states(1) {}
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

		size_t getStates() { return states; }

		std::string toString(ContextFreeGrammar* grammar, int i) const;

		unsigned states;
	};

	size_t getStates() { return states.getStates(); }

	static bitset FIRST(Item item);
	static bitset FIRST(ContextFreeGrammar::Production& production, size_t position);

	void GenerateStates();
	void AnalyseStates(std::ostream &os);

	void GenerateStateProductions();
	void GenerateActions();

	void GenerateShiftReduceTable();
	void GenerateGotoTable();
	size_t CheckReductionsPerState();
	void GenerateAcceptStates();

	void OutputTables(std::ostream &os);

	void OutputHXX(std::ostream &os, std::string className);
	void OutputCXX(std::ostream &os, std::string className);

	void OutputShiftReduceTable(std::ostream &os);
	void OutputGotoTable(std::ostream &os);

	void OutputShiftReduceTableHXX(std::ostream &os, std::string className);
	void OutputShiftReduceTableCXX(std::ostream &os, std::string className);
	void OutputGotoTableHXX(std::ostream &os, std::string className);
	void OutputGotoTableCXX(std::ostream &os, std::string className);

	Items Closure(Items&& I);
	Items Closure(Item& I) { return Closure(Items(I)); }
	Items Goto(Items&, ContextFreeGrammar::Symbol* symbol);

	unsigned debug;
	std::ostream& output;

	bool rowCompressed;
	Items items;
	States<set> states;

	Table<size_t, ACTION, 1>* shiftReduceTable;
	Table<size_t, GOTO, 1>* gotoTable;
	vector<int, 1> acceptTable;
};
/*
inline size_t LR0::Item::size() {
	return production->size();
}

inline Grammar::Production* LR0::Item::getProduction() {
	return production;
}

inline Grammar::Symbol* LR0::Item::rightOfDot() {
	return production->getSymbol(position);
}

inline bool LR0::Item::isNullable() {
	return (position == 0) ? true : (position < size()) ? (*production->rhs)[position]->nullable() : true;
} // TODO: fix or remove

inline bool LR0::Item::hasMove() const {
	return position < production->size();
}

inline bool LR0::Item::isReduction() {
	return !hasMove();
}

inline bool LR0::Item::isStart() {
	return production[0].isStart();
}

inline bool LR0::Item::isFinal() {
	return (position == production->size()) && production->isStart();
}

inline Grammar::Symbol* LR0::Item::getRightOfDot() {
	return (position != production->size()) ? production->getSymbol(position) : Grammar::getEpsilon();
}

inline Grammar::NonTerminal* LR0::Item::getLHS() {
	return production->getLHS();
}
*/
//bool is_member(std::deque<LR0::Item>& items, LR0::Item item);

inline std::string AsString(LR0::ACTION value) {
	std::string s = value.toString();
	return s;
}

inline std::string AsString(LR0::GOTO value) {
	std::string s = value.toString();
	return s;
}

inline std::string AsCXXString(LR0::ACTION value) {
	std::string s = value.toCXXString();
	return s;
}

inline std::string AsCXXString(LR0::GOTO value) {
	std::string s = value.toCXXString();
	return s;
}

} // end namespace ParserGenerator
} // end namespace G

// End g/ParserGenerator/LR0.h - LR0 State And table Generation header.
