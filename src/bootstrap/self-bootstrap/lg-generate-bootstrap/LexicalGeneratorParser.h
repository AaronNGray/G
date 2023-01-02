//
//	g/bootstrap/self-bootstrap/lg-generate-bootstrap/LexicalGeneratorParser.h
//
//  Property and Copyright (c) 2017-2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/File.h"
#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "g/Logger.h"
#include "LexicalGeneratorParser.h"
#include "lg.pg.h"
#include "lg.lg.h"

//
// singleton class LexicalGeneratorParser
//

class LexicalGeneratorParser_LGPG : public LexicalGeneratorParser {
public:
    LexicalGeneratorParser_LGPG(Logger *logger, unsigned debug = 0) : LexicalGeneratorParser(logger, debug) {
        grammar = new RegularGrammar();
    }

	bool Parse(File<FILE*> *file) {

        lgLexer* lexer = new lgLexer(*file, currentValue, grammar);

        lgParser parser(lexer, currentValue, grammar, (debug != 0));

        return parser.parse();
    }
    virtual ~LexicalGeneratorParser_LGPG() {}

    RegularGrammar* grammar;
};

// End g/bootstrap/self-bootstrap/lg-generate-bootstrap/LexicalGeneratorParser.h
