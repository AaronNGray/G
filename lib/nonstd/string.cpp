//
//	nonstd/string.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include <stdlib.h>

#include "nonstd/string.h"

nonstd::string nonstd::string::escape() const {
	std::string ret = *this;

	for (size_t pos = 0; (pos = ret.find("\\", pos)) != std::string::npos; ) {
		ret.replace(pos, 1, "\\\\");
		pos = std::min(pos + 2, ret.size());
	}

	return ret;
}

nonstd::string nonstd::string::stringify() const {
	return "\"" + _stringify() + "\"";
}

nonstd::string nonstd::string::_stringify() const {
	nonstd::string ret;

	for (auto i = cbegin(); i != cend();) {
		switch (*i) {
		case '\a': {
			ret += "\\a";
			++i;
			break;
		}
		case '\b': {
			ret += "\\b";
			++i;
			break;
		}
		case '\f': {
			ret += "\\f";
			++i;
			break;
		}
		case '\n': {
			ret += "\\n";
			++i;
			break;
		}
		case '\r': {
			ret += "\\r";
			++i;
			break;
		}
		case '\t': {
			ret += "\\t";
			++i;
			break;
		}
		case '\v': {
			ret += "\\v";
			++i;
			break;
		}
		case '\\': {
			if (++i == cend()) {
				ret += "\\\\";
				break;
			}
			switch (*i) {
			case 'a':
			case 'b':
			case 'f':
			case 'n':
			case 'r':
			case 't':
			case 'v':
			case '\'':
			case '?': {
				ret += "\\\\";
				ret += *i++;
				break;
			}
			case '"': {
				ret += "\\\\\\\"";
				++i;
				break;
			}
			case '\\': {
				ret += "\\\\\\\\";
				++i;
				break;
			}
			default: {
				ret += *i++;
				break;
			}
			} // end switch
			break;
		}
		case '"': {
			++i;
			ret += "\\\"";
			for (; i != end() && *i != '\"';) {
				switch (*i) {
				case '\a': {
					ret += "\\a";
					++i;
					break;
				}
				case '\b': {
					ret += "\\b";
					++i;
					break;
				}
				case '\f': {
					ret += "\\f";
					++i;
					break;
				}
				case '\n': {
					ret += "\\n";
					++i;
					break;
				}
				case '\r': {
					ret += "\\r";
					++i;
					break;
				}
				case '\t': {
					ret += "\\t";
					++i;
					break;
				}
				case '\v': {
					ret += "\\v";
					++i;
					break;
				}
				case '\\': {
					if (++i == cend())
						throw;
					ret += "\\\\";
					switch (*i) {
					case 'a':
					case 'b':
					case 'f':
					case 'n':
					case 'r':
					case 't':
					case 'v':
					case '\'':
					case '?': {
						ret += "\\";
						ret += *i++;
						break;
					}
					case '"': {
						++i;
						ret += "\\\"";
						break;
					}
					case '\\': {
						ret += "\\\\";
						++i;
						break;
					}
					default: {
						ret += *i++;
						break;
					}
					} // end switch
					break;
				} // end case
				case '"': {
					ret += "\\\"";
					++i;
					break;
				}
				default: {
					ret += *i++;
					break;
				}
				} // end switch
			} // end for
			if (i == cend())
				break;
			//if (*i == '\"')
			//	ret += "\\\"";
			break;
		}
		case '\'': {
			++i;
			ret += '\'';
			switch (*i) {
			case '\\': {
				++i;
				switch (*i) {
				case 'a': {
					ret += "\\\\a";
					++i;
					break;
				}
				case 'b': {
					ret += "\\\\b";
					++i;
					break;
				}
				case 'f': {
					ret += "\\\\f";
					++i;
					break;
				}
				case 'n': {
					ret += "\\\\n";
					++i;
					break;
				}
				case 'r': {
					ret += "\\\\r";
					++i;
					break;
				}
				case 't': {
					ret += "\\\\t";
					++i;
					break;
				}
				case 'v': {
					ret += "\\\\v";
					++i;
					break;
				}
				case '\\': {
					++i;
					ret += "\\\\\\\\";
					break;
				}
				case '\'': {
					++i;
					ret += "\\\\'";
					break;
				}
				case '\"': {
					++i;
					ret += "\\\"";
					break;
				}
				default: {
					ret += "\\\\";
					ret += *i++;
					break;
				}
				} // end switch
				break;
			}
			case '"': {
				ret += "\\\"";
				++i;
				break;
			}
			case '\'': {
				ret += "\\'";
				++i;
				break;
			}
			default: {
				ret += *i++;
				break;
			}
			}
			if (i == cend())
				break;
			if (*i == '\'') {
				++i;
				ret += '\'';
			}
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

// hack from :- http://www.strudel.org.uk/itoa/

std::string itoa(int value, int base) {
	enum { kMaxDigits = 35 };

	std::string buf;
	buf.reserve( kMaxDigits ); // Pre-allocate enough space.

	// check that the base if valid

	if (base < 2 || base > 16) return buf;
	int quotient = value;

	// Translating number to string with base:
	do {
		buf += "0123456789abcdef"[ std::abs( quotient % base ) ];
		quotient /= base;
	} while ( quotient );

	// Append the negative sign for base 10
	if ( value < 0 && base == 10) buf += '-';

	std::reverse( buf.begin(), buf.end() );

	return buf;
}

nonstd::string nonstd::string::printify() const {
	nonstd::string ret;

	for (auto i = cbegin(); i != cend();) {
		switch (*i) {
			case '\a': {
				ret += "<bell>";
				++i;
				break;
			}
			case '\b': {
				ret += "<backspace>";
				++i;
				break;
			}
			case '\f': {
				ret += "<formfeed>";
				++i;
				break;
			}
			case '\n': {
				ret += "<newline>";
				++i;
				break;
			}
			case '\r': {
				ret += "<return>";
				++i;
				break;
			}
			case '\t': {
				ret += "<tab>";
				++i;
				break;
			}
			case '\v': {
				ret += "<vertical-tab>";
				++i;
				break;
			}
			case '\\': {
				ret += "\\";
				++i;
				break;
			}
			case 32: {
				ret += "<space>";
				++i;
				break;
			}
			case 127: {
				ret += "<backspace>";
				++i;
				break;
			}
			default: {

				if (*i < 32 || *i > 126) {
					ret += "\\x" + itoa(*i, 16);
				}
				else
					ret += *i++;
				break;
			}
		}
	}
	return ret;
}
