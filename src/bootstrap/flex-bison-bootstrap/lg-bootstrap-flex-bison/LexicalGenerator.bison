/**
 *  g/src/bootstrap/flex-bison-bootstrap/lg-bootstrap-flex-bison/LexicalGenerator.bison
 *
 *  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
 */

%{
#include <io.h>
#include <stdlib.h>
#include <iostream>

#include "g/Logger.h"
#include "g/LexicalAnalyserGenerator/Ranges.h"
#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "g/LexicalAnalyserGenerator/LexicalMachine.h"
#include "g/LexicalAnalyserGenerator/LexicalContext.h"
#include "g/LexicalAnalyserGenerator/DFA.h"
#include "g/CodeBlock.h"

#define YYDEBUG 1

extern int yylloc;
extern int yyfnln;

//

using namespace G::LexicalAnalyserGenerator;

extern LexicalGenerator* lexicalGenerator;
extern Logger* logger;
Ranges newline = {Char('\n'), Char('\r')};

%}

//%define api.prefix {LexicalGenerator_yy}

%union {
    LexicalMachine* Machine;
    LexicalContext* Context;
    RegularGrammar::RE* RegularGrammar;
    RegularGrammar::RE* Node;
    int Operator;
    char Symbol;
    const char* String;
    char* Identifier;
    Ranges* ranges;
    CodeBlock* CodeBlock;
    const char* StringLiteral;
    const char* Action;
}

%token KEYWORD_LEXER		"lexer"
%token KEYWORD_START		"start"
%token KEYWORD_MACHINE		"machine"
%token KEYWORD_CODE			"code"
%token KEYWORD_HEADER		"header"
%token KEYWORD_CONTEXT		"context"

%token KEYWORD_ROOTTYPE		"roottype"

%token KEYWORD_BASECLASS	"baseclass"
%token KEYWORD_VALUETYPE	"valuetype"
%token KEYWORD_RETURNTYPE	"returntype"

%token <Identifier> IDENTIFIER
%token <String> STRING
%token <StringLiteral> STRING_LITERAL

%token <Operator> OPERATOR_OR					"|"
%token <Operator> OPERATOR_STAR					"*"
%token <Operator> OPERATOR_PLUS					"+"
%token <Operator> OPERATOR_QUERY				"?"
%token <Operator> OPERATOR_OPEN_PAREN			"("
%token <Operator> OPERATOR_CLOSE_PAREN			")"
%token <Operator> OPERATOR_OPEN_BRACE			"["
%token <Operator> OPERATOR_CLOSE_BRACE			"]"
%token <Operator> OPERATOR_OPEN_CURLY_BRACE		"{"
%token <Operator> OPERATOR_CLOSE_CURLY_BRACE	"}"

%token <Operator> OPERATOR_HYPHEN				"-"
%token <Operator> OPERATOR_CARET				"^"
%token <Operator> OPERATOR_PERIOD				"."

%token <Symbol> SYMBOL
%token <Action> TOKEN_ACTION
%token <CodeBlock> TOKEN_CODE
%token WHITESPACE
%token NEWLINE

%type <Machine> ContextsOpt
%type <Machine> Contexts
%type <Context> Context
%type <RegularGrammar> RegularGrammar
%type <Node> Productions
%type <Node> Production
%type <Node> RegularExpression
%type <Node> Selection
%type <Node> Sequence
%type <Node> Repetition
%type <Node> Factor
%type <ranges> CharacterClass
%type <Action> Action

%%
File : Lexer Footer;

Footer : BlankLines;

BlankLines : BlankLines NEWLINE | /* epsilon */
;

Lexer : "lexer" IDENTIFIER "{" HeadersOpt ContextsOpt "}"
    { $5->setName($2); }
;

HeadersOpt : Headers
    | /* epsilon */
;

Headers : Headers Header
    | Header
;

Header :
    "header" TOKEN_CODE
        { lexicalGenerator->addHeader($2); }
    | "code" TOKEN_CODE
        { lexicalGenerator->addCode($2); }
    | "roottype" STRING_LITERAL
        { lexicalGenerator->setRootType($2); }
    | "baseclass" STRING_LITERAL
        { lexicalGenerator->setBaseClass($2); }
    | "valuetype" STRING_LITERAL
        { lexicalGenerator->setValueType($2); }
    | "returntype" IDENTIFIER
        { lexicalGenerator->setReturnType($2); }
    | "start" IDENTIFIER
        { lexicalGenerator->setStartContext($2); }
;

ContextsOpt :
    Contexts
        { $$ = $1; }
    | /* epsilon */
        { $$ = lexicalGenerator->getMachine(); }
;

Contexts :
    Contexts Context
        { $$ = $1;  $$->addContext($2); }
    | Context
        { $$ = lexicalGenerator->getMachine(); $$->addContext($1); }
;

Context :
    "context" IDENTIFIER "{" RegularGrammar "}"
        { $$ = lexicalGenerator->newContext($2, lexicalGenerator->newRegularGrammar($4)); }
;

RegularGrammar :
    Productions
        { $$ = $1; }
    | /* epsilon */
        { $$ = nullptr; }
;

Productions :
    Productions Production
        { $$ = RegularGrammar::newSelection($1, $2); }
    | Production
        { $$ = $1; }
;

Production :
    RegularExpression Action
        { $$ = RegularGrammar::newSequence($1, RegularGrammar::newEnd(lexicalGenerator->addAction($2, yyfnln)->getIndex())); }
    | STRING Action
        { $$ = RegularGrammar::newEnd(lexicalGenerator->addAction($2, yyfnln)->getIndex()); }
;

Action : TOKEN_ACTION
        { $$ = $1; }
;

RegularExpression : Selection
        { $$ = $1; }
;

Selection :
    Selection "|" Sequence
        { $$ = RegularGrammar::newSelection($1, $3); }
    | Sequence
        { $$ = $1; }
;

Sequence :
    Sequence Repetition
        { $$ = RegularGrammar::newSequence($1, $2); }
    | Repetition
        { $$ = $1; }
;

Repetition : Factor
        { $$ = $1; }
    | Factor "*"
        { $$ = RegularGrammar::newKleene($1); }
    | Factor "+"
        { $$ = RegularGrammar::newSequence($1, RegularGrammar::newKleene($1->clone())); }
    | Factor "?"
        { $$ = RegularGrammar::newOptional($1); }
;

Factor :
    SYMBOL
        { $$ = RegularGrammar::newCharacterClass(CharacterClass(yyval.Symbol)); }
    | "[" CharacterClass "]"
        { $$ = RegularGrammar::newCharacterClass(CharacterClass($2)); }
    | "[" "^" CharacterClass "]"
        { $$ = RegularGrammar::newCharacterClass(CharacterClass($3, true)); }
    | "(" Selection ")"
        { $$ = $2; }
    | OPERATOR_PERIOD
        { $$ = RegularGrammar::newCharacterClass(CharacterClass(newline, true)); }
;

CharacterClass :
    CharacterClass SYMBOL "-" SYMBOL
        { $1->add(Range($2,$4)); $$ = $1; }
    | CharacterClass SYMBOL
        { $1->add(Char($2)); $$ = $1; }
    |
        { $$ = new Ranges(); }
;

%%

/* This function is called automatically when Bison detects a parse error. */
void yyerror(const char *error)
{
    extern int yylloc;
    extern Logger *logger;
    logger->LogError(new SyntaxErrorObject(error, yylloc));
}

// End lg-bootstrap-flex-bison/LexicalGenerator.bison
