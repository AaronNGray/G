/**
 *  g/src/bootstrap/flex-bison-bootstrap/lg-bootstrap-flex-bison/LexicalGenerator.flex
 *
 *  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
 */

%{
#include <io.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "g/LexicalAnalyserGenerator/LexicalMachine.h"
#include "g/LexicalAnalyserGenerator/LexicalContext.h"
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "g/CodeBlock.h"

using namespace G::LexicalAnalyserGenerator;
#include "LexicalGenerator.tab.h"


//#define yylval	LexicalGenerator_yylval
//#define yylex	LexicalGenerator_yylex

#define YY_NEVER_INTERACTIVE 1

int yylloc = 1;
int yyfnln;

int curley_braces = 0;
std::string action;
std::string string;
std::string stringLiteral;


enum MODE { NORMAL, CODE_BLOCK };
MODE bracket_mode = NORMAL;

%}

%option noyywrap

%x LEXER CONTEXT RE CCL ACTION DOUBLE_QUOTED_STRING DOUBLE_QUOTED_STRING_ESCAPE_SEQUENCE ACTION_DOUBLE_QUOTED_STRING CODE CODE_DOUBLE_QUOTED_STRING LEX_STRING_LITERAL COMMENT SINGLE_LINE_COMMENT LEXER_COMMENT LEXER_SINGLE_LINE_COMMENT CONTEXT_COMMENT CONTEXT_SINGLE_LINE_COMMENT

ESCAPE_SEQUENCE				(\\([0-7]{1,3}|[xX][0-9A-Fa-f]{1,2}|[^\n]))
CHARACTER_CLASS_CHARACTER	[^\\\n\]\-]
WHITESPACE					[ \t]*
IDENTIFIER					[A-Za-z_][A-Za-z0-9_]*
NEWLINE						\r?\n

%%

<INITIAL>{
	"lexer"						{ return KEYWORD_LEXER; }
	{IDENTIFIER}				{ yylval.Identifier = _strdup(yytext); return IDENTIFIER; }
	"{"							{ BEGIN(LEXER); return OPERATOR_OPEN_CURLY_BRACE; }
	"}"							{ std::cerr << "Extra invalid closing brace" << std::endl; return OPERATOR_CLOSE_CURLY_BRACE; }
	"/*"						{ BEGIN(COMMENT); }
	"//"						{ BEGIN(SINGLE_LINE_COMMENT); }
	{WHITESPACE}				{}
	{NEWLINE}					{ ++yylloc; /* return NEWLINE; */ }
	.							{ std::cerr << "Invalid chararcter '" << yytext[0] << "' in outer scope on line " << yylloc << std::endl; }
	<<EOF>>						{ yyterminate(); }
}

<LEXER>{
	"context"					{ return KEYWORD_CONTEXT; }
	"start"						{ return KEYWORD_START; }
	"code"						{ bracket_mode = MODE::CODE_BLOCK; return KEYWORD_CODE; }
	"header"					{ bracket_mode = MODE::CODE_BLOCK; return KEYWORD_HEADER; }
	"roottype"					{ return KEYWORD_ROOTTYPE; }
	"baseclass"					{ return KEYWORD_BASECLASS; }
	"valuetype"					{ return KEYWORD_VALUETYPE; }
	"returntype"				{ return KEYWORD_RETURNTYPE; }
	"\""						{ stringLiteral = ""; BEGIN(LEX_STRING_LITERAL); }
	{IDENTIFIER}				{ yylval.Identifier = _strdup(yytext); return IDENTIFIER; }
	"{"							{
								  if (bracket_mode == MODE::NORMAL) {
									BEGIN(CONTEXT);
									return OPERATOR_OPEN_CURLY_BRACE;
								  }
								  else {
									BEGIN(CODE);
									yyfnln = yylloc;
									curley_braces = 1;
									action = "";
									bracket_mode = MODE::NORMAL;
								  }
								}
	"}"							{ BEGIN(INITIAL); return OPERATOR_CLOSE_CURLY_BRACE; }
	"/*"						{ BEGIN(LEXER_COMMENT); }
	"//"						{ BEGIN(LEXER_SINGLE_LINE_COMMENT); }
	{WHITESPACE}				{ }
	{NEWLINE}					{ ++yylloc; }
	.							{ std::cerr << "Invalid chararcter '" << yytext[0] << "' in lexer block on line " << yylloc << std::endl; }
}

<CONTEXT>{
	"/*"						{ BEGIN(CONTEXT_COMMENT); }
	"//"						{ BEGIN(CONTEXT_SINGLE_LINE_COMMENT); }
	\/	    					{ BEGIN(RE); }
	\"  						{ BEGIN(DOUBLE_QUOTED_STRING); }
	"{"							{ BEGIN(ACTION); yyfnln = yylloc; curley_braces = 1; action = yytext[0]; }
	"}"							{ BEGIN(LEXER); return OPERATOR_CLOSE_CURLY_BRACE; }
	{WHITESPACE}				{ }
	{NEWLINE}					{ ++yylloc; }
	.							{ std::cerr << "Invalid chararcter '" << yytext[0] << "' in context block on line " << yylloc << std::endl; }
}

