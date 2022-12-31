//
//	g/src/bootstrap/self-bootstrap/pg-bootstrap-pg/main.cpp
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
#include "nonstd/CommandLineParser.h"
#include "pg.parser.h"

using namespace G::ParserGenerator;

int main(int argc, char *argv[]) {

	ParserGeneratorFactory.Register<LR1>();
	ParserGeneratorFactory.Register<LL1>();

	CommandLineParser commandLine(argc, argv);

	if (commandLine.getParameters() == 1) {
		try {
			Logger *logger = new Logger(new StdErrLogger, "pg-bootstrap-pg");

			FileName filename(commandLine.getParameter(0));
			bool debug = commandLine.longOptionExists("debug");
			bool lineDirectives = !commandLine.longOptionExists("noline");

			ParserGenerator<ContextFreeGrammar>* parserGenerator = pg_ParserGenerator();

			parserGenerator->setFilename(filename);
			parserGenerator->setLineDirectives(lineDirectives);
			parserGenerator->setLogger(logger);

			parserGenerator->Generate();
			parserGenerator->GenerateAttributes();

			parserGenerator->Output();
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

// End g/src/bootstrap/self-bootstrap/pg-bootstrap-pg/main.cpp
