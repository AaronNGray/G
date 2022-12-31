//
//  g/ParserGenerator/LR.h - LR header
//
//  Property and Copyright (c) 2016, 20017 Aaron Nathaniel Gray
//

#pragma once

#include "g/Grammar/ContextFreeGrammar.h"
#include "g/ParserGenerator/Machine.h"
#include "g/Table.h"
#include "nonstd/set.h"

namespace G {
namespace ParserGenerator {

using namespace G::Grammar;

class LR : public Machine {
public:
    LR() : grammar(nullptr), gotoTable(nullptr), shiftReduceTable(nullptr) {}
    LR(ContextFreeGrammar* grammar, bool rowCompressed = true, unsigned debug = 0) : Machine(rowCompressed, debug), grammar(grammar), shiftReduceTable(nullptr), gotoTable(nullptr) {}
    ~LR() {
        if (shiftReduceTable)
            delete shiftReduceTable;
        if (gotoTable)
            delete gotoTable;
    }

    ContextFreeGrammar::Rules getRules(ContextFreeGrammar::NonTerminal& nonTerminal);

    struct ACTION {
        enum Function : unsigned {
            Shift,
            Reduce,
            Accept,
            Error
        };

        ACTION() : action(Error), value(0) {}
        ACTION(Function action, size_t value) : action(action), value(value) {}
        ACTION(Function action) : action(action), value(0) {}

        Function action : 2;
        unsigned int value : 30;

        operator enum Function() const { return action; }
        unsigned getValue() const { return value; }

        std::string toString() const;
        std::string toCXXString() const;

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

        operator unsigned int() { return value; }
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

    void GenerateGotoTable();

    struct Item {
        Item() : production(nullptr), position(0) {}
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
        //		bool hasMove() const { return position < production->size(); }
        //		bool isReduction() { return !hasMove(); }

        bool isStart() { return production[0].isStart(); }
        bool isFinal() { return (position == production->size()) && production->isStart(); }

        ContextFreeGrammar::Symbol* getRightOfDot() { return (position != production->size()) ? production->getSymbol(position) : ContextFreeGrammar::getEpsilon(); }
        ContextFreeGrammar::NonTerminal* getLHS() { return production->getLHS(); }

        //		Item Move();

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
        Items(std::initializer_list<Item> items) : set<Item>(items) {}

        Items& getItems() { return *this; }

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

    struct StateAnalysis {
        StateAnalysis(State* state);
        unsigned numberOfConflicts();
        vector<ShiftReduceConflict*>* shiftReduceConflicts;
        vector<ReduceReduceConflict*>* reduceReduceConflicts;
        State* state;
    };

    struct State {
        State(unsigned int index) : index(index), final(false) {}
        State(unsigned int index, const Items& items) : index(index), items(items), final(false) {}
        ~State() {}

        size_t getIndex() { return index; }
        bool isFinal() { return final; }
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
            return true;
        }

        size_t index;
        bool final;
        Items items;
        std::map<ContextFreeGrammar::Terminal*, ACTION> actions;
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

protected:
    ContextFreeGrammar* grammar;

    Table<size_t, ACTION, 1>* shiftReduceTable;
    Table<size_t, GOTO, 1>* gotoTable;
    vector<int, 1> acceptTable;
};

class Lookaheads : public bitset {
public:
    Lookaheads() {}
    Lookaheads(const bitset lookahead) : bitset(lookahead) {}

    virtual std::string toString() const;
    virtual std::string toString(std::vector<std::string> names) const;
};

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR.h - LR header
