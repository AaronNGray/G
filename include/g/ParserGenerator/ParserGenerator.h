//
//  g/ParserGenerator/ParserGenerator.h - Parser Generator header
//
//  Property and Copyright (c) 2016, 2017, 2022 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include "nonstd/File.h"
#include "g/Logger.h"
#include "g/AST.h"
#include "g/SourceFile.h"
#include "g/ParserGenerator/Machine.h"
#include "g/ParserGenerator/Factory.h"
#include "g/ParserGenerator/LR1/LR1.h"
#include "g/ParserGenerator/LL1/LL1.h"
#include "g/CodeBlock.h"
#include "nonstd/Utils.h"
#include "nonstd/Debug.h"

namespace G {
namespace ParserGenerator {

extern Factory ParserGeneratorFactory;

template <class Grammar = ContextFreeGrammar>
class ParserGenerator {
public:
	ParserGenerator(SourceFile<Grammar>* sourceFile, Logger* logger, bool lineDirectives = true, bool debug = false);
	ParserGenerator(FileName& filename, Grammar* grammar, Actions* actions, std::string rootType, std::string valueType, bool _union, std::string returnType, std::initializer_list<CodeBlock> headers, const std::initializer_list<CodeBlock> code);

	FileName getFilename() const {
		return sourceFile->getFilename();
	}
	void setFilename(FileName filename) {
		sourceFile->setFilename(filename);

		base_filepath = filename.remove_extension();
		basename = filename.base_name();

		name = basename;
		className = filename.base_name() + "Parser";

		baseParserName = "Parser";
		baseParserClassName = baseParserName;
	}

	void setLineDirectives(bool lineDirectives) {
		this->lineDirectives = lineDirectives;
	}

	void setLogger(Logger* logger) {
		this->logger = logger;
	}

	void setName(std::string name) {
		this->name = name;
	}
	std::string getName() {
		return name;
	}
	void setType(std::string type) {
		this->type = type;
	}
	std::string getType() {
		return type;
	}

//

	void addHeader(CodeBlock* header) {
		sourceFile->addHeader(header);
	}
	void addCode(CodeBlock* code) {
		sourceFile->addCode(code);
	}

	const CodeBlocks& getHeader() const {
		return sourceFile->getHeaders();
	}
	const CodeBlocks& getCode() const {
		return sourceFile->getCode();
	}


	void setRootType(std::string rootType) {
		sourceFile->setRootType(rootType);
	}
	void setBaseClass(std::string baseClass) {
		sourceFile->setBaseClass(baseClass);
	}
	void setBaseType(std::string valueType, bool useUnion = false) {
		sourceFile->setValueType(valueType, useUnion);
	}
	void setReturnType(std::string returnType) {
		sourceFile->setReturnType(returnType);
	}

	void setGrammar(Grammar* grammar) {
		sourceFile->ast = grammar;
	}
	Grammar* getGrammar() {
		return sourceFile->getAST();
	}
	const Grammar* getGrammar() const {
		return sourceFile->getAST();
	}
	void setActions(Actions* actions) {
		sourceFile->getAST()->setActions(actions);
	}
	Actions* getActions() {
		return sourceFile->getActions();
	}
	const Actions* getActions() const {
		return sourceFile->getActions();
	}


	std::string getRootTypeName() const {
		return sourceFile->getRootTypeName();
	}
	std::string getValueType() const {
		return sourceFile->getValueType();
	}
	std::string getReturnType() const {
		return sourceFile->getReturnType();
	}

	bool getUseUnion() const {
		return sourceFile->getUseUnion();
	}


	void CheckGrammar() {
		getGrammar()->CheckGrammar();
	}

	std::string GenerateGrammar() const {
		return getGrammar()->GenerateGrammar();
	}

	void setMachine(Machine* machine) {
		this->machine = machine;
	}

	Machine* getMachine() {
		return machine;
	}

	bool getRowCompression() {
		return rowCompression;
	}

	void GenerateSource() const;
	void GenerateSourceH() const;
	void GenerateSourceCXX() const;

