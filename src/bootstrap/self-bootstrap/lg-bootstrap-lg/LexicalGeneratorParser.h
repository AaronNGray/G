//
//	g/bootstrap/self-bootstrap/lg-bootstrap-lg/LexicalGeneratorParser.h
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

class LexicalGeneratorParser_ : public LexicalGeneratorParser {
public:
    LexicalGeneratorParser_(Logger *logger, unsigned debug = 0) : LexicalGeneratorParser(logger, debug) {
        grammar = new RegularGrammar();
    }

	bool Parse(File<FILE*> *file) {

        lgLexer* lexer = new lgLexer(*file, currentValue, grammar);

        lgParser parser(lexer, currentValue, grammar, (debug != 0));

        return parser.parse();
    }
    virtual ~LexicalGeneratorParser_() {}

    RegularGrammar* grammar;
};

// End g/bootstrap/self-bootstrap/lg-bootstrap-lg/LexicalGeneratorParser.h
