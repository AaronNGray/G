//
//	g/ParserGenerator/LR1/Move.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"

namespace G {
namespace ParserGenerator {

LR1::Item LR1::Item::Move() {
    Item newitem(*this);

    if (newitem.position < newitem.production->size())
        ++newitem.position;
    else
        throw;

    return newitem;
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/Move.cpp
