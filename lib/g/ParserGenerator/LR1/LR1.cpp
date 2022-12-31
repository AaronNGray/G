//
//	g/ParserGenerator/LR1/LR1.cpp
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"
#include "nonstd/deque.h"
#include "nonstd/Utils.h"

#include <string>
#include <map>
#include <deque>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace G {
namespace ParserGenerator {

std::string LR1::Name = "LR(1)";

//
//  LR1.GenerateItems(G') =
//    C <- { Closure({(S' -> •S$, $)}) }
//    repeat
//      for each set of items I in C and each grammar symbol X
//        such that goto(I, X) is not empty and not in C do
//          add goto(I, X) to C
//    until no more sets of items can be added to C
//
//
//  LR1.Closure(I) =
//    repeat
//    	for each item in (A -> a•Xß, a) in I,
//        each production B -> y in G'
//    		and each item terminal b in FIRST(ßa)
//        such that (B -> •y, b) is not in I
//          add (B -> •y, b) to I
//    until no more items can be added to I
//    return I
//
//  Generate.LR1.Items(S) =
//    T <- { Closure([S' -> •S$, $]) }
//    E <- {}
//    repeat
//    	for each state I in T
//    		for each item [A -> a•Xß, z] in I
//    			J <- Goto(I, X)
//          if J is not empty and J is not in T
//    			  T <- T U J
//    			E <- E U { I -> J }
//    until E and T do not alter
//
//  Generate.LR1.Reductions(T) =
//
//  LR1.Goto(I, X) =
//    let J be the set of items in (A -> aX•ß, a) such that
//      [A -> a•Xß, a] is in I
//    return Closure( J)
//

bool operator == (const LR1::Items& lhs, const LR1::Items& rhs) {
    if (lhs.size() != rhs.size())
        return false;

    for (auto l = lhs.cbegin(), r = rhs.cbegin(); l != lhs.cend(); ++l, ++r)
        if (*l != *r)
            return false;
    return true;
}

bool operator == (const LR1::State *lhs, const LR1::Items& rhs) {
    if (lhs->size() != rhs.size())
        return false;

    for (auto l = lhs->begin(), r = rhs.cbegin(); l != lhs->end(); ++l, ++r)
        if (*l != *r)
            return false;
    return true;
}

void LR1::GenerateStateProductions() {
    for (auto state : states) {
        state->production = state->items[0].production;             // TODO: remove
    }
}

// TODO: Needed for a States Action needs to be tied to reductions action.

bool LR1::compare(const Machine* rhs) const {

	bool items = (this->items == ((const LR1*) rhs)->items);
	bool states = (this->states == ((const LR1*)rhs)->states);

	bool result =
		items &&
		states;

	return result;
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/LR1.cpp
