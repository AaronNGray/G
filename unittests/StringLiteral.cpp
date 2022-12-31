//
//	StringLiteral.cpp
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#include "gtest/gtest.h"
#include "g/CharacterLiteral.h"
#include "g/StringLiteral.h"
#include <assert.h>
/*
TEST(CharacterLiteralTest, toString_1) {
	ASSERT_TRUE(CharacterLiteral::toString('\\') == std::string("'\\'"));
}

TEST(CharacterLiteralTest, toSource_1) {
	ASSERT_TRUE(CharacterLiteral::toSource('\\') == std::string("'\\\\'"));
}
*/
/*
TEST(StringLiteralTest, toString_1) {
	std::cout << StringLiteral("\\\\").toString() << std::endl;

	ASSERT_TRUE(StringLiteral("\\\\").toString() == std::string("\"\\\\\""));
}
*/
TEST(StringLiteralTest, toSource_1) {
	std::cout << StringLiteral("\t")._toSource() << std::endl;
	ASSERT_TRUE(StringLiteral("\t")._toSource() == std::string("\\t"));		// TODO: FIX !!
	std::cout << StringLiteral("\\t")._toSource() << std::endl;
	ASSERT_TRUE(StringLiteral("\\t")._toSource() == std::string("\\\\t"));

	std::cout << StringLiteral("\"")._toSource() << std::endl;
	ASSERT_TRUE(StringLiteral("\"")._toSource() == std::string("\\\""));
}
