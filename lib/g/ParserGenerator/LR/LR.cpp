//
//	g/ParserGenerator/LR.cpp
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR/LR.h"
#include <sstream>

namespace G {
namespace ParserGenerator {

std::string LR::ACTION::toString() const {
	std::stringstream ss;
	switch (action) {
	case Shift:
		ss << "s" << std::to_string(value);
		break;
	case Reduce:
		ss << "r" << std::to_string(value);
		break;
	case Accept:
		ss << "a";
		break;
	case Error:
		ss << "-";
		break;
	}
	return ss.str();
}
std::string LR::ACTION::toCXXString() const {
	std::stringstream ss;
	switch (action) {
	case Shift:
		ss << "{Action::Function::Shift, " << std::to_string(value) << "}";
		break;
	case Reduce:
		ss << "{Action::Function::Reduce, " << std::to_string(value) << "}";
		break;
	case Accept:
		ss << "{Action::Function::Accept}";
		break;
	case Error:
		ss << "{Action::Function::Error}";
		break;
	}
	return ss.str();
}


std::string Lookaheads::toString() const {
	return bitset::toString();
}

std::string Lookaheads::toString(std::vector<std::string> names) const {
	return bitset::toString(names);
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR.cpp
