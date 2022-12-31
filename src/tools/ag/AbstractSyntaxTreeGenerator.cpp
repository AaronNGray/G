//
//  g/src/tools/ag/AbstractSyntaxTreeGenerator.cpp
//
//  Property and Copyright © 2016 - 2022 Aaron Nathaniel Gray under the MIT License
//

#include "AbstractSyntaxTreeGenerator.h"
//#include "g/Logger.h"

namespace G {
namespace AbstractSyntaxTreeGenerator {

ASTGenerator::ASTGenerator(FileName _input_filename) : input_filename(_input_filename) {
    base_filepath = input_filename.remove_extension();
    basename = input_filename.base_name();

    hxx_output_filepath = base_filepath + ".hpp";
    cxx_output_filepath = base_filepath + ".cpp";

    ast = new AbstractSyntaxTree;
//    className = input_filename.base_name() + "Parser";
}

bool ASTGenerator::Parse() {
    auto file = new File<FILE*>(input_filename);
    if (!file->open()) {
        std::cerr << "Error: File not found '" << input_filename.toString() << "'\n";
        return false;
    }

    agLexer* lexer = new agLexer(*file, currentValue, ast);
    agParser parser(lexer, currentValue, ast, false);
    bool ret = parser.parse();

    file->close();

    return ret;
}

void ASTGenerator::Output() {
    OutputHXX();
    OutputCXX();
}

void ASTGenerator::OutputHXX() {
    auto file = new File<std::ostream>(hxx_output_filepath);
    if (!file->open()) {
        std::cerr << "Error: Unable to open file '" << hxx_output_filepath << "'\n";
        throw;
    }

    ast->OutputHXX(file->getStream());

    file->close();
}

void ASTGenerator::OutputCXX() {
    auto file = new File<std::ostream>(cxx_output_filepath);
    if (!file->open()) {
        std::cerr << "Error: Unable to open file '" << cxx_output_filepath << "'\n";
        throw;
    }

    ast->OutputCXX(file->getStream());

    file->close();
}

} // end namespace AbstractSyntaxTreeGenerator
} // end namespace G

// End g/src/tools/ag/AbstractSyntaxTreeGenerator.cpp