<RE>{
	"\/"							{ BEGIN(CONTEXT); }
	"|"								{ return OPERATOR_OR; }
	"*"								{ return OPERATOR_STAR; }
	"+"								{ return OPERATOR_PLUS; }
	"?"								{ return OPERATOR_QUERY; }
	"("								{ return OPERATOR_OPEN_PAREN; }
	")"								{ return OPERATOR_CLOSE_PAREN; }
	"."								{ return OPERATOR_PERIOD; }
	[A-Za-z0-9]						{ yylval.Symbol = yytext[0]; return SYMBOL; }
	"["								{ BEGIN(CCL); yylval.Symbol = yytext[0]; return OPERATOR_OPEN_BRACE; }
	\\[xX][0-9A-Fa-f]{1,2}			{ yylval.Symbol = (char) strtol(&yytext[2], &yy_cp, 16); return SYMBOL; }
	\\[0-7]{1,3}					{ yylval.Symbol = (char) strtol(&yytext[2], &yy_cp, 8); return SYMBOL; }
	\\a    							{ yylval.Symbol = '\a'; return SYMBOL; }
	\\b    							{ yylval.Symbol = '\b'; return SYMBOL; }
	\\f    							{ yylval.Symbol = '\f'; return SYMBOL; }
	\\n    							{ yylval.Symbol = '\n'; return SYMBOL; }
	\\r    							{ yylval.Symbol = '\r'; return SYMBOL; }
	\\t    							{ yylval.Symbol = '\t'; return SYMBOL; }
	\\v    							{ yylval.Symbol = '\v'; return SYMBOL; }
	\\\'   						    { yylval.Symbol = '\''; return SYMBOL; }
	\\\"   						    { yylval.Symbol = '"'; return SYMBOL; }
	\\\?    						{ yylval.Symbol = '\?'; return SYMBOL; }
	\\\\    						{ yylval.Symbol = '\\'; return SYMBOL; }
	\\\/    						{ yylval.Symbol = '/'; return SYMBOL; }
	\\\] 							{ yylval.Symbol = ']'; return SYMBOL; }
	\\\- 							{ yylval.Symbol = '-'; return SYMBOL; }
	\\.        						{
	                                    std::cerr << "Invalid escape sequence '\\" << yytext[1]
	                                              << "' in regular expression on line " << yylloc << std::endl;
	                                }
	" "     						{ yylval.Symbol = ' '; return SYMBOL; }
	\n								{ ++yylloc; return NEWLINE; }
	. 								{ yylval.Symbol = yytext[0]; return SYMBOL; }
}

<CCL>{
	"]"								{ BEGIN(RE); yylval.Symbol = yytext[0]; return OPERATOR_CLOSE_BRACE; }
	"^"								{ yylval.Symbol = yytext[0]; return OPERATOR_CARET; }
	"-"								{ yylval.Symbol = yytext[0]; return OPERATOR_HYPHEN; }
	[^\\\n\]\-]						{ yylval.Symbol = yytext[0]; return SYMBOL; }
	\\[xX][0-9A-Fa-f]{1,2}			{ yylval.Symbol = (char) strtol(&yytext[2], &yy_cp, 16); return SYMBOL; }
	\\[0-7]{1,3}					{ yylval.Symbol = (char) strtol(&yytext[2], &yy_cp, 8); return SYMBOL; }
	\\a    							{ yylval.Symbol = '\a'; return SYMBOL; }
	\\b    							{ yylval.Symbol = '\b'; return SYMBOL; }
	\\f    							{ yylval.Symbol = '\f'; return SYMBOL; }
	\\n    							{ yylval.Symbol = '\n'; return SYMBOL; }
	\\r    							{ yylval.Symbol = '\r'; return SYMBOL; }
	\\t    							{ yylval.Symbol = '\t'; return SYMBOL; }
	\\v    							{ yylval.Symbol = '\v'; return SYMBOL; }
	\\\'   						    { yylval.Symbol = '\''; return SYMBOL; }
	\\\"   						    { yylval.Symbol = '"'; return SYMBOL; }
	\\\?    						{ yylval.Symbol = '\?'; return SYMBOL; }
	\\\\    						{ yylval.Symbol = '\\'; return SYMBOL; }
	\\\/    						{ yylval.Symbol = '/'; return SYMBOL; }
	\\\]    						{ yylval.Symbol = ']'; return SYMBOL; }
	\\\-    						{ yylval.Symbol = '-'; return SYMBOL; }
	\\.        						{
										yylval.Symbol = yytext[1];
										return SYMBOL;
	                                }
	.								{ yylval.Symbol = yytext[0]; return SYMBOL; }
}

