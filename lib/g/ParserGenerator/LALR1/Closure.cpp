//
//	g/ParserGenerator/LALR1/Closure.cpp - LALR1 Closure
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LALR1/LALR1.h"

namespace G {
namespace ParserGenerator {

//
//  LR1.Closure(I) =
//    repeat
//    	for each item in [A -> a•Bß, a] in I,
//        each production B -> y in G'
//    		and each item terminal b in FIRST(ßa)
//        such that [B -> •y, b] is not in I
//          add [B -> •y, b] to I
//    until no more items can be added to I
//    return I
//

LALR1::Items LALR1::Closure(const Items& I) {
	deque<Item> items(I);
	Items closure;

	// for each item in [A -> a•Bß, a] in items
	while (!items.empty()) {
		Item item = items.pop_front();
		closure.push_back(item);

		if (item.hasMove()) {
			ContextFreeGrammar::Symbol* symbol = item.rightOfDot();
			bitset firstset = FIRST(item.Move()); // FIRST(ßa)

			if (symbol->isNonTerminal()) {

				ContextFreeGrammar::Productions productions = grammar->getProductions(symbol->asNonTerminal());

				// each production B -> y in G'
				for (auto production : productions) {

					// and each item terminal b in FIRST(ßa)
					const Item item(production, firstset);

					// such that[B->•y, b] is not in items and not in closure
					if (!items.is_member(item) && !closure.is_member(item)) {
						// add[B->•y, b] to items
						items.push_back(item);
					}

				} // end for (auto production : *productions)
			} // end if (symbol->isNonTerminal())

		} // end if (item.isNext())
	} // end while (!items.empty())

	return closure.MergeLookaheads();
}

//
//
//

LALR1::Items LALR1::Items::MergeLookaheads() {
	Items items;

	for (auto ii = cbegin(); ii != cend(); ++ii)
		items.MergeLookaheads(*ii);

	return items;
}

//

void LALR1::Items::MergeLookaheads(const LALR1::Item item) {
	LALR1::Items::iterator ii = std::find_if(begin(), end(), [item](LR1::Item& i) {
		return i.production == item.production && i.position == item.position;
	});

	if (ii != cend())
		ii->lookaheads |= item.lookaheads;
	else
		push_back(item);
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LALR1/Closure.cpp - LALR1 Closure
