#include "nonstd/CommandLineParser.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <vector>

using namespace nonstd;

TEST(CommandLineParser, Test) {
	
	const char *argv[5] = {
		"C:\\Program.exe",
		"--debug",
		"--tester=test.txt",
		"test.txt",
		"test2.txt"
	};
	int argc = 5;

	CommandLineParser commandLine(argc, argv);

	EXPECT_TRUE(commandLine.getParameters() == 2);
	EXPECT_TRUE(commandLine.getParameter(0) == "test.txt");
	EXPECT_TRUE(commandLine.longOptionExists("debug"));
	EXPECT_FALSE(commandLine.longOptionExists("output"));
	EXPECT_TRUE(commandLine.getLongOption("tester") == "test.txt");
}

TEST(CommandLineParser, Example) {

	const char* argv[3] = {
		"C:\\Users\\aaron\\Projects\\G\\latest\\G\\build\\../bin/Debug/pg-bootstrap-pg", "--noline", "C:\\Users\\aaron\\Projects\\G\\latest\\G\\src\\bootstrap\\self-bootstrap\\pg-bootstrap\\pg.pg"
	};
	int argc = 3;

	CommandLineParser commandLine(argc, argv);

	EXPECT_TRUE(commandLine.longOptionExists("noline"));
}


