//
//	ContextFreeGrammar.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "gtest/gtest.h"
#include "g/Grammar/ContextFreeGrammar.h"
#include "g/ParserGenerator/LR1/LR1.h"
#include <algorithm>

using namespace G::Grammar;
using namespace G::ParserGenerator;

TEST(Grammar, Epsilon) {
	//ContextFreeGrammar contextFreeGrammar;

	ASSERT_TRUE(ContextFreeGrammar::getEpsilon()->getFirstSet() == bitset({ 0 }));
	ASSERT_TRUE(ContextFreeGrammar::getEpsilon()->getIndex() == 0);
}
TEST(Grammar, End) {
	ASSERT_TRUE(ContextFreeGrammar::getEnd()->getFirstSet() == bitset({ 1 }));
	ASSERT_TRUE(ContextFreeGrammar::getEnd()->getIndex() == 1);
}

TEST(Grammar, GrammarTest) {
	ContextFreeGrammar* grammar = new ContextFreeGrammar("");
	auto PlusSymbol = grammar->newTerminal(grammar->newIdentifier("PLUS"), grammar->newStringLiteral("+"));
	grammar->addTerminal(PlusSymbol);
	auto MultSymbol = grammar->newTerminal(grammar->newIdentifier("MULT"), grammar->newStringLiteral("*"));
	grammar->addTerminal(MultSymbol);
	auto numSymbol = grammar->newTerminal(grammar->newIdentifier("NUM"), grammar->newStringLiteral("NUM"));
	grammar->addTerminal(numSymbol);
	auto Expression = grammar->newIdentifier("Expression");
	auto ExpressionSymbol = grammar->newNonTerminal(Expression);
	grammar->addNonTerminal(ExpressionSymbol);

	grammar->addRule(
		grammar->newRule(Expression,
			grammar->newProductions({
				grammar->newProduction(
					grammar->newNamedSymbols({
						grammar->newNamedSymbol(ExpressionSymbol),
						grammar->newNamedSymbol(PlusSymbol),
						grammar->newNamedSymbol(ExpressionSymbol)
					})
				),
				grammar->newProduction(
					grammar->newNamedSymbols({
						grammar->newNamedSymbol(ExpressionSymbol),
						grammar->newNamedSymbol(MultSymbol),
						grammar->newNamedSymbol(ExpressionSymbol)
					})
				),
				grammar->newProduction(
					grammar->newNamedSymbols({
						grammar->newNamedSymbol(numSymbol),
					})
				)
			})
		)
	);

}

TEST(Grammar, ItemTest) {
	ContextFreeGrammar* grammar = new ContextFreeGrammar("");

	ContextFreeGrammar::Identifier* StartIdentifier = grammar->newIdentifier("Start");
	ContextFreeGrammar::NonTerminal* StartSymbol = grammar->newNonTerminal(StartIdentifier);

	grammar->addNonTerminal(StartSymbol);
	ASSERT_TRUE(grammar->getNonTerminal(StartIdentifier) == StartSymbol);

	grammar->addNonTerminal(grammar->newNonTerminal(grammar->newIdentifier("Expression")));

	ContextFreeGrammar::Production* Start = grammar->newProduction(
		grammar->newNamedSymbols({ grammar->newNamedSymbol(grammar->getEnd()) })
	);
	ContextFreeGrammar::Productions* productions = grammar->newProductions({ Start });
	ContextFreeGrammar::Rule* startRule = grammar->newRule(StartIdentifier, productions);

	LR1::Item item(Start, grammar->getEnd()->getFirstSet());

	//std::cerr << "item = " << item.toString(grammar, 4) << std::endl;

	bitset bs = bitset::SingletonSet(grammar->getEnd()->getIndex());

	//std::cerr << "bitset::SingletonSet(grammar->getEnd()->getIndex()) = " << bs.toString() << std::endl;

	Lookaheads lookaheads = item.getLookaheads();

	//std::cerr << "item.getLookaheads() = " << lookaheads.toString() << std::endl;

	ASSERT_TRUE(lookaheads == bs);

}

ContextFreeGrammar* lg_bootstrap() {
	ContextFreeGrammar* lg = new ContextFreeGrammar("lg");
	return lg;
}

TEST(Grammar, ContextFreeGrammarTest) {
	lg_bootstrap();
}



// TODO: epsilon appearing in quotes in 'item.toString(grammar, 4)'
