#include "g/ParserGenerator/ParserGenerator.h"
#include "g/Actions.h"

using namespace G::ParserGenerator;

ContextFreeGrammar* G_bootstrap() {
ContextFreeGrammar* G = new ContextFreeGrammar("G");

	ContextFreeGrammar::Terminal *KEYWORD_GRAMMAR = G->addTerminal("KEYWORD_GRAMMAR","", "grammar", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_TERM = G->addTerminal("KEYWORD_TERM","", "term", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_NONTERM = G->addTerminal("KEYWORD_NONTERM","", "nonterm", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_PRODUCTION = G->addTerminal("KEYWORD_PRODUCTION","", "production", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_START = G->addTerminal("KEYWORD_START","", "start", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_CODE = G->addTerminal("KEYWORD_CODE","", "code", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_HEADER = G->addTerminal("KEYWORD_HEADER","", "header", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_ROOTTYPE = G->addTerminal("KEYWORD_ROOTTYPE","", "roottype", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_BASECLASS = G->addTerminal("KEYWORD_BASECLASS","", "baseclass", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_BASETYPE = G->addTerminal("KEYWORD_BASETYPE","", "basetype", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_RETURNTYPE = G->addTerminal("KEYWORD_RETURNTYPE","", "returntype", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_UNION = G->addTerminal("KEYWORD_UNION","", "union", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_NONASSOC = G->addTerminal("KEYWORD_NONASSOC","", "nonassoc", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_LEFT = G->addTerminal("KEYWORD_LEFT","", "left", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_RIGHT = G->addTerminal("KEYWORD_RIGHT","", "right", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_DOLLAR = G->addTerminal("OPERATOR_DOLLAR","", "$", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_EPSILON = G->addTerminal("OPERATOR_EPSILON","", "epsilon", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_CURLY_BRACE = G->addTerminal("OPERATOR_OPEN_CURLY_BRACE","", "{", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_CURLY_BRACE = G->addTerminal("OPERATOR_CLOSE_CURLY_BRACE","", "}", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_EQUALS = G->addTerminal("OPERATOR_EQUALS","", "=", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OR = G->addTerminal("OPERATOR_OR","", "|", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_STAR = G->addTerminal("OPERATOR_STAR","", "*", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_PLUS = G->addTerminal("OPERATOR_PLUS","", "+", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_LEFT_PARENTHESIS = G->addTerminal("OPERATOR_LEFT_PARENTHESIS","", "(", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_RIGHT_PARENTHESIS = G->addTerminal("OPERATOR_RIGHT_PARENTHESIS","", ")", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_LEFT_BRACKET = G->addTerminal("OPERATOR_LEFT_BRACKET","", "[", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_RIGHT_BRACKET = G->addTerminal("OPERATOR_RIGHT_BRACKET","", "]", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_LEFT_ANGLED_BRACKET = G->addTerminal("OPERATOR_LEFT_ANGLED_BRACKET","", "<", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_RIGHT_ANGLED_BRACKET = G->addTerminal("OPERATOR_RIGHT_ANGLED_BRACKET","", ">", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_COLON = G->addTerminal("OPERATOR_COLON","", ":", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_SEMICOLON = G->addTerminal("OPERATOR_SEMICOLON","", ";", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *IDENTIFIER = G->addTerminal("IDENTIFIER","Identifier", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *STRING_LITERAL = G->addTerminal("STRING_LITERAL","StringLiteral", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *TOKEN_ACTION = G->addTerminal("TOKEN_ACTION","Action", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *TOKEN_CODE = G->addTerminal("TOKEN_CODE","CodeBlock", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *NEWLINE = G->addTerminal("NEWLINE","", "", ContextFreeGrammar::None, 0, false);

	ContextFreeGrammar::Terminal *EPSILON = G->getTerminal("EPSILON");
	ContextFreeGrammar::Terminal *END = G->getTerminal("END");

	ContextFreeGrammar::NonTerminal *File = G->addNonTerminal("File", "File");
	ContextFreeGrammar::NonTerminal *Grammar = G->addNonTerminal("Grammar", "Grammar");
	ContextFreeGrammar::NonTerminal *Headers = G->addNonTerminal("Headers", "Headers");
	ContextFreeGrammar::NonTerminal *Header = G->addNonTerminal("Header", "Header");
	ContextFreeGrammar::NonTerminal *Precedences = G->addNonTerminal("Precedences", "Precedences");
	ContextFreeGrammar::NonTerminal *Precedence = G->addNonTerminal("Precedence", "Precedence");
	ContextFreeGrammar::NonTerminal *NonAssociative = G->addNonTerminal("NonAssociative", "NonAssociative");
	ContextFreeGrammar::NonTerminal *NonAssociativeTerminals = G->addNonTerminal("NonAssociativeTerminals", "NonAssociativeTerminals");
	ContextFreeGrammar::NonTerminal *NonAssociativeTerminal = G->addNonTerminal("NonAssociativeTerminal", "NonAssociativeTerminal");
	ContextFreeGrammar::NonTerminal *LeftAssociative = G->addNonTerminal("LeftAssociative", "LeftAssociative");
	ContextFreeGrammar::NonTerminal *LeftAssociativeTerminals = G->addNonTerminal("LeftAssociativeTerminals", "LeftAssociativeTerminals");
	ContextFreeGrammar::NonTerminal *LeftAssociativeTerminal = G->addNonTerminal("LeftAssociativeTerminal", "LeftAssociativeTerminal");
	ContextFreeGrammar::NonTerminal *RightAssociative = G->addNonTerminal("RightAssociative", "RightAssociative");
	ContextFreeGrammar::NonTerminal *RightAssociativeTerminals = G->addNonTerminal("RightAssociativeTerminals", "RightAssociativeTerminals");
	ContextFreeGrammar::NonTerminal *RightAssociativeTerminal = G->addNonTerminal("RightAssociativeTerminal", "RightAssociativeTerminal");
	ContextFreeGrammar::NonTerminal *Footer = G->addNonTerminal("Footer", "Footer");
	ContextFreeGrammar::NonTerminal *BlankLines = G->addNonTerminal("BlankLines", "BlankLines");
	ContextFreeGrammar::NonTerminal *Rules = G->addNonTerminal("Rules", "Rules");
	ContextFreeGrammar::NonTerminal *Rule = G->addNonTerminal("Rule", "Rule");
	ContextFreeGrammar::NonTerminal *Productions = G->addNonTerminal("Productions", "Productions");
	ContextFreeGrammar::NonTerminal *Production = G->addNonTerminal("Production", "Production");
	ContextFreeGrammar::NonTerminal *NamedSymbols = G->addNonTerminal("NamedSymbols", "NamedSymbols");
	ContextFreeGrammar::NonTerminal *NamedSymbol = G->addNonTerminal("NamedSymbol", "NamedSymbol");
	ContextFreeGrammar::NonTerminal *NamedFactors = G->addNonTerminal("NamedFactors", "NamedFactors");
	ContextFreeGrammar::NonTerminal *NamedFactor = G->addNonTerminal("NamedFactor", "NamedFactor");
	ContextFreeGrammar::NonTerminal *Factor = G->addNonTerminal("Factor", "Factor");
	ContextFreeGrammar::NonTerminal *Grouping = G->addNonTerminal("Grouping", "Factor");
	ContextFreeGrammar::NonTerminal *Selection = G->addNonTerminal("Selection", "Selection");
	ContextFreeGrammar::NonTerminal *Sequence = G->addNonTerminal("Sequence", "Sequence");
	ContextFreeGrammar::NonTerminal *Symbol = G->addNonTerminal("Symbol", "Symbol");
	ContextFreeGrammar::NonTerminal *Identifier = G->addNonTerminal("Identifier", "Identifier");
	ContextFreeGrammar::NonTerminal *Keyword = G->addNonTerminal("Keyword", "Keyword");
	ContextFreeGrammar::NonTerminal *S_ = G->addNonTerminal("S'", "S'");

	G->setStartSymbol(S_);
	G->addRule(File, {
		G->addProduction({
			G->newNamedSymbol(Grammar)
		}, -1)
	});
	G->addRule(Grammar, {
		G->addProduction({
			G->newNamedSymbol(KEYWORD_GRAMMAR),
			G->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			G->newNamedSymbol(Headers),
			G->newNamedSymbol(Precedences),
			G->newNamedSymbol(Rules),
			G->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE),
			G->newNamedSymbol(Footer)
		}, -1)
	});
	G->addRule(Headers, {
		G->addProduction({
			G->newNamedSymbol(Header),
			G->newNamedSymbol(OPERATOR_SEMICOLON),
			G->newNamedSymbol(Headers)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(Header),
			G->newNamedSymbol(OPERATOR_SEMICOLON)
		}, -1)
	});
	G->addRule(Header, {
		G->addProduction({
			G->newNamedSymbol(KEYWORD_TERM),
			G->newNamedSymbol("identifier", Identifier)
		}, 0),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_TERM),
			G->newNamedSymbol("identifier", Identifier),
			G->newNamedSymbol(OPERATOR_COLON),
			G->newNamedSymbol("type", Identifier)
		}, 1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_TERM),
			G->newNamedSymbol("identifier", Identifier),
			G->newNamedSymbol("literal", STRING_LITERAL)
		}, 2),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_TERM),
			G->newNamedSymbol("identifier", Identifier),
			G->newNamedSymbol(OPERATOR_COLON),
			G->newNamedSymbol("type", Identifier),
			G->newNamedSymbol("literal", STRING_LITERAL)
		}, 3),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_NONTERM),
			G->newNamedSymbol("idenfifier", Identifier)
		}, 4),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_NONTERM),
			G->newNamedSymbol("idenfifier", Identifier),
			G->newNamedSymbol(OPERATOR_COLON),
			G->newNamedSymbol("type", Identifier)
		}, 5),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_START),
			G->newNamedSymbol("idenfifier", Identifier)
		}, 6),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_HEADER),
			G->newNamedSymbol("_code", TOKEN_CODE)
		}, 7),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_CODE),
			G->newNamedSymbol("_code", TOKEN_CODE)
		}, 8),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_ROOTTYPE),
			G->newNamedSymbol("type", STRING_LITERAL)
		}, 9),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_BASECLASS),
			G->newNamedSymbol("literal", STRING_LITERAL)
		}, 10),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_BASETYPE),
			G->newNamedSymbol("literal", STRING_LITERAL)
		}, 11),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_BASETYPE),
			G->newNamedSymbol(KEYWORD_UNION),
			G->newNamedSymbol("literal", STRING_LITERAL)
		}, 12),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_RETURNTYPE),
			G->newNamedSymbol("literal", STRING_LITERAL)
		}, 13),
		G->addProduction({
			G->newNamedSymbol(BlankLines)
		}, -1)
	});
	G->addRule(Precedences, {
		G->addProduction({
			G->newNamedSymbol(Precedences),
			G->newNamedSymbol(Precedence),
			G->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 14),
		G->addProduction({
			G->newNamedSymbol(Precedence),
			G->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 15),
		G->addProduction({}, -1)
	});
	G->addRule(Precedence, {
		G->addProduction({
			G->newNamedSymbol(KEYWORD_NONASSOC),
			G->newNamedSymbol(NonAssociativeTerminals)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_LEFT),
			G->newNamedSymbol(LeftAssociativeTerminals)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_RIGHT),
			G->newNamedSymbol(RightAssociativeTerminals)
		}, -1)
	});
	G->addRule(NonAssociativeTerminals, {
		G->addProduction({
			G->newNamedSymbol(NonAssociativeTerminals),
			G->newNamedSymbol(NonAssociativeTerminal)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(NonAssociativeTerminal)
		}, -1)
	});
	G->addRule(NonAssociativeTerminal, {
		G->addProduction({
			G->newNamedSymbol(STRING_LITERAL)
		}, 16),
		G->addProduction({
			G->newNamedSymbol(Identifier)
		}, 17)
	});
	G->addRule(LeftAssociativeTerminals, {
		G->addProduction({
			G->newNamedSymbol(LeftAssociativeTerminals),
			G->newNamedSymbol(LeftAssociativeTerminal)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(LeftAssociativeTerminal)
		}, -1)
	});
	G->addRule(LeftAssociativeTerminal, {
		G->addProduction({
			G->newNamedSymbol(STRING_LITERAL)
		}, 18),
		G->addProduction({
			G->newNamedSymbol(Identifier)
		}, 19)
	});
	G->addRule(RightAssociativeTerminals, {
		G->addProduction({
			G->newNamedSymbol(RightAssociativeTerminals),
			G->newNamedSymbol(RightAssociativeTerminal)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(RightAssociativeTerminal)
		}, -1)
	});
	G->addRule(RightAssociativeTerminal, {
		G->addProduction({
			G->newNamedSymbol(STRING_LITERAL)
		}, 20),
		G->addProduction({
			G->newNamedSymbol(Identifier)
		}, 21)
	});
	G->addRule(Footer, {
		G->addProduction({
			G->newNamedSymbol(BlankLines)
		}, -1)
	});
	G->addRule(BlankLines, {
		G->addProduction({
			G->newNamedSymbol(BlankLines),
			G->newNamedSymbol(NEWLINE)
		}, -1),
		G->addProduction({}, -1)
	});
	G->addRule(Rules, {
		G->addProduction({
			G->newNamedSymbol(Rules),
			G->newNamedSymbol(Rule)
		}, 22),
		G->addProduction({
			G->newNamedSymbol(Rule)
		}, 23)
	});
	G->addRule(Rule, {
		G->addProduction({
			G->newNamedSymbol(KEYWORD_PRODUCTION),
			G->newNamedSymbol("identifier", Identifier),
			G->newNamedSymbol(OPERATOR_EQUALS),
			G->newNamedSymbol("productions", Productions),
			G->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 24)
	});
	G->addRule(Productions, {
		G->addProduction({
			G->newNamedSymbol("productions", Productions),
			G->newNamedSymbol(OPERATOR_OR),
			G->newNamedSymbol("production1", Production)
		}, 25),
		G->addProduction({
			G->newNamedSymbol("production1", Production)
		}, 26)
	});
	G->addRule(Production, {
		G->addProduction({
			G->newNamedSymbol("factors", NamedFactors)
		}, 27),
		G->addProduction({
			G->newNamedSymbol("factors", NamedFactors),
			G->newNamedSymbol("action", TOKEN_ACTION)
		}, 28),
		G->addProduction({
			G->newNamedSymbol(OPERATOR_EPSILON)
		}, 29),
		G->addProduction({
			G->newNamedSymbol(OPERATOR_EPSILON),
			G->newNamedSymbol("action", TOKEN_ACTION)
		}, 30),
		G->addProduction({}, 31),
		G->addProduction({
			G->newNamedSymbol(TOKEN_ACTION)
		}, 32)
	});
	G->addRule(NamedFactors, {
		G->addProduction({
			G->newNamedSymbol("factors", NamedFactors),
			G->newNamedSymbol("factor", NamedFactor)
		}, 33),
		G->addProduction({
			G->newNamedSymbol("factor", NamedFactor)
		}, 34)
	});
	G->addRule(NamedFactor, {
		G->addProduction({
			G->newNamedSymbol("identifier", Identifier),
			G->newNamedSymbol(OPERATOR_COLON),
			G->newNamedSymbol("factor", Factor)
		}, 35),
		G->addProduction({
			G->newNamedSymbol("factor", Factor)
		}, 36)
	});
	G->addRule(Factor, {
		G->addProduction({
			G->newNamedSymbol("grouping", Grouping),
			G->newNamedSymbol(OPERATOR_STAR)
		}, 37),
		G->addProduction({
			G->newNamedSymbol("grouping", Grouping),
			G->newNamedSymbol(OPERATOR_PLUS)
		}, 38),
		G->addProduction({
			G->newNamedSymbol("grouping", Grouping)
		}, 39)
	});
	G->addRule(Grouping, {
		G->addProduction({
			G->newNamedSymbol(OPERATOR_LEFT_PARENTHESIS),
			G->newNamedSymbol("selection", Selection),
			G->newNamedSymbol(OPERATOR_RIGHT_PARENTHESIS)
		}, 40),
		G->addProduction({
			G->newNamedSymbol(OPERATOR_LEFT_BRACKET),
			G->newNamedSymbol("selection", Selection),
			G->newNamedSymbol(OPERATOR_RIGHT_BRACKET)
		}, 41),
		G->addProduction({
			G->newNamedSymbol("symbol", Symbol)
		}, 42)
	});
	G->addRule(Selection, {
		G->addProduction({
			G->newNamedSymbol("selection", Selection),
			G->newNamedSymbol(OPERATOR_OR),
			G->newNamedSymbol("sequence", Sequence)
		}, 43),
		G->addProduction({
			G->newNamedSymbol("sequence", Sequence)
		}, 44)
	});
	G->addRule(Sequence, {
		G->addProduction({
			G->newNamedSymbol("sequence", Sequence),
			G->newNamedSymbol("factor", Factor)
		}, 45),
		G->addProduction({
			G->newNamedSymbol("factor", Factor)
		}, 46)
	});
	G->addRule(Symbol, {
		G->addProduction({
			G->newNamedSymbol(Identifier)
		}, 47),
		G->addProduction({
			G->newNamedSymbol(STRING_LITERAL)
		}, 48),
		G->addProduction({
			G->newNamedSymbol(OPERATOR_DOLLAR)
		}, 49)
	});
	G->addRule(Keyword, {
		G->addProduction({
			G->newNamedSymbol(KEYWORD_GRAMMAR)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_TERM)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_NONTERM)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_PRODUCTION)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_START)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_CODE)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_HEADER)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_BASECLASS)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_ROOTTYPE)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_BASETYPE)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_RETURNTYPE)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_UNION)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_NONASSOC)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_LEFT)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(KEYWORD_RIGHT)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(OPERATOR_EPSILON)
		}, -1)
	});
	G->addRule(Identifier, {
		G->addProduction({
			G->newNamedSymbol(Keyword)
		}, -1),
		G->addProduction({
			G->newNamedSymbol(IDENTIFIER)
		}, -1)
	});
	G->addRule(S_, {
		G->addProduction({
			G->newNamedSymbol(File),
			G->newNamedSymbol(END)
		}, -1)
	});
	return G;
}

