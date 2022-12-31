//
//	g/Grammar/PrettyPrint.cpp
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

#include <sstream>
#include "g/html.h"
#include "g/Grammar/ContextFreeGrammar.h"

namespace G {
namespace Grammar {

std::string ContextFreeGrammar::prettyPrint(int indent) const {
    std::stringstream ss;
    for (auto i = cbegin(), e = cend(); i != e; ++i) {
        ss << (*i)->prettyPrint(indent);
        ss << std::endl;
    }
    return ss.str();
}

std::string ContextFreeGrammar::Rule::prettyPrint(int indent) const {
    std::stringstream ss;
    bool first = true;
    ss << lhs->prettyPrint(indent) << " : ";
    for (auto i = cbegin(), e = cend(); i != e; ++i) {
        if (first) first = false; else ss << " | ";
        ss << (*i)->prettyPrint(indent);
    }
    ss << ";";
    return ss.str();
}

std::string ContextFreeGrammar::Production::prettyPrint(int indent) const {
    std::stringstream ss;
    bool first = true;
    for (auto i = cbegin(), e = cend(); i != e; ++i) {
        if (first) first = false; else ss << " ";
        ss << (*i)->prettyPrint(indent);
    }
    return ss.str();
}

std::string ContextFreeGrammar::NamedSymbol::prettyPrint(int indent) const {
    std::stringstream ss;
    if (name) ss << name->prettyPrint(indent) << ":";
    ss << symbol->prettyPrint(indent);
    return ss.str();
}

std::string ContextFreeGrammar::NonTerminal::prettyPrint(int indent) const {
    return name;
}

std::string ContextFreeGrammar::Terminal::prettyPrint(int indent) const {
    std::stringstream ss;
    if (value != "")
        ss << "\"" << value << "\"";
    else
        ss << name;
    return ss.str();
}

std::string ContextFreeGrammar::Epsilon::prettyPrint(int indent) const {
    return "epsilon";
}

std::string ContextFreeGrammar::End::prettyPrint(int indent) const {
    return "$";
}

std::string ContextFreeGrammar::Identifier::prettyPrint(int indent) const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string ContextFreeGrammar::StringLiteral::prettyPrint(int indent) const {
    std::stringstream ss;
    ss << "\"" << value << "\"";
    return ss.str();
}

//
//
//


std::string ContextFreeGrammar::HTMLPrint(std::string name) const {
    std::stringstream ss;
    ss << "<html>" << "\n";
    ss << HTML::Header(name);
    ss << "<body>" << "\n";
    for (const_iterator i = cbegin(), e = cend(); i != e; ++i) {
        ss << (*i)->HTMLPrint();
        ss << "\n";
    }
    ss << "</body>" << "\n";
    ss << "</html>" << "\n";
    return ss.str();
}

std::string ContextFreeGrammar::Rule::HTMLPrint() const {
    std::stringstream ss;
    bool first = true;
    ss << "<code>" << "\n";
    ss << HTML::a_name(lhs->getName()) << " =" << HTML::br;
    for (const_iterator i = cbegin(), e = cend(); i != e; ++i) {
        ss << HTML::tab;
        if (first)
            first = false;
        else
            ss << "|" << HTML::nbsp;
        ss << (*i)->HTMLPrint() << HTML::br;
    }
    ss << HTML::br;
    ss << "</code>" << "\n";
    return ss.str();
}

std::string ContextFreeGrammar::Production::HTMLPrint() const {
    std::stringstream ss;
    bool first = true;
    for (const_iterator i = cbegin(), e = cend(); i != e; ++i) {
        if (first)
            first = false;
        else
            ss << HTML::nbsp;
        ss << (*i)->HTMLPrint();
    }
    return ss.str();
}

std::string ContextFreeGrammar::NamedSymbol::HTMLPrint() const {
    std::stringstream ss;
    if (name)
        ss << name->HTMLPrint() << ":";
    ss << symbol->HTMLPrint();
    return ss.str();
}

std::string ContextFreeGrammar::NonTerminal::HTMLPrint() const {
    std::stringstream ss;
    ss << HTML::a_href(name);
    return ss.str();
}

std::string ContextFreeGrammar::Terminal::HTMLPrint() const {
    std::stringstream ss;
    ss << "<b>" << ((value != "") ? value : name) << "</b>";
    return ss.str();
}

std::string ContextFreeGrammar::Epsilon::HTMLPrint() const {
    return "epsilon";
}

std::string ContextFreeGrammar::End::HTMLPrint() const {
    return "$";
}

std::string ContextFreeGrammar::Identifier::HTMLPrint() const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::string ContextFreeGrammar::StringLiteral::HTMLPrint() const {
    std::stringstream ss;
    ss << "\"" << value << "\"";
    return ss.str();
}

} // end namespace G
} // end namespace Grammar

// End g/Grammar/PrettyPrint.cpp
