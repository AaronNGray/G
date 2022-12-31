//
//	g/ParserGenerator/LL1/Generate.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LL1/LL1.h"

namespace G {
namespace ParserGenerator {

void LL1::Generate() {
	GenerateStatesAndTransitions();
	CheckForConflicts();
	GenerateDFA();
	GeneratePushTable();
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LL1/Generate.cpp
