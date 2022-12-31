//
//  g/LexicalAnalyserGenerator/ColumnMap.cpp - input column map
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/LexicalAnalyserGenerator/ColumnMap.h"
#include <iomanip>

namespace G {
namespace LexicalAnalyserGenerator {

ColumnMap::ColumnMap(EquivalenceClasses& equivalenceClasses, bool compressed) {
    bitset classes;

    for (auto si : equivalenceClasses.getEquivalenceSets())
        classes |= *si;

	Lowers& lowers = equivalenceClasses.getLowers();

    for (auto ci = classes.begin(); ci != classes.end(); ++ci) {
        unsigned int lower = lowers[ci.index()];
        unsigned int upper = (ci.index() < lowers.size() - 1) ? lowers[ci.index() + 1] : 128; // TODO: Generalize

        for (auto index = lower; index < upper; ++index)
            (*this)[index] = compressed ? equivalenceClasses.getInputIndexFromColumnIndex(ci.index()) : ci.index();
    }
}

void ColumnMap::OutputColumnMapCXX(std::ostream &os, std::string className) {
	os << "unsigned char " << className << "::ec[128] = {" << std::endl;
	for (unsigned int i = 0; i < 8; ++i) {
		os << "//";
		for (unsigned int j = 0; j < 16; ++j) {
			char c = i * 16 + j;
			if (c < 16)
				os << "  " << std::hex << (int)c << " ";
			else if (c < 32 || c >= 127)
				os << " " << std::hex << (int)c << " ";
			else if (c >= 32 && c < 127)
				os << " '" << (char)c << "'";
			os << " ";
		}
		os << std::endl;
		os << std::dec << " ";
		for (size_t j = 0; j < 16; ++j) {
			int c = i * 16 + j;
			signed int ec = (*this)[c];
			if (ec >= 0)
				os << std::setw(4) << ec;
			else
				os << "  -1";
			if (c != 127)
				os << ",";
		}
		os << std::endl;
		if (i != 7)
			os << std::endl;
	}
	os << "};" << std::endl << std::endl;
}

void ColumnMap::OutputColumnMap(std::ostream &os) {
	for (unsigned int i = 0; i < 8; ++i) {
		os << "  ";
		for (unsigned int j = 0; j < 16; ++j) {
			char c = i * 16 + j;
			if (c < 16)
				os << "  " << std::hex << (int)c << " ";
			else if (c < 32 || c >= 127)
				os << " " << std::hex << (int)c << " ";
			else if (c >= 32 && c < 127)
				os << " '" << (char)c << "'";
			os << " ";
		}
		os << std::endl;
		os << std::dec << " ";
		for (size_t j = 0; j < 16; ++j) {
			int c = i * 16 + j;
			signed int ec = (*this)[c];
			if (ec >= 0)
				os << std::setw(4) << ec;
			else
				os << "  -1";
			if (c != 127)
				os << " ";
		}
		os << std::endl;
		if (i != 7)
			os << std::endl;
	}
}

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/ColumnMap.cpp - input column map
