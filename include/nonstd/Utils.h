//
//  Utils.h - utils functions
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#ifndef __LG__LIB__UTILS_H__
#define __LG__LIB__UTILS_H__

#include <sstream>
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

inline std::string Indent(int i) {
    std::stringstream ss;
    while (i--)
        ss << " ";
    return ss.str();
}

inline std::string generateGuardString(std::string filename) {
	std::string guard;

	for (auto ch : filename) {
		if (isupper(ch) || isdigit(ch))
			guard += ch;
		else if (islower(ch))
			guard += toupper(ch);
		else if (ch == '\\')
			guard += "__";
		else
			guard += "_";
	}
	return guard;
}

inline std::string generateSymbolString(std::string symbol) {
	std::string ret;

	for (auto ch : symbol) {
		if (ch == '\'')
			ret += "_";
		else
			ret += ch;
	}
	return ret;
}

template<class Type = char>
std::string toString(Type c) {
    std::stringstream os;
    if (c == 0x09)
        os << "'\\t'";
    else if (c == 0x0A)
        os << "'\\n'";
    else if (c == 0x0D)
        os << "'\\r'";
    else if (c >= 0 && c < 32)
        os << "'\0x" << std::hex << (int)c << "'";
    else if (c < 0)
        os << (signed int)c;
    else if (c >= 127)
        os << "'\0x" << std::hex << (int)c << "'";
    else
        os << "'" << (char)c << "'";
    return os.str();
}

inline std::string toStringBool(bool value) {
	if (value)
		return "true";
	else
		return "false";
}


inline std::string stringify(std::string s) {
    return std::string("\"") +
        std::regex_replace(
            std::regex_replace(s,
                std::regex("\""), "\\\""),
            std::regex("\n"), "")
        + std::string("\"");
}

namespace nonstd {
    extern std::string endl;

    // Trims by LogicStuff - http://stackoverflow.com/users/3552770/logicstuff

    // trim from start
    static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        return s;
    }

    // trim from end
    static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
        return s;
    }

    // trim from both ends
    static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
    }

    // trim from start (copying)
    static inline std::string ltrimmed(std::string s) {
        ltrim(s);
        return s;
    }

    // trim from end (copying)
    static inline std::string rtrimmed(std::string s) {
        rtrim(s);
        return s;
    }

    // trim from both ends (copying)
    static inline std::string trimmed(std::string s) {
        trim(s);
        return s;
    }
}

inline void OutputIncludes(std::ostream &output, std::vector<std::string> files) {
    for (auto file : files)
        output << "#include \"" << file << "\"" << nonstd::endl;
}


namespace nonstd {
	inline std::string generateBoolean(bool value) {
		return value ? "true" : "false";
	}
}

#endif // end __LG__LIB__UTILS_H__

// end lib/utils.h
