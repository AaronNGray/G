#include "gtest/gtest.h"
#include "g/Actions.h"

Actions actions = {
	{ 0, "{\n\t\tparserGenerator->setName($name$->getValue());\n\t\tparserGenerator->setType($type$->getValue());\n\t}", 120},
	{ 1, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2)); }", 133},
	{ 2, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2, $4)); }", 135},
	{ 3, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2, $3)); }", 137},
	{ 4, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2, $4, $5)); }", 139},
	{ 5, "{ root->addNonTerminal(root->create<ContextFreeGrammar::NonTerminal>($2, $2)); }", 141},
	{ 6, "{ root->addNonTerminal(root->create<ContextFreeGrammar::NonTerminal>($2, $4)); }", 143},
	{ 7, "{ root->setStartSymbol(root->getNonTerminal($idenfifier$)); }", 145},
	{ 8, "{ parserGenerator->addHeader($_code$); }", 147},
	{ 9, "{ parserGenerator->addCode($_code$); }", 149},
	{ 10, "{ parserGenerator->setRootType($type$->getValue()); }", 151},
	{ 11, "{ parserGenerator->setBaseClass($literal$->getValue()); }", 153},
	{ 12, "{ parserGenerator->setBaseType($literal$->getValue()); }", 155},
	{ 13, "{ parserGenerator->setBaseType($literal$->getValue(), true); }", 157},
	{ 14, "{ parserGenerator->setReturnType($literal$->getValue()); }", 159},
	{ 15, "{ ++Precedence; }", 164},
	{ 16, "{ ++Precedence; }", 165},
	{ 17, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::None);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 182},
	{ 18, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::None);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 188},
	{ 19, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::Left);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 202},
	{ 20, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::Left);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 208},
	{ 21, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::Right);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 222},
	{ 22, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::Right);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 228},
	{ 23, "{ root->addRule($2); }", 243},
	{ 24, "{ root->addRule($1); }", 245},
	{ 25, "{ $$ = root->findOrCreateRule($identifier$, $productions$); }", 249},
	{ 26, "{ $$ = root->findOrCreateRule($identifier$, $type$, $productions$); }", 251},
	{ 27, "{ $$ = $productions$; $productions$->addProduction($_production$); }", 255},
	{ 28, "{ $$ = root->newProductions(); $$->addProduction($_production$); }", 257},
	{ 29, "{ $$ = root->newProduction($symbols$); }", 261},
	{ 30, "{ $$ = root->newProduction($symbols$, $action$, false); }", 263},
	{ 31, "{ $$ = root->newProduction(); }", 265},
	{ 32, "{ $$ = root->newProduction($action$, false); }", 267},
	{ 33, "{ $$ = root->newProduction(); }", 269},
	{ 34, "{ $$ = root->newProduction($1, false); }", 271},
	{ 35, "{ $$ = $symbols$; $symbols$->addSymbol($symbol$); }", 276},
	{ 36, "{ $$ = root->newNamedSymbols(); $$->addSymbol($symbol$); }", 278},
	{ 37, "{ $$ = root->newNamedSymbol($identifier$, $symbol$); }", 282},
	{ 38, "{ $$ = root->newNamedSymbol($symbol$); }", 284},
	{ 39, "{ $$ = root->findOrCreateSymbol($1); }", 288},
	{ 40, "{\n    \t\tContextFreeGrammar::Symbol* symbol = root->getTerminal($1);\n    \t\tif (symbol == ContextFreeGrammar::getErrorSymbol() || symbol == nullptr)\n    \t\t\tG::logger->LogError(new UndefinedTerminalSymbolErrorObject($1->getValue(), lexer->getLineNumber(), lexer->getCharacter()));\n    \t\t$$ = symbol;\n    \t}", 290},
	{ 41, "{\n    \t\t$$ = root->getTerminal(root->newStringLiteral(\"$\"));\n    \t}", 297}
};

//TEST(Action, compare) {
//	(compare(*actions[0], *actions[0]));
//}

TEST(Action, nonstd_string_compare) {
	EXPECT_TRUE(actions[0]->getAction() == actions[0]->getAction());
}

TEST(Actions, compare) {
	EXPECT_TRUE(compare(actions, actions));
}
