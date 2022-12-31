//
//	g/src/self-bootstrap/pg-generatoe-bootstrap/main.cpp
//
//  Property and Copyright (c) 2017-2022 Aaron Nathaniel Gray
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

Logger* logger;

int main(int argc, char *argv[]) {

	ParserGeneratorFactory.Register<LR1>();
	ParserGeneratorFactory.Register<LL1>();

	CommandLineParser commandLine(argc, argv);

	if (commandLine.getParameters() == 1) {
		Logger logger(new StdErrLogger, "pg-generate-bootstrap");
		try {
			FileName filename(commandLine.getParameter(0));
			bool lineDirectives = !commandLine.longOptionExists("noline");
			bool debug = commandLine.longOptionExists("debug");

			auto sourceFileParser = new SourceFileParser<ContextFreeGrammar, pgLexer, pgParser>(filename, &logger, debug);

			G::ParserGenerator::ParserGenerator<ContextFreeGrammar> parserGenerator(sourceFileParser, &logger, lineDirectives, debug);
			::parserGenerator = &parserGenerator;

			if (!sourceFileParser->Parse()) {
				std::cerr << "Error: Parsing '" << commandLine.getParameter(0) << "'\n";
				logger.LogError(new ParsingErrorObject());
				return 2;
			}

			parserGenerator.GenerateSource();

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
		std::cerr << "Usage: " << argv[0] << " <input file>\n";
		return 1;
	}
}

// End g/src/self-bootstrap/pg-generatoe-bootstrap/main.cpp
