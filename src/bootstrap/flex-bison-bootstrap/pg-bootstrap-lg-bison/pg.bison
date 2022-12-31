//
//	g/src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison/pg.bison
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

%{
#include <io.h>
#include <iostream>
#include <cassert>
#include "g/Grammar/ContextFreeGrammar.h"
#include "g/ParserGenerator/ParserGeneratorParser.h"
#include "g/ParserGenerator/ParserGenerator.h"
#include "g/CodeBlock.h"
#include "g/Actions.h"
#include "pg.lg.h"

//#define YYDEBUG 1

//void yyrestart(FILE *input_file);
void yyerror(const char *s);
extern int yylloc;
extern int yyfnln;

//#define yylex() (lexer->lex())
int yylex();

using namespace G::ParserGenerator;

extern pgLexer		*lexer;
extern ContextFreeGrammar *grammar;
extern ParserGenerator<ContextFreeGrammar>* parserGenerator;
extern Logger* logger;

unsigned Precedence = 1;
%}

//%define api.prefix {Grammar_yy}

%union {
  ContextFreeGrammar *Grammar;
  ContextFreeGrammar::Rules *Rules;
  ContextFreeGrammar::Rule *Rule;
  ContextFreeGrammar::Productions *Productions;
  ContextFreeGrammar::Production *Production;
  ContextFreeGrammar::NamedSymbols *NamedSymbols;
  ContextFreeGrammar::NamedSymbol *NamedSymbol;
  ContextFreeGrammar::Symbol *Symbol;
  ContextFreeGrammar::Identifier *Identifier;
  ContextFreeGrammar::StringLiteral *StringLiteral;
  int Action;
  CodeBlock *CodeBlock;
}

%token KEYWORD_GRAMMAR			"grammar"
%token KEYWORD_TERM				"term"
%token KEYWORD_NONTERM			"nonterm"
%token KEYWORD_PRODUCTION		"production"

%token KEYWORD_START			"start"
%token KEYWORD_EPSILON			"epsilon"

%token KEYWORD_HEADER			"header"
%token KEYWORD_CODE				"code"

%token KEYWORD_ROOTTYPE			"roottype"

%token KEYWORD_BASECLASS		"baseclass"
%token KEYWORD_BASETYPE			"basetype"
%token KEYWORD_RETURNTYPE		"returntype"
%token KEYWORD_UNION			"union"

%token KEYWORD_NONASSOC			"nonassoc"
%token KEYWORD_LEFT				"left"
%token KEYWORD_RIGHT			"right"

%token <Operator>		OPERATOR_DOLLAR				"$"
%token <Operator>		OPERATOR_EQUALS				"="
%token <Operator>		OPERATOR_COLON				":"
%token <Operator>		OPERATOR_OR					"|"
%token <Operator>		OPERATOR_SEMICOLON			";"
%token <Operator>		OPERATOR_OPEN_CURLY_BRACE	"{"
%token <Operator>		OPERATOR_CLOSE_CURLY_BRACE	"}"

%token <Identifier>		IDENTIFIER
%token <StringLiteral>	STRING_LITERAL
%token <Action>			TOKEN_ACTION
%token <CodeBlock>		TOKEN_CODE
%token NEWLINE

%type <Grammar> Grammar
%type <Rules> Rules
%type <Rule> Rule
%type <Productions> Productions
%type <Production> Production
%type <NamedSymbols> NamedSymbols
%type <NamedSymbol> NamedSymbol
%type <Symbol> Symbol
%type <Identifier> Identifier

%%
File : Grammar;

Grammar: "grammar" IDENTIFIER STRING_LITERAL "{" Headers Precedences Rules "}" Footer
	{
		parserGenerator->setName($2->getValue());
		parserGenerator->setType($3->getValue());
	}
;

Headers :
	Header ";" Headers
  | Header ";"
;

Header :
	"term" Identifier
		{ grammar->addTerminal(grammar->create<ContextFreeGrammar::Terminal>($2)); }
  | "term" Identifier ":" Identifier
		{ grammar->addTerminal(grammar->create<ContextFreeGrammar::Terminal>($2, $4)); }
  | "term" Identifier STRING_LITERAL
		{ grammar->addTerminal(grammar->create<ContextFreeGrammar::Terminal>($2, $3)); }
  | "term" Identifier ":" Identifier STRING_LITERAL
		{ grammar->addTerminal(grammar->create<ContextFreeGrammar::Terminal>($2, $4, $5)); }
  | "nonterm" Identifier
  		{ grammar->addNonTerminal(grammar->create<ContextFreeGrammar::NonTerminal>($2, $2)); }
  | "nonterm" Identifier ":" Identifier
  		{ grammar->addNonTerminal(grammar->create<ContextFreeGrammar::NonTerminal>($2, $4)); }
  | "start" Identifier
		{ grammar->setStartSymbol(grammar->getNonTerminal($2)); }
  | "header" TOKEN_CODE
		{ parserGenerator->addHeader($2); }
  | "code" TOKEN_CODE
		{ parserGenerator->addCode($2); }
  | "roottype" STRING_LITERAL
		{ parserGenerator->setRootType($2->getValue()); }
  | "baseclass" STRING_LITERAL
		{ parserGenerator->setBaseClass($2->getValue()); }
  | "basetype" STRING_LITERAL
		{ parserGenerator->setBaseType($2->getValue()); }
  | "basetype" "union" STRING_LITERAL
		{ parserGenerator->setBaseType($3->getValue(), true); }
  | "returntype" STRING_LITERAL
		{ parserGenerator->setReturnType($2->getValue()); }
  | BlankLines
