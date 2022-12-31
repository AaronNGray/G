//
//  LexicalGeneratorParser.h - Lexical Generator Parser class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/File.h"
#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "g/Logger.h"

void			yyrestart(FILE *input_file);        // void yyrestart(FILE *input_file)
int				LexicalGenerator_yyparse();		    // int yyparse()
int				LexicalGenerator_yylex();			// int yylex()
extern void		LexicalGenerator_yyerror(const char *s);	// void yyerror(char *s)
extern int		LexicalGenerator_yychar;			// yychar - The lookahead symbol. - protected
extern int		LexicalGenerator_yydebug;			// int yydebug
extern int		LexicalGenerator_yynerrs;			// int yyerrs

//
// singleton base class LexicalGeneratorParser
//

extern Logger* logger;

namespace G {
namespace LexicalAnalyserGenerator {

class LexicalGeneratorParser {
public:
    LexicalGeneratorParser(Logger *logger, bool debug = false) : debug(debug) {
        ::logger = logger;
    }

    virtual bool Parse(File<FILE*>& file) = 0;
    virtual ~LexicalGeneratorParser() {};

    unsigned debug;
};

class LexerParseError : public ErrorObject {
public:
    LexerParseError(int number, std::string message, std::string filename, int line) :
        ErrorObject(number, message, filename, line) {}
    /*
    virtual std::string generateMessage() {
        std::ostringstream os;
        os << message << " at line " << line << std::endl;
        return os.str();
    }
    */
};

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End LexicalGeneratorParser.h - Lexical Generator Parser class
