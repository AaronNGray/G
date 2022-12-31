//
//  g/ParserGenerator/Machine.h - Abstract Parser Generator Machine Interface
//
//  Property and Copyright (c) 2017-2022 Aaron Nathaniel Gray
//

#pragma once

#include <iostream>

namespace G {

class Machine {
public:
	Machine(bool rowCompressed = true, unsigned debug = 0) : rowCompressed(rowCompressed), debug(debug) {}
	virtual void Generate() = 0;

	virtual void AnalyseStates(std::ostream &os) = 0;

	virtual void Output(std::ostream& os) const = 0;

	virtual void OutputIncludesHXX(std::ostream &os, std::string className) const = 0;

	virtual void OutputCodeHXX(std::ostream &os, std::string className) const = 0;
	virtual void OutputCodeCXX(std::ostream &os, std::string className) const = 0;

	virtual void OutputTablesHXX(std::ostream &os, std::string className) const = 0;
	virtual void OutputTablesCXX(std::ostream &os, std::string className) const = 0;

	virtual void OutputTerminals(std::ostream& os) const = 0;
	virtual void OutputNonTerminals(std::ostream& os) const = 0;

	virtual void OutputStates(std::ostream& os) const = 0;

	virtual bool compare(const Machine* rhs) const = 0;

	bool rowCompressed;
	unsigned debug;
};

} // end namespace G

// End g/ParserGenerator/Machine.h - Abstract Parser Generator Machine Interface
