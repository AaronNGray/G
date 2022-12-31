//
//  g/ParserGenerator/LALR1/LALR1.h - LALR1 State And table Generation header.
//
//  Property and Copyright (c) 2016, 2017 Aaron Nathaniel Gray
//

#pragma once

#include "g/ParserGenerator/LR1/LR1.h"

namespace G {
namespace ParserGenerator {

class LALR1 : public LR1 {
public:
	LALR1(ContextFreeGrammar* grammar, bool rowCompressed = true, unsigned debug = 0) : LR1(grammar, rowCompressed, debug) {}
	~LALR1() {}

	struct Items : public LR1::Items {
		Items() : LR1::Items() {}
		Items(Item& item) : LR1::Items() { insert(item); }
		Items(std::initializer_list<Item> items) : LR1::Items(items) {}

		const Items& getItems() const { return *this; }

		Items MergeLookaheads();
		void MergeLookaheads(const LR1::Item item);
	};

	virtual Items Closure(const Items& I);
	Items Closure(Item& I) { return Closure(static_cast<const Items&>(Items(I))); } // TODO: Align code with LR1

	static Machine* Create(ContextFreeGrammar* grammar, bool rowCompressed, unsigned debug) { return new LALR1(grammar, rowCompressed, debug); }
	static std::string Name;
};

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LALR1/LALR1.h - LALR1 State And table Generation header.
