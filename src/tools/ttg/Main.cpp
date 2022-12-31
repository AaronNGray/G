//
//  g/src/tools/ttg/TextualTemplateGenerator/main.cpp - Textual Template Generator
//
//  Property and Copyright (c) 2016 Aaron Nathaniel Gray
//

#include <io.h>
#include <stdio.h>
#include <iostream>

#include "nonstd/File.h"
#include "nonstd/CommandLineParser.h"
#include "g/Logger.h"
#include "TextualTemplateGenerator.h"

using namespace G::TextualTemplateGenerator;

Logger* logger;

int main(int argc, char *argv[]) {

    CommandLineParser commandLine(argc, argv);

    if (commandLine.getParameters() == 1) {
        try {
            FileName filename(commandLine.getParameter(0));
            TextualTemplateGenerator* textualTemplateGenerator = new TextualTemplateGenerator(filename);

            if (textualTemplateGenerator->Parse()) {
                textualTemplateGenerator->Output();
            }
            else {
                std::cerr << "Error: error parsing '" << argv[1] << "'." << std::endl;
#ifdef PAUSE
                getc(stdin);
#endif
                return 2;
            }
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

// End g/src/tools/ttg/TextualTemplateGenerator/main.cpp - Textual Template Generator