;

Precedences :
    Precedences Precedence ";" { ++Precedence; }
  | Precedence ";" { ++Precedence; }
  |
;

Precedence :
    "nonassoc" NonAssociativeTerminals
  | "left" LeftAssociativeTerminals
  | "right" RightAssociativeTerminals
;

NonAssociativeTerminals:
    NonAssociativeTerminals NonAssociativeTerminal
  | NonAssociativeTerminal
;

NonAssociativeTerminal :
	STRING_LITERAL
		{
			ContextFreeGrammar::Terminal* terminal = grammar->getTerminal($1);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::None);
			terminal->setPrecedence(Precedence);
		}
  | Identifier
		{
			ContextFreeGrammar::Terminal* terminal = grammar->getTerminal($1);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::None);
			terminal->setPrecedence(Precedence);
		}
;

LeftAssociativeTerminals :
    LeftAssociativeTerminals LeftAssociativeTerminal
  | LeftAssociativeTerminal
;

LeftAssociativeTerminal :
	STRING_LITERAL
		{
			ContextFreeGrammar::Terminal* terminal = grammar->getTerminal($1);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::Left);
			terminal->setPrecedence(Precedence);
		}
  | Identifier
		{
			ContextFreeGrammar::Terminal* terminal = grammar->getTerminal($1);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::Left);
			terminal->setPrecedence(Precedence);
		}
;

RightAssociativeTerminals :
    RightAssociativeTerminals RightAssociativeTerminal
  | RightAssociativeTerminal
;

RightAssociativeTerminal :
	STRING_LITERAL
		{
			ContextFreeGrammar::Terminal* terminal = grammar->getTerminal($1);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::Right);
			terminal->setPrecedence(Precedence);
		}
  | Identifier
		{
			ContextFreeGrammar::Terminal* terminal = grammar->getTerminal($1);
			terminal->setAssociativity(ContextFreeGrammar::Associativity::Right);
			terminal->setPrecedence(Precedence);
		}
;

Footer : BlankLines
;

BlankLines : BlankLines NEWLINE | /* empty */
;

Rules :
    Rule ";" Rules
      { grammar->addRule($1); }
  | Rule ";"
      { grammar->addRule($1); }
;

Rule : "production" Identifier "=" Productions
		{ $$ = grammar->findOrCreateRule($2, $4); }
;

Productions : Productions "|" Production
    { $$ = $1; $1->addProduction($3); }
  | Production
    { $$ = grammar->newProductions(); $$->addProduction($1); }
;

Production : NamedSymbols
    { $$ = grammar->newProduction($1); }
  | NamedSymbols TOKEN_ACTION
    { $$ = grammar->newProduction($1, $2, false); }
  | "epsilon"
	{ $$ = grammar->newProduction(); }
  | "epsilon" TOKEN_ACTION
	{ $$ = grammar->newProduction($2, false); }
  | /* epsilon */
	{ $$ = grammar->newProduction(); }
  | TOKEN_ACTION
	{ $$ = grammar->newProduction($1, false); }
;

NamedSymbols :
  NamedSymbols NamedSymbol
    { $$ = $1; $1->addSymbol($2); }
  | NamedSymbol
    { $$ = grammar->newNamedSymbols(); $$->addSymbol($1); }
;

NamedSymbol : Identifier ":" Symbol
    { $$ = grammar->newNamedSymbol($1, $3); }
  | Symbol
    { $$ = grammar->newNamedSymbol($1); }
;

Symbol : Identifier
    { $$ = grammar->findOrCreateSymbol($1); }
  | STRING_LITERAL
    {
		ContextFreeGrammar::Symbol* symbol = grammar->getTerminal($1);
		if (symbol == ContextFreeGrammar::getErrorSymbol()) {
			std::cout << "test: " << $1->getValue() << std::endl;
			logger->LogError(new UndefinedTerminalSymbolErrorObject($1->getValue(), yylloc));
		}
		$$ = symbol;
	}
  | "$"
    { $$ = grammar->getTerminal(grammar->newStringLiteral("$")); }
;

Keyword:
	"grammar"
	| "term"
	| "nonterm"
	| "productions"
	| "start"
	| "code"
	| "header"
	| "baseclass"
	| "roottype"
	| "basetype"
	| "returntype"
	| "union"
	| "nonassoc"
	| "left"
	| "right"
	| "epsilon"
;

Identifier:
	Keyword
	| IDENTIFIER
;

%%

/* This function is called automatically when Bison detects a parse error. */
void yyerror(const char *error) {
  extern int yylloc, yystate, yytoken;
  logger->LogError(new SyntaxErrorObject(error, yylloc));
}

// End g/src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison/pg.bison
