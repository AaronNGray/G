#include "g/ParserGenerator/ParserGenerator.h"
#include "g/Grammar/Grammar.h"
#include "g/Actions.h"
#include "nonstd/File.h"

using namespace G::ParserGenerator;

Actions bootstrapActions = {
	{ 0, "{\n\t\tparserGenerator->setName($name$->getValue());\n\t\tparserGenerator->setType($type$->getValue());\n\t}", 118},
	{ 1, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2)); }", 131},
	{ 2, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2, $4)); }", 133},
	{ 3, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2, $3)); }", 135},
	{ 4, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2, $4, $5)); }", 137},
	{ 5, "{ root->addNonTerminal(root->create<ContextFreeGrammar::NonTerminal>($2, $2)); }", 139},
	{ 6, "{ root->addNonTerminal(root->create<ContextFreeGrammar::NonTerminal>($2, $4)); }", 141},
	{ 7, "{ root->setStartSymbol(root->getNonTerminal($idenfifier$)); }", 143},
	{ 8, "{ parserGenerator->addHeader($_code$); }", 145},
	{ 9, "{ parserGenerator->addCode($_code$); }", 147},
	{ 10, "{ parserGenerator->setRootType($type$->getValue()); }", 149},
	{ 11, "{ parserGenerator->setBaseClass($literal$->getValue()); }", 151},
	{ 12, "{ parserGenerator->setBaseType($literal$->getValue()); }", 153},
	{ 13, "{ parserGenerator->setBaseType($literal$->getValue(), true); }", 155},
	{ 14, "{ parserGenerator->setReturnType($literal$->getValue()); }", 157},
	{ 15, "{ ++Precedence; }", 162},
	{ 16, "{ ++Precedence; }", 163},
	{ 17, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::None);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 180},
	{ 18, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::None);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 186},
	{ 19, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::Left);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 200},
	{ 20, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::Left);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 206},
	{ 21, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::Right);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 220},
	{ 22, "{\n\t\t\tContextFreeGrammar::Terminal* terminal = root->getTerminal($1);\n\t\t\tterminal->setAssociativity(ContextFreeGrammar::Associativity::Right);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 226},
	{ 23, "{ root->addRule($2); }", 241},
	{ 24, "{ root->addRule($1); }", 243},
	{ 25, "{ $$ = root->findOrCreateRule($identifier$, $productions$); }", 247},
	{ 26, "{ $$ = root->findOrCreateRule($identifier$, $type$, $productions$); }", 249},
	{ 27, "{ $$ = $productions$; $productions$->addProduction($_production$); }", 253},
	{ 28, "{ $$ = root->newProductions(); $$->addProduction($_production$); }", 255},
	{ 29, "{ $$ = root->newProduction($symbols$); }", 259},
	{ 30, "{ $$ = root->newProduction($symbols$, $action$, false); }", 261},
	{ 31, "{ $$ = root->newProduction(); }", 263},
	{ 32, "{ $$ = root->newProduction($action$, false); }", 265},
	{ 33, "{ $$ = root->newProduction(); }", 267},
	{ 34, "{ $$ = root->newProduction($1, false); }", 269},
	{ 35, "{ $$ = $symbols$; $symbols$->addSymbol($symbol$); }", 274},
	{ 36, "{ $$ = root->newNamedSymbols(); $$->addSymbol($symbol$); }", 276},
	{ 37, "{ $$ = root->newNamedSymbol($identifier$, $symbol$); }", 280},
	{ 38, "{ $$ = root->newNamedSymbol($symbol$); }", 282},
	{ 39, "{ $$ = root->findOrCreateSymbol($1); }", 286},
	{ 40, "{\n    \t\tContextFreeGrammar::Symbol* symbol = root->getTerminal($1);\n    \t\tif (symbol == ContextFreeGrammar::getErrorSymbol() || symbol == nullptr)\n    \t\t\tG::logger->LogError(new UndefinedTerminalSymbolErrorObject($1->getValue(), lexer->getLineNumber(), lexer->getCharacter()));\n    \t\t$$ = symbol;\n    \t}", 288},
	{ 41, "{\n    \t\t$$ = root->getTerminal(root->newStringLiteral(\"$\"));\n    \t}", 295}
};

