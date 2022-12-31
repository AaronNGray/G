//
//  g/LexicalAnalyserGenerator/GenerateSource.cpp
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/LexicalAnalyserGenerator/LexicalMachine.h"
#include "g/LexicalAnalyserGenerator/LexicalContext.h"
#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "nonstd/Utils.h"

namespace G {
namespace LexicalAnalyserGenerator {

void LexicalGenerator::GenerateSource() const {
    GenerateSourceH();
    GenerateSourceCXX();
}

void LexicalGenerator::GenerateSourceH() const {
    File<std::ostream> output(base_filepath + ".lexer.h");
    auto guard = generateGuardString(base_filepath + ".lexer.h");

    output << "#pragma once" << nonstd::endl;
    output << "#ifndef " << guard << nonstd::endl;
    output << "#define " << guard << nonstd::endl;
    output << nonstd::endl;
	output << "#include \"g/LexicalAnalyserGenerator/LexicalGenerator.h\"" << nonstd::endl;
	output << "#include \"g/LexicalAnalyserGenerator/LexicalMachine.h\"" << nonstd::endl;
    output << "#include \"g/LexicalAnalyserGenerator/LexicalContext.h\"" << nonstd::endl;
    output << "#include \"g/LexicalAnalyserGenerator/RegularGrammar.h\"" << nonstd::endl;
    output << "#include \"nonstd/File.h\"" << nonstd::endl;
    output << "#include \"g/Actions.h\"" << nonstd::endl;

    output << nonstd::endl;

    output << "using namespace G::LexicalAnalyserGenerator;" << nonstd::endl;
    output << nonstd::endl;

    output << "extern LexicalGenerator* " << basename << "_LexicalGenerator;" << nonstd::endl;
    output << nonstd::endl;

    //lexicalMachine->GenerateSourceH(output);

    output << "#endif // " << guard << nonstd::endl;
}

void LexicalGenerator::GenerateSourceCXX() const {
    File<std::ostream> output(base_filepath + ".lexer.cpp");

	output << "#include \"g/LexicalAnalyserGenerator/LexicalGenerator.h\"" << nonstd::endl;
	output << "#include \"g/LexicalAnalyserGenerator/LexicalMachine.h\"" << nonstd::endl;
    output << "#include \"g/LexicalAnalyserGenerator/LexicalContext.h\"" << nonstd::endl;
    output << "#include \"g/LexicalAnalyserGenerator/RegularGrammar.h\"" << nonstd::endl;
    output << "#include \"g/Actions.h\"" << nonstd::endl;
    output << nonstd::endl;

    output << "using namespace G::LexicalAnalyserGenerator;" << nonstd::endl;
    output << nonstd::endl;

    output << "FileName filename(\"" + basename + "\");" << nonstd::endl;
    output << "LexicalGenerator* " << basename << "_LexicalGenerator = new LexicalGenerator(filename, ";
    lexicalMachine->GenerateSourceCXX(output);
	output << "," << nonstd::endl;

	output << "  \"" << lexicalMachine->getRootType() << "\"," << nonstd::endl;
	output << "  \"" << lexicalMachine->getBaseClass() << "\"," << nonstd::endl;
	output << "  \"" << lexicalMachine->getValueType() << "\"," << nonstd::endl;
	output << "  \"" << lexicalMachine->getReturnType() << "\"," << nonstd::endl;

	header.GenerateSource(output, 2);
	output << "," << nonstd::endl;

	code.GenerateSource(output, 2);
	output << nonstd::endl << ");" << nonstd::endl << nonstd::endl;

    output << "// End " + base_filepath + ".lexer.cpp" << nonstd::endl;
}

void LexicalMachine::GenerateSourceH(std::ostream &os) const {
    os << "extern LexicalMachine* " << name << "_lexicalMachine;" << nonstd::endl;
}

void LexicalMachine::GenerateSourceCXX(std::ostream &os) const {
    os << "new LexicalMachine(\"" + name + "\", " + nonstd::generateBoolean(debug) + ", " << "{" << nonstd::endl;
    for (auto context = contexts.begin(); context != contexts.end(); ++context) {
        (*context)->GenerateSourceCXX(os);
        if (context != contexts.last())
            os << "," << std::endl;
    }
    os << "}," << nonstd::endl;
    os << actions.Generate(2);
    os << ")";
}

void LexicalContext::GenerateSourceH(std::ostream &os) const {
//    os << regularGrammar->toSource();
}
void LexicalContext::GenerateSourceCXX(std::ostream &os) const {
    os << "  new LexicalContext(\"" + name + "\", " + regularGrammar->toSource(4);
    os << "  )";
}

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/GenerateSource.cpp

// TODO: do standard file header and footer generators
