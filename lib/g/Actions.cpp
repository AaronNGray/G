//
//  g/Actions.cpp - Action methods
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include <fstream>
#include <map>
#include <regex>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "g/Actions.h"
#include "nonstd/Utils.h"
#include "nonstd/string.h"

void Actions::SubstituteAttributes(Action* action, vector<std::string>& attributes, vector<std::string>& types, bool isUnion, std::string type, size_t rhs_size) {
    if (action)
        action->SubstituteAttributes(attributes, types, isUnion, type, rhs_size);
}

//
//  $$ ->
//  $n$ ->
//  $alpha$ ->
//

void Action::SubstituteAttributes(vector<std::string>& attributes, vector<std::string>& types, bool isUnion, std::string type, size_t rhs_size) {
    std::string result;
    std::string currentValue = type != "" ? ("currentValue" + std::string(isUnion ? ("." + type) : "")) : "currentValue";
    std::string result1 = std::regex_replace(action, std::regex("\\$\\$", std::regex_constants::ECMAScript), currentValue);

    for (size_t attribute = 1; attribute <= rhs_size; ++attribute) {
        std::string variable = "\\$" + std::to_string(attribute);
        std::regex regex(variable, std::regex_constants::ECMAScript);
        std::string replacement = "valueStack[" + std::to_string(rhs_size - attribute) + "]" + std::string(isUnion ? ("." + types[attribute]) : "");
        result = std::regex_replace(result1, regex, replacement);
        result1 = result;
    }
    for (size_t attribute = 1; attribute <= rhs_size; ++attribute) {
        std::string variable = "\\$" + attributes[attribute] + "\\$";
        std::regex regex(variable, std::regex_constants::ECMAScript);
        std::string replacement = "valueStack[" + std::to_string(rhs_size - attribute) + "]" + std::string(isUnion ? ("." + types[attribute]) : "");
        result = std::regex_replace(result1, regex, replacement);
        result1 = result;
    }
    action = result1;
}

void Actions::OutputActionDispatcherCXX(std::ostream &os, std::string className) const {
    os << "int " << className << "::" << "dispatch(int action) {" << std::endl;
    os << "\t" << "return (this->*Actions[action])();" << std::endl;
    os << "}" << std::endl << std::endl;
}

void Actions::OutputActionsHXX(std::ostream &os, std::string className, std::string returnType) const {
    os << "\t" << "static " << returnType << "(" << className << "::*Actions[" << actions.size() << "])()" << ";" << std::endl;
    for (unsigned int action = 0; action < actions.size(); ++action)
        OutputActionHXX(action, os, className, returnType);
}

void Actions::OutputActionHXX(unsigned int action, std::ostream &os, std::string className, std::string returnType) const {
    os << "\t" << returnType << " " << "Action" << action << "()" << ";" << std::endl;
}

void Actions::OutputActionsCXX(std::ostream &os, std::string className, FileName filename, std::string returnType, bool lineDirectives) const {
    for (unsigned int number = 0; number < actions.size(); ++number)
        OutputActionCXX(number, actions[number], os, className, filename, returnType, lineDirectives);

    os << std::endl;
    os << returnType << " (" << className << "::*" << className << "::Actions[" << actions.size() << "])()" << " = {" << std::endl;
    for (unsigned int action = 0; action < actions.size(); ++action) {
        os << "\t" << "&" << className << "::" << "Action" << action;
        if (action < actions.size() - 1)
            os << ",";
        os << std::endl;
    }
    os << "};" << std::endl;
    os << std::endl;
}

void Actions::OutputActionCXX(unsigned int number, Action* action, std::ostream &os, std::string className, FileName filename, std::string returnType, bool lineDirectives) const {
    os << "inline " << returnType << " " << className << "::" << "Action" << number << "()" << std::endl;
    if (lineDirectives)
        os << "#line " << action->getLine() << " \"" << filename.escape() << "\"" << std::endl;
    os << action->getAction();  // TODO: escape()
    os << std::endl;
}

std::string Actions::Generate(int indent) const {
    std::string output;
    output += Indent(indent) + "{" + nonstd::endl;
    for (auto action = actions.begin(); action != actions.end(); ++action) {
        output += (*action)->Generate();
        if (action != actions.last())
            output += ",";

        output += nonstd::endl;
    }
    output += Indent(indent) + "}";
    return output;
}

std::string Actions::toSource() const {
    std::string output;
    output += "Actions bootstrapActions = {" + nonstd::endl;
    for (auto action = actions.begin(); action != actions.end(); ++action) {
        output += (*action)->toSource();
        if (action != actions.last())
            output += ",";

        output += nonstd::endl;
    }
    output += "};" + nonstd::endl;
    return output;
}

std::string Action::Generate() const {
    std::string output;
    output += "\t" "{ ";
    output += std::to_string(index) + ", ";
    output += nonstd::string(action).stringify() + ", ";
    output += std::to_string(line);
    output += std::string("}");
    return output;
}

nonstd::string Action::toSource() const {
    nonstd::string output;
    output += "\t" "{ ";
    output += std::to_string(index) + ", ";
    output += nonstd::string(action).stringify() + ", ";
    output += std::to_string(line);
    output += std::string("}");
    return output;
}

void Actions::Dump(std::ostream &os, unsigned indent) const {
	os << toSource() << std::endl;
}

bool operator == (const Action& lhs, const Action& rhs) {
	return lhs.action == rhs.action;
}
bool operator == (const Actions& lhs, const Actions& rhs) {
	if (lhs.actions.size() != rhs.actions.size())
		return false;
	for (auto l = lhs.actions.begin(), r = rhs.actions.begin(); l != lhs.actions.end(); ++l, ++r)
		if (*l != *r)
			return false;
	return true;
}

bool compare(const Actions& lhs, const Actions& rhs) {
    if (lhs.actions.size() != rhs.actions.size())
        return false;
    for (auto l = lhs.actions.begin(), r = rhs.actions.begin(); l != lhs.actions.end(); ++l, ++r)
        if (*l != *r)
            return false;
    return true;
}

/*
bool compare(const Actions& lhs, const Actions& rhs) {
	return true;
}
*/
// TODO: Quotes need escaping properly.

// End g/Actions.h - Action methods
