//
//  g/src/tools/ag/main.cpp
//
//  Property and Copyright © 2016 - 2022 Aaron Nathaniel Gray under the MIT License
//

#include <io.h>
#include <stdio.h>
#include <iostream>

#include "nonstd/File.h"
#include "nonstd/CommandLineParser.h"
#include "g/Logger.h"

#include "g/AbstractSyntaxTreeGenerator/AbstractSyntaxTree.h"
#include "AbstractSyntaxTreeGenerator.h"

using namespace G::AbstractSyntaxTreeGenerator;

Logger* logger;

int main(int argc, char *argv[]) {

    CommandLineParser commandLine(argc, argv);

    if (commandLine.getParameters() == 1) {
        try {
            FileName filename(commandLine.getParameter(0));

            ASTGenerator* astGenerator = new ASTGenerator(filename);

            astGenerator->Parse();

            //astGenerator->Generate();

            //astGenerator->Output();

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

// End g/src/tools/ag/main.cpp
