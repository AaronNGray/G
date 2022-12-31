//
//  LexicalGenerator.h - Lexical Generator class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <iostream>
#include <string>
#include "nonstd/File.h"
#include "g/CodeBlock.h"
#include "g/LexicalAnalyserGenerator/DFA.h"
#include "g/SourceFile.h"

namespace G {
namespace LexicalAnalyserGenerator {

class LexicalGenerator {
public:
    LexicalGenerator(SourceFile<RegularGrammar>* sourceFile, Logger* _logger, bool lineDirectives = true, bool debug = false);
    LexicalGenerator(FileName& filename, LexicalMachine* lexicalMachine, std::string rootType, std::string baseClass, std::string valueType, std::string returnType, const std::initializer_list<CodeBlock> header, const std::initializer_list<CodeBlock> code);

    //LexicalGenerator(const LexicalGenerator& lexicalGenerator) : input_filename(lexicalGenerator.input_filename), lineDirectives(lexicalGenerator.lineDirectives), parser(nullptr), debug(lexicalGenerator.debug) {}
    //LexicalGenerator(SourceFile<RegularGrammar>& sourceFile, LexicalMachine* lexicalMachine, std::string rootType, std::string baseClass, std::string valueType, std::string returnType, const std::initializer_list<CodeBlock> header, const std::initializer_list<CodeBlock> code);
    ~LexicalGenerator() {
        if (lexicalMachine)
            delete lexicalMachine;
    }

    FileName getFilename() {
        return sourceFile->getFilename();
    }

    void setGrammar(RegularGrammar* grammar) {
        this->grammar = grammar;
    }
    void Process();
    void OutputOutput() const;
    void OutputCXX() const;
    void OutputH() const;

    void GenerateSource() const;
    void GenerateSourceH() const;
    void GenerateSourceCXX() const;

	void Dump(unsigned indent = 0) const;

    std::string base_filepath;
    std::string basename;
    std::string className;

    bool lineDirectives;

	void setFilename(FileName filename) {
        sourceFile->setFilename(filename);
		base_filepath = filename.remove_extension();
		basename = filename.base_name();

		logger->setFilename(filename.toString());

		className = filename.base_name() + "Lexer";

		compressed = true;
	}
	LexicalMachine* getMachine() {
        return lexicalMachine;
    }
	LexicalMachine::Identifier* newIdentifier(std::string _identifier) {
		return lexicalMachine->newIdentifier(_identifier);
	}

	void setLineDirectives(bool lineDirectives) {
		this->lineDirectives = lineDirectives;
	}
	void setLogger(Logger* logger) {
		this->logger = logger;
	}

    LexicalContext* newContext(const char *name, RegularGrammar* regularGrammar) {
        return new LexicalContext(lexicalMachine, regularGrammar, compressed, name);
    }

    RegularGrammar* newRegularGrammar(RegularGrammar::RE* root) {
        return new RegularGrammar(root);
    }

    Action* addAction(const char* action, unsigned int line) {
        return lexicalMachine->addAction(action, line);
    }

    void setStartContext(std::string startContext) {
        lexicalMachine->setStartContext(startContext);
    }
//
    void addHeader(CodeBlock* _header) {
        header.push_back(_header);
    }
    void addCode(CodeBlock* _code) {
        code.push_back(_code);
    }

    void setRootType(std::string _rootType) {
        lexicalMachine->setRootType(_rootType);
    }
    void setBaseClass(std::string baseClass) {
        lexicalMachine->setBaseClass(baseClass);
    }
    void setValueType(std::string valueType) {
        lexicalMachine->setValueType(valueType);
    }
    void setReturnType(std::string returnType) {
        lexicalMachine->setReturnType(returnType);
    }
//
	friend bool compare(const LexicalGenerator* lhs, const LexicalGenerator* rhs);

private:
    SourceFile<RegularGrammar>* sourceFile;

    CodeBlocks header;
	CodeBlocks code;

    bool diagnostics;
    bool compressed;
    Logger* logger;
    bool debug;
    RegularGrammar* grammar;
	LexicalMachine* lexicalMachine;
};

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End LexicalGenerator.h - Lexical Generator class
