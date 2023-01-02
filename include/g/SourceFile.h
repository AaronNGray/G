#pragma once

#include "nonstd/File.h"
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "g/Grammar/ContextFreeGrammar.h"
#include "g/CodeBlock.h"

#include "g/AST.h"
#include "runtime/lexer/Lexer.h"
#include "g/Logger.h"

//

void            yyrestart(FILE* input_file);        // void yyrestart(FILE *input_file)
int             yyparse();         // int yyparse()
int             yylex();           // int yylex()
extern void     yyerror(const char* s);  // void yyerror(char *s)
//extern int      yychar;            // yychar - The lookahead symbol. - protected
extern int      yydebug;           // int yydebug
extern int      yynerrs;           // int yyerrs

//

template <class AST>
class SourceFile {
public:
	typedef AST AST;

	SourceFile() : filename(), ast() {}

	SourceFile(SourceFile<AST>& sourceFile) : filename(sourceFile.filename), ast(sourceFile.ast) {}

	SourceFile(FileName& filename) : filename(filename), ast(new AST) {}

	SourceFile(FileName& filename, std::string rootType, std::string valueType, bool useUnion, std::string returnType) :
		filename(filename), ast(new AST), rootTypeName(rootType), valueType(valueType), useUnion(useUnion), returnType(returnType) {}

	SourceFile(FileName& filename, AST *ast, std::string rootType, std::string valueType, bool useUnion, std::string returnType) :
		filename(filename), ast(ast), rootTypeName(rootType), valueType(valueType), useUnion(useUnion), returnType(returnType) {}

	~SourceFile() {}

	//

	FileName getFilename() const {
		return filename;
	}
	void setFilename(FileName filename) {
		this->filename = filename;
	}

	//

	void setAST(AST* grammar) {
		this->ast = ast;
	}
	AST* getAST() {
		return ast;
	}
	AST* getAST() const {
		return ast;
	}
	void setActions(Actions* actions) {
		getAST()->setActions(actions);
	}
	Actions* getActions() const {
		return getAST()->getActions();
	}

	//

	void addHeader(CodeBlock* header) {
		this->header.push_back(header);
	}
	void addCode(CodeBlock* code) {
		this->code.push_back(code);
	}

	CodeBlocks& getHeaders() {
		return header;
	}
	const CodeBlocks& getHeaders() const {
		return header;
	}
	CodeBlocks& getCode() {
		return code;
	}
	const CodeBlocks& getCode() const {
		return code;
	}

	//

	void setRootType(std::string rootType) {
		rootTypeName = rootType;	// TODO: Normalize name.
	}
	void setBaseClass(std::string baseClass) {
		baseParserClassName = baseClass;
	}
	void setValueType(std::string valueType, bool useUnion = false) {
		this->valueType = valueType;
		this->useUnion = useUnion;
	}
	void setReturnType(std::string returnType) {
		this->returnType = returnType;
	}

	std::string getRootTypeName() const {
		return rootTypeName;
	}
	std::string getValueType() const {
		return valueType;
	}
	std::string getReturnType() const {
		return returnType;
	}

	bool getUseUnion() const {
		return useUnion;
	}

protected:
	FileName filename;

	AST* ast;

	CodeBlocks code;
	CodeBlocks header;

	//

	std::string rootTypeName;

	std::string baseParserName;
	std::string baseParserClassName;

	std::string valueType;
	std::string returnType;
	bool useUnion;
};

extern Logger* logger;

//
// 
// 

template <class AST, class LEXER, class PARSER>
class SourceFileParser : public SourceFile<AST> {
public:
	SourceFileParser(FileName& filename, Logger* logger, bool debug = false) : SourceFile<AST>(filename), debug(debug) {
		::logger = logger;
	}
	~SourceFileParser() {}

	operator SourceFile<AST>* () { return this; }

	virtual bool Parse() {
		File<FILE*> file(SourceFile<AST>::filename);

		if (!file.open())
			return false;	// TODO: throw

		typename PARSER::ValueType currentValue;

		LEXER* lexer = new LEXER(file, currentValue, SourceFile<AST>::getAST(), debug);
		PARSER parser(lexer, currentValue, SourceFile<AST>::getAST(), debug);

		bool result = parser.parse();

		file.close();

		return result;
	}

protected:
	bool debug;
};

//
// 
//

using namespace G::LexicalAnalyserGenerator;

class Flex {};
class Bison {};

extern Logger* ::logger;

//
//  class LexerSourceFile
//

template <class AST>
class SourceFileParser<AST, Flex, Bison> : public SourceFile<AST> {
public:
	SourceFileParser(FileName& filename, Logger* logger, bool debug = false) : SourceFile<AST>(filename), debug(debug) {
		::logger = logger;
	}
	virtual ~SourceFileParser() {}

	operator SourceFile<AST> () { return *this; }

	virtual bool Parse() {
		File<FILE*> file(SourceFile<AST>::filename);

		if (!file.open())
			return false;	// TODO: throw

		yyrestart(file);

		int result = yyparse();

		file.close();

		return result == 0;
	}

protected:
	bool debug;
};

template <class AST, class LEXER>
class SourceFileParser<AST, LEXER, Bison> : public SourceFile<AST> {
public:
	SourceFileParser(FileName& filename, Logger* logger, bool debug = false) : SourceFile<AST>(filename), debug(debug) {
		::logger = logger;
	}
	virtual ~SourceFileParser() {}

	operator SourceFile<AST> () { return *this; }

	virtual bool Parse() {
		File<FILE*> file(SourceFile<AST>::filename);

		if (!file.open())
			return false;	// TODO: throw

		int currentvalue = 0;
		LEXER lexer(file, currentvalue, SourceFile<AST>::ast);
		::lexer = &lexer;

		int result = yyparse();

		file.close();

		return result == 0;
	}

protected:
	bool debug;
};

