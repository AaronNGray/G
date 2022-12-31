//
//	g/bootstrap/self-bootstrap/pg-bootstrap-lg/main.cpp
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
#include "lg.parser.h"
#include "nonstd/CommandLineParser.h"

using namespace G::ParserGenerator;

G::Factory G::ParserGenerator::ParserGeneratorFactory;
ParserGenerator<ContextFreeGrammar>* parserGenerator;

Logger* logger;

int main(int argc, char *argv[]) {

	ParserGenerator<ContextFreeGrammar>* lg_parserGenerator = lg_ParserGenerator();

	ParserGeneratorFactory.Register<LR1>();
	ParserGeneratorFactory.Register<LL1>();

	CommandLineParser commandLine(argc, argv);

	if (commandLine.getParameters() == 1) {
		try {
			Logger *logger = new Logger(new StdErrLogger, "pg-bootstrap-lg");

			FileName filename(commandLine.getParameter(0));
			bool lineDirectives = !commandLine.longOptionExists("noline");
			bool debug = commandLine.longOptionExists("debug");

			lg_parserGenerator->setFilename(filename);
			lg_parserGenerator->setLogger(logger);
			lg_parserGenerator->setLineDirectives(lineDirectives);

			lg_parserGenerator->Generate();
			lg_parserGenerator->GenerateAttributes();

			lg_parserGenerator->Output();
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

// TODO: setDebug()

// End g/bootstrap/self-bootstrap/pg-bootstrap-lg/main.cpp
