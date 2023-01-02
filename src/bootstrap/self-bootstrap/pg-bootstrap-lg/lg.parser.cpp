#include "g/ParserGenerator/ParserGenerator.h"
#include "g/Grammar/Grammar.h"
#include "g/Actions.h"
#include "nonstd/File.h"

using namespace G::ParserGenerator;

Actions bootstrapActions = {
	{ 0, "{ $machine$->setName(*$name$); }", 142},
	{ 1, "{ lexicalGenerator->addHeader($2); }", 155},
	{ 2, "{ lexicalGenerator->addCode($2); }", 157},
	{ 3, "{ lexicalGenerator->setBaseClass($2); }", 159},
	{ 4, "{ lexicalGenerator->setRootType($2); }", 161},
	{ 5, "{ lexicalGenerator->setValueType($2); }", 163},
	{ 6, "{ lexicalGenerator->setReturnType($2); }", 165},
	{ 7, "{ lexicalGenerator->setStartContext(*$2); }", 167},
	{ 8, "{ $$ = $1; }", 172},
	{ 9, "{ $$ = lexicalGenerator->getMachine(); }", 174},
	{ 10, "{ $$ = $1;  $$->addContext($2); }", 179},
	{ 11, "{ $$ = lexicalGenerator->getMachine(); $$->addContext($1); }", 181},
	{ 12, "{ $$ = lexicalGenerator->newContext(*$2, lexicalGenerator->newRegularGrammar($4)); }", 186},
	{ 13, "{ $$ = $1; }", 191},
	{ 14, "{ $$ = nullptr; }", 193},
	{ 15, "{ $$ = RegularGrammar::newSelection($1, $2); }", 198},
	{ 16, "{ $$ = $1; }", 200},
	{ 17, "{ $$ = RegularGrammar::newSequence($1, RegularGrammar::newEnd(lexicalGenerator->addAction($2, yyfnln)->getIndex())); }", 205},
	{ 18, "{ $$ = RegularGrammar::newEnd(lexicalGenerator->addAction($2, yyfnln)->getIndex()); }", 207},
	{ 19, "{ $$ = $1; }", 211},
	{ 20, "{ $$ = RegularGrammar::newSelection($1, $3); }", 216},
	{ 21, "{ $$ = $1; }", 218},
	{ 22, "{ $$ = RegularGrammar::newSequence($1, $2); }", 223},
	{ 23, "{ $$ = $1; }", 225},
	{ 24, "{ $$ = $1; }", 229},
	{ 25, "{ $$ = RegularGrammar::newKleene($1); }", 231},
	{ 26, "{ $$ = RegularGrammar::newSequence($1, RegularGrammar::newKleene($1->clone())); }", 233},
	{ 27, "{ $$ = RegularGrammar::newOptional($1); }", 235},
	{ 28, "{ $$ = RegularGrammar::newCharacterClass(CharacterClass($1)); }", 240},
	{ 29, "{ $$ = RegularGrammar::newCharacterClass(CharacterClass($2)); }", 242},
	{ 30, "{ $$ = RegularGrammar::newCharacterClass(CharacterClass($3, true)); }", 244},
	{ 31, "{ $$ = $2; }", 246},
	{ 32, "{ $$ = RegularGrammar::newCharacterClass(CharacterClass(newline, true)); }", 248},
	{ 33, "{ $1->add(Range($2,$4)); $$ = $1; }", 253},
	{ 34, "{ $1->add(Char($2)); $$ = $1; }", 255},
	{ 35, "{ $$ = new Ranges(); }", 257}
};

