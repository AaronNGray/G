//
//  PG/UnitTests/PGTest.cpp
//
//  Copyright (c) 2016 Aaron Nathaniel Gray under the MIT License
//

#include "gtest/gtest.h"
#include "lib/ParserGenerator/Grammar.h"

#include "g/Grammar/Grammar.h"
#include "g/Actions.h"

//
// pg-bootstrap-pg/pg.parser.cpp
//

using namespace G::Grammar;
ContextFreeGrammar* bootstrapPG() {
	ContextFreeGrammar* PG = new ContextFreeGrammar("PG");

	ContextFreeGrammar::Terminal *EPSILON = PG->addTerminal("EPSILON", "epsilon");
	ContextFreeGrammar::Terminal *END = PG->addTerminal("END", "$");
	ContextFreeGrammar::Terminal *KEYWORD_GRAMMAR = PG->addTerminal("KEYWORD_GRAMMAR", "grammar");
	ContextFreeGrammar::Terminal *KEYWORD_TERM = PG->addTerminal("KEYWORD_TERM", "term");
	ContextFreeGrammar::Terminal *KEYWORD_NONTERM = PG->addTerminal("KEYWORD_NONTERM", "nonterm");
	ContextFreeGrammar::Terminal *KEYWORD_PRODUCTION = PG->addTerminal("KEYWORD_PRODUCTION", "production");
	ContextFreeGrammar::Terminal *KEYWORD_START = PG->addTerminal("KEYWORD_START", "start");
	ContextFreeGrammar::Terminal *KEYWORD_CODE = PG->addTerminal("KEYWORD_CODE", "code");
	ContextFreeGrammar::Terminal *KEYWORD_HEADER = PG->addTerminal("KEYWORD_HEADER", "header");
	ContextFreeGrammar::Terminal *KEYWORD_ROOTTYPE = PG->addTerminal("KEYWORD_ROOTTYPE", "roottype");
	ContextFreeGrammar::Terminal *KEYWORD_BASECLASS = PG->addTerminal("KEYWORD_BASECLASS", "baseclass");
	ContextFreeGrammar::Terminal *KEYWORD_BASETYPE = PG->addTerminal("KEYWORD_BASETYPE", "basetype");
	ContextFreeGrammar::Terminal *KEYWORD_RETURNTYPE = PG->addTerminal("KEYWORD_RETURNTYPE", "returntype");
	ContextFreeGrammar::Terminal *KEYWORD_UNION = PG->addTerminal("KEYWORD_UNION", "union");
	ContextFreeGrammar::Terminal *KEYWORD_NONASSOC = PG->addTerminal("KEYWORD_NONASSOC", "nonassoc");
	ContextFreeGrammar::Terminal *KEYWORD_LEFT = PG->addTerminal("KEYWORD_LEFT", "left");
	ContextFreeGrammar::Terminal *KEYWORD_RIGHT = PG->addTerminal("KEYWORD_RIGHT", "right");
	ContextFreeGrammar::Terminal *OPERATOR_DOLLAR = PG->addTerminal("OPERATOR_DOLLAR", "$");
	ContextFreeGrammar::Terminal *OPERATOR_EPSILON = PG->addTerminal("OPERATOR_EPSILON", "epsilon");
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_CURLY_BRACE = PG->addTerminal("OPERATOR_OPEN_CURLY_BRACE", "{");
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_CURLY_BRACE = PG->addTerminal("OPERATOR_CLOSE_CURLY_BRACE", "}");
	ContextFreeGrammar::Terminal *OPERATOR_EQUALS = PG->addTerminal("OPERATOR_EQUALS", "=");
	ContextFreeGrammar::Terminal *OPERATOR_OR = PG->addTerminal("OPERATOR_OR", "|");
	ContextFreeGrammar::Terminal *OPERATOR_COLON = PG->addTerminal("OPERATOR_COLON", ":");
	ContextFreeGrammar::Terminal *OPERATOR_SEMICOLON = PG->addTerminal("OPERATOR_SEMICOLON", ";");
	ContextFreeGrammar::Terminal *IDENTIFIER = PG->addTerminal("IDENTIFIER", "Identifier");
	ContextFreeGrammar::Terminal *STRING_LITERAL = PG->addTerminal("STRING_LITERAL", "StringLiteral");
	ContextFreeGrammar::Terminal *TOKEN_ACTION = PG->addTerminal("TOKEN_ACTION", "Action");
	ContextFreeGrammar::Terminal *TOKEN_CODE = PG->addTerminal("TOKEN_CODE", "CodeBlock");
	ContextFreeGrammar::Terminal *NEWLINE = PG->addTerminal("NEWLINE");

	ContextFreeGrammar::NonTerminal *Grammar = PG->addNonTerminal("Grammar", "Grammar");
	ContextFreeGrammar::NonTerminal *File = PG->addNonTerminal("File", "File");
	ContextFreeGrammar::NonTerminal *Headers = PG->addNonTerminal("Headers", "Headers");
	ContextFreeGrammar::NonTerminal *Precedences = PG->addNonTerminal("Precedences", "Precedences");
	ContextFreeGrammar::NonTerminal *Rules = PG->addNonTerminal("Rules", "Rules");
	ContextFreeGrammar::NonTerminal *Footer = PG->addNonTerminal("Footer", "Footer");
	ContextFreeGrammar::NonTerminal *Header = PG->addNonTerminal("Header", "Header");
	ContextFreeGrammar::NonTerminal *Identifier = PG->addNonTerminal("Identifier", "Identifier");
	ContextFreeGrammar::NonTerminal *BlankLines = PG->addNonTerminal("BlankLines", "BlankLines");
	ContextFreeGrammar::NonTerminal *Precedence = PG->addNonTerminal("Precedence", "Precedence");
	ContextFreeGrammar::NonTerminal *NonAssociativeTerminals = PG->addNonTerminal("NonAssociativeTerminals", "NonAssociativeTerminals");
	ContextFreeGrammar::NonTerminal *LeftAssociativeTerminals = PG->addNonTerminal("LeftAssociativeTerminals", "LeftAssociativeTerminals");
	ContextFreeGrammar::NonTerminal *RightAssociativeTerminals = PG->addNonTerminal("RightAssociativeTerminals", "RightAssociativeTerminals");
	ContextFreeGrammar::NonTerminal *NonAssociativeTerminal = PG->addNonTerminal("NonAssociativeTerminal", "NonAssociativeTerminal");
	ContextFreeGrammar::NonTerminal *LeftAssociativeTerminal = PG->addNonTerminal("LeftAssociativeTerminal", "LeftAssociativeTerminal");
	ContextFreeGrammar::NonTerminal *RightAssociativeTerminal = PG->addNonTerminal("RightAssociativeTerminal", "RightAssociativeTerminal");
	ContextFreeGrammar::NonTerminal *Rule = PG->addNonTerminal("Rule", "Rule");
	ContextFreeGrammar::NonTerminal *Productions = PG->addNonTerminal("Productions", "Productions");
	ContextFreeGrammar::NonTerminal *Production = PG->addNonTerminal("Production", "Production");
	ContextFreeGrammar::NonTerminal *NamedSymbols = PG->addNonTerminal("NamedSymbols", "NamedSymbols");
	ContextFreeGrammar::NonTerminal *NamedSymbol = PG->addNonTerminal("NamedSymbol", "NamedSymbol");
	ContextFreeGrammar::NonTerminal *Symbol = PG->addNonTerminal("Symbol", "Symbol");
	ContextFreeGrammar::NonTerminal *Keyword = PG->addNonTerminal("Keyword", "Keyword");

	PG->addRule(File, {
		PG->addProduction({
			PG->newNamedSymbol(Grammar)
		})
	});
	PG->addRule(Grammar, {
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_GRAMMAR),
			PG->newNamedSymbol("name", IDENTIFIER),
			PG->newNamedSymbol("type", STRING_LITERAL),
			PG->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			PG->newNamedSymbol(Headers),
			PG->newNamedSymbol(Precedences),
			PG->newNamedSymbol(Rules),
			PG->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE),
			PG->newNamedSymbol(Footer)
		})
	});
	PG->addRule(Headers, {
		PG->addProduction({
			PG->newNamedSymbol(Header),
			PG->newNamedSymbol(OPERATOR_SEMICOLON),
			PG->newNamedSymbol(Headers)
		}),
		PG->addProduction({
			PG->newNamedSymbol(Header),
			PG->newNamedSymbol(OPERATOR_SEMICOLON)
		})
	});
	PG->addRule(Header, {
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_TERM),
			PG->newNamedSymbol(Identifier)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_TERM),
			PG->newNamedSymbol(Identifier),
			PG->newNamedSymbol(OPERATOR_COLON),
			PG->newNamedSymbol(Identifier)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_TERM),
			PG->newNamedSymbol(Identifier),
			PG->newNamedSymbol(STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_TERM),
			PG->newNamedSymbol(Identifier),
			PG->newNamedSymbol(OPERATOR_COLON),
			PG->newNamedSymbol(Identifier),
			PG->newNamedSymbol(STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_NONTERM),
			PG->newNamedSymbol(Identifier)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_NONTERM),
			PG->newNamedSymbol(Identifier),
			PG->newNamedSymbol(OPERATOR_COLON),
			PG->newNamedSymbol(Identifier)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_START),
			PG->newNamedSymbol("idenfifier", Identifier)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_HEADER),
			PG->newNamedSymbol("_code", TOKEN_CODE)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_CODE),
			PG->newNamedSymbol("_code", TOKEN_CODE)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_ROOTTYPE),
			PG->newNamedSymbol("type", STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_BASECLASS),
			PG->newNamedSymbol("literal", STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_BASETYPE),
			PG->newNamedSymbol("literal", STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_BASETYPE),
			PG->newNamedSymbol(KEYWORD_UNION),
			PG->newNamedSymbol("literal", STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_RETURNTYPE),
			PG->newNamedSymbol("literal", STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(BlankLines)
		})
	});
	PG->addRule(Precedences, {
		PG->addProduction({
			PG->newNamedSymbol(Precedences),
			PG->newNamedSymbol(Precedence),
			PG->newNamedSymbol(OPERATOR_SEMICOLON)
		}),
		PG->addProduction({
			PG->newNamedSymbol(Precedence),
			PG->newNamedSymbol(OPERATOR_SEMICOLON)
		}),
		PG->addProduction({PG->newNamedSymbol(ContextFreeGrammar::getEpsilon())})
	});
	PG->addRule(Precedence, {
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_NONASSOC),
			PG->newNamedSymbol(NonAssociativeTerminals)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_LEFT),
			PG->newNamedSymbol(LeftAssociativeTerminals)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_RIGHT),
			PG->newNamedSymbol(RightAssociativeTerminals)
		})
	});
	PG->addRule(NonAssociativeTerminals, {
		PG->addProduction({
			PG->newNamedSymbol(NonAssociativeTerminals),
			PG->newNamedSymbol(NonAssociativeTerminal)
		}),
		PG->addProduction({
			PG->newNamedSymbol(NonAssociativeTerminal)
		})
	});
	PG->addRule(NonAssociativeTerminal, {
		PG->addProduction({
			PG->newNamedSymbol(STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(Identifier)
		})
	});
	PG->addRule(LeftAssociativeTerminals, {
		PG->addProduction({
			PG->newNamedSymbol(LeftAssociativeTerminals),
			PG->newNamedSymbol(LeftAssociativeTerminal)
		}),
		PG->addProduction({
			PG->newNamedSymbol(LeftAssociativeTerminal)
		})
	});
	PG->addRule(LeftAssociativeTerminal, {
		PG->addProduction({
			PG->newNamedSymbol(STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(Identifier)
		})
	});
	PG->addRule(RightAssociativeTerminals, {
		PG->addProduction({
			PG->newNamedSymbol(RightAssociativeTerminals),
			PG->newNamedSymbol(RightAssociativeTerminal)
		}),
		PG->addProduction({
			PG->newNamedSymbol(RightAssociativeTerminal)
		})
	});
	PG->addRule(RightAssociativeTerminal, {
		PG->addProduction({
			PG->newNamedSymbol(STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(Identifier)
		})
	});
	PG->addRule(Footer, {
		PG->addProduction({
			PG->newNamedSymbol(BlankLines)
		})
	});
	PG->addRule(BlankLines, {
		PG->addProduction({
			PG->newNamedSymbol(BlankLines),
			PG->newNamedSymbol(NEWLINE)
		}),
		PG->addProduction({PG->newNamedSymbol(ContextFreeGrammar::getEpsilon())})
	});
	PG->addRule(Rules, {
		PG->addProduction({
			PG->newNamedSymbol(Rules),
			PG->newNamedSymbol(Rule)
		}),
		PG->addProduction({
			PG->newNamedSymbol(Rule)
		})
	});
	PG->addRule(Rule, {
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_PRODUCTION),
			PG->newNamedSymbol("identifier", Identifier),
			PG->newNamedSymbol(OPERATOR_EQUALS),
			PG->newNamedSymbol("productions", Productions),
			PG->newNamedSymbol(OPERATOR_SEMICOLON)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_PRODUCTION),
			PG->newNamedSymbol("identifier", Identifier),
			PG->newNamedSymbol(OPERATOR_COLON),
			PG->newNamedSymbol("type", Identifier),
			PG->newNamedSymbol(OPERATOR_EQUALS),
			PG->newNamedSymbol("productions", Productions),
			PG->newNamedSymbol(OPERATOR_SEMICOLON)
		})
	});
	PG->addRule(Productions, {
		PG->addProduction({
			PG->newNamedSymbol("productions", Productions),
			PG->newNamedSymbol(OPERATOR_OR),
			PG->newNamedSymbol("production", Production)
		}),
		PG->addProduction({
			PG->newNamedSymbol("production", Production)
		})
	});
	PG->addRule(Production, {
		PG->addProduction({
			PG->newNamedSymbol("symbols", NamedSymbols)
		}),
		PG->addProduction({
			PG->newNamedSymbol("symbols", NamedSymbols),
			PG->newNamedSymbol("action", TOKEN_ACTION)
		}),
		PG->addProduction({
			PG->newNamedSymbol(OPERATOR_EPSILON)
		}),
		PG->addProduction({
			PG->newNamedSymbol(OPERATOR_EPSILON),
			PG->newNamedSymbol("action", TOKEN_ACTION)
		}),
		PG->addProduction({PG->newNamedSymbol(ContextFreeGrammar::getEpsilon())}),
		PG->addProduction({
			PG->newNamedSymbol(TOKEN_ACTION)
		})
	});
	PG->addRule(NamedSymbols, {
		PG->addProduction({
			PG->newNamedSymbol("symbols", NamedSymbols),
			PG->newNamedSymbol("symbol", NamedSymbol)
		}),
		PG->addProduction({
			PG->newNamedSymbol("symbol", NamedSymbol)
		})
	});
	PG->addRule(NamedSymbol, {
		PG->addProduction({
			PG->newNamedSymbol("identifier", Identifier),
			PG->newNamedSymbol(OPERATOR_COLON),
			PG->newNamedSymbol("symbol", Symbol)
		}),
		PG->addProduction({
			PG->newNamedSymbol("symbol", Symbol)
		})
	});
	PG->addRule(Symbol, {
		PG->addProduction({
			PG->newNamedSymbol(Identifier)
		}),
		PG->addProduction({
			PG->newNamedSymbol(STRING_LITERAL)
		}),
		PG->addProduction({
			PG->newNamedSymbol(OPERATOR_DOLLAR)
		})
	});
	PG->addRule(Keyword, {
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_GRAMMAR)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_TERM)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_NONTERM)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_PRODUCTION)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_START)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_CODE)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_HEADER)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_BASECLASS)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_ROOTTYPE)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_BASETYPE)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_RETURNTYPE)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_UNION)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_NONASSOC)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_LEFT)
		}),
		PG->addProduction({
			PG->newNamedSymbol(KEYWORD_RIGHT)
		}),
		PG->addProduction({
			PG->newNamedSymbol(OPERATOR_EPSILON)
		})
	});
	PG->addRule(Identifier, {
		PG->addProduction({
			PG->newNamedSymbol(Keyword)
		}),
		PG->addProduction({
			PG->newNamedSymbol(IDENTIFIER)
		})
	});
	return PG;
}
Actions bootstrapActions = {
	{ 0, "{		parserGenerator->setName($name$->getValue());		parserGenerator->setType($type$->getValue());	}", 117},
	{ 1, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2)); }", 130},
	{ 2, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2, $4)); }", 132},
	{ 3, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2, $3)); }", 134},
	{ 4, "{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>($2, $4, $5)); }", 136},
	{ 5, "{ root->addNonTerminal(root->create<ContextFreeGrammar::NonTerminal>($2, $2)); }", 138},
	{ 6, "{ root->addNonTerminal(root->create<ContextFreeGrammar::NonTerminal>($2, $4)); }", 140},
	{ 7, "{ root->setStartSymbol(root->getNonTerminal($idenfifier$)); }", 142},
	{ 8, "{ parserGenerator->addHeader($_code$); }", 144},
	{ 9, "{ parserGenerator->addCode($_code$); }", 146},
	{ 10, "{ parserGenerator->setRootType($type$->getValue()); }", 148},
	{ 11, "{ parserGenerator->setBaseClass($literal$->getValue()); }", 150},
	{ 12, "{ parserGenerator->setBaseType($literal$->getValue()); }", 152},
	{ 13, "{ parserGenerator->setBaseType($literal$->getValue(), true); }", 154},
	{ 14, "{ parserGenerator->setReturnType($literal$->getValue()); }", 156},
	{ 15, "{ ++Precedence; }", 161},
	{ 16, "{ ++Precedence; }", 162},
	{ 17, "{			ContextFreeGrammar::Terminal* terminal = root->getTerminal($1);			terminal->setAssociativity(ContextFreeGrammar::Associativity::None);			terminal->setPrecedence(Precedence);		}", 179},
	{ 18, "{			ContextFreeGrammar::Terminal* terminal = root->getTerminal($1);			terminal->setAssociativity(ContextFreeGrammar::Associativity::None);			terminal->setPrecedence(Precedence);		}", 185},
	{ 19, "{			ContextFreeGrammar::Terminal* terminal = root->getTerminal($1);			terminal->setAssociativity(ContextFreeGrammar::Associativity::Left);			terminal->setPrecedence(Precedence);		}", 199},
	{ 20, "{			ContextFreeGrammar::Terminal* terminal = root->getTerminal($1);			terminal->setAssociativity(ContextFreeGrammar::Associativity::Left);			terminal->setPrecedence(Precedence);		}", 205},
	{ 21, "{			ContextFreeGrammar::Terminal* terminal = root->getTerminal($1);			terminal->setAssociativity(ContextFreeGrammar::Associativity::Right);			terminal->setPrecedence(Precedence);		}", 219},
	{ 22, "{			ContextFreeGrammar::Terminal* terminal = root->getTerminal($1);			terminal->setAssociativity(ContextFreeGrammar::Associativity::Right);			terminal->setPrecedence(Precedence);		}", 225},
	{ 23, "{ root->addRule($2); }", 240},
	{ 24, "{ root->addRule($1); }", 242},
	{ 25, "{ $$ = root->findOrCreateRule($identifier$, $productions$); }", 246},
	{ 26, "{ $$ = root->findOrCreateRule($identifier$, $type$, $productions$); }", 248},
	{ 27, "{ $$ = $productions$; $productions$->addProduction($production$); }", 252},
	{ 28, "{ $$ = root->newProductions(); $$->addProduction($production$); }", 254},
	{ 29, "{ $$ = root->newProduction($symbols$); }", 258},
	{ 30, "{ $$ = root->newProduction($symbols$, $action$, false); }", 260},
	{ 31, "{ $$ = root->newProduction(); }", 262},
	{ 32, "{ $$ = root->newProduction($action$, false); }", 264},
	{ 33, "{ $$ = root->newProduction(); }", 266},
	{ 34, "{ $$ = root->newProduction($1, false); }", 268},
	{ 35, "{ $$ = $symbols$; $symbols$->addSymbol($symbol$); }", 273},
	{ 36, "{ $$ = root->newNamedSymbols(); $$->addSymbol($symbol$); }", 275},
	{ 37, "{ $$ = root->newNamedSymbol($identifier$, $symbol$); }", 279},
	{ 38, "{ $$ = root->newNamedSymbol($symbol$); }", 281},
	{ 39, "{ $$ = root->findOrCreateSymbol($1); }", 285},
	{ 40, "{    		ContextFreeGrammar::Symbol* symbol = root->getTerminal($1);    		if (symbol == ContextFreeGrammar::getErrorSymbol() || symbol == nullptr)    			G::logger->LogError(new UndefinedTerminalSymbolErrorObject($1->getValue(), lexer->getLineNumber(), lexer->getCharacter()));    		$$ = symbol;    	}", 287},
	{ 41, "{    		$$ = root->getTerminal(root->newStringLiteral(\"$\"));    	}", 294}
};

