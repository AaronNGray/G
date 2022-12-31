//
//	g/ParserGenerator/LR1/Goto.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"

namespace G {
namespace ParserGenerator {

//
//
//  LR1.Goto(I, X) =
//    let J be the set of items in (A -> aX•ß, a) such that
//      [A -> a•Xß, a] is in I
//    return Closure(J)
//

LR1::Items LR1::Goto(Items& I, ContextFreeGrammar::Symbol* X) {
    Items J;

    for (auto i : I)
        if (i.hasMove() && i.rightOfDot() == X)
            J.insert(i.Move());

    return Closure(J);
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/Goto.cpp