ContextFreeGrammar* pg_bootstrap() {
	ContextFreeGrammar* pg_ContextFreeGrammar = new ContextFreeGrammar("pg");

	ContextFreeGrammar::Terminal *KEYWORD_GRAMMAR = pg_ContextFreeGrammar->addTerminal("KEYWORD_GRAMMAR","", "grammar", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_TERM = pg_ContextFreeGrammar->addTerminal("KEYWORD_TERM","", "term", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_NONTERM = pg_ContextFreeGrammar->addTerminal("KEYWORD_NONTERM","", "nonterm", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_PRODUCTION = pg_ContextFreeGrammar->addTerminal("KEYWORD_PRODUCTION","", "production", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_START = pg_ContextFreeGrammar->addTerminal("KEYWORD_START","", "start", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_CODE = pg_ContextFreeGrammar->addTerminal("KEYWORD_CODE","", "code", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_HEADER = pg_ContextFreeGrammar->addTerminal("KEYWORD_HEADER","", "header", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_ROOTTYPE = pg_ContextFreeGrammar->addTerminal("KEYWORD_ROOTTYPE","", "roottype", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_BASECLASS = pg_ContextFreeGrammar->addTerminal("KEYWORD_BASECLASS","", "baseclass", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_BASETYPE = pg_ContextFreeGrammar->addTerminal("KEYWORD_BASETYPE","", "basetype", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_RETURNTYPE = pg_ContextFreeGrammar->addTerminal("KEYWORD_RETURNTYPE","", "returntype", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_UNION = pg_ContextFreeGrammar->addTerminal("KEYWORD_UNION","", "union", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_NONASSOC = pg_ContextFreeGrammar->addTerminal("KEYWORD_NONASSOC","", "nonassoc", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_LEFT = pg_ContextFreeGrammar->addTerminal("KEYWORD_LEFT","", "left", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_RIGHT = pg_ContextFreeGrammar->addTerminal("KEYWORD_RIGHT","", "right", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_DOLLAR = pg_ContextFreeGrammar->addTerminal("OPERATOR_DOLLAR","", "$", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_EPSILON = pg_ContextFreeGrammar->addTerminal("OPERATOR_EPSILON","", "epsilon", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_CURLY_BRACE = pg_ContextFreeGrammar->addTerminal("OPERATOR_OPEN_CURLY_BRACE","", "{", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_CURLY_BRACE = pg_ContextFreeGrammar->addTerminal("OPERATOR_CLOSE_CURLY_BRACE","", "}", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_EQUALS = pg_ContextFreeGrammar->addTerminal("OPERATOR_EQUALS","", "=", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OR = pg_ContextFreeGrammar->addTerminal("OPERATOR_OR","", "|", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_COLON = pg_ContextFreeGrammar->addTerminal("OPERATOR_COLON","", ":", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_SEMICOLON = pg_ContextFreeGrammar->addTerminal("OPERATOR_SEMICOLON","", ";", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *IDENTIFIER = pg_ContextFreeGrammar->addTerminal("IDENTIFIER","Identifier", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *STRING_LITERAL = pg_ContextFreeGrammar->addTerminal("STRING_LITERAL","StringLiteral", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *TOKEN_ACTION = pg_ContextFreeGrammar->addTerminal("TOKEN_ACTION","Action", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *TOKEN_CODE = pg_ContextFreeGrammar->addTerminal("TOKEN_CODE","CodeBlock", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *NEWLINE = pg_ContextFreeGrammar->addTerminal("NEWLINE","", "", ContextFreeGrammar::None, 0, false);

	ContextFreeGrammar::Terminal *EPSILON = pg_ContextFreeGrammar->getTerminal("EPSILON");
	ContextFreeGrammar::Terminal *END = pg_ContextFreeGrammar->getTerminal("END");

	ContextFreeGrammar::NonTerminal *Grammar = pg_ContextFreeGrammar->addNonTerminal("Grammar", "Grammar");
	ContextFreeGrammar::NonTerminal *File = pg_ContextFreeGrammar->addNonTerminal("File", "File");
	ContextFreeGrammar::NonTerminal *Headers = pg_ContextFreeGrammar->addNonTerminal("Headers", "Headers");
	ContextFreeGrammar::NonTerminal *Precedences = pg_ContextFreeGrammar->addNonTerminal("Precedences", "Precedences");
	ContextFreeGrammar::NonTerminal *Rules = pg_ContextFreeGrammar->addNonTerminal("Rules", "Rules");
	ContextFreeGrammar::NonTerminal *Footer = pg_ContextFreeGrammar->addNonTerminal("Footer", "Footer");
	ContextFreeGrammar::NonTerminal *Header = pg_ContextFreeGrammar->addNonTerminal("Header", "Header");
	ContextFreeGrammar::NonTerminal *Identifier = pg_ContextFreeGrammar->addNonTerminal("Identifier", "Identifier");
	ContextFreeGrammar::NonTerminal *BlankLines = pg_ContextFreeGrammar->addNonTerminal("BlankLines", "BlankLines");
	ContextFreeGrammar::NonTerminal *Precedence = pg_ContextFreeGrammar->addNonTerminal("Precedence", "Precedence");
	ContextFreeGrammar::NonTerminal *NonAssociativeTerminals = pg_ContextFreeGrammar->addNonTerminal("NonAssociativeTerminals", "NonAssociativeTerminals");
	ContextFreeGrammar::NonTerminal *LeftAssociativeTerminals = pg_ContextFreeGrammar->addNonTerminal("LeftAssociativeTerminals", "LeftAssociativeTerminals");
	ContextFreeGrammar::NonTerminal *RightAssociativeTerminals = pg_ContextFreeGrammar->addNonTerminal("RightAssociativeTerminals", "RightAssociativeTerminals");
	ContextFreeGrammar::NonTerminal *NonAssociativeTerminal = pg_ContextFreeGrammar->addNonTerminal("NonAssociativeTerminal", "NonAssociativeTerminal");
	ContextFreeGrammar::NonTerminal *LeftAssociativeTerminal = pg_ContextFreeGrammar->addNonTerminal("LeftAssociativeTerminal", "LeftAssociativeTerminal");
	ContextFreeGrammar::NonTerminal *RightAssociativeTerminal = pg_ContextFreeGrammar->addNonTerminal("RightAssociativeTerminal", "RightAssociativeTerminal");
	ContextFreeGrammar::NonTerminal *Rule = pg_ContextFreeGrammar->addNonTerminal("Rule", "Rule");
	ContextFreeGrammar::NonTerminal *Productions = pg_ContextFreeGrammar->addNonTerminal("Productions", "Productions");
	ContextFreeGrammar::NonTerminal *Production = pg_ContextFreeGrammar->addNonTerminal("Production", "Production");
	ContextFreeGrammar::NonTerminal *NamedSymbols = pg_ContextFreeGrammar->addNonTerminal("NamedSymbols", "NamedSymbols");
	ContextFreeGrammar::NonTerminal *NamedSymbol = pg_ContextFreeGrammar->addNonTerminal("NamedSymbol", "NamedSymbol");
	ContextFreeGrammar::NonTerminal *Symbol = pg_ContextFreeGrammar->addNonTerminal("Symbol", "Symbol");
	ContextFreeGrammar::NonTerminal *Keyword = pg_ContextFreeGrammar->addNonTerminal("Keyword", "Keyword");

	pg_ContextFreeGrammar->addRule(File, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Grammar)
		}, -1)
	});
	pg_ContextFreeGrammar->addRule(Grammar, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_GRAMMAR),
			pg_ContextFreeGrammar->newNamedSymbol("name", IDENTIFIER),
			pg_ContextFreeGrammar->newNamedSymbol("type", STRING_LITERAL),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			pg_ContextFreeGrammar->newNamedSymbol(Headers),
			pg_ContextFreeGrammar->newNamedSymbol(Precedences),
			pg_ContextFreeGrammar->newNamedSymbol(Rules),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE),
			pg_ContextFreeGrammar->newNamedSymbol(Footer)
		}, 0)
	});
	pg_ContextFreeGrammar->addRule(Headers, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Header),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_SEMICOLON),
			pg_ContextFreeGrammar->newNamedSymbol(Headers)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Header),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_SEMICOLON)
		}, -1)
	});
	pg_ContextFreeGrammar->addRule(Header, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_TERM),
			pg_ContextFreeGrammar->newNamedSymbol(Identifier)
		}, 1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_TERM),
			pg_ContextFreeGrammar->newNamedSymbol(Identifier),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_COLON),
			pg_ContextFreeGrammar->newNamedSymbol(Identifier)
		}, 2),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_TERM),
			pg_ContextFreeGrammar->newNamedSymbol(Identifier),
			pg_ContextFreeGrammar->newNamedSymbol(STRING_LITERAL)
		}, 3),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_TERM),
			pg_ContextFreeGrammar->newNamedSymbol(Identifier),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_COLON),
			pg_ContextFreeGrammar->newNamedSymbol(Identifier),
			pg_ContextFreeGrammar->newNamedSymbol(STRING_LITERAL)
		}, 4),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_NONTERM),
			pg_ContextFreeGrammar->newNamedSymbol(Identifier)
		}, 5),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_NONTERM),
			pg_ContextFreeGrammar->newNamedSymbol(Identifier),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_COLON),
			pg_ContextFreeGrammar->newNamedSymbol(Identifier)
		}, 6),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_START),
			pg_ContextFreeGrammar->newNamedSymbol("idenfifier", Identifier)
		}, 7),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_HEADER),
			pg_ContextFreeGrammar->newNamedSymbol("_code", TOKEN_CODE)
		}, 8),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_CODE),
			pg_ContextFreeGrammar->newNamedSymbol("_code", TOKEN_CODE)
		}, 9),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_ROOTTYPE),
			pg_ContextFreeGrammar->newNamedSymbol("type", STRING_LITERAL)
		}, 10),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_BASECLASS),
			pg_ContextFreeGrammar->newNamedSymbol("literal", STRING_LITERAL)
		}, 11),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_BASETYPE),
			pg_ContextFreeGrammar->newNamedSymbol("literal", STRING_LITERAL)
		}, 12),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_BASETYPE),
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_UNION),
			pg_ContextFreeGrammar->newNamedSymbol("literal", STRING_LITERAL)
		}, 13),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_RETURNTYPE),
			pg_ContextFreeGrammar->newNamedSymbol("literal", STRING_LITERAL)
		}, 14),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(BlankLines)
		}, -1)
	});
	pg_ContextFreeGrammar->addRule(Precedences, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Precedences),
			pg_ContextFreeGrammar->newNamedSymbol(Precedence),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 15),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Precedence),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 16),
		pg_ContextFreeGrammar->addProduction({}, -1)
	});
	pg_ContextFreeGrammar->addRule(Precedence, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_NONASSOC),
			pg_ContextFreeGrammar->newNamedSymbol(NonAssociativeTerminals)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_LEFT),
			pg_ContextFreeGrammar->newNamedSymbol(LeftAssociativeTerminals)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_RIGHT),
			pg_ContextFreeGrammar->newNamedSymbol(RightAssociativeTerminals)
		}, -1)
	});
	pg_ContextFreeGrammar->addRule(NonAssociativeTerminals, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(NonAssociativeTerminals),
			pg_ContextFreeGrammar->newNamedSymbol(NonAssociativeTerminal)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(NonAssociativeTerminal)
		}, -1)
	});
	pg_ContextFreeGrammar->addRule(NonAssociativeTerminal, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(STRING_LITERAL)
		}, 17),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Identifier)
		}, 18)
	});
	pg_ContextFreeGrammar->addRule(LeftAssociativeTerminals, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(LeftAssociativeTerminals),
			pg_ContextFreeGrammar->newNamedSymbol(LeftAssociativeTerminal)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(LeftAssociativeTerminal)
		}, -1)
	});
	pg_ContextFreeGrammar->addRule(LeftAssociativeTerminal, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(STRING_LITERAL)
		}, 19),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Identifier)
		}, 20)
	});
	pg_ContextFreeGrammar->addRule(RightAssociativeTerminals, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(RightAssociativeTerminals),
			pg_ContextFreeGrammar->newNamedSymbol(RightAssociativeTerminal)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(RightAssociativeTerminal)
		}, -1)
	});
	pg_ContextFreeGrammar->addRule(RightAssociativeTerminal, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(STRING_LITERAL)
		}, 21),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Identifier)
		}, 22)
	});
	pg_ContextFreeGrammar->addRule(Footer, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(BlankLines)
		}, -1)
	});
	pg_ContextFreeGrammar->addRule(BlankLines, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(BlankLines),
			pg_ContextFreeGrammar->newNamedSymbol(NEWLINE)
		}, -1),
		pg_ContextFreeGrammar->addProduction({}, -1)
	});
	pg_ContextFreeGrammar->addRule(Rules, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Rules),
			pg_ContextFreeGrammar->newNamedSymbol(Rule)
		}, 23),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Rule)
		}, 24)
	});
	pg_ContextFreeGrammar->addRule(Rule, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_PRODUCTION),
			pg_ContextFreeGrammar->newNamedSymbol("identifier", Identifier),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_EQUALS),
			pg_ContextFreeGrammar->newNamedSymbol("productions", Productions),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 25),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_PRODUCTION),
			pg_ContextFreeGrammar->newNamedSymbol("identifier", Identifier),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_COLON),
			pg_ContextFreeGrammar->newNamedSymbol("type", Identifier),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_EQUALS),
			pg_ContextFreeGrammar->newNamedSymbol("productions", Productions),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 26)
	});
	pg_ContextFreeGrammar->addRule(Productions, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol("productions", Productions),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_OR),
			pg_ContextFreeGrammar->newNamedSymbol("_production", Production)
		}, 27),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol("_production", Production)
		}, 28)
	});
	pg_ContextFreeGrammar->addRule(Production, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol("symbols", NamedSymbols)
		}, 29),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol("symbols", NamedSymbols),
			pg_ContextFreeGrammar->newNamedSymbol("action", TOKEN_ACTION)
		}, 30),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_EPSILON)
		}, 31),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_EPSILON),
			pg_ContextFreeGrammar->newNamedSymbol("action", TOKEN_ACTION)
		}, 32),
		pg_ContextFreeGrammar->addProduction({}, 33),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(TOKEN_ACTION)
		}, 34)
	});
	pg_ContextFreeGrammar->addRule(NamedSymbols, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol("symbols", NamedSymbols),
			pg_ContextFreeGrammar->newNamedSymbol("symbol", NamedSymbol)
		}, 35),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol("symbol", NamedSymbol)
		}, 36)
	});
	pg_ContextFreeGrammar->addRule(NamedSymbol, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol("identifier", Identifier),
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_COLON),
			pg_ContextFreeGrammar->newNamedSymbol("symbol", Symbol)
		}, 37),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol("symbol", Symbol)
		}, 38)
	});
	pg_ContextFreeGrammar->addRule(Symbol, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Identifier)
		}, 39),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(STRING_LITERAL)
		}, 40),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_DOLLAR)
		}, 41)
	});
	pg_ContextFreeGrammar->addRule(Keyword, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_GRAMMAR)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_TERM)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_NONTERM)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_PRODUCTION)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_START)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_CODE)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_HEADER)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_BASECLASS)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_ROOTTYPE)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_BASETYPE)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_RETURNTYPE)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_UNION)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_NONASSOC)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_LEFT)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(KEYWORD_RIGHT)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(OPERATOR_EPSILON)
		}, -1)
	});
	pg_ContextFreeGrammar->addRule(Identifier, {
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(Keyword)
		}, -1),
		pg_ContextFreeGrammar->addProduction({
			pg_ContextFreeGrammar->newNamedSymbol(IDENTIFIER)
		}, -1)
	});
	pg_ContextFreeGrammar->setActions(&bootstrapActions);

	return pg_ContextFreeGrammar;
}