ParserGenerator<ContextFreeGrammar, ParserGeneratorParser>* pg_ParserGenerator = new ParserGenerator<ContextFreeGrammar, ParserGeneratorParser>("pg",
  pg_bootstrap(), &bootstrapActions,
  "ContextFreeGrammar",
  "ValueType",
  "true",
  "void",
  {
    { "\n\t#include <io.h>\n\t#include <iostream>\n\t#include <cassert>\n\n\t//#include \"nonstd/Grammar/Grammar.h\"\n\t#include \"g/ParserGenerator/ParserGeneratorParser.h\"\n\t#include \"g/ParserGenerator/ParserGenerator.h\"\n\n\tusing namespace G::ParserGenerator;\n\n\textern ParserGenerator<ContextFreeGrammar, ParserGeneratorParser>* parserGenerator;\n\n    struct Token {\n        Token(std::string name) : name(name) {}\n        std::string name;\n    };\n\ttypedef Token Keyword;\n    struct Identifier : public Token {\n        Identifier(std::string name) : Token(name) {}\n    };\n\n\tunion ValueType {\n\t\tContextFreeGrammar *Grammar;\n\t\tContextFreeGrammar::Rules *Rules;\n\t\tContextFreeGrammar::Rule *Rule;\n\t\tContextFreeGrammar::Productions *Productions;\n\t\tContextFreeGrammar::Production *Production;\n\t\tContextFreeGrammar::NamedSymbols *NamedSymbols;\n\t\tContextFreeGrammar::NamedSymbol *NamedSymbol;\n\t\tContextFreeGrammar::Symbol *Symbol;\n\t\tContextFreeGrammar::Identifier *Identifier;\n\t\tContextFreeGrammar::StringLiteral *StringLiteral;\n\t\tint Action;\t\t// TODO: 'typedef ContextFreeGrammar::Action int'\n\t\tCodeBlock* CodeBlock;\n\t};\n\n\textern ValueType currentValue;\n\tusing namespace Runtime;\n", 9, "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-pg\\pg.pg" }
  },
  {
    { "\n\t#include \"pg.lg.h\"\n\tValueType currentValue;\n\tunsigned Precedence = 1;\n", 50, "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-pg\\pg.pg" },
    { "\n\tvoid pgParser::reportError(State state, Input input) {\n\t\tstd::string report = std::string(\"Found \") + Terminals[input] + \" Expecting \";\n\n\t\tPair<Action>* pair = ShiftReduce_states[state - 1]->pair;\n\t\tif (pair) {\n\t\t\tfor (size_t pairs = ShiftReduce_states[state - 1]->pairs; pairs > 0; --pairs) {\n                report += std::string(Terminals[pair->input]) + ((pairs > 1) ? \", \" : \"\");\n\t\t\t\t++pair;\n\t\t\t}\n\t\t}\n\t\telse\n            report += std::string(\"<nothing>\");\n        report += std::string(\" in state \") + std::to_string(state) + \".\\\n\";\n\n\t\tG::logger->LogError(new SyntaxErrorObject(report, lexer->getLineNumber(), lexer->getCharacter()));\n\t}\n", 55, "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-pg\\pg.pg" }
  }
);

//
// pg-bootstrap-lg-pg/pg.pg.h
//

#include "runtime/lexer/Lexer.h"
#include "runtime/parser/Parser.h"

class pgParser : public Parser<short, ValueType> {
public:
	pgParser(Lexer* lexer, ValueType& currentValue, ContextFreeGrammar* root, bool debug = false) : root(root), Parser(lexer, currentValue, debug) {}
	ContextFreeGrammar* root;
	virtual size_t getStates() {
		return 259;
	}
	virtual Action nextState(State state, Input input) {
		auto cell = ShiftReduce_states[state - 1];
		return cell ? cell->lookup(input) : Action(Action::Function::Error);
	}
	virtual State nextGoto(State state, NonTerminal lhs) {
		auto cell = Goto_states[state - 1];
		return cell ? cell->lookup(lhs) : 0;
	}
	virtual int getAcceptAction(size_t production) {
		return ActionMap[production];
	}
	virtual void dispatch(int action) {
		(this->*Actions[action])();
	}
	virtual size_t getNumberOfRHSSymbols(unsigned production) {
		return rhsSymbols[production];
	}
	virtual NonTerminal getLHSSymbolIndex(unsigned production) {
		return production2lhs[production];
	}
	virtual size_t getNumberOfTerminals() {
		return 30;
	}
	virtual std::string getTerminalName(size_t index) {
		return (index >= 0 && index < getNumberOfTerminals()) ? Terminals[index] : "<" + std::to_string(index) + ">";
	}
	virtual std::string getNonTerminalName(size_t index) {
		return NonTerminals[index - 1];
	}
	virtual void reportError(State state, Input input);

	static const char* Terminals[30];
	static const char* NonTerminals[24];
	enum Terminal {
		EPSILON,
		END,
		KEYWORD_GRAMMAR,
		KEYWORD_TERM,
		KEYWORD_NONTERM,
		KEYWORD_PRODUCTION,
		KEYWORD_START,
		KEYWORD_CODE,
		KEYWORD_HEADER,
		KEYWORD_ROOTTYPE,
		KEYWORD_BASECLASS,
		KEYWORD_BASETYPE,
		KEYWORD_RETURNTYPE,
		KEYWORD_UNION,
		KEYWORD_NONASSOC,
		KEYWORD_LEFT,
		KEYWORD_RIGHT,
		OPERATOR_DOLLAR,
		OPERATOR_EPSILON,
		OPERATOR_OPEN_CURLY_BRACE,
		OPERATOR_CLOSE_CURLY_BRACE,
		OPERATOR_EQUALS,
		OPERATOR_OR,
		OPERATOR_COLON,
		OPERATOR_SEMICOLON,
		IDENTIFIER,
		STRING_LITERAL,
		TOKEN_ACTION,
		TOKEN_CODE,
		NEWLINE
	};
	static size_t rhsSymbols[78];
	static NonTerminal production2lhs[78];
	static int ActionMap[78];
	static Pairs<Action> ShiftReduce_row_1;
	static Pairs<Action> ShiftReduce_row_2;
	static Pairs<Action> ShiftReduce_row_3;
	static Pairs<Action> ShiftReduce_row_4;
	static Pairs<Action> ShiftReduce_row_5;
	static Pairs<Action> ShiftReduce_row_6;
	static Pairs<Action> ShiftReduce_row_7;
	static Pairs<Action> ShiftReduce_row_8;
	static Pairs<Action> ShiftReduce_row_9;
	static Pairs<Action> ShiftReduce_row_10;
	static Pairs<Action> ShiftReduce_row_11;
	static Pairs<Action> ShiftReduce_row_12;
	static Pairs<Action> ShiftReduce_row_13;
	static Pairs<Action> ShiftReduce_row_14;
	static Pairs<Action> ShiftReduce_row_15;
	static Pairs<Action> ShiftReduce_row_16;
	static Pairs<Action> ShiftReduce_row_17;
	static Pairs<Action> ShiftReduce_row_18;
	static Pairs<Action> ShiftReduce_row_19;
	static Pairs<Action> ShiftReduce_row_20;
	static Pairs<Action> ShiftReduce_row_21;
	static Pairs<Action> ShiftReduce_row_22;
	static Pairs<Action> ShiftReduce_row_23;
	static Pairs<Action> ShiftReduce_row_24;
	static Pairs<Action> ShiftReduce_row_25;
	static Pairs<Action> ShiftReduce_row_26;
	static Pairs<Action> ShiftReduce_row_27;
	static Pairs<Action> ShiftReduce_row_28;
	static Pairs<Action> ShiftReduce_row_29;
	static Pairs<Action> ShiftReduce_row_30;
	static Pairs<Action> ShiftReduce_row_31;
	static Pairs<Action> ShiftReduce_row_32;
	static Pairs<Action> ShiftReduce_row_33;
	static Pairs<Action> ShiftReduce_row_34;
	static Pairs<Action> ShiftReduce_row_35;
	static Pairs<Action> ShiftReduce_row_36;
	static Pairs<Action> ShiftReduce_row_37;
	static Pairs<Action> ShiftReduce_row_38;
	static Pairs<Action> ShiftReduce_row_39;
	static Pairs<Action> ShiftReduce_row_40;
	static Pairs<Action> ShiftReduce_row_41;
	static Pairs<Action> ShiftReduce_row_42;
	static Pairs<Action> ShiftReduce_row_43;
	static Pairs<Action> ShiftReduce_row_44;
	static Pairs<Action> ShiftReduce_row_45;
	static Pairs<Action> ShiftReduce_row_46;
	static Pairs<Action> ShiftReduce_row_47;
	static Pairs<Action> ShiftReduce_row_48;
	static Pairs<Action> ShiftReduce_row_49;
	static Pairs<Action> ShiftReduce_row_50;
	static Pairs<Action> ShiftReduce_row_51;
	static Pairs<Action> ShiftReduce_row_52;
	static Pairs<Action> ShiftReduce_row_53;
	static Pairs<Action> ShiftReduce_row_54;
	static Pairs<Action> ShiftReduce_row_55;
	static Pairs<Action> ShiftReduce_row_56;
	static Pairs<Action> ShiftReduce_row_57;
	static Pairs<Action> ShiftReduce_row_58;
	static Pairs<Action> ShiftReduce_row_59;
	static Pairs<Action> ShiftReduce_row_60;
	static Pairs<Action> ShiftReduce_row_61;
	static Pairs<Action> ShiftReduce_row_62;
	static Pairs<Action> ShiftReduce_row_63;
	static Pairs<Action> ShiftReduce_row_64;
	static Pairs<Action> ShiftReduce_row_65;
	static Pairs<Action> ShiftReduce_row_66;
	static Pairs<Action> ShiftReduce_row_67;
	static Pairs<Action> ShiftReduce_row_68;
	static Pairs<Action> ShiftReduce_row_69;
	static Pairs<Action> ShiftReduce_row_70;
	static Pairs<Action> ShiftReduce_row_71;
	static Pairs<Action> ShiftReduce_row_72;
	static Pairs<Action> ShiftReduce_row_73;
	static Pairs<Action> ShiftReduce_row_74;
	static Pairs<Action> ShiftReduce_row_75;
	static Pairs<Action> ShiftReduce_row_76;
	static Pairs<Action> ShiftReduce_row_77;
	static Pairs<Action> ShiftReduce_row_78;
	static Pairs<Action> ShiftReduce_row_79;
	static Pairs<Action> ShiftReduce_row_80;
	static Pairs<Action> ShiftReduce_row_81;
	static Pairs<Action> ShiftReduce_row_82;
	static Pairs<Action> ShiftReduce_row_83;
	static Pairs<Action> ShiftReduce_row_84;
	static Pairs<Action> ShiftReduce_row_85;
	static Pairs<Action> ShiftReduce_row_86;
	static Pairs<Action> ShiftReduce_row_87;
	static Pairs<Action> ShiftReduce_row_88;
	static Pairs<Action> ShiftReduce_row_89;
	static Pairs<Action> ShiftReduce_row_90;
	static Pairs<Action> ShiftReduce_row_91;
	static Pairs<Action> ShiftReduce_row_92;
	static Pairs<Action> ShiftReduce_row_93;
	static Pairs<Action> ShiftReduce_row_94;
	static Pairs<Action> ShiftReduce_row_95;
	static Pairs<Action> ShiftReduce_row_96;
	static Pairs<Action> ShiftReduce_row_97;
	static Pairs<Action> ShiftReduce_row_98;
	static Pairs<Action> ShiftReduce_row_99;
	static Pairs<Action> ShiftReduce_row_100;
	static Pairs<Action> ShiftReduce_row_101;
	static Pairs<Action> ShiftReduce_row_102;
	static Pairs<Action> ShiftReduce_row_103;
	static Pairs<Action> ShiftReduce_row_104;
	static Pairs<Action> ShiftReduce_row_105;
	static Pairs<Action> ShiftReduce_row_106;
	static Pairs<Action> ShiftReduce_row_107;
	static Pairs<Action> ShiftReduce_row_108;
	static Pairs<Action> ShiftReduce_row_109;
	static Pairs<Action> ShiftReduce_row_110;
	static Pairs<Action> ShiftReduce_row_111;
	static Pairs<Action> ShiftReduce_row_112;
	static Pairs<Action> ShiftReduce_row_113;
	static Pairs<Action> ShiftReduce_row_114;
	static Pairs<Action> ShiftReduce_row_115;
	static Pairs<Action> ShiftReduce_row_116;
	static Pairs<Action> ShiftReduce_row_117;
	static Pairs<Action> ShiftReduce_row_118;
	static Pairs<Action> ShiftReduce_row_119;
	static Pairs<Action> ShiftReduce_row_120;
	static Pairs<Action> ShiftReduce_row_121;
	static Pairs<Action> ShiftReduce_row_122;
	static Pairs<Action> ShiftReduce_row_123;
	static Pairs<Action> ShiftReduce_row_124;
	static Pairs<Action> ShiftReduce_row_125;
	static Pairs<Action> ShiftReduce_row_126;
	static Pairs<Action> ShiftReduce_row_127;
	static Pairs<Action> ShiftReduce_row_128;
	static Pairs<Action> ShiftReduce_row_129;
	static Pairs<Action> ShiftReduce_row_130;
	static Pairs<Action> ShiftReduce_row_131;
	static Pairs<Action> ShiftReduce_row_132;
	static Pairs<Action> ShiftReduce_row_133;
	static Pairs<Action> ShiftReduce_row_134;
	static Pairs<Action> ShiftReduce_row_135;
	static Pairs<Action> ShiftReduce_row_136;
	static Pairs<Action> ShiftReduce_row_137;
	static Pairs<Action> ShiftReduce_row_138;
	static Pairs<Action> ShiftReduce_row_139;
	static Pairs<Action> ShiftReduce_row_140;
	static Pairs<Action> ShiftReduce_row_141;
	static Pairs<Action> ShiftReduce_row_142;
	static Pairs<Action> ShiftReduce_row_143;
	static Pairs<Action> ShiftReduce_row_144;
	static Pairs<Action> ShiftReduce_row_145;
	static Pairs<Action> ShiftReduce_row_146;
	static Pairs<Action> ShiftReduce_row_147;
	static Pairs<Action> ShiftReduce_row_148;
	static Pairs<Action> ShiftReduce_row_149;
	static Pairs<Action> ShiftReduce_row_150;
	static Pairs<Action> ShiftReduce_row_151;
	static Pairs<Action> ShiftReduce_row_152;
	static Pairs<Action> ShiftReduce_row_153;
	static Pairs<Action> ShiftReduce_row_154;
	static Pairs<Action> ShiftReduce_row_155;
	static Pairs<Action> ShiftReduce_row_156;
	static Pairs<Action> ShiftReduce_row_157;
	static Pairs<Action> ShiftReduce_row_158;
	static Pairs<Action> ShiftReduce_row_159;
	static Pairs<Action> ShiftReduce_row_160;
	static Pairs<Action> ShiftReduce_row_161;
	static Pairs<Action> ShiftReduce_row_162;
	static Pairs<Action> ShiftReduce_row_163;
	static Pairs<Action> ShiftReduce_row_164;
	static Pairs<Action> ShiftReduce_row_165;
	static Pairs<Action> ShiftReduce_row_166;
	static Pairs<Action> ShiftReduce_row_167;
	static Pairs<Action> ShiftReduce_row_168;
	static Pairs<Action> ShiftReduce_row_169;
	static Pairs<Action> ShiftReduce_row_170;
	static Pairs<Action> ShiftReduce_row_171;
	static Pairs<Action> ShiftReduce_row_172;
	static Pairs<Action> ShiftReduce_row_173;
	static Pairs<Action> ShiftReduce_row_174;
	static Pairs<Action> ShiftReduce_row_175;
	static Pairs<Action> ShiftReduce_row_176;
	static Pairs<Action> ShiftReduce_row_177;
	static Pairs<Action> ShiftReduce_row_178;
	static Pairs<Action> ShiftReduce_row_179;
	static Pairs<Action> ShiftReduce_row_180;
	static Pairs<Action> ShiftReduce_row_181;
	static Pairs<Action> ShiftReduce_row_182;
	static Pairs<Action> ShiftReduce_row_183;
	static Pairs<Action> ShiftReduce_row_184;
	static Pairs<Action> ShiftReduce_row_185;
	static Pairs<Action> ShiftReduce_row_186;
	static Pairs<Action> ShiftReduce_row_187;
	static Pairs<Action> ShiftReduce_row_188;
	static Pairs<Action> ShiftReduce_row_189;
	static Pairs<Action> ShiftReduce_row_190;
	static Pairs<Action> ShiftReduce_row_191;
	static Pairs<Action> ShiftReduce_row_192;
	static Pairs<Action> ShiftReduce_row_193;
	static Pairs<Action> ShiftReduce_row_194;
	static Pairs<Action> ShiftReduce_row_195;
	static Pairs<Action> ShiftReduce_row_196;
	static Pairs<Action> ShiftReduce_row_197;
	static Pairs<Action> ShiftReduce_row_198;
	static Pairs<Action> ShiftReduce_row_199;
	static Pairs<Action> ShiftReduce_row_200;
	static Pairs<Action> ShiftReduce_row_201;
	static Pairs<Action> ShiftReduce_row_202;
	static Pairs<Action> ShiftReduce_row_203;
	static Pairs<Action> ShiftReduce_row_204;
	static Pairs<Action> ShiftReduce_row_205;
	static Pairs<Action> ShiftReduce_row_206;
	static Pairs<Action> ShiftReduce_row_207;
	static Pairs<Action> ShiftReduce_row_208;
	static Pairs<Action> ShiftReduce_row_209;
	static Pairs<Action> ShiftReduce_row_210;
	static Pairs<Action> ShiftReduce_row_211;
	static Pairs<Action> ShiftReduce_row_212;
	static Pairs<Action> ShiftReduce_row_213;
	static Pairs<Action> ShiftReduce_row_214;
	static Pairs<Action> ShiftReduce_row_215;
	static Pairs<Action> ShiftReduce_row_216;
	static Pairs<Action> ShiftReduce_row_217;
	static Pairs<Action> ShiftReduce_row_218;
	static Pairs<Action> ShiftReduce_row_219;
	static Pairs<Action> ShiftReduce_row_220;
	static Pairs<Action>* ShiftReduce_states[259];