ContextFreeGrammar* lg_bootstrap() {
	ContextFreeGrammar* lg_ContextFreeGrammar = new ContextFreeGrammar("lg");

	ContextFreeGrammar::Terminal *KEYWORD_LEXER = lg_ContextFreeGrammar->addTerminal("KEYWORD_LEXER","", "lexer", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_START = lg_ContextFreeGrammar->addTerminal("KEYWORD_START","", "start", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_MACHINE = lg_ContextFreeGrammar->addTerminal("KEYWORD_MACHINE","", "machine", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_CODE = lg_ContextFreeGrammar->addTerminal("KEYWORD_CODE","", "code", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_HEADER = lg_ContextFreeGrammar->addTerminal("KEYWORD_HEADER","", "header", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_CONTEXT = lg_ContextFreeGrammar->addTerminal("KEYWORD_CONTEXT","", "context", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_BASECLASS = lg_ContextFreeGrammar->addTerminal("KEYWORD_BASECLASS","", "baseclass", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_ROOTTYPE = lg_ContextFreeGrammar->addTerminal("KEYWORD_ROOTTYPE","", "roottype", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_VALUETYPE = lg_ContextFreeGrammar->addTerminal("KEYWORD_VALUETYPE","", "valuetype", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_RETURNTYPE = lg_ContextFreeGrammar->addTerminal("KEYWORD_RETURNTYPE","", "returntype", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *IDENTIFIER = lg_ContextFreeGrammar->addTerminal("IDENTIFIER","Identifier", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *STRING = lg_ContextFreeGrammar->addTerminal("STRING","String", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *STRING_LITERAL = lg_ContextFreeGrammar->addTerminal("STRING_LITERAL","StringLiteral", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OR = lg_ContextFreeGrammar->addTerminal("OPERATOR_OR","Operator", "|", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_STAR = lg_ContextFreeGrammar->addTerminal("OPERATOR_STAR","Operator", "*", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_PLUS = lg_ContextFreeGrammar->addTerminal("OPERATOR_PLUS","Operator", "+", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_QUERY = lg_ContextFreeGrammar->addTerminal("OPERATOR_QUERY","Operator", "?", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_PAREN = lg_ContextFreeGrammar->addTerminal("OPERATOR_OPEN_PAREN","Operator", "(", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_PAREN = lg_ContextFreeGrammar->addTerminal("OPERATOR_CLOSE_PAREN","Operator", ")", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_BRACE = lg_ContextFreeGrammar->addTerminal("OPERATOR_OPEN_BRACE","Operator", "[", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_BRACE = lg_ContextFreeGrammar->addTerminal("OPERATOR_CLOSE_BRACE","Operator", "]", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_CURLY_BRACE = lg_ContextFreeGrammar->addTerminal("OPERATOR_OPEN_CURLY_BRACE","Operator", "{", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_CURLY_BRACE = lg_ContextFreeGrammar->addTerminal("OPERATOR_CLOSE_CURLY_BRACE","Operator", "}", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_HYPHEN = lg_ContextFreeGrammar->addTerminal("OPERATOR_HYPHEN","Operator", "-", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CARET = lg_ContextFreeGrammar->addTerminal("OPERATOR_CARET","Operator", "^", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_PERIOD = lg_ContextFreeGrammar->addTerminal("OPERATOR_PERIOD","Operator", ".", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *SYMBOL = lg_ContextFreeGrammar->addTerminal("SYMBOL","Symbol", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *TOKEN_ACTION = lg_ContextFreeGrammar->addTerminal("TOKEN_ACTION","Action", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *TOKEN_CODE = lg_ContextFreeGrammar->addTerminal("TOKEN_CODE","CodeBlock", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *WHITESPACE = lg_ContextFreeGrammar->addTerminal("WHITESPACE","", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *NEWLINE = lg_ContextFreeGrammar->addTerminal("NEWLINE","", "", ContextFreeGrammar::None, 0, false);

	ContextFreeGrammar::Terminal *EPSILON = lg_ContextFreeGrammar->getTerminal("EPSILON");
	ContextFreeGrammar::Terminal *END = lg_ContextFreeGrammar->getTerminal("END");

	ContextFreeGrammar::NonTerminal *File = lg_ContextFreeGrammar->addNonTerminal("File", "File");
	ContextFreeGrammar::NonTerminal *Footer = lg_ContextFreeGrammar->addNonTerminal("Footer", "Footer");
	ContextFreeGrammar::NonTerminal *BlankLines = lg_ContextFreeGrammar->addNonTerminal("BlankLines", "BlankLines");
	ContextFreeGrammar::NonTerminal *Lexer = lg_ContextFreeGrammar->addNonTerminal("Lexer", "Lexer");
	ContextFreeGrammar::NonTerminal *HeadersOpt = lg_ContextFreeGrammar->addNonTerminal("HeadersOpt", "HeadersOpt");
	ContextFreeGrammar::NonTerminal *Headers = lg_ContextFreeGrammar->addNonTerminal("Headers", "Headers");
	ContextFreeGrammar::NonTerminal *Header = lg_ContextFreeGrammar->addNonTerminal("Header", "Header");
	ContextFreeGrammar::NonTerminal *ContextsOpt = lg_ContextFreeGrammar->addNonTerminal("ContextsOpt", "Machine");
	ContextFreeGrammar::NonTerminal *Contexts = lg_ContextFreeGrammar->addNonTerminal("Contexts", "Machine");
	ContextFreeGrammar::NonTerminal *Context = lg_ContextFreeGrammar->addNonTerminal("Context", "Context");
	ContextFreeGrammar::NonTerminal *RegularGrammar = lg_ContextFreeGrammar->addNonTerminal("RegularGrammar", "RegularGrammar");
	ContextFreeGrammar::NonTerminal *Productions = lg_ContextFreeGrammar->addNonTerminal("Productions", "Node");
	ContextFreeGrammar::NonTerminal *Production = lg_ContextFreeGrammar->addNonTerminal("Production", "Node");
	ContextFreeGrammar::NonTerminal *RegularExpression = lg_ContextFreeGrammar->addNonTerminal("RegularExpression", "Node");
	ContextFreeGrammar::NonTerminal *Selection = lg_ContextFreeGrammar->addNonTerminal("Selection", "Node");
	ContextFreeGrammar::NonTerminal *Sequence = lg_ContextFreeGrammar->addNonTerminal("Sequence", "Node");
	ContextFreeGrammar::NonTerminal *Repetition = lg_ContextFreeGrammar->addNonTerminal("Repetition", "Node");
	ContextFreeGrammar::NonTerminal *Factor = lg_ContextFreeGrammar->addNonTerminal("Factor", "Node");
	ContextFreeGrammar::NonTerminal *CharacterClass = lg_ContextFreeGrammar->addNonTerminal("CharacterClass", "ranges");

	lg_ContextFreeGrammar->setStartSymbol(File);
	lg_ContextFreeGrammar->addRule(File, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Lexer),
			lg_ContextFreeGrammar->newNamedSymbol(Footer)
		}, -1)
	});
	lg_ContextFreeGrammar->addRule(Footer, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(BlankLines)
		}, -1)
	});
	lg_ContextFreeGrammar->addRule(BlankLines, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(BlankLines),
			lg_ContextFreeGrammar->newNamedSymbol(NEWLINE)
		}, -1),
		lg_ContextFreeGrammar->addProduction({}, -1)
	});
	lg_ContextFreeGrammar->addRule(Lexer, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(KEYWORD_LEXER),
			lg_ContextFreeGrammar->newNamedSymbol("name", IDENTIFIER),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			lg_ContextFreeGrammar->newNamedSymbol(HeadersOpt),
			lg_ContextFreeGrammar->newNamedSymbol("machine", ContextsOpt),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE)
		}, 0)
	});
	lg_ContextFreeGrammar->addRule(HeadersOpt, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Headers)
		}, -1),
		lg_ContextFreeGrammar->addProduction({}, -1)
	});
	lg_ContextFreeGrammar->addRule(Headers, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Headers),
			lg_ContextFreeGrammar->newNamedSymbol(Header)
		}, -1),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Header)
		}, -1)
	});
	lg_ContextFreeGrammar->addRule(Header, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(KEYWORD_HEADER),
			lg_ContextFreeGrammar->newNamedSymbol(TOKEN_CODE)
		}, 1),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(KEYWORD_CODE),
			lg_ContextFreeGrammar->newNamedSymbol(TOKEN_CODE)
		}, 2),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(KEYWORD_BASECLASS),
			lg_ContextFreeGrammar->newNamedSymbol(STRING_LITERAL)
		}, 3),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(KEYWORD_ROOTTYPE),
			lg_ContextFreeGrammar->newNamedSymbol(STRING_LITERAL)
		}, 4),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(KEYWORD_VALUETYPE),
			lg_ContextFreeGrammar->newNamedSymbol(STRING_LITERAL)
		}, 5),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(KEYWORD_RETURNTYPE),
			lg_ContextFreeGrammar->newNamedSymbol(STRING_LITERAL)
		}, 6),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(KEYWORD_START),
			lg_ContextFreeGrammar->newNamedSymbol(IDENTIFIER)
		}, 7)
	});
	lg_ContextFreeGrammar->addRule(ContextsOpt, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Contexts)
		}, 8),
		lg_ContextFreeGrammar->addProduction({}, 9)
	});
	lg_ContextFreeGrammar->addRule(Contexts, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Contexts),
			lg_ContextFreeGrammar->newNamedSymbol(Context)
		}, 10),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Context)
		}, 11)
	});
	lg_ContextFreeGrammar->addRule(Context, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(KEYWORD_CONTEXT),
			lg_ContextFreeGrammar->newNamedSymbol(IDENTIFIER),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			lg_ContextFreeGrammar->newNamedSymbol(RegularGrammar),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE)
		}, 12)
	});
	lg_ContextFreeGrammar->addRule(RegularGrammar, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Productions)
		}, 13),
		lg_ContextFreeGrammar->addProduction({}, 14)
	});
	lg_ContextFreeGrammar->addRule(Productions, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Productions),
			lg_ContextFreeGrammar->newNamedSymbol(Production)
		}, 15),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Production)
		}, 16)
	});
	lg_ContextFreeGrammar->addRule(Production, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(RegularExpression),
			lg_ContextFreeGrammar->newNamedSymbol(TOKEN_ACTION)
		}, 17),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(STRING),
			lg_ContextFreeGrammar->newNamedSymbol(TOKEN_ACTION)
		}, 18)
	});
	lg_ContextFreeGrammar->addRule(RegularExpression, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Selection)
		}, 19)
	});
	lg_ContextFreeGrammar->addRule(Selection, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Selection),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_OR),
			lg_ContextFreeGrammar->newNamedSymbol(Sequence)
		}, 20),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Sequence)
		}, 21)
	});
	lg_ContextFreeGrammar->addRule(Sequence, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Sequence),
			lg_ContextFreeGrammar->newNamedSymbol(Repetition)
		}, 22),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Repetition)
		}, 23)
	});
	lg_ContextFreeGrammar->addRule(Repetition, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Factor)
		}, 24),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Factor),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_STAR)
		}, 25),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Factor),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_PLUS)
		}, 26),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(Factor),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_QUERY)
		}, 27)
	});
	lg_ContextFreeGrammar->addRule(Factor, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(SYMBOL)
		}, 28),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_OPEN_BRACE),
			lg_ContextFreeGrammar->newNamedSymbol(CharacterClass),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_CLOSE_BRACE)
		}, 29),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_OPEN_BRACE),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_CARET),
			lg_ContextFreeGrammar->newNamedSymbol(CharacterClass),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_CLOSE_BRACE)
		}, 30),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_OPEN_PAREN),
			lg_ContextFreeGrammar->newNamedSymbol(Selection),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_CLOSE_PAREN)
		}, 31),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_PERIOD)
		}, 32)
	});
	lg_ContextFreeGrammar->addRule(CharacterClass, {
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(CharacterClass),
			lg_ContextFreeGrammar->newNamedSymbol(SYMBOL),
			lg_ContextFreeGrammar->newNamedSymbol(OPERATOR_HYPHEN),
			lg_ContextFreeGrammar->newNamedSymbol(SYMBOL)
		}, 33),
		lg_ContextFreeGrammar->addProduction({
			lg_ContextFreeGrammar->newNamedSymbol(CharacterClass),
			lg_ContextFreeGrammar->newNamedSymbol(SYMBOL)
		}, 34),
		lg_ContextFreeGrammar->addProduction({}, 35)
	});
	lg_ContextFreeGrammar->setActions(&bootstrapActions);

	return lg_ContextFreeGrammar;
}

