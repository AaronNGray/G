//
//	g/src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison/main.cpp
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

#include <io.h>
#include <stdio.h>
#include <iostream>
#include "nonstd/File.h"
#include "g/Logger.h"
#include "g/Grammar/ContextFreeGrammar.h"
#include "g/ParserGenerator/Factory.h"
#include "g/ParserGenerator/LR1/LR1.h"
#include "g/ParserGenerator/LL1/LL1.h"
#include "g/ParserGenerator/ParserGenerator.h"
#include "nonstd/CommandLineParser.h"
#include "nonstd/Debug.h"

#include "g/SourceFile.h"
Runtime::Lexer* lexer;

using namespace G::Grammar;
#include "pg.tab.h"
#include "pg.lg.h"

using namespace G;

Logger* logger;
ContextFreeGrammar* grammar;
G::ParserGenerator::ParserGenerator<ContextFreeGrammar>* parserGenerator;


int main(int argc, char *argv[]) {

    G::ParserGenerator::ParserGeneratorFactory.Register<G::ParserGenerator::LR1>();
    G::ParserGenerator::ParserGeneratorFactory.Register<G::ParserGenerator::LL1>();

	CommandLineParser commandLine(argc, argv);

	if (commandLine.getParameters() == 1) {
        try {
            Logger *logger = new Logger(new StdErrLogger, "pg-bootstrap-lg-bison");
            FileName filename(commandLine.getParameter(0));
            bool lineDirectives = !commandLine.longOptionExists("noline");
			bool debug = commandLine.longOptionExists("debug");

            SourceFileParser<ContextFreeGrammar, pgLexer, Bison>* sourceFileParser = new SourceFileParser<ContextFreeGrammar, pgLexer, Bison>(filename, logger, debug);

            G::ParserGenerator::ParserGenerator<ContextFreeGrammar> parserGenerator(sourceFileParser, logger, lineDirectives, debug);
            ::parserGenerator = &parserGenerator;
            ::grammar = sourceFileParser->getAST();

            if (!sourceFileParser->Parse()) {
                std::cerr << "Error: Parsing '" << commandLine.getParameter(0) << "'\n";
                logger->LogError(new ParsingErrorObject());
                return 2;
            }

            parserGenerator.Generate();
            parserGenerator.GenerateAttributes();

            parserGenerator.Output();

            delete logger;
        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
#ifdef PAUSE
            getc(stdin);
#endif
			return 3;
        }

#ifdef PAUSE
        getc(stdin);
#endif
        return 0;
    }
    else {
        std::cerr << "Usage: " << commandLine.getProgramName() << " <input file>\n";
        return 1;
    }
}
