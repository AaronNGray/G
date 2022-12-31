//
//  g/src/tools/ag/AbstractSyntaxTreeGenerator.h
//
//  Property and Copyright (c) 2016-2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/File.h"
#include "runtime/Lexer/Lexer.h"
#include "ag.lg.h"
#include "ag.pg.h"

namespace G {
namespace AbstractSyntaxTreeGenerator {

//
// class ASTTemplateGenerator
//

class ASTGenerator {
public:
    ASTGenerator(FileName _input_filename);

    virtual bool Parse();
    virtual void Output();
    virtual void OutputHXX();
    virtual void OutputCXX();

    virtual ~ASTGenerator() {}

protected:
    FileName input_filename;
    std::string base_filepath;
    std::string basename;
    std::string className;
    std::string hxx_output_filepath;
    std::string cxx_output_filepath;

    AbstractSyntaxTree* ast;
};

} // end namespace AbstractSyntaxTreeGenerator
} // end namespace G

// End g/src/tools/ag/AbstractSyntaxTreeGenerator.h