	static Pairs<size_t> Goto_row_1;
	static Pairs<size_t> Goto_row_2;
	static Pairs<size_t> Goto_row_3;
	static Pairs<size_t> Goto_row_4;
	static Pairs<size_t> Goto_row_5;
	static Pairs<size_t> Goto_row_6;
	static Pairs<size_t> Goto_row_7;
	static Pairs<size_t> Goto_row_8;
	static Pairs<size_t> Goto_row_9;
	static Pairs<size_t> Goto_row_10;
	static Pairs<size_t> Goto_row_11;
	static Pairs<size_t> Goto_row_12;
	static Pairs<size_t> Goto_row_13;
	static Pairs<size_t> Goto_row_14;
	static Pairs<size_t> Goto_row_15;
	static Pairs<size_t> Goto_row_16;
	static Pairs<size_t> Goto_row_17;
	static Pairs<size_t> Goto_row_18;
	static Pairs<size_t> Goto_row_19;
	static Pairs<size_t> Goto_row_20;
	static Pairs<size_t> Goto_row_21;
	static Pairs<size_t> Goto_row_22;
	static Pairs<size_t> Goto_row_23;
	static Pairs<size_t> Goto_row_24;
	static Pairs<size_t> Goto_row_25;
	static Pairs<size_t>* Goto_states[259];

	static void(pgParser::*Actions[42])();
	void Action0();
	void Action1();
	void Action2();
	void Action3();
	void Action4();
	void Action5();
	void Action6();
	void Action7();
	void Action8();
	void Action9();
	void Action10();
	void Action11();
	void Action12();
	void Action13();
	void Action14();
	void Action15();
	void Action16();
	void Action17();
	void Action18();
	void Action19();
	void Action20();
	void Action21();
	void Action22();
	void Action23();
	void Action24();
	void Action25();
	void Action26();
	void Action27();
	void Action28();
	void Action29();
	void Action30();
	void Action31();
	void Action32();
	void Action33();
	void Action34();
	void Action35();
	void Action36();
	void Action37();
	void Action38();
	void Action39();
	void Action40();
	void Action41();
};

//
// pg-bootstrap-lg-pg/pg.pg.cpp
//

