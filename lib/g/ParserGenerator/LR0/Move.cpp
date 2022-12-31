//
//	g/ParserGenerator/LR0/Move.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR0/LR0.h"

namespace G {
namespace ParserGenerator {

LR0::Item LR0::Item::Move() {
	Item newitem(*this);

	if (newitem.position < newitem.production->size())
		++newitem.position;
	else
		throw;

	return newitem;
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR0/Move.cpp
