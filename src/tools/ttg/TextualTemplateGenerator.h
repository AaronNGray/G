//
//  g/src/tools/ttg/TextualTemplateGenerator.h - Textual Template Generator Parser
//
//  Copyright (c) 2016 Aaron Nathaniel Gray under the MIT License
//

#pragma once

#include "nonstd/File.h"
#include "runtime/Lexer/Lexer.h"
#include "g/TextualTemplateGenerator/TextualTemplate.h"
#include "ttg.lg.h"
#include "ttg.pg.h"

namespace G {
namespace TextualTemplateGenerator {

//
// class TextualTemplateGenerator
//

class TextualTemplateGenerator {
public:
    TextualTemplateGenerator(FileName _input_filename);

    virtual bool Parse();
    virtual void Output();
    virtual void OutputHXX();
    virtual void OutputCXX();
	virtual ~TextualTemplateGenerator() {}
private:
    FileName input_filename;
    std::string base_filepath;
    std::string basename;
    std::string className;
    std::string hxx_output_filepath;
    std::string cxx_output_filepath;

    TextualTemplate* textualTemplate;
};

} // end namespace TextualTemplateGenerator
} // end namespace G

// End g/src/tools/TextualTemplateGenerator/TextualTemplateGenerator.h - Textual Template Generator Parser
