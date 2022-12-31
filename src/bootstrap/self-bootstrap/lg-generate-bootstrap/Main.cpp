//
//	g/bootstrap/self-bootstrap/lg-generate-bootstrap/main.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include <io.h>
#include <iostream>
#include <cstdio>

#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "g/SourceFile.h"
#include "nonstd/CommandLineParser.h"
#include "nonstd/Debug.h"

#include "lg.lg.h"
#include "lg.pg.h"

using namespace G::LexicalAnalyserGenerator;

LexicalGenerator* lexicalGenerator;
Logger* logger;

int main(int argc, char *argv[]) {

	CommandLineParser commandLine(argc, argv);

	if (commandLine.getParameters() == 1) {
        Logger logger(new StdErrLogger, "lg-generate-bootstrap");

        try {
            FileName filename(commandLine.getParameter(0));
			bool lineDirectives = !commandLine.longOptionExists("noline");
			bool debug = commandLine.longOptionExists("debug");

            auto sourceFileParser = new SourceFileParser<RegularGrammar, lgLexer, lgParser>(filename, &logger, debug);

            LexicalGenerator lexicalGenerator(sourceFileParser, &logger, lineDirectives, debug);
            ::lexicalGenerator = &lexicalGenerator;

            if (!sourceFileParser->Parse()) {
                std::cerr << "Error: Parsing '" << commandLine.getParameter(0) << "'\n";
                logger.LogError(new ParsingErrorObject());
                return 2;
            }

            lexicalGenerator.GenerateSource();
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
        setMessage("Usage: lg-generate-bootstrap <input file>\n");
    }

};

// End g/bootstrap/self-bootstrap/lg-generate-bootstrap/main.cpp
