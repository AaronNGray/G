//
//  g/GeneratorParser.h - Generator Parser class
//
//  Property and Copyright (c) 2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/File.h"
#include "g/Grammar/Grammar.h"
#include "g/Actions.h"
#include "g/Logger.h"

//

void            yyrestart(FILE* input_file);        // void yyrestart(FILE *input_file)
int             yyparse();         // int yyparse()
int             yylex();           // int yylex()
extern void     yyerror(const char* s);  // void yyerror(char *s)
extern int      yychar;            // yychar - The lookahead symbol. - protected
extern int      yydebug;           // int yydebug
extern int      yynerrs;           // int yyerrs

//
// singleton base class GeneratorParser
//

extern Logger* logger;  // TODO: Fold in Logger

namespace G {

namespace GeneratorParser {

using namespace G::Grammar;

class GeneratorParserBase {
public:
    GeneratorParserBase(Logger* logger, bool lineDirectives = true, bool debug = false) : lineDirectives(lineDirectives), debug(debug), grammar(nullptr) {
        logger = logger;
        actions = new Actions(lineDirectives);
    }
    virtual ~GeneratorParserBase() {};
    virtual bool Parse(File<FILE*>& file) = 0;
    virtual G::Grammar::Grammar* getGrammar() = 0;

    bool debug;
    bool lineDirectives;
    G::Grammar::Grammar* grammar;
    Actions* actions;
};

using namespace G::Grammar;

template <class Grammar, class Lexer, class Parser>
class GeneratorParser : public GeneratorParserBase {
public:
    GeneratorParser(Logger* logger, bool lineDirectives = true, unsigned debug = 0) : GeneratorParserBase(logger, debug) {
        ::logger = logger;
        grammar = new Grammar("grammar", actions);
    }
    virtual ~GeneratorParser() {};

    virtual bool Parse(File<FILE*>& file) {
        Lexer* lexer = new Lexer(file, currentValue, grammar);
        Parser parser(lexer, currentValue, grammar, debug);
        return parser.parse();
    }

    Grammar* getGrammar() { return grammar; }

protected:
    Grammar* grammar;
    int currentValue;
};

//

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

// End g/GeneratorParser.h - Generator Parser class
