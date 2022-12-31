//
//	g/ParserGenerator/LR1/GenerateGotoTable.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"

namespace G {
namespace ParserGenerator {

void LR1::GenerateGotoTable() {
    Table<size_t, GOTO, 1>* table = new Table<size_t, GOTO, 1>(grammar->getNumberOfNonTerminalSymbols());

    table->resize(states.size());

    for (auto state : states) {
        for (auto nonterminal : grammar->getNonTerminals()) {
			auto iterator = state->shifts.find(nonterminal);
            if (iterator != state->shifts.end())
                (*table)[state->index][nonterminal->getIndex()] = iterator->second->getIndex();
        }
    }

    if (rowCompressed) {
        gotoTable = new CompressedTable<size_t, GOTO, 1>(table);
        delete table;
    }
    else
        gotoTable = table;
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/GenerateGotoTable.cpp
