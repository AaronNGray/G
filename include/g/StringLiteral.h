//
//  g/StringLiteral.h - String Literal
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "g/CharacterLiteral.h"

class StringLiteral : public std::string {
public:
	StringLiteral() {}
	StringLiteral(std::string string) : std::string(string) {}
    std::string toString() {
		return toSource();
    }

    std::string toSource() {
        return "\"" + _toSource() + "\"";
    }

    std::string _toSource() {
        std::string ret;

		std::cout << *this << std::endl;

        for (auto i = cbegin(); i != cend();) {
            switch (*i) {
				case '\\': {
					if (++i == cend())
						throw;
					switch (*i) {
						case 'a':
						case 'b':
						case 'f':
						case 'n':
						case 'r':
						case 't':
						case 'v':
						case '\'':
						case '\"':
						case '\?':
						case '\\': {
							ret += std::string("\\") + *i++;
							break;
						}
						default: {
							ret += *i++;
							break;
						}
					} // end switch
					break;
				}
				case '\"': {
					++i;
					ret += "\"";
					for (; i != end() && *i != '\"';) {
						switch (*i) {
							case '\\': {
								ret += std::string("\\") + *i++;
								break;
							}
							default: {
								ret += *i++;
								break;
							}
						}
					}
					//ret += "\"";
					break;
				}
                case '\'': {
					ret += '\'';
					switch (*i) {
						case '\\': {
							switch (*++i) {
								case '\\': {
									++i;
									ret += "\\\\";
									break;
								}
								case '\'': {
									++i;
									ret += "\\\'";
									break;
								}
								default: {
									ret += std::string("\\") + *i++;
									break;
								}
							}
							break;
						}
						default: {
							ret += *i++;
							break;
						}
					};
					if (*i++ == '\'')
						ret += '\'';
					else
						throw;
					break;
                }
                default: {
                    ret += *i++;
                    break;
                }
            } // end switch
        } // end for
        return ret;
    }
};

// End g/StringLiteral.h - String Literal

// TODO: Move to nonstd ?
