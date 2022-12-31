//
//	nonstd::string.h
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#pragma once
#include <string>
#include <algorithm>
#include <iostream>

namespace nonstd {

class string : public std::string {
public:
	string() {}
	string(const std::string s) : std::string(s) {}
	string(const char* s) : std::string(s) {}

	nonstd::string escape() const;
	nonstd::string stringify() const;

	nonstd::string _stringify() const;
	nonstd::string printify() const;

}; // end class string

} // end namespace nonstd


