//
//	g/bootstrap/self-bootstrap/lg-bootstrap-pg/main.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include <io.h>
#include <iostream>
#include <cstdio>

#include "nonstd/CommandLineParser.h"
#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "pg.lexer.h"

using namespace G::LexicalAnalyserGenerator;

Logger *logger;

int main(int argc, char *argv[]) {
	CommandLineParser commandLine(argc, argv);

	if (commandLine.getParameters() == 1) {
		try {
            logger = new Logger(new StdErrLogger, "lg-bootstrap-pg");
            FileName filename(commandLine.getParameter(0));

            LexicalGenerator* lexicalGenerator = pg_LexicalGenerator;

			lexicalGenerator->setLogger(logger);
			lexicalGenerator->setFilename(filename);

            lexicalGenerator->Process();

            lexicalGenerator->OutputH();
            lexicalGenerator->OutputCXX();
            lexicalGenerator->OutputOutput();

            delete lexicalGenerator;
            delete logger;
        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            logger->LogError(new ExceptionErrorObject(e.what()));
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

// End g/bootstrap/self-bootstrap/lg-bootstrap-pg/main.cpp
