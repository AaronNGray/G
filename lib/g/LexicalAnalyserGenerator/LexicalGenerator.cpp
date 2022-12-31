//
//  g/LexicalAnalyserGenerator/LexicalGenerator.cpp
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/LexicalAnalyserGenerator/LexicalMachine.h"
#include "g/LexicalAnalyserGenerator/LexicalContext.h"
#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
//#include "g/Parser.h"
#include "g/GeneratorParser.h"

#include "nonstd/File.h"
#include "nonstd/Utils.h"

#include <string>

namespace G {
namespace LexicalAnalyserGenerator {

using namespace G::GeneratorParser;

LexicalGenerator::LexicalGenerator(SourceFile<RegularGrammar>* sourceFile, Logger *logger, bool lineDirectives, bool debug) :
    sourceFile(sourceFile), logger(logger), lineDirectives(lineDirectives), debug(debug)
{

    base_filepath = getFilename().remove_extension();
    basename = getFilename().base_name();

    logger->setFilename(getFilename());

    className = getFilename().base_name() + "Lexer";

    compressed = true;
    lexicalMachine = new LexicalMachine(this, className, className, compressed, debug);
}

LexicalGenerator::LexicalGenerator(FileName& filename, LexicalMachine* lexicalMachine, std::string rootType, std::string baseClass, std::string valueType, std::string returnType, const std::initializer_list<CodeBlock> headers, const std::initializer_list<CodeBlock> codes) :
    sourceFile(new SourceFile<RegularGrammar>(filename)), lexicalMachine(lexicalMachine), lineDirectives(true), debug(false /*nonstd::debug*/)
{
    lexicalMachine->setLexicalGenerator(this);

    base_filepath = getFilename().remove_extension();
    basename = getFilename().base_name();

    className = getFilename().base_name() + "Lexer";

    compressed = true;
    lineDirectives = true;

    setRootType(rootType);
    setBaseClass(baseClass);
    setValueType(valueType);
    setReturnType(returnType);

    for (auto header : headers)
        addHeader(new CodeBlock(header));
    for (auto code : codes)
        addCode(new CodeBlock(code));
}
/*
LexicalGenerator::LexicalGenerator(SourceFile<RegularGrammar>& sourceFile, LexicalMachine* lexicalMachine, std::string rootType, std::string baseClass, std::string valueType, std::string returnType, const std::initializer_list<CodeBlock> headers, const std::initializer_list<CodeBlock> codes) :
    SourceFile<RegularGrammar>(sourceFile), lexicalMachine(lexicalMachine), lineDirectives(true), debug(false)
{
    lexicalMachine->setLexicalGenerator(this);

    base_filepath = filename.remove_extension();
    basename = filename.base_name();

    logger->setFilename(filename);

    className = filename.base_name() + "Lexer";

    compressed = true;
    lineDirectives = true;

	setRootType(rootType);
	setBaseClass(baseClass);
	setValueType(valueType);
	setReturnType(returnType);


	for (auto header : headers)
		addHeader(new CodeBlock(header));
	for (auto code : codes)
		addCode(new CodeBlock(code));
}
*/

void LexicalGenerator::Process() {
    lexicalMachine->Generate();
}

void LexicalGenerator::OutputOutput() const {
    File<std::ostream> output(base_filepath + ".lg.out");

    for (unsigned int context = 0; context < lexicalMachine->getContexts().size(); ++context) {
        output << "context: " << lexicalMachine->getContexts()[context]->getName() << nonstd::endl << nonstd::endl;

        output << "firstpos: " << lexicalMachine->getContexts()[context]->getGrammar()->firstpos().toString() << nonstd::endl << nonstd::endl;

        output << "Regular Grammar:" << nonstd::endl;
        output << lexicalMachine->getContexts()[context]->getGrammar()->prettyPrint(2) << nonstd::endl << nonstd::endl;
    }

    output << "Equivalence Class Diag:" << nonstd::endl << nonstd::endl;
    output << lexicalMachine->getEquivalenceClasses().diag() << nonstd::endl;

    output << "Equivalence Class Column Map:" << nonstd::endl << nonstd::endl;
    lexicalMachine->OutputColumnMap(output);
    output << nonstd::endl;

    output << "Contexts:" << nonstd::endl;
    lexicalMachine->OutputContexts(output);
    output << nonstd::endl;

    output << "DFA:" << nonstd::endl;
    lexicalMachine->getDFA()->OutputDFA(output);

    output << "Accept:" << nonstd::endl;
    lexicalMachine->getDFA()->OutputAccept(output);
}

void LexicalGenerator::OutputH() const {
    File<std::ostream> output(base_filepath + ".lg.h");
    //  std::string preprocessor_name = PreprocessorName(filename.base_name());
    auto guard = generateGuardString(base_filepath + ".lg.h");

    output << "#pragma once" << nonstd::endl;
    output << "#ifndef " << guard << nonstd::endl;
    output << "#define " << guard << nonstd::endl;

    output << "#include \"runtime/lexer/Lexer.h\"" << nonstd::endl;
    output << nonstd::endl;

	header.OutputCodeBlocks(output, lineDirectives);

	lexicalMachine->OutputH(output, className);

    output << "#endif // " << guard << nonstd::endl;
}

void LexicalGenerator::OutputCXX() const {
	File<std::ostream> output(base_filepath + ".lg.cpp");

	output << "#include " << "\"" << basename << ".lg.h" << "\"" << nonstd::endl;
	output << nonstd::endl;

	code.OutputCodeBlocks(output, lineDirectives);

	lexicalMachine->OutputCXX(output, className);
}

void LexicalGenerator::Dump(unsigned indent) const {
	File<std::ostream> output(base_filepath + ".dump");

	output << Indent(indent) << "base_filepath = " << base_filepath << std::endl;
	output << Indent(indent) << "basename = " << basename << std::endl;
	output << Indent(indent) << "className = " << className << std::endl;

	output << Indent(indent) << "lineDirectives = " << lineDirectives << std::endl;

	output << Indent(indent) << "header = {" << std::endl;
	header.OutputCodeBlocks(output);
	output << Indent(indent) << "}" << std::endl;
	output << Indent(indent) << "code = {" << std::endl;
	code.OutputCodeBlocks(output);
	output << Indent(indent) << "}" << std::endl;

	output << Indent(indent) << "diagnostics = " << diagnostics << std::endl;
	output << Indent(indent) << "compressed = " << compressed << std::endl;
	output << Indent(indent) << "debug = " << debug << std::endl;
	output << Indent(indent) << "lexicalMachine:LexicalMachine = {" << std::endl;
	lexicalMachine->Dump(output, indent);
	output << Indent(indent) << "}" << std::endl;
}

bool compare(const LexicalGenerator* lhs, const LexicalGenerator* rhs) {
	bool result = compare(lhs->lexicalMachine, rhs->lexicalMachine);

	if (!result)
		std::cout << "lexicalMachine." << nonstd::endl;

	return result;
}

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/LexicalGenerator.cpp
