//
//	g/src/tools/pg/ParserGeneratorParser.h
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/File.h"
#include "g/Logger.h"
#include "g/ParserGenerator/ParserGeneratorParser.h"
#include "runtime/lexer/Lexer.h"
#include "pg.lg.h"
#include "pg.pg.h"

//
// singleton class LexicalGeneratorParser
//

class ParserGeneratorParser_LGPG : public ParserGeneratorParser {
public:
    ParserGeneratorParser_LGPG(Logger *logger, bool lineDirectives = true, unsigned debug = 0) : ParserGeneratorParser(logger, lineDirectives, debug) {}

    virtual bool Parse(File<FILE*>* file) {
        pgLexer* lexer = new pgLexer(*file, currentValue, grammar);
        pgParser parser(lexer, currentValue, grammar, (debug != 0));
        return parser.parse();
    }
    virtual ~ParserGeneratorParser_LGPG() {}
};

// End g/src/tools/pg/ParserGeneratorParser.h
