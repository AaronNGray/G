// Stringify.cpp : Defines the entry point for the console application.
//

#include "nonstd/string.h"
#include "gtest/gtest.h"
#include <stdlib.h>

using namespace nonstd;

void print_test(nonstd::string s) {
	std::cout << s.printify() << " -> " << s.stringify() << std::endl;
}


// <tab> -> \t

TEST(StringifyTest, tab) {
	print_test("\t");
	EXPECT_TRUE(nonstd::string("\t")._stringify() == nonstd::string("\\t"));
}

// \t -> \\t

TEST(StringifyTest, escaped_tab) {
	print_test("\\t");
	EXPECT_TRUE(nonstd::string("\\t")._stringify() == nonstd::string("\\\\t"));
}

// <newline> -> \n

TEST(StringifyTest, newline) {
	print_test("\n");
	EXPECT_TRUE(nonstd::string("\n")._stringify() == nonstd::string("\\n"));
}

// \n -> \\n

TEST(StringifyTest, escaped_newline) {
	print_test("\\n");
	EXPECT_TRUE(nonstd::string("\\n")._stringify() == nonstd::string("\\\\n"));
}

// \ -> \\

TEST(StringifyTest, backslash) {
	print_test("\\");
	EXPECT_TRUE(nonstd::string("\\")._stringify() == nonstd::string("\\\\"));
}

// \\ -> \\\\

TEST(StringifyTest, double_backslash) {
	print_test("\\\\");
	EXPECT_TRUE(nonstd::string("\\\\")._stringify() == nonstd::string("\\\\\\\\"));
}

// " -> \"

TEST(StringifyTest, single_double_quote) {
	print_test("\"");
	EXPECT_TRUE(nonstd::string("\"")._stringify() == nonstd::string("\\\""));
}

// "" -> \"\"

TEST(StringifyTest, double_double_quote) {
	print_test("\"\"");
	EXPECT_TRUE(nonstd::string("\"\"")._stringify() == nonstd::string("\\\"\\\""));
}

// \" -> \\\"

TEST(StringifyTest, escaped_double_quote) {
	print_test("\\\"");
	EXPECT_TRUE(nonstd::string("\\\"")._stringify() == nonstd::string("\\\\\\\""));
}

// \"\" -> \\\"\\\"

TEST(StringifyTest, double_escaped_double_quote) {
	print_test("\\\"\\\"");
	EXPECT_TRUE(nonstd::string("\\\"\\\"")._stringify() == nonstd::string("\\\\\\\"\\\\\\\""));
}

