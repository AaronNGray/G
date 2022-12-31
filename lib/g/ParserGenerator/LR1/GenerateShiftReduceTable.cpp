//
//	g/ParserGenerator/LR1/GenerateShiftReduceTable.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"

namespace G {
namespace ParserGenerator {

void LR1::GenerateShiftReduceTable() {
    Table<size_t, ACTION, 1>* table = new Table<size_t, ACTION, 1>(grammar->getNumberOfTerminalSymbols());

    table->resize(states.size());

    for (auto state : states) {
        for (auto terminal : grammar->getTerminals()) {

			if (terminal->isFinal() && state->isStart())
				(*table)[state->getIndex()][terminal->getIndex()] = ACTION(ACTION::Function::Accept);
			else if (!terminal->isPseudoTerminal())
				(*table)[state->getIndex()][terminal->getIndex()] = state->actions[terminal];
			else
				;
        }
    }

    if (rowCompressed) {
        shiftReduceTable = new CompressedTable<size_t, ACTION, 1>(table);
        delete table;
    }
    else
        shiftReduceTable = table;
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/GenerateShiftReduceTable.cpp
