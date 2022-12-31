//
//  g/CodeBlock.h - Code Block class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include <vector>
#include "nonstd/string.h"
#include "nonstd/vector.h"
#include "nonstd/Utils.h"

class CodeBlock {
public:
	CodeBlock() : line(0) {}
	CodeBlock(std::string code, unsigned int line, nonstd::string filename) : code(code), line(line), filename(filename) {}

	nonstd::string getCode() const { return code; }
	unsigned int getLine() const { return line; }
	nonstd::string getFilename() const { return filename; }

	nonstd::string generate() const;

	void GenerateSource(std::ostream &output, unsigned indent) const {
		output << Indent(indent) << "{ " << getCode().stringify() << ", " << getLine() << ", \"" << getFilename().escape() << "\" }";
	}
	void OutputCodeBlock(std::ostream &output, bool lineDirectives = false) const {
		if (lineDirectives)
			output << "#line " << getLine() << " \"" << getFilename().escape() << "\"" << nonstd::endl;
		output << getCode() /*.escape()*/ << nonstd::endl;
	}

	friend bool compare(const CodeBlock& lhs, const CodeBlock& rhs) {
		return lhs.code == rhs.code;
	}

	nonstd::string code;
	unsigned line;
	nonstd::string filename;
};

class CodeBlocks : public vector<CodeBlock*> {
public:
	CodeBlocks() {}
	CodeBlocks(const std::initializer_list<CodeBlock*> lines) : vector<CodeBlock*>(lines) {}

	void OutputCodeBlocks(std::ostream &output, bool lineDirectives = false) const {
		for (auto code : *this)
			code->OutputCodeBlock(output, lineDirectives);
	}
	void GenerateSource(std::ostream &output, unsigned indent) const {
		output << Indent(indent) << "{" << nonstd::endl;
		for (auto code = cbegin(); code != cend(); ++code) {
			(*code)->GenerateSource(output, indent + 2);
			if (code != clast())
				output << ",";
			output << nonstd::endl;
		}
		output << Indent(indent) << "}";
	}
	friend bool compare(const CodeBlocks& lhs, const CodeBlocks& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (auto l = lhs.begin(), r = rhs.begin(); l != lhs.end(); ++l, ++r)
			if (*l != *r)
				return false;
		return true;
	}
};

// End g/CodeBlock.h

// TODO: format CodeBlocks::GenerateSource() no newlimes to separate lines with indent
