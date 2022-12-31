//
//	g/src/tools/g/main.cpp
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include <io.h>
#include <stdio.h>
#include <iostream>

#include "nonstd/File.h"
#include "g/Logger.h"
#include "g/Grammar/ContextFreeGrammar.h"
#include "g/ParserGenerator/Factory.h"
#include "g/ParserGenerator/LR1/LR1.h"
#include "g/ParserGenerator/LALR1/LALR1.h"
#include "g/ParserGenerator/LL1/LL1.h"
#include "g/ParserGenerator/ParserGenerator.h"
#include "g/SourceFile.h"
#include "nonstd/CommandLineParser.h"
#include "nonstd/Debug.h"

#include "g.lg.h"
#include "g.pg.h"


using namespace G::ParserGenerator;

G::Factory G::ParserGenerator::ParserGeneratorFactory;
ParserGenerator<ExtendedGrammar>* parserGenerator;

Logger* G::logger;
int main(int argc, char *argv[]) {

	ParserGeneratorFactory.Register<LR1>();
    ParserGeneratorFactory.Register<LALR1>();
    ParserGeneratorFactory.Register<LL1>();

    CommandLineParser commandLine(argc, argv);

    if (commandLine.getParameters() == 1) {
        try {
            FileName filename(commandLine.getParameter(0));
            bool lineDirectives = !commandLine.longOptionExists("noline");
            bool debug = commandLine.longOptionExists("debug");
            bool html = true;

            G::logger = new Logger(new StdErrLogger, "G");

            auto sourceFileParser = new SourceFileParser<ExtendedGrammar, gLexer, gParser>(filename, logger, debug);

            G::ParserGenerator::ParserGenerator<ExtendedGrammar> parserGenerator(sourceFileParser, logger, lineDirectives, debug);
            ::parserGenerator = &parserGenerator;

            if (!sourceFileParser->Parse()) {
                std::cerr << "Error: Parsing '" << commandLine.getParameter(0) << "'\n";
#ifdef PAUSE
                getc(stdin);
#endif
                return 2;
            }

            parserGenerator.Generate();
            parserGenerator.GenerateAttributes();

            parserGenerator.Output();
        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            G::logger->LogError(new ExceptionErrorObject(e.what()));
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
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }
}

// End g/src/tools/g/main.cpp
