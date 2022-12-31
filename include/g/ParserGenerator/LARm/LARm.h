//
//  g/ParserGenerator/LARm/LARm.h - LARm State And table Generation header.
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#pragma once

#include "g/ParserGenerator/LR/LR.h"
#include "g/ParserGenerator/LARm/LAA.h"

#include "nonstd/set.h"
#include "nonstd/deque.h"
#include "nonstd/bitset.h"
#include "g/Table.h"
#include <iostream>
#include <deque>
#include <map>
#include <initializer_list>

namespace G {
namespace ParserGenerator {

class LARm : public LR {
public:
    LARm(ContextFreeGrammar* grammar, std::ostream& output, bool rowCompressed = true, unsigned debug = 0) : LR(grammar), rowCompressed(rowCompressed), output(output), debug(debug), shiftReduceTable(nullptr), gotoTable(nullptr) {}
    ~LARm() {
        if (shiftReduceTable)
            delete shiftReduceTable;
        if (gotoTable)
            delete gotoTable;
    }

    struct Item {
        Item() {}
        Item(Item* item) : production(item->production), position(item->position), lookaheads(item->lookaheads) {}
        Item(ContextFreeGrammar::Production* production, Lookaheads lookaheads) : production(production), position(0), lookaheads(lookaheads) {}
        Item(ContextFreeGrammar::Production* production, unsigned int position, Lookaheads lookaheads) : production(production), position(position), lookaheads(lookaheads) {}

        Item& operator = (const Item& i) = default;

        size_t size() { return production->size(); }

		ContextFreeGrammar::Production* getProduction() { return production; }

		ContextFreeGrammar::Symbol* rightOfDot() {
            return production->getSymbol(position);
        }

        bool isNullable() { return (position == 0) ? true : (position < size()) ? production->getRHS()[position]->nullable() : true; } // TODO: fix or remove
        bool hasMove() const { return position < production->size(); }

        bool isReduction() { return !hasMove(); }
        bool isStart() { return production[0].isStart(); }
        bool isFinal() { return (position == production->size()) && production->isStart(); }
        Lookaheads& getLookaheads() { return lookaheads; }

		ContextFreeGrammar::Symbol* getRightOfDot() { return (position != production->size()) ? production->getSymbol(position) : ContextFreeGrammar::getEpsilon(); }
		ContextFreeGrammar::NonTerminal* getLHS() { return production->getLHS(); }

        Item Item::Move();

        std::string toString() const;
        std::string toString(ContextFreeGrammar*, int indent = 0) const;

		ContextFreeGrammar::Production* production;
        unsigned int position;
        Lookaheads lookaheads;

        friend bool operator < (const Item& lhs, const Item& rhs) {
            return lhs.production < rhs.production && lhs.position < rhs.position && lhs.lookaheads < rhs.lookaheads;
        }
        friend bool operator == (const Item& lhs, const Item& rhs) {
            return lhs.production == rhs.production && lhs.position == rhs.position && lhs.lookaheads == rhs.lookaheads;
        }
        friend bool operator != (const Item& lhs, const Item& rhs) {
            return !(lhs == rhs);
        }
    };

    struct Items : public set<Item> {
        Items() : set<Item>() {}
        Items(Item& item) : set<Item>() { insert(item); }
        Items(std::initializer_list<Item> items) : set<Item>(items) {}

		Items& getItems() { return *this; }

        Items MergeLookaheads();
        void MergeLookaheads(const LARm::Item item);

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

    struct ACTION {
        enum Function : unsigned {
            Shift,
            Reduce,
            Lookahead,
            Accept,
            Error
        };

        ACTION() : action(Error), value(0) {}
        ACTION(Function action, size_t value) : action(action), value(value) {}
        ACTION(Function action) : action(action), value(0) {}

        Function action:3;
        unsigned int value:29;

        operator enum Function () const { return action; }
        unsigned getValue() const { return value; }

