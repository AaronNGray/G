#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace nonstd {

class CommandLineParser {
public:
	CommandLineParser(unsigned argc, const char* argv[]) : shortSwitchString("-"), longSwitchString("--") {
		parseArguments(argc, argv);
	}
	CommandLineParser(unsigned argc, char* argv[]) : shortSwitchString("-"), longSwitchString("--") {
		parseArguments(argc, const_cast<const char**>(argv));
	}
	void parseArguments(unsigned argc, const char* argv[]) {
		programName = argv[0];
		for (unsigned i = 1; i < argc; ++i) {
			auto value = std::string(argv[i]);
			//std::cout << "value.substr(0, 2) = " << value.substr(0, 2) << std::endl;
			if (value.substr(0, 2) == longSwitchString) {
				size_t pos = value.find('=', 3);
				if (pos == std::string::npos) {
					long_options.push_back(value.substr(2));
					//std::cout << "long_options = " << value.substr(2) << std::endl;
				}
				else {
					long_options.push_back(value.substr(2, pos - 2));
					long_value[value.substr(2, pos - 2)] = value.substr(pos + 1);
					//std::cout << "long_value[" << value.substr(2, pos - 2) << "] = " << value.substr(pos + 1) << std::endl;
				}
			}
			else if (value.substr(0, 1) == shortSwitchString) {
				if (value.size() == 2) {
					short_options.push_back(value);
				}
				else
					short_value[value[1]] = value.substr(3);
			}
			else
				params.push_back(value);
		}
	}
	size_t getParameters() const {
		return params.size();
	}
	std::string getParameter(unsigned param) const {
		if (param < params.size())
			return params[param];
		else
			return "";
	}
	std::string getProgramName() const {
		return programName;
	}
	size_t getNumberOfShortOptions() const {
		return short_options.size();
	}
	size_t getNumberOfLongOptions() const {
		return long_options.size();
	}
	const std::string getShortOption(char option) {
		return short_value[option];
	}
	const std::string getLongOption(std::string option) {
		return long_value[option];
	}
	bool shortOptionExists(const std::string& option) const {
		return std::find(short_options.begin(), short_options.end(), option) != short_options.end();
	}
	bool longOptionExists(const std::string& option) const {
		return std::find(long_options.begin(), long_options.end(), option) != long_options.end();
	}

	using const_iterator = std::vector<std::string>::const_iterator;
	const_iterator params_cbegin() const {
		return params.cbegin();
	}
	const_iterator params_cend() const {
		return params.cend();
	}
	const_iterator short_options_cbegin() const {
		return short_options.cbegin();
	}
	const_iterator short_options_cend() const {
		return short_options.cend();
	}
	const_iterator long_options_cbegin() const {
		return long_options.cbegin();
	}
	const_iterator long_options_cend() const {
		return long_options.cend();
	}

private:
	std::string programName;
	std::string shortSwitchString;
	std::string longSwitchString;

	std::vector<std::string> params;
	std::vector<std::string> short_options;
	std::vector<std::string> long_options;

	std::map<char, std::string> short_value;
	std::map<std::string, std::string> long_value;
};

} // End namespace nonstd

// End CommandLineParser.h
