//
//	g/src/tools/g/ParserGeneratorParser.h
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/File.h"
#include "g/Logger.h"
#include "g/Grammar/ExtendedGrammar.h"
#include "runtime/lexer/Lexer.h"
#include "g.lg.h"
#include "g.pg.h"

//
// singleton class LexicalGeneratorParser
//

class ParserGeneratorParser {
public:
    ParserGeneratorParser(Logger *logger, bool lineDirectives = true, unsigned debug = 0) : logger(logger), lineDirectives(lineDirectives), debug(debug) {}

	virtual bool Parse(File<FILE*>* file) {
        gLexer* lexer = new gLexer(*file, currentValue, grammar);
        gParser parser(lexer, currentValue, grammar, (debug != 0));
		return parser.parse();
	}
    virtual ~ParserGeneratorParser() {}

	ExtendedGrammar* getGrammar() { return grammar; }

	Actions* actions;
	ExtendedGrammar* grammar;

	unsigned debug;
	Logger *logger;
	bool lineDirectives;
};

// End g/src/tools/g/ParserGeneratorParser.h
