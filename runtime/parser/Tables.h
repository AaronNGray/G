//
//	runtime/Tables.h
//
//  Copyright © 2016 Aaron Nathaniel Gray under the MIT License
//

#pragma once

typedef unsigned short Input;
typedef unsigned short State;

struct Pair {
    Input input;
    State state;
};

struct CompressedPairRowMapping {
    size_t pairs;
    Pair pair[1];

    State lookup(Input input) {
        size_t pairs = this->pairs;
        Pair* pair = this->pair;
        do {
            if (pair->input == input)
                return pair->state;
            ++pair;
        } while (--pairs);
        return -1;
    }
};

template<size_t states, size_t terminals, size_t nonterminals>
struct CompressedPairTable {
    CompressedPairTable() : states(states), terminals(terminals), nonterminals(nonterminals) {}
    size_t states;
    size_t terminals;
    size_t nonterminals;

    CompressedPairRowMapping* shiftReduceTable[states];
    CompressedPairRowMapping* gotoTable[states];
};

template<size_t size>
struct RowMapping {
    States state[size];
};

template<size_t states, size_t rules, size_t terminals, size_t nonterminals, typename State = short, typename Terminals = short, typename NonTerminals = short>
struct Table {
    Table() : states(states), rules(rules), terminals(terminals), nonterminals(nonterminals) {}
    typedef State State;
    typedef Input Input;

    State states;
    Terminals terminals;
    NonTerminals nonterminals;

    RowMapping<Terminals>* shiftReduceTable[states];
    RowMapping<NonTerminals>* gotoTable[states];
    size_t rhsSymbols[states];
    size_t production[states];
    size_t production2lhs[rules];

};

// End runtime/Tables.h
