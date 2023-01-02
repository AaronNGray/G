//
//	g/bootstrap/self-bootstrap/pg-bootstrap/ParserGeneratorParser.cpp
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/File.h"
#include "g/logger.h"
#include "g/ParserGenerator/ParserGeneratorParser.h"
#include "g/CodeBlock.h"
#include "runtime/lexer/Lexer.h"
#include "pg.lg.h"

//
// singleton class LexicalGeneratorParser
//

//extern pgLexer* lexer;
//extern Grammar* grammar;

class ParserGeneratorParser_LGPG : public ParserGeneratorParser {
public:
    ParserGeneratorParser_LGPG(Logger *logger, bool lineDirectives = true, unsigned debug = 0) : ParserGeneratorParser(logger, lineDirectives, debug) {
//        ::grammar = grammar; // TODO: fold in and remove !!!
    }

    int root;

	virtual bool Parse(File<FILE*>* file) {
        pgLexer* lexer = new pgLexer(*file, currentValue, grammar);
        pgParser parser(lexer, currentValue, grammar, (debug != 0));
		return parser.parse();
	}
  virtual ~ParserGeneratorParser_LGPG() {}

  //Grammar* grammar;
};

// End g/bootstrap/self-bootstrap/pg-bootstrap/ParserGeneratorParser.cpp