Actions bootstrapActions = {
	{ 0, "{ root->addTerminal(root->newTerminal(valueStack[0].Identifier)); }", 174},
	{ 1, "{ root->addTerminal(root->newTerminal(valueStack[2].Identifier, valueStack[0].Identifier)); }", 176},
	{ 2, "{ root->addTerminal(root->newTerminal(valueStack[1].Identifier, valueStack[0].StringLiteral)); }", 178},
	{ 3, "{ root->addTerminal(root->newTerminal(valueStack[3].Identifier, valueStack[1].Identifier, valueStack[0].StringLiteral)); }", 180},
	{ 4, "{ root->addNonTerminal(root->newNonTerminal(valueStack[0].Identifier)); }", 182},
	{ 5, "{ root->addNonTerminal(root->newNonTerminal(valueStack[2].Identifier, valueStack[0].Identifier)); }", 184},
	{ 6, "{ root->setStartSymbol(root->getNonTerminal(valueStack[0].Identifier)); }", 186},
	{ 7, "{ parserGenerator->addHeader(valueStack[0].CodeBlock); }", 188},
	{ 8, "{ parserGenerator->addCode(valueStack[0].CodeBlock); }", 190},
	{ 9, "{ parserGenerator->setRootType(valueStack[0].StringLiteral->getValue()); }", 192},
	{ 10, "{ parserGenerator->setBaseClass(valueStack[0].StringLiteral->getValue()); }", 194},
	{ 11, "{ parserGenerator->setBaseType(valueStack[0].StringLiteral->getValue()); }", 196},
	{ 12, "{ parserGenerator->setBaseType(valueStack[0].StringLiteral->getValue(), true); }", 198},
	{ 13, "{ parserGenerator->setReturnType(valueStack[0].StringLiteral->getValue()); }", 200},
	{ 14, "{ ++Precedence; }", 205},
	{ 15, "{ ++Precedence; }", 206},
	{ 16, "{\n\t\t\tExtendedGrammar::Terminal* terminal = root->getTerminal(valueStack[0].StringLiteral);\n\t\t\tterminal->setAssociativity(ExtendedGrammar::Associativity::None);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 223},
	{ 17, "{\n\t\t\tExtendedGrammar::Terminal* terminal = root->getTerminal(valueStack[0].Identifier);\n\t\t\tterminal->setAssociativity(ExtendedGrammar::Associativity::None);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 229},
	{ 18, "{\n\t\t\tExtendedGrammar::Terminal* terminal = root->getTerminal(valueStack[0].StringLiteral);\n\t\t\tterminal->setAssociativity(ExtendedGrammar::Associativity::Left);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 243},
	{ 19, "{\n\t\t\tExtendedGrammar::Terminal* terminal = root->getTerminal(valueStack[0].Identifier);\n\t\t\tterminal->setAssociativity(ExtendedGrammar::Associativity::Left);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 249},
	{ 20, "{\n\t\t\tExtendedGrammar::Terminal* terminal = root->getTerminal(valueStack[0].StringLiteral);\n\t\t\tterminal->setAssociativity(ExtendedGrammar::Associativity::Right);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 263},
	{ 21, "{\n\t\t\tExtendedGrammar::Terminal* terminal = root->getTerminal(valueStack[0].Identifier);\n\t\t\tterminal->setAssociativity(ExtendedGrammar::Associativity::Right);\n\t\t\tterminal->setPrecedence(Precedence);\n\t\t}", 269},
	{ 22, "{ root->addRule(valueStack[0].Rule); }", 286},
	{ 23, "{ root->addRule(valueStack[0].Rule); }", 288},
	{ 24, "{ currentValue.Rule = root->newRule(valueStack[3].Identifier, valueStack[1].Productions); }", 292},
	{ 25, "{ currentValue.Productions = valueStack[2].Productions; valueStack[2].Productions->addProduction(valueStack[0].Production); }", 296},
	{ 26, "{ currentValue.Productions = root->newProductions(); currentValue.Productions->addProduction(valueStack[0].Production); }", 298},
	{ 27, "{ currentValue.Production = root->newProduction(valueStack[0].NamedFactors); }", 302},
	{ 28, "{ currentValue.Production = root->newProduction(valueStack[1].NamedFactors, valueStack[0].Action); }", 304},
	{ 29, "{ currentValue.Production = root->newProduction(); }", 306},
	{ 30, "{ currentValue.Production = root->newProduction(valueStack[0].Action); }", 308},
	{ 31, "{ currentValue.Production = root->newProduction(); }", 310},
	{ 32, "{ currentValue.Production = root->newProduction(valueStack[0].Action); }", 312},
	{ 33, "{ currentValue.NamedFactors = valueStack[1].NamedFactors; valueStack[1].NamedFactors->add(valueStack[0].NamedFactor); }", 317},
	{ 34, "{ currentValue.NamedFactors = root->newNamedFactors(); currentValue.NamedFactors->add(valueStack[0].NamedFactor); }", 319},
	{ 35, "{ currentValue.NamedFactor = root->newNamedFactor(valueStack[2].Identifier, valueStack[0].Factor); }", 323},
	{ 36, "{ currentValue.NamedFactor = root->newNamedFactor(valueStack[0].Factor); }", 325},
	{ 37, "{ currentValue.Factor = root->newOptionalRepetition(valueStack[1].Factor); }", 330},
	{ 38, "{ currentValue.Factor = root->newRepetition(valueStack[1].Factor); }", 332},
	{ 39, "{ currentValue.Factor = valueStack[0].Factor; }", 334},
	{ 40, "{ currentValue.Factor = valueStack[1].Selection; }", 339},
	{ 41, "{ currentValue.Factor = root->newOptional(valueStack[1].Selection); }", 341},
	{ 42, "{ currentValue.Factor = new ExtendedGrammar::Factor(valueStack[0].Symbol); }", 343},
	{ 43, "{ currentValue.Selection = valueStack[2].Selection; valueStack[2].Selection->add(valueStack[0].Sequence); }", 348},
	{ 44, "{ currentValue.Selection = root->newSelection(); currentValue.Selection->add(valueStack[0].Sequence); }", 350},
	{ 45, "{ currentValue.Sequence = valueStack[1].Sequence; valueStack[1].Sequence->add(valueStack[0].Factor); }", 355},
	{ 46, "{ currentValue.Sequence = root->newSequence(); currentValue.Sequence->add(valueStack[0].Factor); }", 357},
	{ 47, "{\n    \t\tExtendedGrammar::Symbol* symbol = root->getSymbol(valueStack[0].Identifier);\n    \t\tif (symbol == ExtendedGrammar::getErrorSymbol() || symbol == nullptr)\n    \t\t\tG::logger->LogError(new UndefinedSymbolErrorObject(valueStack[0].Identifier->getValue(), lexer->getLineNumber(), lexer->getCharacter()));\n    \t\tcurrentValue.Symbol = symbol;\n    \t}", 361},
	{ 48, "{\n    \t\tExtendedGrammar::Symbol* symbol = root->getTerminal(valueStack[0].StringLiteral);\n    \t\tif (symbol == ExtendedGrammar::getErrorSymbol() || symbol == nullptr)\n    \t\t\tG::logger->LogError(new UndefinedTerminalSymbolErrorObject(valueStack[0].StringLiteral->getValue(), lexer->getLineNumber(), lexer->getCharacter()));\n    \t\tcurrentValue.Symbol = symbol;\n    \t}", 368},
	{ 49, "{\n    \t\tcurrentValue.Symbol = root->getTerminal(root->newStringLiteral(\"$\"));\n    \t}", 375}
};

ParserGenerator<ContextFreeGrammar, ParserGeneratorParser>* g_ParserGenerator = new ParserGenerator<ContextFreeGrammar, ParserGeneratorParser>("g", 
g_bootstrap(), &bootstrapActions,
"ExtendedGrammar",
"ValueType",
"true",
"void",
  {
    { "\n\t#include <io.h>\n\t#include <iostream>\n\t#include <cassert>\n\n\t#include \"g/Grammar/ExtendedGrammar.h\"\n\tclass ParserGeneratorParser;\n\t#include \"g/ParserGenerator/ParserGenerator.h\"\n\n\tusing namespace G::ParserGenerator;\n\n\textern ParserGenerator<ExtendedGrammar, ::ParserGeneratorParser>* parserGenerator;\n\n    struct Token {\n        Token(std::string name) : name(name) {}\n        std::string name;\n    };\n\ttypedef Token Keyword;\n    struct Identifier : public Token {\n        Identifier(std::string name) : Token(name) {}\n    };\n\n\tunion ValueType {\n\t\tExtendedGrammar* Grammar;\n\t\tExtendedGrammar::Rules* Rules;\n\t\tExtendedGrammar::Rule* Rule;\n\t\tExtendedGrammar::Productions* Productions;\n\t\tExtendedGrammar::Production* Production;\n\t\tExtendedGrammar::NamedFactors* NamedFactors;\n\t\tExtendedGrammar::NamedFactor* NamedFactor;\n\t\tExtendedGrammar::Factor* Grouping;\n\t\tExtendedGrammar::Selection* Selection;\n\t\tExtendedGrammar::Sequence* Sequence;\n\t\tExtendedGrammar::Factor* Factor;\n\t\tExtendedGrammar::Symbol* Symbol;\n\t\tExtendedGrammar::Identifier* Identifier;\n\t\tExtendedGrammar::StringLiteral* StringLiteral;\n\t\tint Action;\n\t\tCodeBlock* CodeBlock;\n\t};\n\n\textern ValueType currentValue;\n\tusing namespace Runtime;\n", 9, "C:\\Users\\aaron\\Projects\\G\\latest\\G\\src\\tools\\g\\g.pg" }
  }, 
  {
    { "\n\t#include \"g.lg.h\"\n\tValueType currentValue;\n\tunsigned Precedence = 1;\n", 54, "C:\\Users\\aaron\\Projects\\G\\latest\\G\\src\\tools\\g\\g.pg" },
    { "\n\tvoid gParser::reportError(State state, Input input) {\n\t\tstd::string report = std::string(\"Found \") + Terminals[input] + \" Expecting \";\n\n\t\tPair<Action>* pair = ShiftReduce_states[state - 1]->pair;\n\t\tif (pair) {\n\t\t\tfor (size_t pairs = ShiftReduce_states[state - 1]->pairs; pairs > 0; --pairs) {\n                report += std::string(Terminals[pair->input]) + ((pairs > 1) ? \", \" : \"\");\n\t\t\t\t++pair;\n\t\t\t}\n\t\t}\n\t\telse\n            report += std::string(\"<nothing>\");\n        report += std::string(\" in state \") + std::to_string(state) + \".\\\n\";\n\n\t\tG::logger->LogError(new SyntaxErrorObject(report, lexer->getLineNumber(), lexer->getCharacter()));\n\t}\n", 59, "C:\\Users\\aaron\\Projects\\G\\latest\\G\\src\\tools\\g\\g.pg" }
  });

// End C:\Users\aaron\Projects\G\latest\G\src\tools\g\g.lexer.cpp