        std::string toString() const {
            std::stringstream ss;
            switch (action) {
            case Shift:
                ss << "s" << std::to_string(value);
                break;
            case Reduce:
                ss << "r" << std::to_string(value);
                break;
            case Lookahead:
                ss << "l" << std::to_string(value);
            case Accept:
                ss << "a";
                break;
            case Error:
                ss << "-";
                break;
            }
            return ss.str();
        }
        std::string toCXXString() const {
            std::stringstream ss;
            switch (action) {
            case Shift:
                ss << "{Action::Function::Shift, " << std::to_string(value) << "}";
                break;
            case Reduce:
                ss << "{Action::Function::Reduce, " << std::to_string(value) << "}";
                break;
            case Lookahead:
                ss << "{Action::Function::Lookahead, " << std::to_string(value) << "}";
            case Accept:
                ss << "{Action::Function::Accept}";
                break;
            case Error:
                ss << "{Action::Function::Error}";
                break;
            }
            return ss.str();
        }
        friend bool operator == (const ACTION& lhs, const ACTION& rhs) {
            return lhs.action == rhs.action && lhs.value == rhs.value;
        }
        friend bool operator != (const ACTION& lhs, const ACTION& rhs) {
            return !(lhs == rhs);
        }
    };

    struct GOTO {
        GOTO() : value(0) {}
        GOTO(unsigned int value) : value(value) {}
        unsigned int value;

        operator unsigned int () { return value; }
        std::string toString() const {
            return value ? std::to_string(value) : "-";
        }
        std::string toCXXString() const {
            return std::to_string(value);
        }
        friend bool operator == (const GOTO& lhs, const GOTO& rhs) {
            return lhs.value == rhs.value;
        }
        friend bool operator != (const GOTO& lhs, const GOTO& rhs) {
            return lhs.value != rhs.value;
        }
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

        bool isShift(ContextFreeGrammar::Terminal* terminal) {
            return shifts[terminal] != nullptr;
        }
        bool isReduction() {
            return items[0].isReduction();  // TODO: Wrong
        }
        bool hasReduction() {
            return items.hasReductions() != 0;
        }
        bool isAccept() {
            return items[0].isStart();      // TODO: Wrong
        }
        bool isLookahead(ContextFreeGrammar::Terminal* terminal) {
            return getLookaheads()[terminal->getIndex()];
        }

        bool isStart() { return items.isStart(); } // TODO: is this semantically correct or should it be 'hasStart()' ?
        size_t hasReductions() { return items.hasReductions(); }

        size_t getIndex() { return index; }
        bitset& getLookaheads() {
            return items[0].getLookaheads(); // TODO: Check !
        }

        void GenerateActions(ContextFreeGrammar* grammar, std::ostream& output);
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

        std::string toString(ContextFreeGrammar* grammar, int i) const;

        size_t index;
        Grammar::ContextFreeGrammar* production;
        bool final;
        Items items;
        std::map<ContextFreeGrammar::Symbol*, State*> shifts;      // map Symbol To State
        std::map<ContextFreeGrammar::Terminal*, ACTION> actions;
		LAA::STATE laaState;

		vector<Item*> reductions;
    };

    template<template <class T> class C = set>
    struct States : public C<State*> {
        States() : states(1) {}
        State* newState(Items items) {
            return new State(states++, items);
        }

        State* find(Items& items) {
            auto sp = std::find_if(cbegin(), cend(), [items](State* sp) { return items == *sp; });
            if (sp != cend())
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

	Items Closure(Items& I);
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
	LAA* laa;
};

bool is_member(std::deque<LARm::Item>& items, LARm::Item item);

inline std::string AsString(LARm::ACTION value) {
    std::string s = value.toString();
    return s;
}

inline std::string AsString(LARm::GOTO value) {
    std::string s = value.toString();
    return s;
}

inline std::string AsCXXString(LARm::ACTION value) {
    std::string s = value.toCXXString();
    return s;
}

inline std::string AsCXXString(LARm::GOTO value) {
    std::string s = value.toCXXString();
    return s;
}

} // end namespace ParserGenerator
} // end namespce G
