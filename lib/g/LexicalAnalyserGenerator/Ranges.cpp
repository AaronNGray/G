//
//  g/LexicalAnalyserGenerator/Ranges.cpp - Character Ranges
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/LexicalAnalyserGenerator/Ranges.h"

namespace G {
namespace LexicalAnalyserGenerator {

std::string Ranges::toString() const {
	std::ostringstream os;
	os << "{" << std::endl;
	if (ranges.size()) {
		auto i = cbegin();
		for (; i != cend() - 1; ++i) {
			os << "  " << i->toString() << "," << std::endl;
		}
		os << "  " << i->toString() << std::endl;
	}
	os << "}" << std::endl;
	return os.str();
}

std::string Ranges::toSource() const {
	std::ostringstream os;
	os << "{" << std::endl;
	if (ranges.size()) {
		auto i = cbegin();
		for (; i != clast(); ++i) {
			os << "  " << i->toSource() << "," << std::endl;
		}
		os << "  " << i->toSource() << std::endl;
	}
	os << "}" << std::endl;
	return os.str();
}

bool Compare(const Ranges& rs1, const Ranges& rs2) {
	if (rs1.ranges.size() != rs2.ranges.size())
		return false;

	return std::equal(rs1.cbegin(), rs1.cend(), rs2.cbegin());
}

bool Compare2(const Ranges& rs1, const Ranges& rs2) {
	if (rs1.ranges.size() != rs2.ranges.size())
		return false;

	for (auto ri1 = rs1.cbegin(), ri2 = rs2.cbegin(); ri1 != rs1.cend(); ++ri1, ++ri2) {
		if (*ri1 == *ri2)
			std::cout << "same: " << ri1->toString() << " - " << ri2->toString() << std::endl;
		else
			std::cout << "diff: " << ri1->toString() << " - " << ri2->toString() << std::endl;
	}

	return std::equal(rs1.cbegin(), rs1.cend(), rs2.cbegin());
}

bool operator == (const Ranges& rs1, const Ranges& rs2) {
	return Compare(rs1, rs2);
}

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/Ranges.cpp - Character Ranges