Pairs<pgParser::Action> pgParser::ShiftReduce_row_1 = { {2, {Action::Function::Shift, 4}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_2 = { {1, {Action::Function::Shift, 5}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_3 = { {1, {Action::Function::Reduce, 0}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_4 = { {25, {Action::Function::Shift, 6}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_5 = { {1, {Action::Function::Accept}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_6 = { {26, {Action::Function::Shift, 7}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_7 = { {19, {Action::Function::Shift, 8}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_8 = { {3, {Action::Function::Shift, 11}}, {4, {Action::Function::Shift, 12}}, {6, {Action::Function::Shift, 13}}, {7, {Action::Function::Shift, 15}}, {8, {Action::Function::Shift, 14}}, {9, {Action::Function::Shift, 16}}, {10, {Action::Function::Shift, 17}}, {11, {Action::Function::Shift, 18}}, {12, {Action::Function::Shift, 19}}, {24, {Action::Function::Reduce, 39}}, {29, {Action::Function::Reduce, 39}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_9 = { {1, {Action::Function::Reduce, 21}}, {2, {Action::Function::Reduce, 21}}, {3, {Action::Function::Reduce, 21}}, {4, {Action::Function::Reduce, 21}}, {5, {Action::Function::Reduce, 21}}, {6, {Action::Function::Reduce, 21}}, {7, {Action::Function::Reduce, 21}}, {8, {Action::Function::Reduce, 21}}, {9, {Action::Function::Reduce, 21}}, {10, {Action::Function::Reduce, 21}}, {11, {Action::Function::Reduce, 21}}, {12, {Action::Function::Reduce, 21}}, {13, {Action::Function::Reduce, 21}}, {14, {Action::Function::Shift, 23}}, {15, {Action::Function::Shift, 24}}, {16, {Action::Function::Shift, 25}}, {17, {Action::Function::Reduce, 21}}, {18, {Action::Function::Reduce, 21}}, {20, {Action::Function::Reduce, 21}}, {22, {Action::Function::Reduce, 21}}, {23, {Action::Function::Reduce, 21}}, {24, {Action::Function::Reduce, 21}}, {25, {Action::Function::Reduce, 21}}, {26, {Action::Function::Reduce, 21}}, {27, {Action::Function::Reduce, 21}}, {29, {Action::Function::Reduce, 21}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_10 = { {24, {Action::Function::Shift, 26}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_11 = { {2, {Action::Function::Shift, 30}}, {3, {Action::Function::Shift, 31}}, {4, {Action::Function::Shift, 32}}, {5, {Action::Function::Shift, 33}}, {6, {Action::Function::Shift, 34}}, {7, {Action::Function::Shift, 35}}, {8, {Action::Function::Shift, 36}}, {9, {Action::Function::Shift, 38}}, {10, {Action::Function::Shift, 37}}, {11, {Action::Function::Shift, 39}}, {12, {Action::Function::Shift, 40}}, {13, {Action::Function::Shift, 41}}, {14, {Action::Function::Shift, 42}}, {15, {Action::Function::Shift, 43}}, {16, {Action::Function::Shift, 44}}, {18, {Action::Function::Shift, 45}}, {25, {Action::Function::Shift, 29}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_12 = { {2, {Action::Function::Shift, 49}}, {3, {Action::Function::Shift, 50}}, {4, {Action::Function::Shift, 51}}, {5, {Action::Function::Shift, 52}}, {6, {Action::Function::Shift, 53}}, {7, {Action::Function::Shift, 54}}, {8, {Action::Function::Shift, 55}}, {9, {Action::Function::Shift, 57}}, {10, {Action::Function::Shift, 56}}, {11, {Action::Function::Shift, 58}}, {12, {Action::Function::Shift, 59}}, {13, {Action::Function::Shift, 60}}, {14, {Action::Function::Shift, 61}}, {15, {Action::Function::Shift, 62}}, {16, {Action::Function::Shift, 63}}, {18, {Action::Function::Shift, 64}}, {25, {Action::Function::Shift, 48}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_13 = { {2, {Action::Function::Shift, 68}}, {3, {Action::Function::Shift, 69}}, {4, {Action::Function::Shift, 70}}, {5, {Action::Function::Shift, 71}}, {6, {Action::Function::Shift, 72}}, {7, {Action::Function::Shift, 73}}, {8, {Action::Function::Shift, 74}}, {9, {Action::Function::Shift, 76}}, {10, {Action::Function::Shift, 75}}, {11, {Action::Function::Shift, 77}}, {12, {Action::Function::Shift, 78}}, {13, {Action::Function::Shift, 79}}, {14, {Action::Function::Shift, 80}}, {15, {Action::Function::Shift, 81}}, {16, {Action::Function::Shift, 82}}, {18, {Action::Function::Shift, 83}}, {25, {Action::Function::Shift, 67}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_14 = { {28, {Action::Function::Shift, 84}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_15 = { {28, {Action::Function::Shift, 85}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_16 = { {26, {Action::Function::Shift, 86}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_17 = { {26, {Action::Function::Shift, 87}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_18 = { {13, {Action::Function::Shift, 89}}, {26, {Action::Function::Shift, 88}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_19 = { {26, {Action::Function::Shift, 90}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_20 = { {24, {Action::Function::Reduce, 18}}, {29, {Action::Function::Shift, 91}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_21 = { {5, {Action::Function::Shift, 95}}, {14, {Action::Function::Shift, 23}}, {15, {Action::Function::Shift, 24}}, {16, {Action::Function::Shift, 25}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_22 = { {24, {Action::Function::Shift, 96}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_23 = { {2, {Action::Function::Shift, 103}}, {3, {Action::Function::Shift, 104}}, {4, {Action::Function::Shift, 105}}, {5, {Action::Function::Shift, 106}}, {6, {Action::Function::Shift, 107}}, {7, {Action::Function::Shift, 108}}, {8, {Action::Function::Shift, 109}}, {9, {Action::Function::Shift, 111}}, {10, {Action::Function::Shift, 110}}, {11, {Action::Function::Shift, 112}}, {12, {Action::Function::Shift, 113}}, {13, {Action::Function::Shift, 114}}, {14, {Action::Function::Shift, 115}}, {15, {Action::Function::Shift, 116}}, {16, {Action::Function::Shift, 117}}, {18, {Action::Function::Shift, 118}}, {25, {Action::Function::Shift, 102}}, {26, {Action::Function::Shift, 99}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_24 = { {2, {Action::Function::Shift, 103}}, {3, {Action::Function::Shift, 104}}, {4, {Action::Function::Shift, 105}}, {5, {Action::Function::Shift, 106}}, {6, {Action::Function::Shift, 107}}, {7, {Action::Function::Shift, 108}}, {8, {Action::Function::Shift, 109}}, {9, {Action::Function::Shift, 111}}, {10, {Action::Function::Shift, 110}}, {11, {Action::Function::Shift, 112}}, {12, {Action::Function::Shift, 113}}, {13, {Action::Function::Shift, 114}}, {14, {Action::Function::Shift, 115}}, {15, {Action::Function::Shift, 116}}, {16, {Action::Function::Shift, 117}}, {18, {Action::Function::Shift, 118}}, {25, {Action::Function::Shift, 102}}, {26, {Action::Function::Shift, 121}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_25 = { {2, {Action::Function::Shift, 103}}, {3, {Action::Function::Shift, 104}}, {4, {Action::Function::Shift, 105}}, {5, {Action::Function::Shift, 106}}, {6, {Action::Function::Shift, 107}}, {7, {Action::Function::Shift, 108}}, {8, {Action::Function::Shift, 109}}, {9, {Action::Function::Shift, 111}}, {10, {Action::Function::Shift, 110}}, {11, {Action::Function::Shift, 112}}, {12, {Action::Function::Shift, 113}}, {13, {Action::Function::Shift, 114}}, {14, {Action::Function::Shift, 115}}, {15, {Action::Function::Shift, 116}}, {16, {Action::Function::Shift, 117}}, {18, {Action::Function::Shift, 118}}, {25, {Action::Function::Shift, 102}}, {26, {Action::Function::Shift, 125}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_26 = { {1, {Action::Function::Reduce, 3}}, {2, {Action::Function::Reduce, 3}}, {3, {Action::Function::Shift, 11}}, {4, {Action::Function::Shift, 12}}, {5, {Action::Function::Reduce, 3}}, {6, {Action::Function::Shift, 13}}, {7, {Action::Function::Shift, 15}}, {8, {Action::Function::Shift, 14}}, {9, {Action::Function::Shift, 16}}, {10, {Action::Function::Shift, 17}}, {11, {Action::Function::Shift, 18}}, {12, {Action::Function::Shift, 19}}, {13, {Action::Function::Reduce, 3}}, {14, {Action::Function::Reduce, 3}}, {15, {Action::Function::Reduce, 3}}, {16, {Action::Function::Reduce, 3}}, {17, {Action::Function::Reduce, 3}}, {18, {Action::Function::Reduce, 3}}, {20, {Action::Function::Reduce, 3}}, {22, {Action::Function::Reduce, 3}}, {23, {Action::Function::Reduce, 3}}, {24, {Action::Function::Reduce, 3}}, {25, {Action::Function::Reduce, 3}}, {26, {Action::Function::Reduce, 3}}, {27, {Action::Function::Reduce, 3}}, {29, {Action::Function::Reduce, 3}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_27 = { {23, {Action::Function::Shift, 128}}, {24, {Action::Function::Reduce, 4}}, {26, {Action::Function::Shift, 129}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_28 = { {23, {Action::Function::Reduce, 75}}, {24, {Action::Function::Reduce, 75}}, {26, {Action::Function::Reduce, 75}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_29 = { {23, {Action::Function::Reduce, 76}}, {24, {Action::Function::Reduce, 76}}, {26, {Action::Function::Reduce, 76}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_30 = { {23, {Action::Function::Reduce, 59}}, {24, {Action::Function::Reduce, 59}}, {26, {Action::Function::Reduce, 59}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_31 = { {23, {Action::Function::Reduce, 60}}, {24, {Action::Function::Reduce, 60}}, {26, {Action::Function::Reduce, 60}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_32 = { {23, {Action::Function::Reduce, 61}}, {24, {Action::Function::Reduce, 61}}, {26, {Action::Function::Reduce, 61}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_33 = { {23, {Action::Function::Reduce, 62}}, {24, {Action::Function::Reduce, 62}}, {26, {Action::Function::Reduce, 62}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_34 = { {23, {Action::Function::Reduce, 63}}, {24, {Action::Function::Reduce, 63}}, {26, {Action::Function::Reduce, 63}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_35 = { {23, {Action::Function::Reduce, 64}}, {24, {Action::Function::Reduce, 64}}, {26, {Action::Function::Reduce, 64}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_36 = { {23, {Action::Function::Reduce, 65}}, {24, {Action::Function::Reduce, 65}}, {26, {Action::Function::Reduce, 65}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_37 = { {23, {Action::Function::Reduce, 66}}, {24, {Action::Function::Reduce, 66}}, {26, {Action::Function::Reduce, 66}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_38 = { {23, {Action::Function::Reduce, 67}}, {24, {Action::Function::Reduce, 67}}, {26, {Action::Function::Reduce, 67}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_39 = { {23, {Action::Function::Reduce, 68}}, {24, {Action::Function::Reduce, 68}}, {26, {Action::Function::Reduce, 68}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_40 = { {23, {Action::Function::Reduce, 69}}, {24, {Action::Function::Reduce, 69}}, {26, {Action::Function::Reduce, 69}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_41 = { {23, {Action::Function::Reduce, 70}}, {24, {Action::Function::Reduce, 70}}, {26, {Action::Function::Reduce, 70}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_42 = { {23, {Action::Function::Reduce, 71}}, {24, {Action::Function::Reduce, 71}}, {26, {Action::Function::Reduce, 71}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_43 = { {23, {Action::Function::Reduce, 72}}, {24, {Action::Function::Reduce, 72}}, {26, {Action::Function::Reduce, 72}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_44 = { {23, {Action::Function::Reduce, 73}}, {24, {Action::Function::Reduce, 73}}, {26, {Action::Function::Reduce, 73}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_45 = { {23, {Action::Function::Reduce, 74}}, {24, {Action::Function::Reduce, 74}}, {26, {Action::Function::Reduce, 74}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_46 = { {23, {Action::Function::Shift, 130}}, {24, {Action::Function::Reduce, 8}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_47 = { {23, {Action::Function::Reduce, 75}}, {24, {Action::Function::Reduce, 75}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_48 = { {23, {Action::Function::Reduce, 76}}, {24, {Action::Function::Reduce, 76}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_49 = { {23, {Action::Function::Reduce, 59}}, {24, {Action::Function::Reduce, 59}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_50 = { {23, {Action::Function::Reduce, 60}}, {24, {Action::Function::Reduce, 60}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_51 = { {23, {Action::Function::Reduce, 61}}, {24, {Action::Function::Reduce, 61}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_52 = { {23, {Action::Function::Reduce, 62}}, {24, {Action::Function::Reduce, 62}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_53 = { {23, {Action::Function::Reduce, 63}}, {24, {Action::Function::Reduce, 63}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_54 = { {23, {Action::Function::Reduce, 64}}, {24, {Action::Function::Reduce, 64}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_55 = { {23, {Action::Function::Reduce, 65}}, {24, {Action::Function::Reduce, 65}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_56 = { {23, {Action::Function::Reduce, 66}}, {24, {Action::Function::Reduce, 66}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_57 = { {23, {Action::Function::Reduce, 67}}, {24, {Action::Function::Reduce, 67}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_58 = { {23, {Action::Function::Reduce, 68}}, {24, {Action::Function::Reduce, 68}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_59 = { {23, {Action::Function::Reduce, 69}}, {24, {Action::Function::Reduce, 69}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_60 = { {23, {Action::Function::Reduce, 70}}, {24, {Action::Function::Reduce, 70}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_61 = { {23, {Action::Function::Reduce, 71}}, {24, {Action::Function::Reduce, 71}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_62 = { {23, {Action::Function::Reduce, 72}}, {24, {Action::Function::Reduce, 72}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_63 = { {23, {Action::Function::Reduce, 73}}, {24, {Action::Function::Reduce, 73}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_64 = { {23, {Action::Function::Reduce, 74}}, {24, {Action::Function::Reduce, 74}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_65 = { {24, {Action::Function::Reduce, 10}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_66 = { {24, {Action::Function::Reduce, 75}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_67 = { {24, {Action::Function::Reduce, 76}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_68 = { {24, {Action::Function::Reduce, 59}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_69 = { {24, {Action::Function::Reduce, 60}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_70 = { {24, {Action::Function::Reduce, 61}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_71 = { {24, {Action::Function::Reduce, 62}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_72 = { {24, {Action::Function::Reduce, 63}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_73 = { {24, {Action::Function::Reduce, 64}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_74 = { {24, {Action::Function::Reduce, 65}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_75 = { {24, {Action::Function::Reduce, 66}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_76 = { {24, {Action::Function::Reduce, 67}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_77 = { {24, {Action::Function::Reduce, 68}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_78 = { {24, {Action::Function::Reduce, 69}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_79 = { {24, {Action::Function::Reduce, 70}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_80 = { {24, {Action::Function::Reduce, 71}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_81 = { {24, {Action::Function::Reduce, 72}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_82 = { {24, {Action::Function::Reduce, 73}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_83 = { {24, {Action::Function::Reduce, 74}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_84 = { {24, {Action::Function::Reduce, 11}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_85 = { {24, {Action::Function::Reduce, 12}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_86 = { {24, {Action::Function::Reduce, 13}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_87 = { {24, {Action::Function::Reduce, 14}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_88 = { {24, {Action::Function::Reduce, 15}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_89 = { {26, {Action::Function::Shift, 131}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_90 = { {24, {Action::Function::Reduce, 17}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_91 = { {24, {Action::Function::Reduce, 38}}, {29, {Action::Function::Reduce, 38}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_92 = { {5, {Action::Function::Shift, 95}}, {20, {Action::Function::Shift, 132}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_93 = { {24, {Action::Function::Shift, 134}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_94 = { {1, {Action::Function::Reduce, 41}}, {2, {Action::Function::Reduce, 41}}, {3, {Action::Function::Reduce, 41}}, {4, {Action::Function::Reduce, 41}}, {5, {Action::Function::Reduce, 41}}, {6, {Action::Function::Reduce, 41}}, {7, {Action::Function::Reduce, 41}}, {8, {Action::Function::Reduce, 41}}, {9, {Action::Function::Reduce, 41}}, {10, {Action::Function::Reduce, 41}}, {11, {Action::Function::Reduce, 41}}, {12, {Action::Function::Reduce, 41}}, {13, {Action::Function::Reduce, 41}}, {14, {Action::Function::Reduce, 41}}, {15, {Action::Function::Reduce, 41}}, {16, {Action::Function::Reduce, 41}}, {17, {Action::Function::Reduce, 41}}, {18, {Action::Function::Reduce, 41}}, {20, {Action::Function::Reduce, 41}}, {22, {Action::Function::Reduce, 41}}, {23, {Action::Function::Reduce, 41}}, {24, {Action::Function::Reduce, 41}}, {25, {Action::Function::Reduce, 41}}, {26, {Action::Function::Reduce, 41}}, {27, {Action::Function::Reduce, 41}}, {29, {Action::Function::Reduce, 41}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_95 = { {2, {Action::Function::Shift, 138}}, {3, {Action::Function::Shift, 139}}, {4, {Action::Function::Shift, 140}}, {5, {Action::Function::Shift, 141}}, {6, {Action::Function::Shift, 142}}, {7, {Action::Function::Shift, 143}}, {8, {Action::Function::Shift, 144}}, {9, {Action::Function::Shift, 146}}, {10, {Action::Function::Shift, 145}}, {11, {Action::Function::Shift, 147}}, {12, {Action::Function::Shift, 148}}, {13, {Action::Function::Shift, 149}}, {14, {Action::Function::Shift, 150}}, {15, {Action::Function::Shift, 151}}, {16, {Action::Function::Shift, 152}}, {18, {Action::Function::Shift, 153}}, {25, {Action::Function::Shift, 137}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_96 = { {1, {Action::Function::Reduce, 20}}, {2, {Action::Function::Reduce, 20}}, {3, {Action::Function::Reduce, 20}}, {4, {Action::Function::Reduce, 20}}, {5, {Action::Function::Reduce, 20}}, {6, {Action::Function::Reduce, 20}}, {7, {Action::Function::Reduce, 20}}, {8, {Action::Function::Reduce, 20}}, {9, {Action::Function::Reduce, 20}}, {10, {Action::Function::Reduce, 20}}, {11, {Action::Function::Reduce, 20}}, {12, {Action::Function::Reduce, 20}}, {13, {Action::Function::Reduce, 20}}, {14, {Action::Function::Reduce, 20}}, {15, {Action::Function::Reduce, 20}}, {16, {Action::Function::Reduce, 20}}, {17, {Action::Function::Reduce, 20}}, {18, {Action::Function::Reduce, 20}}, {20, {Action::Function::Reduce, 20}}, {22, {Action::Function::Reduce, 20}}, {23, {Action::Function::Reduce, 20}}, {24, {Action::Function::Reduce, 20}}, {25, {Action::Function::Reduce, 20}}, {26, {Action::Function::Reduce, 20}}, {27, {Action::Function::Reduce, 20}}, {29, {Action::Function::Reduce, 20}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_97 = { {2, {Action::Function::Shift, 103}}, {3, {Action::Function::Shift, 104}}, {4, {Action::Function::Shift, 105}}, {5, {Action::Function::Shift, 106}}, {6, {Action::Function::Shift, 107}}, {7, {Action::Function::Shift, 108}}, {8, {Action::Function::Shift, 109}}, {9, {Action::Function::Shift, 111}}, {10, {Action::Function::Shift, 110}}, {11, {Action::Function::Shift, 112}}, {12, {Action::Function::Shift, 113}}, {13, {Action::Function::Shift, 114}}, {14, {Action::Function::Shift, 115}}, {15, {Action::Function::Shift, 116}}, {16, {Action::Function::Shift, 117}}, {18, {Action::Function::Shift, 118}}, {24, {Action::Function::Reduce, 22}}, {25, {Action::Function::Shift, 102}}, {26, {Action::Function::Shift, 99}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_98 = { {1, {Action::Function::Reduce, 26}}, {2, {Action::Function::Reduce, 26}}, {3, {Action::Function::Reduce, 26}}, {4, {Action::Function::Reduce, 26}}, {5, {Action::Function::Reduce, 26}}, {6, {Action::Function::Reduce, 26}}, {7, {Action::Function::Reduce, 26}}, {8, {Action::Function::Reduce, 26}}, {9, {Action::Function::Reduce, 26}}, {10, {Action::Function::Reduce, 26}}, {11, {Action::Function::Reduce, 26}}, {12, {Action::Function::Reduce, 26}}, {13, {Action::Function::Reduce, 26}}, {14, {Action::Function::Reduce, 26}}, {15, {Action::Function::Reduce, 26}}, {16, {Action::Function::Reduce, 26}}, {17, {Action::Function::Reduce, 26}}, {18, {Action::Function::Reduce, 26}}, {22, {Action::Function::Reduce, 26}}, {23, {Action::Function::Reduce, 26}}, {24, {Action::Function::Reduce, 26}}, {25, {Action::Function::Reduce, 26}}, {26, {Action::Function::Reduce, 26}}, {27, {Action::Function::Reduce, 26}}, {29, {Action::Function::Reduce, 26}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_99 = { {1, {Action::Function::Reduce, 27}}, {2, {Action::Function::Reduce, 27}}, {3, {Action::Function::Reduce, 27}}, {4, {Action::Function::Reduce, 27}}, {5, {Action::Function::Reduce, 27}}, {6, {Action::Function::Reduce, 27}}, {7, {Action::Function::Reduce, 27}}, {8, {Action::Function::Reduce, 27}}, {9, {Action::Function::Reduce, 27}}, {10, {Action::Function::Reduce, 27}}, {11, {Action::Function::Reduce, 27}}, {12, {Action::Function::Reduce, 27}}, {13, {Action::Function::Reduce, 27}}, {14, {Action::Function::Reduce, 27}}, {15, {Action::Function::Reduce, 27}}, {16, {Action::Function::Reduce, 27}}, {17, {Action::Function::Reduce, 27}}, {18, {Action::Function::Reduce, 27}}, {22, {Action::Function::Reduce, 27}}, {23, {Action::Function::Reduce, 27}}, {24, {Action::Function::Reduce, 27}}, {25, {Action::Function::Reduce, 27}}, {26, {Action::Function::Reduce, 27}}, {27, {Action::Function::Reduce, 27}}, {29, {Action::Function::Reduce, 27}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_100 = { {1, {Action::Function::Reduce, 28}}, {2, {Action::Function::Reduce, 28}}, {3, {Action::Function::Reduce, 28}}, {4, {Action::Function::Reduce, 28}}, {5, {Action::Function::Reduce, 28}}, {6, {Action::Function::Reduce, 28}}, {7, {Action::Function::Reduce, 28}}, {8, {Action::Function::Reduce, 28}}, {9, {Action::Function::Reduce, 28}}, {10, {Action::Function::Reduce, 28}}, {11, {Action::Function::Reduce, 28}}, {12, {Action::Function::Reduce, 28}}, {13, {Action::Function::Reduce, 28}}, {14, {Action::Function::Reduce, 28}}, {15, {Action::Function::Reduce, 28}}, {16, {Action::Function::Reduce, 28}}, {17, {Action::Function::Reduce, 28}}, {18, {Action::Function::Reduce, 28}}, {22, {Action::Function::Reduce, 28}}, {23, {Action::Function::Reduce, 28}}, {24, {Action::Function::Reduce, 28}}, {25, {Action::Function::Reduce, 28}}, {26, {Action::Function::Reduce, 28}}, {27, {Action::Function::Reduce, 28}}, {29, {Action::Function::Reduce, 28}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_101 = { {1, {Action::Function::Reduce, 75}}, {2, {Action::Function::Reduce, 75}}, {3, {Action::Function::Reduce, 75}}, {4, {Action::Function::Reduce, 75}}, {5, {Action::Function::Reduce, 75}}, {6, {Action::Function::Reduce, 75}}, {7, {Action::Function::Reduce, 75}}, {8, {Action::Function::Reduce, 75}}, {9, {Action::Function::Reduce, 75}}, {10, {Action::Function::Reduce, 75}}, {11, {Action::Function::Reduce, 75}}, {12, {Action::Function::Reduce, 75}}, {13, {Action::Function::Reduce, 75}}, {14, {Action::Function::Reduce, 75}}, {15, {Action::Function::Reduce, 75}}, {16, {Action::Function::Reduce, 75}}, {17, {Action::Function::Reduce, 75}}, {18, {Action::Function::Reduce, 75}}, {22, {Action::Function::Reduce, 75}}, {23, {Action::Function::Reduce, 75}}, {24, {Action::Function::Reduce, 75}}, {25, {Action::Function::Reduce, 75}}, {26, {Action::Function::Reduce, 75}}, {27, {Action::Function::Reduce, 75}}, {29, {Action::Function::Reduce, 75}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_102 = { {1, {Action::Function::Reduce, 76}}, {2, {Action::Function::Reduce, 76}}, {3, {Action::Function::Reduce, 76}}, {4, {Action::Function::Reduce, 76}}, {5, {Action::Function::Reduce, 76}}, {6, {Action::Function::Reduce, 76}}, {7, {Action::Function::Reduce, 76}}, {8, {Action::Function::Reduce, 76}}, {9, {Action::Function::Reduce, 76}}, {10, {Action::Function::Reduce, 76}}, {11, {Action::Function::Reduce, 76}}, {12, {Action::Function::Reduce, 76}}, {13, {Action::Function::Reduce, 76}}, {14, {Action::Function::Reduce, 76}}, {15, {Action::Function::Reduce, 76}}, {16, {Action::Function::Reduce, 76}}, {17, {Action::Function::Reduce, 76}}, {18, {Action::Function::Reduce, 76}}, {22, {Action::Function::Reduce, 76}}, {23, {Action::Function::Reduce, 76}}, {24, {Action::Function::Reduce, 76}}, {25, {Action::Function::Reduce, 76}}, {26, {Action::Function::Reduce, 76}}, {27, {Action::Function::Reduce, 76}}, {29, {Action::Function::Reduce, 76}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_103 = { {1, {Action::Function::Reduce, 59}}, {2, {Action::Function::Reduce, 59}}, {3, {Action::Function::Reduce, 59}}, {4, {Action::Function::Reduce, 59}}, {5, {Action::Function::Reduce, 59}}, {6, {Action::Function::Reduce, 59}}, {7, {Action::Function::Reduce, 59}}, {8, {Action::Function::Reduce, 59}}, {9, {Action::Function::Reduce, 59}}, {10, {Action::Function::Reduce, 59}}, {11, {Action::Function::Reduce, 59}}, {12, {Action::Function::Reduce, 59}}, {13, {Action::Function::Reduce, 59}}, {14, {Action::Function::Reduce, 59}}, {15, {Action::Function::Reduce, 59}}, {16, {Action::Function::Reduce, 59}}, {17, {Action::Function::Reduce, 59}}, {18, {Action::Function::Reduce, 59}}, {22, {Action::Function::Reduce, 59}}, {23, {Action::Function::Reduce, 59}}, {24, {Action::Function::Reduce, 59}}, {25, {Action::Function::Reduce, 59}}, {26, {Action::Function::Reduce, 59}}, {27, {Action::Function::Reduce, 59}}, {29, {Action::Function::Reduce, 59}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_104 = { {1, {Action::Function::Reduce, 60}}, {2, {Action::Function::Reduce, 60}}, {3, {Action::Function::Reduce, 60}}, {4, {Action::Function::Reduce, 60}}, {5, {Action::Function::Reduce, 60}}, {6, {Action::Function::Reduce, 60}}, {7, {Action::Function::Reduce, 60}}, {8, {Action::Function::Reduce, 60}}, {9, {Action::Function::Reduce, 60}}, {10, {Action::Function::Reduce, 60}}, {11, {Action::Function::Reduce, 60}}, {12, {Action::Function::Reduce, 60}}, {13, {Action::Function::Reduce, 60}}, {14, {Action::Function::Reduce, 60}}, {15, {Action::Function::Reduce, 60}}, {16, {Action::Function::Reduce, 60}}, {17, {Action::Function::Reduce, 60}}, {18, {Action::Function::Reduce, 60}}, {22, {Action::Function::Reduce, 60}}, {23, {Action::Function::Reduce, 60}}, {24, {Action::Function::Reduce, 60}}, {25, {Action::Function::Reduce, 60}}, {26, {Action::Function::Reduce, 60}}, {27, {Action::Function::Reduce, 60}}, {29, {Action::Function::Reduce, 60}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_105 = { {1, {Action::Function::Reduce, 61}}, {2, {Action::Function::Reduce, 61}}, {3, {Action::Function::Reduce, 61}}, {4, {Action::Function::Reduce, 61}}, {5, {Action::Function::Reduce, 61}}, {6, {Action::Function::Reduce, 61}}, {7, {Action::Function::Reduce, 61}}, {8, {Action::Function::Reduce, 61}}, {9, {Action::Function::Reduce, 61}}, {10, {Action::Function::Reduce, 61}}, {11, {Action::Function::Reduce, 61}}, {12, {Action::Function::Reduce, 61}}, {13, {Action::Function::Reduce, 61}}, {14, {Action::Function::Reduce, 61}}, {15, {Action::Function::Reduce, 61}}, {16, {Action::Function::Reduce, 61}}, {17, {Action::Function::Reduce, 61}}, {18, {Action::Function::Reduce, 61}}, {22, {Action::Function::Reduce, 61}}, {23, {Action::Function::Reduce, 61}}, {24, {Action::Function::Reduce, 61}}, {25, {Action::Function::Reduce, 61}}, {26, {Action::Function::Reduce, 61}}, {27, {Action::Function::Reduce, 61}}, {29, {Action::Function::Reduce, 61}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_106 = { {1, {Action::Function::Reduce, 62}}, {2, {Action::Function::Reduce, 62}}, {3, {Action::Function::Reduce, 62}}, {4, {Action::Function::Reduce, 62}}, {5, {Action::Function::Reduce, 62}}, {6, {Action::Function::Reduce, 62}}, {7, {Action::Function::Reduce, 62}}, {8, {Action::Function::Reduce, 62}}, {9, {Action::Function::Reduce, 62}}, {10, {Action::Function::Reduce, 62}}, {11, {Action::Function::Reduce, 62}}, {12, {Action::Function::Reduce, 62}}, {13, {Action::Function::Reduce, 62}}, {14, {Action::Function::Reduce, 62}}, {15, {Action::Function::Reduce, 62}}, {16, {Action::Function::Reduce, 62}}, {17, {Action::Function::Reduce, 62}}, {18, {Action::Function::Reduce, 62}}, {22, {Action::Function::Reduce, 62}}, {23, {Action::Function::Reduce, 62}}, {24, {Action::Function::Reduce, 62}}, {25, {Action::Function::Reduce, 62}}, {26, {Action::Function::Reduce, 62}}, {27, {Action::Function::Reduce, 62}}, {29, {Action::Function::Reduce, 62}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_107 = { {1, {Action::Function::Reduce, 63}}, {2, {Action::Function::Reduce, 63}}, {3, {Action::Function::Reduce, 63}}, {4, {Action::Function::Reduce, 63}}, {5, {Action::Function::Reduce, 63}}, {6, {Action::Function::Reduce, 63}}, {7, {Action::Function::Reduce, 63}}, {8, {Action::Function::Reduce, 63}}, {9, {Action::Function::Reduce, 63}}, {10, {Action::Function::Reduce, 63}}, {11, {Action::Function::Reduce, 63}}, {12, {Action::Function::Reduce, 63}}, {13, {Action::Function::Reduce, 63}}, {14, {Action::Function::Reduce, 63}}, {15, {Action::Function::Reduce, 63}}, {16, {Action::Function::Reduce, 63}}, {17, {Action::Function::Reduce, 63}}, {18, {Action::Function::Reduce, 63}}, {22, {Action::Function::Reduce, 63}}, {23, {Action::Function::Reduce, 63}}, {24, {Action::Function::Reduce, 63}}, {25, {Action::Function::Reduce, 63}}, {26, {Action::Function::Reduce, 63}}, {27, {Action::Function::Reduce, 63}}, {29, {Action::Function::Reduce, 63}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_108 = { {1, {Action::Function::Reduce, 64}}, {2, {Action::Function::Reduce, 64}}, {3, {Action::Function::Reduce, 64}}, {4, {Action::Function::Reduce, 64}}, {5, {Action::Function::Reduce, 64}}, {6, {Action::Function::Reduce, 64}}, {7, {Action::Function::Reduce, 64}}, {8, {Action::Function::Reduce, 64}}, {9, {Action::Function::Reduce, 64}}, {10, {Action::Function::Reduce, 64}}, {11, {Action::Function::Reduce, 64}}, {12, {Action::Function::Reduce, 64}}, {13, {Action::Function::Reduce, 64}}, {14, {Action::Function::Reduce, 64}}, {15, {Action::Function::Reduce, 64}}, {16, {Action::Function::Reduce, 64}}, {17, {Action::Function::Reduce, 64}}, {18, {Action::Function::Reduce, 64}}, {22, {Action::Function::Reduce, 64}}, {23, {Action::Function::Reduce, 64}}, {24, {Action::Function::Reduce, 64}}, {25, {Action::Function::Reduce, 64}}, {26, {Action::Function::Reduce, 64}}, {27, {Action::Function::Reduce, 64}}, {29, {Action::Function::Reduce, 64}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_109 = { {1, {Action::Function::Reduce, 65}}, {2, {Action::Function::Reduce, 65}}, {3, {Action::Function::Reduce, 65}}, {4, {Action::Function::Reduce, 65}}, {5, {Action::Function::Reduce, 65}}, {6, {Action::Function::Reduce, 65}}, {7, {Action::Function::Reduce, 65}}, {8, {Action::Function::Reduce, 65}}, {9, {Action::Function::Reduce, 65}}, {10, {Action::Function::Reduce, 65}}, {11, {Action::Function::Reduce, 65}}, {12, {Action::Function::Reduce, 65}}, {13, {Action::Function::Reduce, 65}}, {14, {Action::Function::Reduce, 65}}, {15, {Action::Function::Reduce, 65}}, {16, {Action::Function::Reduce, 65}}, {17, {Action::Function::Reduce, 65}}, {18, {Action::Function::Reduce, 65}}, {22, {Action::Function::Reduce, 65}}, {23, {Action::Function::Reduce, 65}}, {24, {Action::Function::Reduce, 65}}, {25, {Action::Function::Reduce, 65}}, {26, {Action::Function::Reduce, 65}}, {27, {Action::Function::Reduce, 65}}, {29, {Action::Function::Reduce, 65}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_110 = { {1, {Action::Function::Reduce, 66}}, {2, {Action::Function::Reduce, 66}}, {3, {Action::Function::Reduce, 66}}, {4, {Action::Function::Reduce, 66}}, {5, {Action::Function::Reduce, 66}}, {6, {Action::Function::Reduce, 66}}, {7, {Action::Function::Reduce, 66}}, {8, {Action::Function::Reduce, 66}}, {9, {Action::Function::Reduce, 66}}, {10, {Action::Function::Reduce, 66}}, {11, {Action::Function::Reduce, 66}}, {12, {Action::Function::Reduce, 66}}, {13, {Action::Function::Reduce, 66}}, {14, {Action::Function::Reduce, 66}}, {15, {Action::Function::Reduce, 66}}, {16, {Action::Function::Reduce, 66}}, {17, {Action::Function::Reduce, 66}}, {18, {Action::Function::Reduce, 66}}, {22, {Action::Function::Reduce, 66}}, {23, {Action::Function::Reduce, 66}}, {24, {Action::Function::Reduce, 66}}, {25, {Action::Function::Reduce, 66}}, {26, {Action::Function::Reduce, 66}}, {27, {Action::Function::Reduce, 66}}, {29, {Action::Function::Reduce, 66}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_111 = { {1, {Action::Function::Reduce, 67}}, {2, {Action::Function::Reduce, 67}}, {3, {Action::Function::Reduce, 67}}, {4, {Action::Function::Reduce, 67}}, {5, {Action::Function::Reduce, 67}}, {6, {Action::Function::Reduce, 67}}, {7, {Action::Function::Reduce, 67}}, {8, {Action::Function::Reduce, 67}}, {9, {Action::Function::Reduce, 67}}, {10, {Action::Function::Reduce, 67}}, {11, {Action::Function::Reduce, 67}}, {12, {Action::Function::Reduce, 67}}, {13, {Action::Function::Reduce, 67}}, {14, {Action::Function::Reduce, 67}}, {15, {Action::Function::Reduce, 67}}, {16, {Action::Function::Reduce, 67}}, {17, {Action::Function::Reduce, 67}}, {18, {Action::Function::Reduce, 67}}, {22, {Action::Function::Reduce, 67}}, {23, {Action::Function::Reduce, 67}}, {24, {Action::Function::Reduce, 67}}, {25, {Action::Function::Reduce, 67}}, {26, {Action::Function::Reduce, 67}}, {27, {Action::Function::Reduce, 67}}, {29, {Action::Function::Reduce, 67}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_112 = { {1, {Action::Function::Reduce, 68}}, {2, {Action::Function::Reduce, 68}}, {3, {Action::Function::Reduce, 68}}, {4, {Action::Function::Reduce, 68}}, {5, {Action::Function::Reduce, 68}}, {6, {Action::Function::Reduce, 68}}, {7, {Action::Function::Reduce, 68}}, {8, {Action::Function::Reduce, 68}}, {9, {Action::Function::Reduce, 68}}, {10, {Action::Function::Reduce, 68}}, {11, {Action::Function::Reduce, 68}}, {12, {Action::Function::Reduce, 68}}, {13, {Action::Function::Reduce, 68}}, {14, {Action::Function::Reduce, 68}}, {15, {Action::Function::Reduce, 68}}, {16, {Action::Function::Reduce, 68}}, {17, {Action::Function::Reduce, 68}}, {18, {Action::Function::Reduce, 68}}, {22, {Action::Function::Reduce, 68}}, {23, {Action::Function::Reduce, 68}}, {24, {Action::Function::Reduce, 68}}, {25, {Action::Function::Reduce, 68}}, {26, {Action::Function::Reduce, 68}}, {27, {Action::Function::Reduce, 68}}, {29, {Action::Function::Reduce, 68}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_113 = { {1, {Action::Function::Reduce, 69}}, {2, {Action::Function::Reduce, 69}}, {3, {Action::Function::Reduce, 69}}, {4, {Action::Function::Reduce, 69}}, {5, {Action::Function::Reduce, 69}}, {6, {Action::Function::Reduce, 69}}, {7, {Action::Function::Reduce, 69}}, {8, {Action::Function::Reduce, 69}}, {9, {Action::Function::Reduce, 69}}, {10, {Action::Function::Reduce, 69}}, {11, {Action::Function::Reduce, 69}}, {12, {Action::Function::Reduce, 69}}, {13, {Action::Function::Reduce, 69}}, {14, {Action::Function::Reduce, 69}}, {15, {Action::Function::Reduce, 69}}, {16, {Action::Function::Reduce, 69}}, {17, {Action::Function::Reduce, 69}}, {18, {Action::Function::Reduce, 69}}, {22, {Action::Function::Reduce, 69}}, {23, {Action::Function::Reduce, 69}}, {24, {Action::Function::Reduce, 69}}, {25, {Action::Function::Reduce, 69}}, {26, {Action::Function::Reduce, 69}}, {27, {Action::Function::Reduce, 69}}, {29, {Action::Function::Reduce, 69}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_114 = { {1, {Action::Function::Reduce, 70}}, {2, {Action::Function::Reduce, 70}}, {3, {Action::Function::Reduce, 70}}, {4, {Action::Function::Reduce, 70}}, {5, {Action::Function::Reduce, 70}}, {6, {Action::Function::Reduce, 70}}, {7, {Action::Function::Reduce, 70}}, {8, {Action::Function::Reduce, 70}}, {9, {Action::Function::Reduce, 70}}, {10, {Action::Function::Reduce, 70}}, {11, {Action::Function::Reduce, 70}}, {12, {Action::Function::Reduce, 70}}, {13, {Action::Function::Reduce, 70}}, {14, {Action::Function::Reduce, 70}}, {15, {Action::Function::Reduce, 70}}, {16, {Action::Function::Reduce, 70}}, {17, {Action::Function::Reduce, 70}}, {18, {Action::Function::Reduce, 70}}, {22, {Action::Function::Reduce, 70}}, {23, {Action::Function::Reduce, 70}}, {24, {Action::Function::Reduce, 70}}, {25, {Action::Function::Reduce, 70}}, {26, {Action::Function::Reduce, 70}}, {27, {Action::Function::Reduce, 70}}, {29, {Action::Function::Reduce, 70}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_115 = { {1, {Action::Function::Reduce, 71}}, {2, {Action::Function::Reduce, 71}}, {3, {Action::Function::Reduce, 71}}, {4, {Action::Function::Reduce, 71}}, {5, {Action::Function::Reduce, 71}}, {6, {Action::Function::Reduce, 71}}, {7, {Action::Function::Reduce, 71}}, {8, {Action::Function::Reduce, 71}}, {9, {Action::Function::Reduce, 71}}, {10, {Action::Function::Reduce, 71}}, {11, {Action::Function::Reduce, 71}}, {12, {Action::Function::Reduce, 71}}, {13, {Action::Function::Reduce, 71}}, {14, {Action::Function::Reduce, 71}}, {15, {Action::Function::Reduce, 71}}, {16, {Action::Function::Reduce, 71}}, {17, {Action::Function::Reduce, 71}}, {18, {Action::Function::Reduce, 71}}, {22, {Action::Function::Reduce, 71}}, {23, {Action::Function::Reduce, 71}}, {24, {Action::Function::Reduce, 71}}, {25, {Action::Function::Reduce, 71}}, {26, {Action::Function::Reduce, 71}}, {27, {Action::Function::Reduce, 71}}, {29, {Action::Function::Reduce, 71}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_116 = { {1, {Action::Function::Reduce, 72}}, {2, {Action::Function::Reduce, 72}}, {3, {Action::Function::Reduce, 72}}, {4, {Action::Function::Reduce, 72}}, {5, {Action::Function::Reduce, 72}}, {6, {Action::Function::Reduce, 72}}, {7, {Action::Function::Reduce, 72}}, {8, {Action::Function::Reduce, 72}}, {9, {Action::Function::Reduce, 72}}, {10, {Action::Function::Reduce, 72}}, {11, {Action::Function::Reduce, 72}}, {12, {Action::Function::Reduce, 72}}, {13, {Action::Function::Reduce, 72}}, {14, {Action::Function::Reduce, 72}}, {15, {Action::Function::Reduce, 72}}, {16, {Action::Function::Reduce, 72}}, {17, {Action::Function::Reduce, 72}}, {18, {Action::Function::Reduce, 72}}, {22, {Action::Function::Reduce, 72}}, {23, {Action::Function::Reduce, 72}}, {24, {Action::Function::Reduce, 72}}, {25, {Action::Function::Reduce, 72}}, {26, {Action::Function::Reduce, 72}}, {27, {Action::Function::Reduce, 72}}, {29, {Action::Function::Reduce, 72}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_117 = { {1, {Action::Function::Reduce, 73}}, {2, {Action::Function::Reduce, 73}}, {3, {Action::Function::Reduce, 73}}, {4, {Action::Function::Reduce, 73}}, {5, {Action::Function::Reduce, 73}}, {6, {Action::Function::Reduce, 73}}, {7, {Action::Function::Reduce, 73}}, {8, {Action::Function::Reduce, 73}}, {9, {Action::Function::Reduce, 73}}, {10, {Action::Function::Reduce, 73}}, {11, {Action::Function::Reduce, 73}}, {12, {Action::Function::Reduce, 73}}, {13, {Action::Function::Reduce, 73}}, {14, {Action::Function::Reduce, 73}}, {15, {Action::Function::Reduce, 73}}, {16, {Action::Function::Reduce, 73}}, {17, {Action::Function::Reduce, 73}}, {18, {Action::Function::Reduce, 73}}, {22, {Action::Function::Reduce, 73}}, {23, {Action::Function::Reduce, 73}}, {24, {Action::Function::Reduce, 73}}, {25, {Action::Function::Reduce, 73}}, {26, {Action::Function::Reduce, 73}}, {27, {Action::Function::Reduce, 73}}, {29, {Action::Function::Reduce, 73}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_118 = { {1, {Action::Function::Reduce, 74}}, {2, {Action::Function::Reduce, 74}}, {3, {Action::Function::Reduce, 74}}, {4, {Action::Function::Reduce, 74}}, {5, {Action::Function::Reduce, 74}}, {6, {Action::Function::Reduce, 74}}, {7, {Action::Function::Reduce, 74}}, {8, {Action::Function::Reduce, 74}}, {9, {Action::Function::Reduce, 74}}, {10, {Action::Function::Reduce, 74}}, {11, {Action::Function::Reduce, 74}}, {12, {Action::Function::Reduce, 74}}, {13, {Action::Function::Reduce, 74}}, {14, {Action::Function::Reduce, 74}}, {15, {Action::Function::Reduce, 74}}, {16, {Action::Function::Reduce, 74}}, {17, {Action::Function::Reduce, 74}}, {18, {Action::Function::Reduce, 74}}, {22, {Action::Function::Reduce, 74}}, {23, {Action::Function::Reduce, 74}}, {24, {Action::Function::Reduce, 74}}, {25, {Action::Function::Reduce, 74}}, {26, {Action::Function::Reduce, 74}}, {27, {Action::Function::Reduce, 74}}, {29, {Action::Function::Reduce, 74}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_119 = { {2, {Action::Function::Shift, 103}}, {3, {Action::Function::Shift, 104}}, {4, {Action::Function::Shift, 105}}, {5, {Action::Function::Shift, 106}}, {6, {Action::Function::Shift, 107}}, {7, {Action::Function::Shift, 108}}, {8, {Action::Function::Shift, 109}}, {9, {Action::Function::Shift, 111}}, {10, {Action::Function::Shift, 110}}, {11, {Action::Function::Shift, 112}}, {12, {Action::Function::Shift, 113}}, {13, {Action::Function::Shift, 114}}, {14, {Action::Function::Shift, 115}}, {15, {Action::Function::Shift, 116}}, {16, {Action::Function::Shift, 117}}, {18, {Action::Function::Shift, 118}}, {24, {Action::Function::Reduce, 23}}, {25, {Action::Function::Shift, 102}}, {26, {Action::Function::Shift, 121}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_120 = { {1, {Action::Function::Reduce, 30}}, {2, {Action::Function::Reduce, 30}}, {3, {Action::Function::Reduce, 30}}, {4, {Action::Function::Reduce, 30}}, {5, {Action::Function::Reduce, 30}}, {6, {Action::Function::Reduce, 30}}, {7, {Action::Function::Reduce, 30}}, {8, {Action::Function::Reduce, 30}}, {9, {Action::Function::Reduce, 30}}, {10, {Action::Function::Reduce, 30}}, {11, {Action::Function::Reduce, 30}}, {12, {Action::Function::Reduce, 30}}, {13, {Action::Function::Reduce, 30}}, {14, {Action::Function::Reduce, 30}}, {15, {Action::Function::Reduce, 30}}, {16, {Action::Function::Reduce, 30}}, {17, {Action::Function::Reduce, 30}}, {18, {Action::Function::Reduce, 30}}, {22, {Action::Function::Reduce, 30}}, {23, {Action::Function::Reduce, 30}}, {24, {Action::Function::Reduce, 30}}, {25, {Action::Function::Reduce, 30}}, {26, {Action::Function::Reduce, 30}}, {27, {Action::Function::Reduce, 30}}, {29, {Action::Function::Reduce, 30}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_121 = { {1, {Action::Function::Reduce, 31}}, {2, {Action::Function::Reduce, 31}}, {3, {Action::Function::Reduce, 31}}, {4, {Action::Function::Reduce, 31}}, {5, {Action::Function::Reduce, 31}}, {6, {Action::Function::Reduce, 31}}, {7, {Action::Function::Reduce, 31}}, {8, {Action::Function::Reduce, 31}}, {9, {Action::Function::Reduce, 31}}, {10, {Action::Function::Reduce, 31}}, {11, {Action::Function::Reduce, 31}}, {12, {Action::Function::Reduce, 31}}, {13, {Action::Function::Reduce, 31}}, {14, {Action::Function::Reduce, 31}}, {15, {Action::Function::Reduce, 31}}, {16, {Action::Function::Reduce, 31}}, {17, {Action::Function::Reduce, 31}}, {18, {Action::Function::Reduce, 31}}, {22, {Action::Function::Reduce, 31}}, {23, {Action::Function::Reduce, 31}}, {24, {Action::Function::Reduce, 31}}, {25, {Action::Function::Reduce, 31}}, {26, {Action::Function::Reduce, 31}}, {27, {Action::Function::Reduce, 31}}, {29, {Action::Function::Reduce, 31}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_122 = { {1, {Action::Function::Reduce, 32}}, {2, {Action::Function::Reduce, 32}}, {3, {Action::Function::Reduce, 32}}, {4, {Action::Function::Reduce, 32}}, {5, {Action::Function::Reduce, 32}}, {6, {Action::Function::Reduce, 32}}, {7, {Action::Function::Reduce, 32}}, {8, {Action::Function::Reduce, 32}}, {9, {Action::Function::Reduce, 32}}, {10, {Action::Function::Reduce, 32}}, {11, {Action::Function::Reduce, 32}}, {12, {Action::Function::Reduce, 32}}, {13, {Action::Function::Reduce, 32}}, {14, {Action::Function::Reduce, 32}}, {15, {Action::Function::Reduce, 32}}, {16, {Action::Function::Reduce, 32}}, {17, {Action::Function::Reduce, 32}}, {18, {Action::Function::Reduce, 32}}, {22, {Action::Function::Reduce, 32}}, {23, {Action::Function::Reduce, 32}}, {24, {Action::Function::Reduce, 32}}, {25, {Action::Function::Reduce, 32}}, {26, {Action::Function::Reduce, 32}}, {27, {Action::Function::Reduce, 32}}, {29, {Action::Function::Reduce, 32}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_123 = { {2, {Action::Function::Shift, 103}}, {3, {Action::Function::Shift, 104}}, {4, {Action::Function::Shift, 105}}, {5, {Action::Function::Shift, 106}}, {6, {Action::Function::Shift, 107}}, {7, {Action::Function::Shift, 108}}, {8, {Action::Function::Shift, 109}}, {9, {Action::Function::Shift, 111}}, {10, {Action::Function::Shift, 110}}, {11, {Action::Function::Shift, 112}}, {12, {Action::Function::Shift, 113}}, {13, {Action::Function::Shift, 114}}, {14, {Action::Function::Shift, 115}}, {15, {Action::Function::Shift, 116}}, {16, {Action::Function::Shift, 117}}, {18, {Action::Function::Shift, 118}}, {24, {Action::Function::Reduce, 24}}, {25, {Action::Function::Shift, 102}}, {26, {Action::Function::Shift, 125}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_124 = { {1, {Action::Function::Reduce, 34}}, {2, {Action::Function::Reduce, 34}}, {3, {Action::Function::Reduce, 34}}, {4, {Action::Function::Reduce, 34}}, {5, {Action::Function::Reduce, 34}}, {6, {Action::Function::Reduce, 34}}, {7, {Action::Function::Reduce, 34}}, {8, {Action::Function::Reduce, 34}}, {9, {Action::Function::Reduce, 34}}, {10, {Action::Function::Reduce, 34}}, {11, {Action::Function::Reduce, 34}}, {12, {Action::Function::Reduce, 34}}, {13, {Action::Function::Reduce, 34}}, {14, {Action::Function::Reduce, 34}}, {15, {Action::Function::Reduce, 34}}, {16, {Action::Function::Reduce, 34}}, {17, {Action::Function::Reduce, 34}}, {18, {Action::Function::Reduce, 34}}, {22, {Action::Function::Reduce, 34}}, {23, {Action::Function::Reduce, 34}}, {24, {Action::Function::Reduce, 34}}, {25, {Action::Function::Reduce, 34}}, {26, {Action::Function::Reduce, 34}}, {27, {Action::Function::Reduce, 34}}, {29, {Action::Function::Reduce, 34}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_125 = { {1, {Action::Function::Reduce, 35}}, {2, {Action::Function::Reduce, 35}}, {3, {Action::Function::Reduce, 35}}, {4, {Action::Function::Reduce, 35}}, {5, {Action::Function::Reduce, 35}}, {6, {Action::Function::Reduce, 35}}, {7, {Action::Function::Reduce, 35}}, {8, {Action::Function::Reduce, 35}}, {9, {Action::Function::Reduce, 35}}, {10, {Action::Function::Reduce, 35}}, {11, {Action::Function::Reduce, 35}}, {12, {Action::Function::Reduce, 35}}, {13, {Action::Function::Reduce, 35}}, {14, {Action::Function::Reduce, 35}}, {15, {Action::Function::Reduce, 35}}, {16, {Action::Function::Reduce, 35}}, {17, {Action::Function::Reduce, 35}}, {18, {Action::Function::Reduce, 35}}, {22, {Action::Function::Reduce, 35}}, {23, {Action::Function::Reduce, 35}}, {24, {Action::Function::Reduce, 35}}, {25, {Action::Function::Reduce, 35}}, {26, {Action::Function::Reduce, 35}}, {27, {Action::Function::Reduce, 35}}, {29, {Action::Function::Reduce, 35}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_126 = { {1, {Action::Function::Reduce, 36}}, {2, {Action::Function::Reduce, 36}}, {3, {Action::Function::Reduce, 36}}, {4, {Action::Function::Reduce, 36}}, {5, {Action::Function::Reduce, 36}}, {6, {Action::Function::Reduce, 36}}, {7, {Action::Function::Reduce, 36}}, {8, {Action::Function::Reduce, 36}}, {9, {Action::Function::Reduce, 36}}, {10, {Action::Function::Reduce, 36}}, {11, {Action::Function::Reduce, 36}}, {12, {Action::Function::Reduce, 36}}, {13, {Action::Function::Reduce, 36}}, {14, {Action::Function::Reduce, 36}}, {15, {Action::Function::Reduce, 36}}, {16, {Action::Function::Reduce, 36}}, {17, {Action::Function::Reduce, 36}}, {18, {Action::Function::Reduce, 36}}, {22, {Action::Function::Reduce, 36}}, {23, {Action::Function::Reduce, 36}}, {24, {Action::Function::Reduce, 36}}, {25, {Action::Function::Reduce, 36}}, {26, {Action::Function::Reduce, 36}}, {27, {Action::Function::Reduce, 36}}, {29, {Action::Function::Reduce, 36}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_127 = { {1, {Action::Function::Reduce, 2}}, {2, {Action::Function::Reduce, 2}}, {3, {Action::Function::Reduce, 2}}, {4, {Action::Function::Reduce, 2}}, {5, {Action::Function::Reduce, 2}}, {6, {Action::Function::Reduce, 2}}, {7, {Action::Function::Reduce, 2}}, {8, {Action::Function::Reduce, 2}}, {9, {Action::Function::Reduce, 2}}, {10, {Action::Function::Reduce, 2}}, {11, {Action::Function::Reduce, 2}}, {12, {Action::Function::Reduce, 2}}, {13, {Action::Function::Reduce, 2}}, {14, {Action::Function::Reduce, 2}}, {15, {Action::Function::Reduce, 2}}, {16, {Action::Function::Reduce, 2}}, {17, {Action::Function::Reduce, 2}}, {18, {Action::Function::Reduce, 2}}, {20, {Action::Function::Reduce, 2}}, {22, {Action::Function::Reduce, 2}}, {23, {Action::Function::Reduce, 2}}, {24, {Action::Function::Reduce, 2}}, {25, {Action::Function::Reduce, 2}}, {26, {Action::Function::Reduce, 2}}, {27, {Action::Function::Reduce, 2}}, {29, {Action::Function::Reduce, 2}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_128 = { {2, {Action::Function::Shift, 160}}, {3, {Action::Function::Shift, 161}}, {4, {Action::Function::Shift, 162}}, {5, {Action::Function::Shift, 163}}, {6, {Action::Function::Shift, 164}}, {7, {Action::Function::Shift, 165}}, {8, {Action::Function::Shift, 166}}, {9, {Action::Function::Shift, 168}}, {10, {Action::Function::Shift, 167}}, {11, {Action::Function::Shift, 169}}, {12, {Action::Function::Shift, 170}}, {13, {Action::Function::Shift, 171}}, {14, {Action::Function::Shift, 172}}, {15, {Action::Function::Shift, 173}}, {16, {Action::Function::Shift, 174}}, {18, {Action::Function::Shift, 175}}, {25, {Action::Function::Shift, 159}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_129 = { {24, {Action::Function::Reduce, 6}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_130 = { {24, {Action::Function::Reduce, 16}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_131 = { {1, {Action::Function::Reduce, 39}}, {29, {Action::Function::Reduce, 39}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_132 = { {1, {Action::Function::Reduce, 40}}, {2, {Action::Function::Reduce, 40}}, {3, {Action::Function::Reduce, 40}}, {4, {Action::Function::Reduce, 40}}, {5, {Action::Function::Reduce, 40}}, {6, {Action::Function::Reduce, 40}}, {7, {Action::Function::Reduce, 40}}, {8, {Action::Function::Reduce, 40}}, {9, {Action::Function::Reduce, 40}}, {10, {Action::Function::Reduce, 40}}, {11, {Action::Function::Reduce, 40}}, {12, {Action::Function::Reduce, 40}}, {13, {Action::Function::Reduce, 40}}, {14, {Action::Function::Reduce, 40}}, {15, {Action::Function::Reduce, 40}}, {16, {Action::Function::Reduce, 40}}, {17, {Action::Function::Reduce, 40}}, {18, {Action::Function::Reduce, 40}}, {20, {Action::Function::Reduce, 40}}, {22, {Action::Function::Reduce, 40}}, {23, {Action::Function::Reduce, 40}}, {24, {Action::Function::Reduce, 40}}, {25, {Action::Function::Reduce, 40}}, {26, {Action::Function::Reduce, 40}}, {27, {Action::Function::Reduce, 40}}, {29, {Action::Function::Reduce, 40}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_133 = { {1, {Action::Function::Reduce, 19}}, {2, {Action::Function::Reduce, 19}}, {3, {Action::Function::Reduce, 19}}, {4, {Action::Function::Reduce, 19}}, {5, {Action::Function::Reduce, 19}}, {6, {Action::Function::Reduce, 19}}, {7, {Action::Function::Reduce, 19}}, {8, {Action::Function::Reduce, 19}}, {9, {Action::Function::Reduce, 19}}, {10, {Action::Function::Reduce, 19}}, {11, {Action::Function::Reduce, 19}}, {12, {Action::Function::Reduce, 19}}, {13, {Action::Function::Reduce, 19}}, {14, {Action::Function::Reduce, 19}}, {15, {Action::Function::Reduce, 19}}, {16, {Action::Function::Reduce, 19}}, {17, {Action::Function::Reduce, 19}}, {18, {Action::Function::Reduce, 19}}, {20, {Action::Function::Reduce, 19}}, {22, {Action::Function::Reduce, 19}}, {23, {Action::Function::Reduce, 19}}, {24, {Action::Function::Reduce, 19}}, {25, {Action::Function::Reduce, 19}}, {26, {Action::Function::Reduce, 19}}, {27, {Action::Function::Reduce, 19}}, {29, {Action::Function::Reduce, 19}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_134 = { {21, {Action::Function::Shift, 179}}, {23, {Action::Function::Shift, 180}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_135 = { {21, {Action::Function::Reduce, 75}}, {23, {Action::Function::Reduce, 75}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_136 = { {21, {Action::Function::Reduce, 76}}, {23, {Action::Function::Reduce, 76}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_137 = { {21, {Action::Function::Reduce, 59}}, {23, {Action::Function::Reduce, 59}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_138 = { {21, {Action::Function::Reduce, 60}}, {23, {Action::Function::Reduce, 60}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_139 = { {21, {Action::Function::Reduce, 61}}, {23, {Action::Function::Reduce, 61}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_140 = { {21, {Action::Function::Reduce, 62}}, {23, {Action::Function::Reduce, 62}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_141 = { {21, {Action::Function::Reduce, 63}}, {23, {Action::Function::Reduce, 63}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_142 = { {21, {Action::Function::Reduce, 64}}, {23, {Action::Function::Reduce, 64}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_143 = { {21, {Action::Function::Reduce, 65}}, {23, {Action::Function::Reduce, 65}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_144 = { {21, {Action::Function::Reduce, 66}}, {23, {Action::Function::Reduce, 66}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_145 = { {21, {Action::Function::Reduce, 67}}, {23, {Action::Function::Reduce, 67}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_146 = { {21, {Action::Function::Reduce, 68}}, {23, {Action::Function::Reduce, 68}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_147 = { {21, {Action::Function::Reduce, 69}}, {23, {Action::Function::Reduce, 69}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_148 = { {21, {Action::Function::Reduce, 70}}, {23, {Action::Function::Reduce, 70}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_149 = { {21, {Action::Function::Reduce, 71}}, {23, {Action::Function::Reduce, 71}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_150 = { {21, {Action::Function::Reduce, 72}}, {23, {Action::Function::Reduce, 72}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_151 = { {21, {Action::Function::Reduce, 73}}, {23, {Action::Function::Reduce, 73}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_152 = { {21, {Action::Function::Reduce, 74}}, {23, {Action::Function::Reduce, 74}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_153 = { {1, {Action::Function::Reduce, 25}}, {2, {Action::Function::Reduce, 25}}, {3, {Action::Function::Reduce, 25}}, {4, {Action::Function::Reduce, 25}}, {5, {Action::Function::Reduce, 25}}, {6, {Action::Function::Reduce, 25}}, {7, {Action::Function::Reduce, 25}}, {8, {Action::Function::Reduce, 25}}, {9, {Action::Function::Reduce, 25}}, {10, {Action::Function::Reduce, 25}}, {11, {Action::Function::Reduce, 25}}, {12, {Action::Function::Reduce, 25}}, {13, {Action::Function::Reduce, 25}}, {14, {Action::Function::Reduce, 25}}, {15, {Action::Function::Reduce, 25}}, {16, {Action::Function::Reduce, 25}}, {17, {Action::Function::Reduce, 25}}, {18, {Action::Function::Reduce, 25}}, {22, {Action::Function::Reduce, 25}}, {23, {Action::Function::Reduce, 25}}, {24, {Action::Function::Reduce, 25}}, {25, {Action::Function::Reduce, 25}}, {26, {Action::Function::Reduce, 25}}, {27, {Action::Function::Reduce, 25}}, {29, {Action::Function::Reduce, 25}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_154 = { {1, {Action::Function::Reduce, 29}}, {2, {Action::Function::Reduce, 29}}, {3, {Action::Function::Reduce, 29}}, {4, {Action::Function::Reduce, 29}}, {5, {Action::Function::Reduce, 29}}, {6, {Action::Function::Reduce, 29}}, {7, {Action::Function::Reduce, 29}}, {8, {Action::Function::Reduce, 29}}, {9, {Action::Function::Reduce, 29}}, {10, {Action::Function::Reduce, 29}}, {11, {Action::Function::Reduce, 29}}, {12, {Action::Function::Reduce, 29}}, {13, {Action::Function::Reduce, 29}}, {14, {Action::Function::Reduce, 29}}, {15, {Action::Function::Reduce, 29}}, {16, {Action::Function::Reduce, 29}}, {17, {Action::Function::Reduce, 29}}, {18, {Action::Function::Reduce, 29}}, {22, {Action::Function::Reduce, 29}}, {23, {Action::Function::Reduce, 29}}, {24, {Action::Function::Reduce, 29}}, {25, {Action::Function::Reduce, 29}}, {26, {Action::Function::Reduce, 29}}, {27, {Action::Function::Reduce, 29}}, {29, {Action::Function::Reduce, 29}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_155 = { {1, {Action::Function::Reduce, 33}}, {2, {Action::Function::Reduce, 33}}, {3, {Action::Function::Reduce, 33}}, {4, {Action::Function::Reduce, 33}}, {5, {Action::Function::Reduce, 33}}, {6, {Action::Function::Reduce, 33}}, {7, {Action::Function::Reduce, 33}}, {8, {Action::Function::Reduce, 33}}, {9, {Action::Function::Reduce, 33}}, {10, {Action::Function::Reduce, 33}}, {11, {Action::Function::Reduce, 33}}, {12, {Action::Function::Reduce, 33}}, {13, {Action::Function::Reduce, 33}}, {14, {Action::Function::Reduce, 33}}, {15, {Action::Function::Reduce, 33}}, {16, {Action::Function::Reduce, 33}}, {17, {Action::Function::Reduce, 33}}, {18, {Action::Function::Reduce, 33}}, {22, {Action::Function::Reduce, 33}}, {23, {Action::Function::Reduce, 33}}, {24, {Action::Function::Reduce, 33}}, {25, {Action::Function::Reduce, 33}}, {26, {Action::Function::Reduce, 33}}, {27, {Action::Function::Reduce, 33}}, {29, {Action::Function::Reduce, 33}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_156 = { {24, {Action::Function::Reduce, 5}}, {26, {Action::Function::Shift, 181}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_157 = { {24, {Action::Function::Reduce, 75}}, {26, {Action::Function::Reduce, 75}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_158 = { {24, {Action::Function::Reduce, 76}}, {26, {Action::Function::Reduce, 76}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_159 = { {24, {Action::Function::Reduce, 59}}, {26, {Action::Function::Reduce, 59}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_160 = { {24, {Action::Function::Reduce, 60}}, {26, {Action::Function::Reduce, 60}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_161 = { {24, {Action::Function::Reduce, 61}}, {26, {Action::Function::Reduce, 61}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_162 = { {24, {Action::Function::Reduce, 62}}, {26, {Action::Function::Reduce, 62}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_163 = { {24, {Action::Function::Reduce, 63}}, {26, {Action::Function::Reduce, 63}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_164 = { {24, {Action::Function::Reduce, 64}}, {26, {Action::Function::Reduce, 64}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_165 = { {24, {Action::Function::Reduce, 65}}, {26, {Action::Function::Reduce, 65}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_166 = { {24, {Action::Function::Reduce, 66}}, {26, {Action::Function::Reduce, 66}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_167 = { {24, {Action::Function::Reduce, 67}}, {26, {Action::Function::Reduce, 67}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_168 = { {24, {Action::Function::Reduce, 68}}, {26, {Action::Function::Reduce, 68}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_169 = { {24, {Action::Function::Reduce, 69}}, {26, {Action::Function::Reduce, 69}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_170 = { {24, {Action::Function::Reduce, 70}}, {26, {Action::Function::Reduce, 70}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_171 = { {24, {Action::Function::Reduce, 71}}, {26, {Action::Function::Reduce, 71}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_172 = { {24, {Action::Function::Reduce, 72}}, {26, {Action::Function::Reduce, 72}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_173 = { {24, {Action::Function::Reduce, 73}}, {26, {Action::Function::Reduce, 73}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_174 = { {24, {Action::Function::Reduce, 74}}, {26, {Action::Function::Reduce, 74}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_175 = { {24, {Action::Function::Reduce, 9}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_176 = { {1, {Action::Function::Reduce, 1}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_177 = { {1, {Action::Function::Reduce, 37}}, {29, {Action::Function::Shift, 182}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_178 = { {2, {Action::Function::Shift, 195}}, {3, {Action::Function::Shift, 196}}, {4, {Action::Function::Shift, 197}}, {5, {Action::Function::Shift, 198}}, {6, {Action::Function::Shift, 199}}, {7, {Action::Function::Shift, 200}}, {8, {Action::Function::Shift, 201}}, {9, {Action::Function::Shift, 203}}, {10, {Action::Function::Shift, 202}}, {11, {Action::Function::Shift, 204}}, {12, {Action::Function::Shift, 205}}, {13, {Action::Function::Shift, 206}}, {14, {Action::Function::Shift, 207}}, {15, {Action::Function::Shift, 208}}, {16, {Action::Function::Shift, 209}}, {17, {Action::Function::Shift, 194}}, {18, {Action::Function::Shift, 186}}, {22, {Action::Function::Reduce, 50}}, {24, {Action::Function::Reduce, 50}}, {25, {Action::Function::Shift, 192}}, {26, {Action::Function::Shift, 193}}, {27, {Action::Function::Shift, 187}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_179 = { {2, {Action::Function::Shift, 213}}, {3, {Action::Function::Shift, 214}}, {4, {Action::Function::Shift, 215}}, {5, {Action::Function::Shift, 216}}, {6, {Action::Function::Shift, 217}}, {7, {Action::Function::Shift, 218}}, {8, {Action::Function::Shift, 219}}, {9, {Action::Function::Shift, 221}}, {10, {Action::Function::Shift, 220}}, {11, {Action::Function::Shift, 222}}, {12, {Action::Function::Shift, 223}}, {13, {Action::Function::Shift, 224}}, {14, {Action::Function::Shift, 225}}, {15, {Action::Function::Shift, 226}}, {16, {Action::Function::Shift, 227}}, {18, {Action::Function::Shift, 228}}, {25, {Action::Function::Shift, 212}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_180 = { {24, {Action::Function::Reduce, 7}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_181 = { {1, {Action::Function::Reduce, 38}}, {29, {Action::Function::Reduce, 38}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_182 = { {22, {Action::Function::Shift, 230}}, {24, {Action::Function::Shift, 229}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_183 = { {22, {Action::Function::Reduce, 45}}, {24, {Action::Function::Reduce, 45}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_184 = { {2, {Action::Function::Shift, 195}}, {3, {Action::Function::Shift, 196}}, {4, {Action::Function::Shift, 197}}, {5, {Action::Function::Shift, 198}}, {6, {Action::Function::Shift, 199}}, {7, {Action::Function::Shift, 200}}, {8, {Action::Function::Shift, 201}}, {9, {Action::Function::Shift, 203}}, {10, {Action::Function::Shift, 202}}, {11, {Action::Function::Shift, 204}}, {12, {Action::Function::Shift, 205}}, {13, {Action::Function::Shift, 206}}, {14, {Action::Function::Shift, 207}}, {15, {Action::Function::Shift, 208}}, {16, {Action::Function::Shift, 209}}, {17, {Action::Function::Shift, 194}}, {18, {Action::Function::Shift, 233}}, {22, {Action::Function::Reduce, 46}}, {24, {Action::Function::Reduce, 46}}, {25, {Action::Function::Shift, 192}}, {26, {Action::Function::Shift, 193}}, {27, {Action::Function::Shift, 231}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_185 = { {1, {Action::Function::Reduce, 74}}, {2, {Action::Function::Reduce, 74}}, {3, {Action::Function::Reduce, 74}}, {4, {Action::Function::Reduce, 74}}, {5, {Action::Function::Reduce, 74}}, {6, {Action::Function::Reduce, 74}}, {7, {Action::Function::Reduce, 74}}, {8, {Action::Function::Reduce, 74}}, {9, {Action::Function::Reduce, 74}}, {10, {Action::Function::Reduce, 74}}, {11, {Action::Function::Reduce, 74}}, {12, {Action::Function::Reduce, 74}}, {13, {Action::Function::Reduce, 74}}, {14, {Action::Function::Reduce, 74}}, {15, {Action::Function::Reduce, 74}}, {16, {Action::Function::Reduce, 74}}, {17, {Action::Function::Reduce, 74}}, {18, {Action::Function::Reduce, 74}}, {22, {Action::Function::Reduce, 48}}, {23, {Action::Function::Reduce, 74}}, {24, {Action::Function::Reduce, 48}}, {25, {Action::Function::Reduce, 74}}, {26, {Action::Function::Reduce, 74}}, {27, {Action::Function::Shift, 234}}, {29, {Action::Function::Reduce, 74}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_186 = { {22, {Action::Function::Reduce, 51}}, {24, {Action::Function::Reduce, 51}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_187 = { {1, {Action::Function::Reduce, 53}}, {2, {Action::Function::Reduce, 53}}, {3, {Action::Function::Reduce, 53}}, {4, {Action::Function::Reduce, 53}}, {5, {Action::Function::Reduce, 53}}, {6, {Action::Function::Reduce, 53}}, {7, {Action::Function::Reduce, 53}}, {8, {Action::Function::Reduce, 53}}, {9, {Action::Function::Reduce, 53}}, {10, {Action::Function::Reduce, 53}}, {11, {Action::Function::Reduce, 53}}, {12, {Action::Function::Reduce, 53}}, {13, {Action::Function::Reduce, 53}}, {14, {Action::Function::Reduce, 53}}, {15, {Action::Function::Reduce, 53}}, {16, {Action::Function::Reduce, 53}}, {17, {Action::Function::Reduce, 53}}, {18, {Action::Function::Reduce, 53}}, {22, {Action::Function::Reduce, 53}}, {23, {Action::Function::Reduce, 53}}, {24, {Action::Function::Reduce, 53}}, {25, {Action::Function::Reduce, 53}}, {26, {Action::Function::Reduce, 53}}, {27, {Action::Function::Reduce, 53}}, {29, {Action::Function::Reduce, 53}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_188 = { {1, {Action::Function::Reduce, 56}}, {2, {Action::Function::Reduce, 56}}, {3, {Action::Function::Reduce, 56}}, {4, {Action::Function::Reduce, 56}}, {5, {Action::Function::Reduce, 56}}, {6, {Action::Function::Reduce, 56}}, {7, {Action::Function::Reduce, 56}}, {8, {Action::Function::Reduce, 56}}, {9, {Action::Function::Reduce, 56}}, {10, {Action::Function::Reduce, 56}}, {11, {Action::Function::Reduce, 56}}, {12, {Action::Function::Reduce, 56}}, {13, {Action::Function::Reduce, 56}}, {14, {Action::Function::Reduce, 56}}, {15, {Action::Function::Reduce, 56}}, {16, {Action::Function::Reduce, 56}}, {17, {Action::Function::Reduce, 56}}, {18, {Action::Function::Reduce, 56}}, {22, {Action::Function::Reduce, 56}}, {23, {Action::Function::Shift, 235}}, {24, {Action::Function::Reduce, 56}}, {25, {Action::Function::Reduce, 56}}, {26, {Action::Function::Reduce, 56}}, {27, {Action::Function::Reduce, 56}}, {29, {Action::Function::Reduce, 56}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_189 = { {1, {Action::Function::Reduce, 55}}, {2, {Action::Function::Reduce, 55}}, {3, {Action::Function::Reduce, 55}}, {4, {Action::Function::Reduce, 55}}, {5, {Action::Function::Reduce, 55}}, {6, {Action::Function::Reduce, 55}}, {7, {Action::Function::Reduce, 55}}, {8, {Action::Function::Reduce, 55}}, {9, {Action::Function::Reduce, 55}}, {10, {Action::Function::Reduce, 55}}, {11, {Action::Function::Reduce, 55}}, {12, {Action::Function::Reduce, 55}}, {13, {Action::Function::Reduce, 55}}, {14, {Action::Function::Reduce, 55}}, {15, {Action::Function::Reduce, 55}}, {16, {Action::Function::Reduce, 55}}, {17, {Action::Function::Reduce, 55}}, {18, {Action::Function::Reduce, 55}}, {22, {Action::Function::Reduce, 55}}, {23, {Action::Function::Reduce, 55}}, {24, {Action::Function::Reduce, 55}}, {25, {Action::Function::Reduce, 55}}, {26, {Action::Function::Reduce, 55}}, {27, {Action::Function::Reduce, 55}}, {29, {Action::Function::Reduce, 55}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_190 = { {1, {Action::Function::Reduce, 57}}, {2, {Action::Function::Reduce, 57}}, {3, {Action::Function::Reduce, 57}}, {4, {Action::Function::Reduce, 57}}, {5, {Action::Function::Reduce, 57}}, {6, {Action::Function::Reduce, 57}}, {7, {Action::Function::Reduce, 57}}, {8, {Action::Function::Reduce, 57}}, {9, {Action::Function::Reduce, 57}}, {10, {Action::Function::Reduce, 57}}, {11, {Action::Function::Reduce, 57}}, {12, {Action::Function::Reduce, 57}}, {13, {Action::Function::Reduce, 57}}, {14, {Action::Function::Reduce, 57}}, {15, {Action::Function::Reduce, 57}}, {16, {Action::Function::Reduce, 57}}, {17, {Action::Function::Reduce, 57}}, {18, {Action::Function::Reduce, 57}}, {22, {Action::Function::Reduce, 57}}, {23, {Action::Function::Reduce, 57}}, {24, {Action::Function::Reduce, 57}}, {25, {Action::Function::Reduce, 57}}, {26, {Action::Function::Reduce, 57}}, {27, {Action::Function::Reduce, 57}}, {29, {Action::Function::Reduce, 57}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_191 = { {1, {Action::Function::Reduce, 58}}, {2, {Action::Function::Reduce, 58}}, {3, {Action::Function::Reduce, 58}}, {4, {Action::Function::Reduce, 58}}, {5, {Action::Function::Reduce, 58}}, {6, {Action::Function::Reduce, 58}}, {7, {Action::Function::Reduce, 58}}, {8, {Action::Function::Reduce, 58}}, {9, {Action::Function::Reduce, 58}}, {10, {Action::Function::Reduce, 58}}, {11, {Action::Function::Reduce, 58}}, {12, {Action::Function::Reduce, 58}}, {13, {Action::Function::Reduce, 58}}, {14, {Action::Function::Reduce, 58}}, {15, {Action::Function::Reduce, 58}}, {16, {Action::Function::Reduce, 58}}, {17, {Action::Function::Reduce, 58}}, {18, {Action::Function::Reduce, 58}}, {22, {Action::Function::Reduce, 58}}, {23, {Action::Function::Reduce, 58}}, {24, {Action::Function::Reduce, 58}}, {25, {Action::Function::Reduce, 58}}, {26, {Action::Function::Reduce, 58}}, {27, {Action::Function::Reduce, 58}}, {29, {Action::Function::Reduce, 58}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_192 = { {21, {Action::Function::Shift, 236}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_193 = { {21, {Action::Function::Reduce, 75}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_194 = { {21, {Action::Function::Reduce, 76}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_195 = { {21, {Action::Function::Reduce, 59}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_196 = { {21, {Action::Function::Reduce, 60}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_197 = { {21, {Action::Function::Reduce, 61}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_198 = { {21, {Action::Function::Reduce, 62}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_199 = { {21, {Action::Function::Reduce, 63}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_200 = { {21, {Action::Function::Reduce, 64}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_201 = { {21, {Action::Function::Reduce, 65}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_202 = { {21, {Action::Function::Reduce, 66}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_203 = { {21, {Action::Function::Reduce, 67}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_204 = { {21, {Action::Function::Reduce, 68}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_205 = { {21, {Action::Function::Reduce, 69}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_206 = { {21, {Action::Function::Reduce, 70}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_207 = { {21, {Action::Function::Reduce, 71}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_208 = { {21, {Action::Function::Reduce, 72}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_209 = { {21, {Action::Function::Reduce, 73}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_210 = { {21, {Action::Function::Reduce, 74}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_211 = { {1, {Action::Function::Reduce, 42}}, {2, {Action::Function::Reduce, 42}}, {3, {Action::Function::Reduce, 42}}, {4, {Action::Function::Reduce, 42}}, {5, {Action::Function::Reduce, 42}}, {6, {Action::Function::Reduce, 42}}, {7, {Action::Function::Reduce, 42}}, {8, {Action::Function::Reduce, 42}}, {9, {Action::Function::Reduce, 42}}, {10, {Action::Function::Reduce, 42}}, {11, {Action::Function::Reduce, 42}}, {12, {Action::Function::Reduce, 42}}, {13, {Action::Function::Reduce, 42}}, {14, {Action::Function::Reduce, 42}}, {15, {Action::Function::Reduce, 42}}, {16, {Action::Function::Reduce, 42}}, {17, {Action::Function::Reduce, 42}}, {18, {Action::Function::Reduce, 42}}, {20, {Action::Function::Reduce, 42}}, {22, {Action::Function::Reduce, 42}}, {23, {Action::Function::Reduce, 42}}, {24, {Action::Function::Reduce, 42}}, {25, {Action::Function::Reduce, 42}}, {26, {Action::Function::Reduce, 42}}, {27, {Action::Function::Reduce, 42}}, {29, {Action::Function::Reduce, 42}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_212 = { {22, {Action::Function::Reduce, 47}}, {24, {Action::Function::Reduce, 47}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_213 = { {1, {Action::Function::Reduce, 52}}, {2, {Action::Function::Reduce, 52}}, {3, {Action::Function::Reduce, 52}}, {4, {Action::Function::Reduce, 52}}, {5, {Action::Function::Reduce, 52}}, {6, {Action::Function::Reduce, 52}}, {7, {Action::Function::Reduce, 52}}, {8, {Action::Function::Reduce, 52}}, {9, {Action::Function::Reduce, 52}}, {10, {Action::Function::Reduce, 52}}, {11, {Action::Function::Reduce, 52}}, {12, {Action::Function::Reduce, 52}}, {13, {Action::Function::Reduce, 52}}, {14, {Action::Function::Reduce, 52}}, {15, {Action::Function::Reduce, 52}}, {16, {Action::Function::Reduce, 52}}, {17, {Action::Function::Reduce, 52}}, {18, {Action::Function::Reduce, 52}}, {22, {Action::Function::Reduce, 52}}, {23, {Action::Function::Reduce, 52}}, {24, {Action::Function::Reduce, 52}}, {25, {Action::Function::Reduce, 52}}, {26, {Action::Function::Reduce, 52}}, {27, {Action::Function::Reduce, 52}}, {29, {Action::Function::Reduce, 52}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_214 = { {22, {Action::Function::Reduce, 49}}, {24, {Action::Function::Reduce, 49}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_215 = { {2, {Action::Function::Shift, 242}}, {3, {Action::Function::Shift, 243}}, {4, {Action::Function::Shift, 244}}, {5, {Action::Function::Shift, 245}}, {6, {Action::Function::Shift, 246}}, {7, {Action::Function::Shift, 247}}, {8, {Action::Function::Shift, 248}}, {9, {Action::Function::Shift, 250}}, {10, {Action::Function::Shift, 249}}, {11, {Action::Function::Shift, 251}}, {12, {Action::Function::Shift, 252}}, {13, {Action::Function::Shift, 253}}, {14, {Action::Function::Shift, 254}}, {15, {Action::Function::Shift, 255}}, {16, {Action::Function::Shift, 256}}, {17, {Action::Function::Shift, 194}}, {18, {Action::Function::Shift, 257}}, {25, {Action::Function::Shift, 241}}, {26, {Action::Function::Shift, 193}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_216 = { {22, {Action::Function::Reduce, 44}}, {24, {Action::Function::Reduce, 44}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_217 = { {1, {Action::Function::Reduce, 54}}, {2, {Action::Function::Reduce, 54}}, {3, {Action::Function::Reduce, 54}}, {4, {Action::Function::Reduce, 54}}, {5, {Action::Function::Reduce, 54}}, {6, {Action::Function::Reduce, 54}}, {7, {Action::Function::Reduce, 54}}, {8, {Action::Function::Reduce, 54}}, {9, {Action::Function::Reduce, 54}}, {10, {Action::Function::Reduce, 54}}, {11, {Action::Function::Reduce, 54}}, {12, {Action::Function::Reduce, 54}}, {13, {Action::Function::Reduce, 54}}, {14, {Action::Function::Reduce, 54}}, {15, {Action::Function::Reduce, 54}}, {16, {Action::Function::Reduce, 54}}, {17, {Action::Function::Reduce, 54}}, {18, {Action::Function::Reduce, 54}}, {22, {Action::Function::Reduce, 54}}, {23, {Action::Function::Reduce, 54}}, {24, {Action::Function::Reduce, 54}}, {25, {Action::Function::Reduce, 54}}, {26, {Action::Function::Reduce, 54}}, {27, {Action::Function::Reduce, 54}}, {29, {Action::Function::Reduce, 54}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_218 = { {1, {Action::Function::Reduce, 56}}, {2, {Action::Function::Reduce, 56}}, {3, {Action::Function::Reduce, 56}}, {4, {Action::Function::Reduce, 56}}, {5, {Action::Function::Reduce, 56}}, {6, {Action::Function::Reduce, 56}}, {7, {Action::Function::Reduce, 56}}, {8, {Action::Function::Reduce, 56}}, {9, {Action::Function::Reduce, 56}}, {10, {Action::Function::Reduce, 56}}, {11, {Action::Function::Reduce, 56}}, {12, {Action::Function::Reduce, 56}}, {13, {Action::Function::Reduce, 56}}, {14, {Action::Function::Reduce, 56}}, {15, {Action::Function::Reduce, 56}}, {16, {Action::Function::Reduce, 56}}, {17, {Action::Function::Reduce, 56}}, {18, {Action::Function::Reduce, 56}}, {22, {Action::Function::Reduce, 56}}, {23, {Action::Function::Reduce, 56}}, {24, {Action::Function::Reduce, 56}}, {25, {Action::Function::Reduce, 56}}, {26, {Action::Function::Reduce, 56}}, {27, {Action::Function::Reduce, 56}}, {29, {Action::Function::Reduce, 56}} };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_219 = { {22, {Action::Function::Shift, 230}}, {24, {Action::Function::Shift, 259}},  };
Pairs<pgParser::Action> pgParser::ShiftReduce_row_220 = { {1, {Action::Function::Reduce, 43}}, {2, {Action::Function::Reduce, 43}}, {3, {Action::Function::Reduce, 43}}, {4, {Action::Function::Reduce, 43}}, {5, {Action::Function::Reduce, 43}}, {6, {Action::Function::Reduce, 43}}, {7, {Action::Function::Reduce, 43}}, {8, {Action::Function::Reduce, 43}}, {9, {Action::Function::Reduce, 43}}, {10, {Action::Function::Reduce, 43}}, {11, {Action::Function::Reduce, 43}}, {12, {Action::Function::Reduce, 43}}, {13, {Action::Function::Reduce, 43}}, {14, {Action::Function::Reduce, 43}}, {15, {Action::Function::Reduce, 43}}, {16, {Action::Function::Reduce, 43}}, {17, {Action::Function::Reduce, 43}}, {18, {Action::Function::Reduce, 43}}, {20, {Action::Function::Reduce, 43}}, {22, {Action::Function::Reduce, 43}}, {23, {Action::Function::Reduce, 43}}, {24, {Action::Function::Reduce, 43}}, {25, {Action::Function::Reduce, 43}}, {26, {Action::Function::Reduce, 43}}, {27, {Action::Function::Reduce, 43}}, {29, {Action::Function::Reduce, 43}} };
Pairs<pgParser::Action>* pgParser::ShiftReduce_states[259] = {
	&ShiftReduce_row_1,		//1
	&ShiftReduce_row_2,		//2
	&ShiftReduce_row_3,		//3
	&ShiftReduce_row_4,		//4
	&ShiftReduce_row_5,		//5
	&ShiftReduce_row_6,		//6
	&ShiftReduce_row_7,		//7
	&ShiftReduce_row_8,		//8
	&ShiftReduce_row_9,		//9
	&ShiftReduce_row_10,		//10
	&ShiftReduce_row_11,		//11
	&ShiftReduce_row_12,		//12
	&ShiftReduce_row_13,		//13
	&ShiftReduce_row_14,		//14
	&ShiftReduce_row_15,		//15
	&ShiftReduce_row_16,		//16
	&ShiftReduce_row_17,		//17
	&ShiftReduce_row_18,		//18
	&ShiftReduce_row_19,		//19
	&ShiftReduce_row_20,		//20
	&ShiftReduce_row_21,		//21
	&ShiftReduce_row_22,		//22
	&ShiftReduce_row_23,		//23
	&ShiftReduce_row_24,		//24
	&ShiftReduce_row_25,		//25
	&ShiftReduce_row_26,		//26
	&ShiftReduce_row_27,		//27
	&ShiftReduce_row_28,		//28
	&ShiftReduce_row_29,		//29
	&ShiftReduce_row_30,		//30
	&ShiftReduce_row_31,		//31
	&ShiftReduce_row_32,		//32
	&ShiftReduce_row_33,		//33
	&ShiftReduce_row_34,		//34
	&ShiftReduce_row_35,		//35
	&ShiftReduce_row_36,		//36
	&ShiftReduce_row_37,		//37
	&ShiftReduce_row_38,		//38
	&ShiftReduce_row_39,		//39
	&ShiftReduce_row_40,		//40
	&ShiftReduce_row_41,		//41
	&ShiftReduce_row_42,		//42
	&ShiftReduce_row_43,		//43
	&ShiftReduce_row_44,		//44
	&ShiftReduce_row_45,		//45
	&ShiftReduce_row_46,		//46
	&ShiftReduce_row_47,		//47
	&ShiftReduce_row_48,		//48
	&ShiftReduce_row_49,		//49
	&ShiftReduce_row_50,		//50
	&ShiftReduce_row_51,		//51
	&ShiftReduce_row_52,		//52
	&ShiftReduce_row_53,		//53
	&ShiftReduce_row_54,		//54
	&ShiftReduce_row_55,		//55
	&ShiftReduce_row_56,		//56
	&ShiftReduce_row_57,		//57
	&ShiftReduce_row_58,		//58
	&ShiftReduce_row_59,		//59
	&ShiftReduce_row_60,		//60
	&ShiftReduce_row_61,		//61
	&ShiftReduce_row_62,		//62
	&ShiftReduce_row_63,		//63
	&ShiftReduce_row_64,		//64
	&ShiftReduce_row_65,		//65
	&ShiftReduce_row_66,		//66
	&ShiftReduce_row_67,		//67
	&ShiftReduce_row_68,		//68
	&ShiftReduce_row_69,		//69
	&ShiftReduce_row_70,		//70
	&ShiftReduce_row_71,		//71
	&ShiftReduce_row_72,		//72
	&ShiftReduce_row_73,		//73
	&ShiftReduce_row_74,		//74
	&ShiftReduce_row_75,		//75
	&ShiftReduce_row_76,		//76
	&ShiftReduce_row_77,		//77
	&ShiftReduce_row_78,		//78
	&ShiftReduce_row_79,		//79
	&ShiftReduce_row_80,		//80
	&ShiftReduce_row_81,		//81
	&ShiftReduce_row_82,		//82
	&ShiftReduce_row_83,		//83
	&ShiftReduce_row_84,		//84
	&ShiftReduce_row_85,		//85
	&ShiftReduce_row_86,		//86
	&ShiftReduce_row_87,		//87
	&ShiftReduce_row_88,		//88
	&ShiftReduce_row_89,		//89
	&ShiftReduce_row_90,		//90
	&ShiftReduce_row_91,		//91
	&ShiftReduce_row_92,		//92
	&ShiftReduce_row_93,		//93
	&ShiftReduce_row_94,		//94
	&ShiftReduce_row_95,		//95
	&ShiftReduce_row_96,		//96
	&ShiftReduce_row_97,		//97
	&ShiftReduce_row_98,		//98
	&ShiftReduce_row_99,		//99
	&ShiftReduce_row_100,		//100
	&ShiftReduce_row_101,		//101
	&ShiftReduce_row_102,		//102
	&ShiftReduce_row_103,		//103
	&ShiftReduce_row_104,		//104
	&ShiftReduce_row_105,		//105
	&ShiftReduce_row_106,		//106
	&ShiftReduce_row_107,		//107
	&ShiftReduce_row_108,		//108
	&ShiftReduce_row_109,		//109
	&ShiftReduce_row_110,		//110
	&ShiftReduce_row_111,		//111
	&ShiftReduce_row_112,		//112
	&ShiftReduce_row_113,		//113
	&ShiftReduce_row_114,		//114
	&ShiftReduce_row_115,		//115
	&ShiftReduce_row_116,		//116
	&ShiftReduce_row_117,		//117
	&ShiftReduce_row_118,		//118
	&ShiftReduce_row_119,		//119
	&ShiftReduce_row_120,		//120
	&ShiftReduce_row_121,		//121
	&ShiftReduce_row_122,		//122
	&ShiftReduce_row_123,		//123
	&ShiftReduce_row_124,		//124
	&ShiftReduce_row_125,		//125
	&ShiftReduce_row_126,		//126
	&ShiftReduce_row_127,		//127
	&ShiftReduce_row_128,		//128
	&ShiftReduce_row_129,		//129
	&ShiftReduce_row_13,		//130
	&ShiftReduce_row_130,		//131
	&ShiftReduce_row_131,		//132
	&ShiftReduce_row_132,		//133
	&ShiftReduce_row_133,		//134
	&ShiftReduce_row_134,		//135
	&ShiftReduce_row_135,		//136
	&ShiftReduce_row_136,		//137
	&ShiftReduce_row_137,		//138
	&ShiftReduce_row_138,		//139
	&ShiftReduce_row_139,		//140
	&ShiftReduce_row_140,		//141
	&ShiftReduce_row_141,		//142
	&ShiftReduce_row_142,		//143
	&ShiftReduce_row_143,		//144
	&ShiftReduce_row_144,		//145
	&ShiftReduce_row_145,		//146
	&ShiftReduce_row_146,		//147
	&ShiftReduce_row_147,		//148
	&ShiftReduce_row_148,		//149
	&ShiftReduce_row_149,		//150
	&ShiftReduce_row_150,		//151
	&ShiftReduce_row_151,		//152
	&ShiftReduce_row_152,		//153
	&ShiftReduce_row_153,		//154
	&ShiftReduce_row_154,		//155
	&ShiftReduce_row_155,		//156
	&ShiftReduce_row_156,		//157
	&ShiftReduce_row_157,		//158
	&ShiftReduce_row_158,		//159
	&ShiftReduce_row_159,		//160
	&ShiftReduce_row_160,		//161
	&ShiftReduce_row_161,		//162
	&ShiftReduce_row_162,		//163
	&ShiftReduce_row_163,		//164
	&ShiftReduce_row_164,		//165
	&ShiftReduce_row_165,		//166
	&ShiftReduce_row_166,		//167
	&ShiftReduce_row_167,		//168
	&ShiftReduce_row_168,		//169
	&ShiftReduce_row_169,		//170
	&ShiftReduce_row_170,		//171
	&ShiftReduce_row_171,		//172
	&ShiftReduce_row_172,		//173
	&ShiftReduce_row_173,		//174
	&ShiftReduce_row_174,		//175
	&ShiftReduce_row_175,		//176
	&ShiftReduce_row_176,		//177
	&ShiftReduce_row_177,		//178
	&ShiftReduce_row_178,		//179
	&ShiftReduce_row_179,		//180
	&ShiftReduce_row_180,		//181
	&ShiftReduce_row_181,		//182
	&ShiftReduce_row_182,		//183
	&ShiftReduce_row_183,		//184
	&ShiftReduce_row_184,		//185
	&ShiftReduce_row_185,		//186
	&ShiftReduce_row_186,		//187
	&ShiftReduce_row_187,		//188
	&ShiftReduce_row_188,		//189
	&ShiftReduce_row_189,		//190
	&ShiftReduce_row_101,		//191
	&ShiftReduce_row_102,		//192
	&ShiftReduce_row_190,		//193
	&ShiftReduce_row_191,		//194
	&ShiftReduce_row_103,		//195
	&ShiftReduce_row_104,		//196
	&ShiftReduce_row_105,		//197
	&ShiftReduce_row_106,		//198
	&ShiftReduce_row_107,		//199
	&ShiftReduce_row_108,		//200
	&ShiftReduce_row_109,		//201
	&ShiftReduce_row_110,		//202
	&ShiftReduce_row_111,		//203
	&ShiftReduce_row_112,		//204
	&ShiftReduce_row_113,		//205
	&ShiftReduce_row_114,		//206
	&ShiftReduce_row_115,		//207
	&ShiftReduce_row_116,		//208
	&ShiftReduce_row_117,		//209
	&ShiftReduce_row_192,		//210
	&ShiftReduce_row_193,		//211
	&ShiftReduce_row_194,		//212
	&ShiftReduce_row_195,		//213
	&ShiftReduce_row_196,		//214
	&ShiftReduce_row_197,		//215
	&ShiftReduce_row_198,		//216
	&ShiftReduce_row_199,		//217
	&ShiftReduce_row_200,		//218
	&ShiftReduce_row_201,		//219
	&ShiftReduce_row_202,		//220
	&ShiftReduce_row_203,		//221
	&ShiftReduce_row_204,		//222
	&ShiftReduce_row_205,		//223
	&ShiftReduce_row_206,		//224
	&ShiftReduce_row_207,		//225
	&ShiftReduce_row_208,		//226
	&ShiftReduce_row_209,		//227
	&ShiftReduce_row_210,		//228
	&ShiftReduce_row_211,		//229
	&ShiftReduce_row_178,		//230
	&ShiftReduce_row_212,		//231
	&ShiftReduce_row_213,		//232
	&ShiftReduce_row_118,		//233
	&ShiftReduce_row_214,		//234
	&ShiftReduce_row_215,		//235
	&ShiftReduce_row_178,		//236
	&ShiftReduce_row_216,		//237
	&ShiftReduce_row_217,		//238
	&ShiftReduce_row_218,		//239
	&ShiftReduce_row_101,		//240
	&ShiftReduce_row_102,		//241
	&ShiftReduce_row_103,		//242
	&ShiftReduce_row_104,		//243
	&ShiftReduce_row_105,		//244
	&ShiftReduce_row_106,		//245
	&ShiftReduce_row_107,		//246
	&ShiftReduce_row_108,		//247
	&ShiftReduce_row_109,		//248
	&ShiftReduce_row_110,		//249
	&ShiftReduce_row_111,		//250
	&ShiftReduce_row_112,		//251
	&ShiftReduce_row_113,		//252
	&ShiftReduce_row_114,		//253
	&ShiftReduce_row_115,		//254
	&ShiftReduce_row_116,		//255
	&ShiftReduce_row_117,		//256
	&ShiftReduce_row_118,		//257
	&ShiftReduce_row_219,		//258
	&ShiftReduce_row_220		//259
};

Pairs<size_t> pgParser::Goto_row_1 = { {1, 3}, {2, 2} };
Pairs<size_t> pgParser::Goto_row_2 = { {3, 9}, {7, 10}, {9, 20} };
Pairs<size_t> pgParser::Goto_row_3 = { {4, 21}, {10, 22} };
Pairs<size_t> pgParser::Goto_row_4 = { {8, 27}, {23, 28} };
Pairs<size_t> pgParser::Goto_row_5 = { {8, 46}, {23, 47} };
Pairs<size_t> pgParser::Goto_row_6 = { {8, 65}, {23, 66} };
Pairs<size_t> pgParser::Goto_row_7 = { {5, 92}, {10, 93}, {17, 94} };
Pairs<size_t> pgParser::Goto_row_8 = { {8, 100}, {11, 97}, {14, 98}, {23, 101} };
Pairs<size_t> pgParser::Goto_row_9 = { {8, 122}, {12, 119}, {15, 120}, {23, 101} };
Pairs<size_t> pgParser::Goto_row_10 = { {8, 126}, {13, 123}, {16, 124}, {23, 101} };
Pairs<size_t> pgParser::Goto_row_11 = { {3, 127}, {7, 10}, {9, 20} };
Pairs<size_t> pgParser::Goto_row_12 = { {17, 133} };
Pairs<size_t> pgParser::Goto_row_13 = { {8, 135}, {23, 136} };
Pairs<size_t> pgParser::Goto_row_14 = { {8, 100}, {14, 154}, {23, 101} };
Pairs<size_t> pgParser::Goto_row_15 = { {8, 122}, {15, 155}, {23, 101} };
Pairs<size_t> pgParser::Goto_row_16 = { {8, 126}, {16, 156}, {23, 101} };
Pairs<size_t> pgParser::Goto_row_17 = { {8, 157}, {23, 158} };
Pairs<size_t> pgParser::Goto_row_18 = { {8, 176}, {23, 66} };
Pairs<size_t> pgParser::Goto_row_19 = { {6, 177}, {9, 178} };
Pairs<size_t> pgParser::Goto_row_20 = { {8, 189}, {18, 183}, {19, 184}, {20, 185}, {21, 188}, {22, 190}, {23, 191} };
Pairs<size_t> pgParser::Goto_row_21 = { {8, 210}, {23, 211} };
Pairs<size_t> pgParser::Goto_row_22 = { {8, 189}, {21, 232}, {22, 190}, {23, 191} };
Pairs<size_t> pgParser::Goto_row_23 = { {8, 189}, {19, 237}, {20, 185}, {21, 188}, {22, 190}, {23, 191} };
Pairs<size_t> pgParser::Goto_row_24 = { {8, 239}, {22, 238}, {23, 240} };
Pairs<size_t> pgParser::Goto_row_25 = { {8, 189}, {18, 258}, {19, 184}, {20, 185}, {21, 188}, {22, 190}, {23, 191} };
Pairs<size_t>* pgParser::Goto_states[259] = {
	&Goto_row_1,		//1
	nullptr,		//2
	nullptr,		//3
	nullptr,		//4
	nullptr,		//5
	nullptr,		//6
	nullptr,		//7
	&Goto_row_2,		//8
	&Goto_row_3,		//9
	nullptr,		//10
	&Goto_row_4,		//11
	&Goto_row_5,		//12
	&Goto_row_6,		//13
	nullptr,		//14
	nullptr,		//15
	nullptr,		//16
	nullptr,		//17
	nullptr,		//18
	nullptr,		//19
	nullptr,		//20
	&Goto_row_7,		//21
	nullptr,		//22
	&Goto_row_8,		//23
	&Goto_row_9,		//24
	&Goto_row_10,		//25
	&Goto_row_11,		//26
	nullptr,		//27
	nullptr,		//28
	nullptr,		//29
	nullptr,		//30
	nullptr,		//31
	nullptr,		//32
	nullptr,		//33
	nullptr,		//34
	nullptr,		//35
	nullptr,		//36
	nullptr,		//37
	nullptr,		//38
	nullptr,		//39
	nullptr,		//40
	nullptr,		//41
	nullptr,		//42
	nullptr,		//43
	nullptr,		//44
	nullptr,		//45
	nullptr,		//46
	nullptr,		//47
	nullptr,		//48
	nullptr,		//49
	nullptr,		//50
	nullptr,		//51
	nullptr,		//52
	nullptr,		//53
	nullptr,		//54
	nullptr,		//55
	nullptr,		//56
	nullptr,		//57
	nullptr,		//58
	nullptr,		//59
	nullptr,		//60
	nullptr,		//61
	nullptr,		//62
	nullptr,		//63
	nullptr,		//64
	nullptr,		//65
	nullptr,		//66
	nullptr,		//67
	nullptr,		//68
	nullptr,		//69
	nullptr,		//70
	nullptr,		//71
	nullptr,		//72
	nullptr,		//73
	nullptr,		//74
	nullptr,		//75
	nullptr,		//76
	nullptr,		//77
	nullptr,		//78
	nullptr,		//79
	nullptr,		//80
	nullptr,		//81
	nullptr,		//82
	nullptr,		//83
	nullptr,		//84
	nullptr,		//85
	nullptr,		//86
	nullptr,		//87
	nullptr,		//88
	nullptr,		//89
	nullptr,		//90
	nullptr,		//91
	&Goto_row_12,		//92
	nullptr,		//93
	nullptr,		//94
	&Goto_row_13,		//95
	nullptr,		//96
	&Goto_row_14,		//97
	nullptr,		//98
	nullptr,		//99
	nullptr,		//100
	nullptr,		//101
	nullptr,		//102
	nullptr,		//103
	nullptr,		//104
	nullptr,		//105
	nullptr,		//106
	nullptr,		//107
	nullptr,		//108
	nullptr,		//109
	nullptr,		//110
	nullptr,		//111
	nullptr,		//112
	nullptr,		//113
	nullptr,		//114
	nullptr,		//115
	nullptr,		//116
	nullptr,		//117
	nullptr,		//118
	&Goto_row_15,		//119
	nullptr,		//120
	nullptr,		//121
	nullptr,		//122
	&Goto_row_16,		//123
	nullptr,		//124
	nullptr,		//125
	nullptr,		//126
	nullptr,		//127
	&Goto_row_17,		//128
	nullptr,		//129
	&Goto_row_18,		//130
	nullptr,		//131
	&Goto_row_19,		//132
	nullptr,		//133
	nullptr,		//134
	nullptr,		//135
	nullptr,		//136
	nullptr,		//137
	nullptr,		//138
	nullptr,		//139
	nullptr,		//140
	nullptr,		//141
	nullptr,		//142
	nullptr,		//143
	nullptr,		//144
	nullptr,		//145
	nullptr,		//146
	nullptr,		//147
	nullptr,		//148
	nullptr,		//149
	nullptr,		//150
	nullptr,		//151
	nullptr,		//152
	nullptr,		//153
	nullptr,		//154
	nullptr,		//155
	nullptr,		//156
	nullptr,		//157
	nullptr,		//158
	nullptr,		//159
	nullptr,		//160
	nullptr,		//161
	nullptr,		//162
	nullptr,		//163
	nullptr,		//164
	nullptr,		//165
	nullptr,		//166
	nullptr,		//167
	nullptr,		//168
	nullptr,		//169
	nullptr,		//170
	nullptr,		//171
	nullptr,		//172
	nullptr,		//173
	nullptr,		//174
	nullptr,		//175
	nullptr,		//176
	nullptr,		//177
	nullptr,		//178
	&Goto_row_20,		//179
	&Goto_row_21,		//180
	nullptr,		//181
	nullptr,		//182
	nullptr,		//183
	nullptr,		//184
	&Goto_row_22,		//185
	nullptr,		//186
	nullptr,		//187
	nullptr,		//188
	nullptr,		//189
	nullptr,		//190
	nullptr,		//191
	nullptr,		//192
	nullptr,		//193
	nullptr,		//194
	nullptr,		//195
	nullptr,		//196
	nullptr,		//197
	nullptr,		//198
	nullptr,		//199
	nullptr,		//200
	nullptr,		//201
	nullptr,		//202
	nullptr,		//203
	nullptr,		//204
	nullptr,		//205
	nullptr,		//206
	nullptr,		//207
	nullptr,		//208
	nullptr,		//209
	nullptr,		//210
	nullptr,		//211
	nullptr,		//212
	nullptr,		//213
	nullptr,		//214
	nullptr,		//215
	nullptr,		//216
	nullptr,		//217
	nullptr,		//218
	nullptr,		//219
	nullptr,		//220
	nullptr,		//221
	nullptr,		//222
	nullptr,		//223
	nullptr,		//224
	nullptr,		//225
	nullptr,		//226
	nullptr,		//227
	nullptr,		//228
	nullptr,		//229
	&Goto_row_23,		//230
	nullptr,		//231
	nullptr,		//232
	nullptr,		//233
	nullptr,		//234
	&Goto_row_24,		//235
	&Goto_row_25,		//236
	nullptr,		//237
	nullptr,		//238
	nullptr,		//239
	nullptr,		//240
	nullptr,		//241
	nullptr,		//242
	nullptr,		//243
	nullptr,		//244
	nullptr,		//245
	nullptr,		//246
	nullptr,		//247
	nullptr,		//248
	nullptr,		//249
	nullptr,		//250
	nullptr,		//251
	nullptr,		//252
	nullptr,		//253
	nullptr,		//254
	nullptr,		//255
	nullptr,		//256
	nullptr,		//257
	nullptr,		//258
	nullptr		//259
};

inline void pgParser::Action0()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{
		parserGenerator->setName(valueStack[7].Identifier->getValue());
		parserGenerator->setType(valueStack[6].StringLiteral->getValue());
	}
inline void pgParser::Action1()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>(valueStack[0].Identifier)); }
inline void pgParser::Action2()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>(valueStack[2].Identifier, valueStack[0].Identifier)); }
inline void pgParser::Action3()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>(valueStack[1].Identifier, valueStack[0].StringLiteral)); }
inline void pgParser::Action4()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ root->addTerminal(root->create<ContextFreeGrammar::Terminal>(valueStack[3].Identifier, valueStack[1].Identifier, valueStack[0].StringLiteral)); }
inline void pgParser::Action5()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ root->addNonTerminal(root->create<ContextFreeGrammar::NonTerminal>(valueStack[0].Identifier, valueStack[0].Identifier)); }
inline void pgParser::Action6()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ root->addNonTerminal(root->create<ContextFreeGrammar::NonTerminal>(valueStack[2].Identifier, valueStack[0].Identifier)); }
inline void pgParser::Action7()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ root->setStartSymbol(root->getNonTerminal(valueStack[0].Identifier)); }
inline void pgParser::Action8()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ parserGenerator->addHeader(valueStack[0].CodeBlock); }
inline void pgParser::Action9()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ parserGenerator->addCode(valueStack[0].CodeBlock); }
inline void pgParser::Action10()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ parserGenerator->setRootType(valueStack[0].StringLiteral->getValue()); }
inline void pgParser::Action11()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ parserGenerator->setBaseClass(valueStack[0].StringLiteral->getValue()); }
inline void pgParser::Action12()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ parserGenerator->setBaseType(valueStack[0].StringLiteral->getValue()); }
inline void pgParser::Action13()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ parserGenerator->setBaseType(valueStack[0].StringLiteral->getValue(), true); }
inline void pgParser::Action14()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ parserGenerator->setReturnType(valueStack[0].StringLiteral->getValue()); }
inline void pgParser::Action15()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ ++Precedence; }
inline void pgParser::Action16()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ ++Precedence; }
inline void pgParser::Action17()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{
			ContextFreeGrammar::Terminal* terminal = root->getTerminal(valueStack[0].StringLiteral);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::None);
			terminal->setPrecedence(Precedence);
		}
inline void pgParser::Action18()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{
			ContextFreeGrammar::Terminal* terminal = root->getTerminal(valueStack[0].Identifier);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::None);
			terminal->setPrecedence(Precedence);
		}
inline void pgParser::Action19()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{
			ContextFreeGrammar::Terminal* terminal = root->getTerminal(valueStack[0].StringLiteral);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::Left);
			terminal->setPrecedence(Precedence);
		}
inline void pgParser::Action20()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{
			ContextFreeGrammar::Terminal* terminal = root->getTerminal(valueStack[0].Identifier);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::Left);
			terminal->setPrecedence(Precedence);
		}
inline void pgParser::Action21()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{
			ContextFreeGrammar::Terminal* terminal = root->getTerminal(valueStack[0].StringLiteral);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::Right);
			terminal->setPrecedence(Precedence);
		}
inline void pgParser::Action22()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{
			ContextFreeGrammar::Terminal* terminal = root->getTerminal(valueStack[0].Identifier);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::Right);
			terminal->setPrecedence(Precedence);
		}
inline void pgParser::Action23()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ root->addRule(valueStack[0].Rule); }
inline void pgParser::Action24()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ root->addRule(valueStack[0].Rule); }
inline void pgParser::Action25()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Rule = root->findOrCreateRule(valueStack[3].Identifier, valueStack[1].Productions); }
inline void pgParser::Action26()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Rule = root->findOrCreateRule(valueStack[5].Identifier, valueStack[3].Identifier, valueStack[1].Productions); }
inline void pgParser::Action27()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Productions = valueStack[2].Productions; valueStack[2].Productions->addProduction(valueStack[0].Production); }
inline void pgParser::Action28()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Productions = root->newProductions(); currentValue.Productions->addProduction(valueStack[0].Production); }
inline void pgParser::Action29()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Production = root->newProduction(valueStack[0].NamedSymbols); }
inline void pgParser::Action30()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Production = root->newProduction(valueStack[1].NamedSymbols, valueStack[0].Action, false); }
inline void pgParser::Action31()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Production = root->newProduction(); }
inline void pgParser::Action32()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Production = root->newProduction(valueStack[0].Action, false); }
inline void pgParser::Action33()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Production = root->newProduction(); }
inline void pgParser::Action34()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Production = root->newProduction(valueStack[0].Action, false); }
inline void pgParser::Action35()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.NamedSymbols = valueStack[1].NamedSymbols; valueStack[1].NamedSymbols->addSymbol(valueStack[0].NamedSymbol); }
inline void pgParser::Action36()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.NamedSymbols = root->newNamedSymbols(); currentValue.NamedSymbols->addSymbol(valueStack[0].NamedSymbol); }
inline void pgParser::Action37()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.NamedSymbol = root->newNamedSymbol(valueStack[2].Identifier, valueStack[0].Symbol); }
inline void pgParser::Action38()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.NamedSymbol = root->newNamedSymbol(valueStack[0].Symbol); }
inline void pgParser::Action39()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{ currentValue.Symbol = root->findOrCreateSymbol(valueStack[0].Identifier); }
inline void pgParser::Action40()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{
    		ContextFreeGrammar::Symbol* symbol = root->getTerminal(valueStack[0].StringLiteral);
    		if (symbol == ContextFreeGrammar::getErrorSymbol() || symbol == nullptr)
    			G::logger->LogError(new UndefinedTerminalSymbolErrorObject(valueStack[0].StringLiteral->getValue(), lexer->getLineNumber(), lexer->getCharacter()));
    		currentValue.Symbol = symbol;
    	}
inline void pgParser::Action41()
#line 1 "C:\\Users\\aaron\\Projects\\G\\G - 0.6.108 - bootstrap 20\\tools\\bootstrap\\pg-bootstrap-lg-pg\\pg.pg"
{
    		currentValue.Symbol = root->getTerminal(root->newStringLiteral("$"));
    	}

void (pgParser::*pgParser::Actions[42])() = {
	&pgParser::Action0,
	&pgParser::Action1,
	&pgParser::Action2,
	&pgParser::Action3,
	&pgParser::Action4,
	&pgParser::Action5,
	&pgParser::Action6,
	&pgParser::Action7,
	&pgParser::Action8,
	&pgParser::Action9,
	&pgParser::Action10,
	&pgParser::Action11,
	&pgParser::Action12,
	&pgParser::Action13,
	&pgParser::Action14,
	&pgParser::Action15,
	&pgParser::Action16,
	&pgParser::Action17,
	&pgParser::Action18,
	&pgParser::Action19,
	&pgParser::Action20,
	&pgParser::Action21,
	&pgParser::Action22,
	&pgParser::Action23,
	&pgParser::Action24,
	&pgParser::Action25,
	&pgParser::Action26,
	&pgParser::Action27,
	&pgParser::Action28,
	&pgParser::Action29,
	&pgParser::Action30,
	&pgParser::Action31,
	&pgParser::Action32,
	&pgParser::Action33,
	&pgParser::Action34,
	&pgParser::Action35,
	&pgParser::Action36,
	&pgParser::Action37,
	&pgParser::Action38,
	&pgParser::Action39,
	&pgParser::Action40,
	&pgParser::Action41
};




TEST(Grammar, full_bootstrap_test) {
    ParserGenerator<ContextFreeGrammar, ParserGeneratorParser>* parserGenerator_main = pg_ParserGenerator;
    parserGenerator_main->Generate();


}
