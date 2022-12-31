//
//  g/src/tools/ttg/TextualTemplateGenerator.cpp - Textual Template Generator Parser
//
//  Property and Copyright (c) 2016 Aaron Nathaniel Gray
//

#include "TextualTemplateGenerator.h"

namespace G {
namespace TextualTemplateGenerator {

TextualTemplateGenerator::TextualTemplateGenerator(FileName _input_filename) : input_filename(_input_filename) {
    base_filepath = input_filename.remove_extension();
    basename = input_filename.base_name();

    hxx_output_filepath = base_filepath + ".h";
    cxx_output_filepath = base_filepath + ".cpp";

    textualTemplate = new TextualTemplate;
}

bool TextualTemplateGenerator::Parse() {
    auto file = new File<FILE*>(input_filename);
    if (!file->open()) {
        std::cerr << "Error: File not found '" << input_filename.toString() << "'\n";
        return false;
    }

    ttgLexer* lexer = new ttgLexer(*file, currentValue, textualTemplate);
    ttgParser parser(lexer, currentValue, textualTemplate, false);
    bool ret = parser.parse();

    file->close();

    return ret;
}

void TextualTemplateGenerator::Output() {
    OutputHXX();
    OutputCXX();
}

void TextualTemplateGenerator::OutputHXX() {
	File<std::ostream> output(hxx_output_filepath);

	output << textualTemplate->OutputHXX();
}

void TextualTemplateGenerator::OutputCXX() {
	File<std::ostream> output(cxx_output_filepath);

	output << textualTemplate->OutputCXX();
}

} // end namespace TextualTemplateGenerator
} // end namespace G

// End g/src/tools/TextualTemplateGenerator/TextualTemplateGenerator.cpp - Textual Template Generator Parser