	void Generate();
	void GenerateAttributes();

	void Analysis();
	void Output() const;

	void OutputStates(std::string fileName) const;

	void OutputCXX() const;
	void OutputHXX() const;

	template <class _Grammar>
	friend bool compare(const ParserGenerator<_Grammar>* lhs, const ParserGenerator<_Grammar>* rhs);

private:
	SourceFile<Grammar>* sourceFile;

	std::string base_filepath;
	std::string basename;
	std::string className;
//
	std::string name;
	std::string type;

	std::string baseParserName;
	std::string baseParserClassName;

	bool rowCompression;
	bool debug;

	bool lineDirectives;

	Logger* logger;

	Machine* machine;
};

template <class Grammar>
ParserGenerator<Grammar>::ParserGenerator(SourceFile<Grammar>* sourceFile, Logger* logger, bool lineDirectives, bool debug) :
	sourceFile(sourceFile), /*actions(grammar->getActions()), useUnion(false), */ logger(logger), lineDirectives(lineDirectives), debug(debug)
{
	logger->setFilename(getFilename().toString());

	base_filepath = getFilename().remove_extension();
	basename = getFilename().base_name();

	name = basename;
	type = "LR(1)";
	className = getFilename().base_name() + "Parser";

	baseParserName = "Parser";
	baseParserClassName = baseParserName;

	setRootType("void");
	setBaseType("int", true);
	setReturnType("void");

	rowCompression = true;
}
/*
template <class Grammar>
ParserGenerator<Grammar>::ParserGenerator(SourceFile<Grammar> sourceFile, Logger* logger, bool lineDirectives, bool debug) :
	sourceFile(sourceFile), actions(grammar->getActions()), useUnion(false), logger(logger), lineDirectives(lineDirectives), debug(debug)
{
	logger->setFilename(getFilename().toString());

	base_filepath = getFilename().remove_extension();
	basename = getFilename().base_name();

	name = basename;
	type = "LR(1)";
	className = getFilename().base_name() + "Parser";

	baseParserName = "Parser";
	baseParserClassName = baseParserName;

	sourceFile->setRootType("void");
	sourceFile->setValueType("int");
	sourceFile->setReturnType("void");

	rowCompression = true;
}
*/
template <class Grammar>
ParserGenerator<Grammar>::ParserGenerator(FileName& filename, Grammar* grammar, Actions* actions, std::string rootType, std::string valueType, bool useUnion, std::string returnType, const std::initializer_list<CodeBlock> headers, const std::initializer_list<CodeBlock> codes) :
	sourceFile(new SourceFile<Grammar>(filename, grammar, actions, rootType, valueType, useUnion, returnType)), lineDirectives(true), debug(false)
{
	base_filepath = getFilename().remove_extension();
	basename = getFilename().base_name();

	std::cout << "basename = " << basename << std::endl;

	name = basename;
	type = "LR(1)";
	className = getFilename().base_name() + "Parser";

	baseParserName = "Parser";
	baseParserClassName = baseParserName;

	rowCompression = true;

	for (auto header : headers)
		addHeader(new CodeBlock(header));
	for (auto code : codes)
		addCode(new CodeBlock(code));
}

/*
template <class Grammar>
ParserGenerator<Grammar>::ParserGenerator(char* filename, std::string rootType, std::string valueType, bool useUnion, std::string returnType, const std::initializer_list<CodeBlock> headers, const std::initializer_list<CodeBlock> code) :
	sourceFile(filename, rootType, valueType, useUnion, returnType), lineDirectives(true), debug(debug)
{
	base_filepath = getFilename().remove_extension();
	basename = getFilename().base_name();

	name = basename;
	type = "LR(1)";
	className = getFilename().base_name() + "Parser";

	baseParserName = "Parser";
	baseParserClassName = baseParserName;

	rowCompression = true;

	for (auto header : headers)
		addHeader(new CodeBlock(header));
	for (auto c : code)
		addCode(new CodeBlock(c));
}
*/

template <class Grammar>
void ParserGenerator<Grammar>::GenerateSource() const {
	GenerateSourceH();
	GenerateSourceCXX();
}

template <class Grammar>
void ParserGenerator<Grammar>::Generate() {
	Grammar* grammar = sourceFile->getAST();

	grammar->CheckGrammar();

	grammar->GenerateTerminalNamesAsVector();

	grammar->GenerateFirstSets();
	grammar->GenerateFollowSets();
	grammar->GenerateSelectSets();

	FactoryMethod* factoryMethod = ParserGeneratorFactory.getFactoryMethod(type);

	machine = factoryMethod->Create(grammar, rowCompression, debug);

	machine->Generate();
}

template <class Grammar>
void ParserGenerator<Grammar>::GenerateAttributes() {
	getGrammar()->GenerateAttributes(getActions(), sourceFile->getUseUnion());
}

template <class Grammar>
void ParserGenerator<Grammar>::Analysis() {
//	AnalyseStates(output);
}


template <class Grammar>
void ParserGenerator<Grammar>::Output() const {
	OutputHXX();
	OutputCXX();

	File<std::ostream> output(base_filepath + ".pg.out");
	machine->Output(output);
}

template <class Grammar>
void ParserGenerator<Grammar>::OutputHXX() const {
	File<std::ostream> output(base_filepath + ".pg.h");

	output << "//  " << nonstd::endl;
	output << "//  " << base_filepath + ".pg.h" << nonstd::endl << nonstd::endl;
	output << "//  " << nonstd::endl;
	output << nonstd::endl;

	output << "#pragma once" << nonstd::endl;
	output << nonstd::endl;

	machine->OutputIncludesHXX(output, baseParserName);
	output << nonstd::endl;

	getHeader().OutputCodeBlocks(output, lineDirectives);

	output << "class " << className << " : public " << baseParserClassName << "<" "short" ", " << getValueType() << ">" << " {" << nonstd::endl;
	output << "public:" << nonstd::endl;

	output << "\t" << className << "(Lexer* lexer, " << getValueType() << "& currentValue, " << getRootTypeName() << "* root, " << "bool debug = false) : " << "root(root), " << baseParserClassName << "(lexer, currentValue, debug) {}" << nonstd::endl;

	output << "\t" << getRootTypeName() << "* root;" << nonstd::endl;

	machine->OutputCodeHXX(output, className);
	machine->OutputTablesHXX(output, className);

	getActions()->OutputActionsHXX(output, className, getReturnType());  // BUG: why parserGeneratorParser->actions ?

	output << "};" << nonstd::endl;

	output << nonstd::endl << "// End " << base_filepath + ".pg.h" << nonstd::endl;
}

template <class Grammar>
void ParserGenerator<Grammar>::OutputCXX() const {
	File<std::ostream> output(base_filepath + ".pg.cpp");

	output << "#include " << "\"" << basename << ".pg.h" << "\"" << nonstd::endl;
	output << nonstd::endl;

	getCode().OutputCodeBlocks(output, lineDirectives);

	machine->OutputCodeCXX(output, className);
	machine->OutputTablesCXX(output, className);

	getActions()->OutputActionsCXX(output, className, getFilename(), getReturnType(), lineDirectives);
}

template <class Grammar>
void ParserGenerator<Grammar>::GenerateSourceH() const {
	File<std::ostream> output(base_filepath + ".parser.h");
	auto guard = generateGuardString(base_filepath + ".parser.h");

	output << "#pragma once" << nonstd::endl;
	output << nonstd::endl;
	output << "#include \"g/ParserGenerator/ParserGenerator.h\"" << nonstd::endl;
	output << "#include \"g/Actions.h\"" << nonstd::endl;
	output << nonstd::endl;

	output << "using namespace G::ParserGenerator;" << nonstd::endl;
	output << nonstd::endl;

	output << "ParserGenerator<ContextFreeGrammar>* " << basename << "_ParserGenerator();" << nonstd::endl;
	output << nonstd::endl;
}

template <class Grammar>
void ParserGenerator<Grammar>::GenerateSourceCXX() const {
	File<std::ostream> output(base_filepath + ".parser.cpp");

	output << "#include \"g/ParserGenerator/ParserGenerator.h\"" << nonstd::endl;
	output << "#include \"g/Grammar/Grammar.h\"" << nonstd::endl;
	output << "#include \"g/Actions.h\"" << nonstd::endl;
	output << "#include \"nonstd/File.h\"" << nonstd::endl;
	output << nonstd::endl;

	output << "using namespace G::ParserGenerator;" << nonstd::endl;
	output << nonstd::endl;

	output << "Actions bootstrapActions = ";
	output << getActions()->Generate(0) << ";" << nonstd::endl;
	output << nonstd::endl;

	getGrammar()->GenerateSourceCXX(name, output);
	output << nonstd::endl << nonstd::endl;
	output << "ParserGenerator<ContextFreeGrammar>* " << basename << "_ParserGenerator() {" << nonstd::endl;
	output << "\tFileName filename(\"" + basename + "\");" + nonstd::endl;
		output << "\treturn new ParserGenerator<ContextFreeGrammar>(" << nonstd::endl;
	output << "\t\t" << "filename, " << basename << "_bootstrap(), &bootstrapActions," << nonstd::endl;

	output << "\t\t" "\"" << getRootTypeName() << "\"," << nonstd::endl;
	output << "\t\t" << "\"" << getValueType() << "\"," << nonstd::endl;
	output << "\t\t" "\"" << toStringBool(getUseUnion()) << "\"," << nonstd::endl;
	output << "\t\t" "\"" << getReturnType() << "\"," << nonstd::endl;

	getHeader().GenerateSource(output, 4);
	output << "\t\t" << ", " << nonstd::endl;

	getCode().GenerateSource(output, 4);
	output << nonstd::endl;
	output << "\t" << ");" << nonstd::endl;
	output << "}" << nonstd::endl;
	output << nonstd::endl;

	output << "// End " + base_filepath + ".lexer.cpp" << nonstd::endl;
}

template <class Grammar>
void ParserGenerator<Grammar>::OutputStates(std::string fileName) const {
	File<std::ostream> output(fileName == "" ? (base_filepath + ".pg.states") : fileName);
	machine->OutputStates(output);
}

template <class Grammar>
bool compare(const ParserGenerator<Grammar>* lhs, const ParserGenerator<Grammar>* rhs) {
	bool input_filename = (lhs->getFilename().toString() == rhs->getFilename().toString());
	bool base_filepath = (lhs->base_filepath == rhs->base_filepath);
	bool basename = (lhs->basename == rhs->basename);
	bool className(lhs->className == rhs->className);

	bool name = (lhs->name == rhs->name);
	bool type = (lhs->type == rhs->type);

	bool rootTypeName = (lhs->rootTypeName == rhs->rootTypeName);

	bool baseParserName = (lhs->baseParserName == rhs->baseParserName);
	bool baseParserClassName = (lhs->baseParserName == rhs->baseParserName);

	bool valueType = (lhs->valueType == rhs->valueType);
	bool returnType = (lhs->returnType == rhs->returnType);
	bool useUnion = (lhs->useUnion == rhs->useUnion);

	bool rowCompression = (lhs->rowCompression == rhs->rowCompression);
	bool debug = (lhs->debug == rhs->debug);

	bool grammar = compare(lhs->grammar, rhs->grammar);
	bool actions = *lhs->actions == *rhs->actions;
	bool lineDirectives = lhs->lineDirectives == rhs->lineDirectives;

	bool code = compare(lhs->code, rhs->code);
	bool header = compare(lhs->header, rhs->header);

	bool machine = true;
	if (lhs->machine && rhs->machine)
		machine = lhs->machine->compare(rhs->machine);

	bool result =
		input_filename &&
		base_filepath &&
		basename &&
		className &&
		name &&
		type &&
		rootTypeName &&
		baseParserName &&
		baseParserClassName &&
		valueType &&
		returnType &&
		useUnion &&
		rowCompression &&
		debug &&
		grammar &&
		actions &&
		lineDirectives &&
		code &&
		header &&
		machine;

	if (!result) {
		std::cout << "\t" "input_filename: " << nonstd::generateBoolean(input_filename) << " - \"" << lhs->input_filename.toString() << "\" - \"" << rhs->input_filename.toString() << "\"" << nonstd::endl;
		std::cout << "\t" "base_filepath: " << nonstd::generateBoolean(base_filepath) << " - \"" << lhs->base_filepath << "\" - \"" << rhs->base_filepath << "\"" << nonstd::endl;
		std::cout << "\t" "basename: " << nonstd::generateBoolean(basename) << " - \"" << lhs->basename << "\" - \"" << rhs->basename << "\"" << nonstd::endl;
		std::cout << "\t" "className: " << nonstd::generateBoolean(className) << " - \"" << lhs->className << "\" - \"" << rhs->className << "\"" << nonstd::endl;
		std::cout << "\t" "name: " << nonstd::generateBoolean(name) << " - \"" << lhs->name << "\" - \"" << rhs->name << "\"" << nonstd::endl;
		std::cout << "\t" "type: " << nonstd::generateBoolean(type) << " - \"" << lhs->type << "\" - \"" << rhs->type << "\"" << nonstd::endl;
		std::cout << "\t" "rootTypeName: " << nonstd::generateBoolean(rootTypeName) << " - \"" << lhs->rootTypeName << "\" - \"" << rhs->rootTypeName << "\"" << nonstd::endl;
		std::cout << "\t" "baseParserName: " << nonstd::generateBoolean(baseParserName) << " - \"" << lhs->baseParserName << "\" - \"" << rhs->baseParserName << "\"" << nonstd::endl;
		std::cout << "\t" "baseParserClassName: " << nonstd::generateBoolean(baseParserClassName) << " - \"" << lhs->baseParserClassName << "\" - \"" << rhs->baseParserClassName << "\"" << nonstd::endl;
		std::cout << "\t" "valueType: " << nonstd::generateBoolean(valueType) << " - \"" << lhs->valueType << "\" - \"" << rhs->valueType << "\"" << nonstd::endl;
		std::cout << "\t" "returnType: " << nonstd::generateBoolean(returnType) << " - \"" << lhs->returnType << "\" - \"" << rhs->returnType << "\"" << nonstd::endl;
		std::cout << "\t" "useUnion: " << nonstd::generateBoolean(useUnion) << " - \"" << lhs->useUnion << "\" - \"" << rhs->useUnion << "\"" << nonstd::endl;
		std::cout << "\t" "rowCompression: " << nonstd::generateBoolean(rowCompression) << " - \"" << lhs->rowCompression << "\" - \"" << rhs->rowCompression << "\"" << nonstd::endl;
		std::cout << "\t" "debug: " << nonstd::generateBoolean(debug) << " - \"" << lhs->debug << "\" - \"" << rhs->debug << "\"" << nonstd::endl;
		std::cout << "\t" "grammar: " << nonstd::generateBoolean(grammar) << nonstd::endl << lhs->grammar->prettyPrint(4) << nonstd::endl << rhs->grammar->prettyPrint(4) << nonstd::endl;
		std::cout << "\t" "actions: " << nonstd::generateBoolean(actions) << nonstd::endl;
		std::cout << "\t" "lineDirectives: " << nonstd::generateBoolean(lineDirectives) << " - \"" << lhs->lineDirectives << "\" - \"" << rhs->lineDirectives << "\"" << nonstd::endl;
		std::cout << "\t" "code: " << nonstd::generateBoolean(code) << nonstd::endl;
		std::cout << "\t" "header: " << nonstd::generateBoolean(header) << nonstd::endl;
		std::cout << "\t" "machine: " << nonstd::generateBoolean(machine) << " - \"" << lhs->machine << "\" - \"" << rhs->machine << "\"" << nonstd::endl;
	}

	return result;
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/ParserGenerator.h - Parser Generator header
