//
//	g/ParserGenerator/LR1/toString.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "g/ParserGenerator/LR1/LR1.h"

namespace G {
namespace ParserGenerator {

std::string LR1::Item::toString() const {
    std::stringstream ss;

    ss << production->getLHS()->toString() << " ->";

    size_t length = production->getRHS().size();
    size_t pos = 0;

    for (; pos < length; ++pos) {
        if (pos == position)
            ss << " .";

        ss << " " << production->getRHS()[pos]->toString();
    }

    if (pos == position)
        ss << " .";

    ss << ", " << lookaheads.toString();

    return ss.str();
}

//

std::string LR1::Item::toString(ContextFreeGrammar* grammar, int i) const {
    std::stringstream ss;

    ss << Indent(i);
    ss << production->getLHS()->toString() << " ->";

    size_t length = production->getRHS().size();
    size_t pos = 0;

    for (; pos < length; ++pos) {
        if (pos == position)
            ss << " .";

        ss << " " << production->getRHS()[pos]->toString();
    }

    if (pos == position)
        ss << " .";

    ss << ", " << lookaheads.toString(grammar->getTerminalNamesAsVector());

    return ss.str();
}

//

std::string LR1::Items::toString() const {
    std::stringstream ss;

    for (auto item : getItems())
        ss << item.toString() << std::endl;

    return ss.str();
}

std::string LR1::Items::toString(ContextFreeGrammar* grammar, int i) const {
    std::stringstream ss;

    for (auto item : getItems())
        ss << Indent(i) << item.toString(grammar) << std::endl;

    return ss.str();
}

//

std::string LR1::State::toString(ContextFreeGrammar* grammar, int i) const {
    std::stringstream ss;

//    ss << "Production: " << production->index << std::endl << std::endl;  // TODO: Production is not really satisfactory at all this will be removed soon.

    ss << "state:" << index << std::endl;

    if (items.size()) ss << Indent(i) << "items:" << std::endl;
    ss << items.toString(grammar, i + 4);

    if (shifts.size()) ss << Indent(i) << "shifts:" << std::endl;

    for (auto mapping : shifts) {
        if (mapping.first->isTerminal() && mapping.second)  // TODO: check why null !
            ss << Indent(i) << Indent(i) << mapping.first->toString() << " shift to " << mapping.second->index << std::endl;
    }

    if (shifts.size()) ss << Indent(i) << "gotos:" << std::endl;
    for (auto mapping : shifts)
        if (mapping.first->isNonTerminal() && mapping.second)
            ss << Indent(i) << Indent(i) << mapping.first->toString() << " go to " << mapping.second->index << std::endl;

    if (reductions.size()) ss << Indent(i) << "reductions:" << std::endl;
    for (auto item : reductions) {
        ss << Indent(i) << Indent(i) << item->getLookaheads().toString(grammar->getTerminalNamesAsVector()) << " reduce by production " << item->getProduction()->getIndex() << " to " << item->getLHS()->toString() << std::endl; // TODO: Check bug in getLHS() returning invalid data, but results correct ?!
    }
    if (reductions.size()) ss << std::endl;

    if (actions.size()) ss << Indent(i) << "actions:" << std::endl;
    for (auto action : actions)
        ss << Indent(i) << Indent(i) << action.first->toString() << " - " << action.second.toString() << std::endl;
    if (actions.size()) ss << std::endl;

    return ss.str();
}

// TODO: !!!

template<>
std::string LR1::States<>::toString(ContextFreeGrammar* grammar, int i) const {
    std::stringstream ss;
    int s = 0;
    for (auto state : getStates()) {
        ss << state->index << " : {" << std::endl;
        ss << state->toString(grammar, i);
        ss << "}" << std::endl;
    }
    return ss.str();
}

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LR1/toString.cpp
