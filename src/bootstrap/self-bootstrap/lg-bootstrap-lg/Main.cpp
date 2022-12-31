//
//	g/bootstrap/self-bootstrap/lg-bootstrap-lg/main.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include <io.h>
#include <iostream>
#include <cstdio>

#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "lg.lexer.h"
#include "nonstd/CommandLineParser.h"

using namespace G::LexicalAnalyserGenerator;

LexicalGenerator* lexicalGenerator;
Logger *logger;

int main(int argc, char *argv[]) {

    Logger logger(new StdErrLogger, "lg-bootstrap-lg");
    ::logger = &logger;

	CommandLineParser commandLine(argc, argv);

	if (commandLine.getParameters() == 1) {

		try {
            FileName filename(commandLine.getParameter(0));
            LexicalGenerator* lexicalGenerator = lg_LexicalGenerator;

            lexicalGenerator->setLogger(&logger);

            lexicalGenerator->setLineDirectives(!commandLine.longOptionExists("noline"));
            lexicalGenerator->setFilename(filename);

			lexicalGenerator->Process();

            lexicalGenerator->OutputH();
            lexicalGenerator->OutputCXX();
            lexicalGenerator->OutputOutput();

            delete lexicalGenerator;
        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            logger.LogError(new ExceptionErrorObject(e.what()));
			return 3;
        }

		return 0;
    }
    else {
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

// End g/bootstrap/self-bootstrap/lg-bootstrap-lg/main.cpp