<DOUBLE_QUOTED_STRING>{
    \" 							{ BEGIN(CONTEXT); }
	\\							{ yylval.Symbol = '\\'; BEGIN(DOUBLE_QUOTED_STRING_ESCAPE_SEQUENCE); return SYMBOL; }
    .							{ yylval.Symbol = yytext[0]; return SYMBOL; }
}

<DOUBLE_QUOTED_STRING_ESCAPE_SEQUENCE>{
    [xX][0-9A-Fa-f]+			{ yylval.Symbol = (char) strtol(&yytext[2], &yy_cp, 16); BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    [0-7]+  					{ yylval.Symbol = (char) strtol(&yytext[2], &yy_cp, 8); BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    a    						{ yylval.Symbol = 'a'; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    b    						{ yylval.Symbol = 'b'; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    f    						{ yylval.Symbol = 'f'; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    n    						{ yylval.Symbol = 'n'; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    r    						{ yylval.Symbol = 'r'; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    t    						{ yylval.Symbol = 't'; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    v    						{ yylval.Symbol = 'v'; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    \\	    					{ yylval.Symbol = '\\'; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    \'	    					{ yylval.Symbol = '\''; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    \"	    					{ yylval.Symbol = '"'; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    \?    						{ yylval.Symbol = '?'; BEGIN(DOUBLE_QUOTED_STRING); return SYMBOL; }
    .		   					{
    	                            std::cerr << "Invalid escape sequence '\\" << yytext[0]
    	                                        << "' in quoted string on line " << yylloc << std::endl;
    	                            BEGIN(DOUBLE_QUOTED_STRING);
    	                        }
}

<ACTION>{
	"{"								{ action += yytext[0]; ++curley_braces; }
	"}"								{
										action += "}";
										if (--curley_braces == 0) {
											BEGIN(CONTEXT);
											yylval.Action = action.c_str();
											return TOKEN_ACTION;
										}
									}
	"\""							{ BEGIN(ACTION_DOUBLE_QUOTED_STRING); action += "\""; }
	\'{ESCAPE_SEQUENCE}\'			{ action += yytext; }
	\'/\'							{ action += yytext; }
	\'.\'							{ action += yytext; }
	\r?\n+							{ ++yylloc; action += '\n'; }
	.								{ action += yytext[0]; }
}

<ACTION_DOUBLE_QUOTED_STRING>{
	"\""							{ action += yytext[0]; BEGIN(ACTION); }
	{ESCAPE_SEQUENCE}				{ action += yytext; }
	.								{ action += yytext[0]; }
}

<CODE>{
	"{"								{ action += yytext[0]; ++curley_braces; }
	"}"								{
										if (--curley_braces == 0) {
											BEGIN(LEXER);
											yylval.CodeBlock = new CodeBlock(action, yyfnln, "");	// TODO: Ignore
											return TOKEN_CODE;
										}
										else
										  action += "}";
									}
	"\""							{ BEGIN(CODE_DOUBLE_QUOTED_STRING); action += "\""; }
	\'{ESCAPE_SEQUENCE}\'			{ action += yytext; }
	\'/\'							{ action += yytext; }
	\'.\'							{ action += yytext; }
	\r?\n+							{ ++yylloc; action += '\n'; }
	.								{ action += yytext[0]; }
}

<CODE_DOUBLE_QUOTED_STRING>{
	"\""							{ action += yytext[0]; BEGIN(CODE); }
	{ESCAPE_SEQUENCE}				{ action += yytext; }
	.								{ action += yytext[0]; }
}

<LEX_STRING_LITERAL>{
		"\"" 						{
										yylval.StringLiteral = stringLiteral.c_str();
										BEGIN(LEXER);
										return STRING_LITERAL;
									}
    	.							{ stringLiteral += yytext[0]; }
    }

<COMMENT>{
	"*/"							{ BEGIN(INITIAL); }
	\r								{}
	\n								{ ++yylloc; }
	.								{}
}
<SINGLE_LINE_COMMENT>{
	\r?\n							{ ++yylloc; BEGIN(INITIAL); }
	.								{}
}
<LEXER_COMMENT>{
	"*/"							{ BEGIN(LEXER); }
	\r								{}
	\n								{ ++yylloc; }
	.								{}
}
<LEXER_SINGLE_LINE_COMMENT>{
	\r?\n							{ ++yylloc; BEGIN(LEXER); }
	.								{}
}
<CONTEXT_COMMENT>{
	"*/"							{ BEGIN(CONTEXT); }
	\r								{}
	\n								{ ++yylloc; }
	.								{}
}
<CONTEXT_SINGLE_LINE_COMMENT>{
	\r?\n							{ ++yylloc; BEGIN(CONTEXT); }
	.								{}
}

%%
