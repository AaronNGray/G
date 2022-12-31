//
//  g/ParserGenerator/ParserGeneratorParser.h - Parser Generator Parser class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/File.h"
#include "g/Grammar/ContextFreeGrammar.h"
#include "g/Actions.h"
#include "g/Logger.h"

void			yyrestart(FILE *input_file);    // void yyrestart(FILE *input_file)
int				Grammar_yyparse();		        // int yyparse()
int				Grammar_yylex();			    // int yylex()
extern void		Grammar_yyerror(const char *s);	    // void yyerror(char *s)
extern int		Grammar_yychar;			        // yychar - The lookahead symbol. - protected
extern int		Grammar_yydebug;			    // int yydebug
extern int		Grammar_yynerrs;			    // int yyerrs

//
// singleton base class LexicalGeneratorParser
//

namespace G {

extern Logger* logger;  // TODO: Fold in Logger

namespace ParserGenerator {

using namespace G::Grammar;

class ParserGeneratorParser {
public:
    ParserGeneratorParser(Logger *logger, bool lineDirectives = true, unsigned debug = 0) : debug(debug) {
        G::logger = logger;
        actions = new Actions(lineDirectives);
        grammar = new ContextFreeGrammar("grammar", actions);
    }

	ContextFreeGrammar* getGrammar() { return grammar; }

    unsigned debug;
    virtual bool Parse(File<FILE*>& file) = 0;
    virtual ~ParserGeneratorParser() {};

    Actions* actions;
	ContextFreeGrammar* grammar;
};

class ParserParseError : public ErrorObject {
public:
    ParserParseError(int number, std::string message, std::string filename, int line) :
        ErrorObject(number, message, filename, line) {}
    /*
    virtual std::string generateMessage() {
        std::ostringstream os;
        os << message << " at line " << line << std::endl;
        return os.str();
    }
    */
};

} // end namespace ParserGenerator
} // end namespce G

// TODO: Either remove extern Logger, and use exceptions or implement error mechanism ?

// End g/ParserGenerator/ParserGeneratorParser.h - Parser Generator Parser class