ParserGenerator<ContextFreeGrammar>* lg_ParserGenerator() {
	FileName filename("lg");
	return new ParserGenerator<ContextFreeGrammar>(
		filename, lg_bootstrap(),
		"RegularGrammar",
		"ValueType",
		"true",
		"void",
    {
      { "\n\t#include <io.h>\n\t#include <stdlib.h>\n\t#include <iostream>\n\n\t#include \"g/Logger.h\"\n\t#include \"g/LexicalAnalyserGenerator/Ranges.h\"\n\t#include \"g/LexicalAnalyserGenerator/LexicalGenerator.h\"\n\t#include \"g/LexicalAnalyserGenerator/LexicalMachine.h\"\n\t#include \"g/LexicalAnalyserGenerator/LexicalContext.h\"\n\t#include \"g/LexicalAnalyserGenerator/DFA.h\"\n\t#include \"g/LexicalAnalyserGenerator/RegularGrammar.h\"\n\t#include \"g/CodeBlock.h\"\n\n\tusing namespace G::LexicalAnalyserGenerator;\n\n\textern LexicalGenerator*\tlexicalGenerator;\n\n\tunion ValueType {\n    \tLexicalMachine* Machine;\n    \tLexicalContext* Context;\n    \tRegularGrammar::RE* RegularGrammar;\n    \tRegularGrammar::RE* Node;\n    \tint Operator;\n    \tchar Symbol;\n    \tconst char* String;\n    \tLexicalMachine::Identifier* Identifier;\n    \tRanges* ranges;\n\t\tCodeBlock* CodeBlock;\n    \tconst char* StringLiteral;\n    \tconst char* Action;\t\t\t\t// TODO: Promote to Action and Code classes/objects !\n\t};\n\n\t//extern int yylloc;\n\textern int yyfnln;\n\textern ValueType currentValue;\n\n\tusing namespace Runtime;\n", 9, "C:\\Users\\aaron\\Projects\\G\\latest\\G - saving 6\\src\\bootstrap\\self-bootstrap\\pg-bootstrap-lg\\lg.pg" }
    }, 
    {
      { "\n\tValueType currentValue;\n\n\tRanges newline = {Char('\\n'), Char('\\r')};\n", 49, "C:\\Users\\aaron\\Projects\\G\\latest\\G - saving 6\\src\\bootstrap\\self-bootstrap\\pg-bootstrap-lg\\lg.pg" },
      { "\n    void lgParser::reportError(State state, Input input) {\n        std::string report = std::string(\"Found \") + getTerminalName(input) + \" Expecting \";\n\n        Pair<Action>* pair = ShiftReduce_states[state - 1]->pair;\n        if (pair) {\n            for (size_t pairs = ShiftReduce_states[state - 1]->pairs; pairs > 0; --pairs) {\n                report += getTerminalName(pair->input) + ((pairs > 1) ? \", \" : \"\");\n                ++pair;\n            }\n        }\n        else\n            report += std::string(\"<nothing>\");\n        report += std::string(\" in state \") + std::to_string(state) + \".\\\n\";\n\n        logger->LogError(new SyntaxErrorObject(report, lexer->getLineNumber(), lexer->getCharacter()));\n    }\n", 54, "C:\\Users\\aaron\\Projects\\G\\latest\\G - saving 6\\src\\bootstrap\\self-bootstrap\\pg-bootstrap-lg\\lg.pg" }
    }
	);
}

// End C:\Users\aaron\Projects\G\latest\G - saving 6\src\bootstrap\self-bootstrap\pg-bootstrap-lg\lg.lexer.cpp