ParserGenerator<ContextFreeGrammar>* pg_ParserGenerator() {
	FileName filename("pg");
	return new ParserGenerator<ContextFreeGrammar>(
		filename, pg_bootstrap(),
		"ContextFreeGrammar",
		"ValueType",
		"true",
		"void",
    {
      { "\n\t#include <io.h>\n\t#include <iostream>\n\t#include <cassert>\n\n\t#include \"g/ParserGenerator/ParserGenerator.h\"\n\n\tusing namespace G::ParserGenerator;\n\n\textern ParserGenerator<ContextFreeGrammar>* parserGenerator;\n\n    struct Token {\n        Token(std::string name) : name(name) {}\n        std::string name;\n    };\n\ttypedef Token Keyword;\n    struct Identifier : public Token {\n        Identifier(std::string name) : Token(name) {}\n    };\n\n\tunion ValueType {\n\t\tContextFreeGrammar *Grammar;\n\t\tContextFreeGrammar::Rules *Rules;\n\t\tContextFreeGrammar::Rule *Rule;\n\t\tContextFreeGrammar::Productions *Productions;\n\t\tContextFreeGrammar::Production *Production;\n\t\tContextFreeGrammar::NamedSymbols *NamedSymbols;\n\t\tContextFreeGrammar::NamedSymbol *NamedSymbol;\n\t\tContextFreeGrammar::Symbol *Symbol;\n\t\tContextFreeGrammar::Identifier *Identifier;\n\t\tContextFreeGrammar::StringLiteral *StringLiteral;\n\t\tint Action;\t\t// TODO: 'typedef ContextFreeGrammar::Action int'\n\t\tCodeBlock* CodeBlock;\n\t};\n\n\textern ValueType currentValue;\n\tusing namespace Runtime;\n", 9, "C:\\Users\\aaron\\Projects\\G\\latest\\G - saving 6\\src\\bootstrap\\self-bootstrap\\pg-bootstrap-pg\\pg.pg" }
    }, 
    {
      { "\n\t#include \"pg.lg.h\"\n\tValueType currentValue;\n\tunsigned Precedence = 1;\n", 48, "C:\\Users\\aaron\\Projects\\G\\latest\\G - saving 6\\src\\bootstrap\\self-bootstrap\\pg-bootstrap-pg\\pg.pg" },
      { "\n\tvoid pgParser::reportError(State state, Input input) {\n\t\tstd::string report = std::string(\"Found \") + Terminals[input] + \" Expecting \";\n\n\t\tPair<Action>* pair = ShiftReduce_states[state - 1]->pair;\n\t\tif (pair) {\n\t\t\tfor (size_t pairs = ShiftReduce_states[state - 1]->pairs; pairs > 0; --pairs) {\n                report += std::string(Terminals[pair->input]) + ((pairs > 1) ? \", \" : \"\");\n\t\t\t\t++pair;\n\t\t\t}\n\t\t}\n\t\telse\n            report += std::string(\"<nothing>\");\n        report += std::string(\" in state \") + std::to_string(state) + \".\\\n\";\n\n\t\tG::logger->LogError(new SyntaxErrorObject(report, lexer->getLineNumber(), lexer->getCharacter()));\n\t}\n", 53, "C:\\Users\\aaron\\Projects\\G\\latest\\G - saving 6\\src\\bootstrap\\self-bootstrap\\pg-bootstrap-pg\\pg.pg" }
    }
	);
}

// End C:\Users\aaron\Projects\G\latest\G - saving 6\src\bootstrap\self-bootstrap\pg-bootstrap-pg\pg.lexer.cpp
