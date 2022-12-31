//
//	g/bootstrap/self-bootstrap/pg-bootstrap/main.cpp
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
#include "g/SourceFile.h"
#include "nonstd/CommandLineParser.h"
#include "nonstd/Debug.h"
#include "pg.lg.h"
#include "pg.pg.h"

using namespace G::ParserGenerator;

G::Factory G::ParserGenerator::ParserGeneratorFactory;
ParserGenerator<ContextFreeGrammar>* parserGenerator;

Logger* G::logger;
Logger* logger;

int main(int argc, char *argv[]) {

    ParserGeneratorFactory.Register<LR1>();
    ParserGeneratorFactory.Register<LL1>();

	CommandLineParser commandLine(argc, argv);

	if (commandLine.getParameters() == 1) {
        Logger logger(new StdErrLogger, "pg-bootstrap");

        try {
            FileName filename(commandLine.getParameter(0));
			bool lineDirectives = !commandLine.longOptionExists("noline");
			bool debug = commandLine.longOptionExists("debug");

            SourceFileParser<ContextFreeGrammar, pgLexer, pgParser> sourceFileParser(filename, &logger, debug);

            G::ParserGenerator::ParserGenerator<ContextFreeGrammar> parserGenerator(sourceFileParser, &logger, lineDirectives, debug);
            ::parserGenerator = &parserGenerator;

            if (!sourceFileParser.Parse()) {
                std::cerr << "Error: Parsing '" << commandLine.getParameter(0) << "'\n";
                logger.LogError(new ParsingErrorObject());
                return 2;
            }

            parserGenerator.Generate();
            parserGenerator.GenerateAttributes();

            parserGenerator.Output();

            if (commandLine.longOptionExists("states"))
                parserGenerator.OutputStates(commandLine.getLongOption("states"));
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

// End g/bootstrap/self-bootstrap/pg-bootstrap/main.cpp
