//
//  g/CharacterLiteral.h - String Literal
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#pragma once

#include <iostream>
#include <sstream>
#include <string>

class CharacterLiteral {
public:
	template<class T = char>
	static std::string toString(T c) {
		std::ostringstream os;
		if (c < 32 || c > 126)
			os << "\\x" << std::hex << (int)c;
		else
			os << (unsigned char)c;
		return os.str();
	}

	template<class T = char>
	static std::string toSource(T c) {
		return "'" + _toSource(c) + "'";
	}

	template<class T = char>
	static std::string _toSource(T c) {
		std::stringstream os;
		if (c == '\\')
			os << "\\\\";
		else if (c == '\'')
			os << "\\\'";
		else if (c == 0x09)
			os << "\\t";
		else if (c == 0x0A)
			os << "\\n";
		else if (c == 0x0D)
			os << "\\r";
		else if (c >= 0 && c < 32)
			os << "\0x" << std::hex << (int)c;
		else if (c < 0)
			os << (signed int)c;
		else if (c >= 127)
			os << "'\0x" << std::hex << (int)c << "'";
		else
			os << (char)c;
		return os.str();
	}
};

// End g/CharaterLiteral.h - Character Literal
