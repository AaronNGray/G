//
//  g/TextualTemplateGenerator/TextualTemplate.cpp
//
//  Property and Copyright (c) 2016 Aaron Nathaniel Gray
//

#pragma once

#include "lib/TextualTemplateGenerator/TextualTemplate.h"
#include "lib/Utils.h"

namespace G {
namespace TextualTemplateGenerator {

std::string TextualTemplate::OutputHXX() const {
    return module->OutputHXX();
}

std::string TextualTemplate::OutputCXX() const {
	return module->OutputCXX();
}

std::string TextualTemplate::Module::OutputHXX() const {
	return templates->OutputHXX();
}
std::string TextualTemplate::Module::OutputCXX() const {
	return templates->OutputCXX();
}

std::string TextualTemplate::Templates::OutputHXX() const {
	std::string s;
	for (auto _template : *templates)
		s += _template->OutputHXX();
	return s;
}
std::string TextualTemplate::Templates::OutputCXX() const {
	std::string s;
	for (auto _template : *templates)
		s += _template->OutputCXX();
	return s;
}

std::string TextualTemplate::ClassTemplate::OutputHXX() const {
	std::string s;
	s += "std::string " + name->toString() + "(" + (arguments ? arguments->toString() : "") + ")" + "{" + nonstd::endl;
	s += "std::string s;" + nonstd::endl;
	s += "s += " + stringify("class " + name->toString() + " {") + " << std::endl;" + nonstd::endl;
	s += block->Output();
	s += "s += \"};\"" + nonstd::endl;
	s += "return s;" + nonstd::endl;
	s += "};" + nonstd::endl;
	return s;
}
std::string TextualTemplate::ClassTemplate::OutputCXX() const {
	return "";
}


std::string TextualTemplate::FunctionTemplate::OutputHXX() const {
	std::string s;
	s += "void " + name->toString() + "(" + (arguments ? arguments->toString() : "") + ")" + ";" + nonstd::endl;
	return s;
}
std::string TextualTemplate::FunctionTemplate::OutputCXX() const {
	std::string s;
	s = "std::string " + name->toString() + "(" + (arguments ? arguments->toString() : "") + ")" + "{" + nonstd::endl;
	s += "\tstd::string s;" + nonstd::endl;
	s += block->Output();
	s += "\treturn s;" + nonstd::endl;
	s += "};" + nonstd::endl;
	return s;
}

std::string TextualTemplate::Block::Output() const {
	std::string s;
	for (auto i : list)
		s += i->Output();
	return s;
}

std::string TextualTemplate::CodeBlock::Output() const {
	std::string s;
	std::cout << "CodeBlock(" << stringify(code) << ")" << std::endl;
	if (code == "" || code == "\n")
		s += "\ts += nonstd::endl;" + nonstd::endl;
	else
		s += "\ts += " + stringify(code) + " + nonstd::endl;" + nonstd::endl;
	return s;
}

std::string TextualTemplate::ActionCode::Output() const {
	std::string s;
	std::cout << "ActionBlock(" << stringify(code) << ")" << std::endl;
	if (code == "" || code == "\n")
		s += nonstd::endl;
	else
		s += code;
	return s;
}

std::string TextualTemplate::Parameter::Output() const {
	std::string s;
	std::cout << "Parameter(" << stringify(code) << ")" << std::endl;
	if (code == "" || code == "\n")
		s += nonstd::endl;
	else
		s += "\ts += " + code + ";" + nonstd::endl;
	return s;
}

std::string TextualTemplate::Argument::toString() const {
	return type->toString() + " " + name->toString();
}
std::string TextualTemplate::Arguments::toString() const {
	std::string s;
	for (auto argument = arguments->begin(); argument != arguments->end(); ++argument) {
		s += (*argument)->toString();

		if (argument != arguments->last())
			s += ", ";
	}
	return s;
}

} // end namespace TextualTemplateGenerator
} // end namespace G

// End g/TextualTemplateGenerator/TextualTemplate.cpp
