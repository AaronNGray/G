//
//  g/src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-bison/main.cpp
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include <io.h>
#include <iostream>
#include <cstdio>

#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "g/SourceFile.h"
#include "nonstd/CommandLineParser.h"
#include "nonstd/Debug.h"
#include "lg.lg.h"

using namespace G;
using namespace G::LexicalAnalyserGenerator;

Logger* logger;
LexicalGenerator* lexicalGenerator;
Runtime::Lexer* lexer;
RegularGrammar* grammar;

int main(int argc, char *argv[]) {

	Logger logger(new StdErrLogger, "lg-bootstrap-lg-bison");

	CommandLineParser commandLine(argc, argv);

	if (commandLine.getParameters() == 1) {
		try {
			FileName filename(commandLine.getParameter(0));
			bool lineDirectives = !commandLine.longOptionExists("noline");
			bool debug = commandLine.longOptionExists("debug");

			SourceFileParser<RegularGrammar, lgLexer, Bison>* sourceFileParser = new SourceFileParser<RegularGrammar, lgLexer, Bison>(filename, &logger, debug);

			LexicalGenerator lexicalGenerator(sourceFileParser, &logger, lineDirectives, debug);
			::lexicalGenerator = &lexicalGenerator;

			if (!sourceFileParser->Parse()) {
				std::cerr << "Error: Parsing '" << commandLine.getParameter(0) << "'\n";
				logger.LogError(new ParsingErrorObject());
				return 2;
			}

			lexicalGenerator.Process();

			//    lexicalGenerator->GenerateOutput();

			lexicalGenerator.OutputCXX();
			lexicalGenerator.OutputH();
			lexicalGenerator.OutputOutput();
		}
		catch (const std::exception& e) {
			std::cerr << "Exception: " << e.what() << std::endl;
			logger.LogError(new ExceptionErrorObject(e.what()));
			return 3;
		}

		return 0;
	} else {
		std::cerr << "Usage: " << commandLine.getProgramName() << " <input file>\n";
		return 1;
	}
}

class UsageMessage : public ErrorObject {
public:
    UsageMessage(message_type type, std::string type_name, int number, int line) :
        ErrorObject(number, std::string(), std::string(), line) {
    }

    virtual std::string generateMessage() {
        setMessage("Usage: RegularGrammar <input file>\n");
    }
};

// End lg-bootstrap-lg-bison/main.cpp
