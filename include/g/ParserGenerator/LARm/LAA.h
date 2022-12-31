//
//  g/ParserGenerator/LARm/LAA.h - LAR(m) LookAhead Automaton
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#pragma once

#include "g/ParserGenerator/LR/LR.h"
#include "nonstd/set.h"
#include "nonstd/deque.h"
#include "nonstd/bitset.h"
#include "g/Table.h"
#include <iostream>
#include <deque>
#include <map>

namespace G {
namespace ParserGenerator {

//  LAA - LAR(m) LookAhead Automaton

struct LAA {

	LAA() : states(0) {}

	typedef size_t STATE;
	typedef size_t SYMBOL;

	struct ACTION {
		enum Function : unsigned {
			Shift,
			Reduce,
			Lookahead,
			Error
		};

		ACTION() : action(Error), state(0) {}
		ACTION(Function action, size_t value) : action(action), state(value) {}
		ACTION(Function action) : action(action), state(0) {}

		Function action : 2;
		unsigned int state : 30;

		operator enum Function() const { return action; }
		unsigned getValue() const { return state; }

		std::string toString() const {
			std::stringstream ss;
			switch (action) {
			case Shift:
				ss << "s" << std::to_string(state);
				break;
			case Reduce:
				ss << "r" << std::to_string(state);
				break;
			case Lookahead:
				ss << "l" << std::to_string(state);
				break;
			default:
				ss << "e" << std::to_string(state);
				break;
			}
			return ss.str();
		}
		std::string toCXXString() const {
			std::stringstream ss;
			switch (action) {
			case Shift:
				ss << "{Action::Function::Shift, " << std::to_string(state) << "}";
				break;
			case Reduce:
				ss << "{Action::Function::Reduce, " << std::to_string(state) << "}";
				break;
			case Lookahead:
				ss << "{Action::Function::Lookahead, " << std::to_string(state) << "}";
				break;
			case Error:
				ss << "{Action::Function::Error}";
				break;
			}
			return ss.str();
		}
		friend bool operator == (const ACTION& lhs, const ACTION& rhs) {
			return lhs.action == rhs.action && lhs.state == rhs.state;
		}
		friend bool operator != (const ACTION& lhs, const ACTION& rhs) {
			return !(lhs == rhs);
		}
	};

	STATE states;

	std::map<std::pair<STATE, SYMBOL>, ACTION> dfa;

	size_t size() { return states; }

	STATE newState() { return states++; }

	STATE newTransition(STATE first, SYMBOL symbol, ACTION::Function action) {
		STATE state = newState();
		dfa[std::make_pair(first, symbol)] = ACTION(action, state);
		return state;
	}
	ACTION lookup(STATE state, SYMBOL symbol) {
		auto action = dfa.find(std::make_pair(state, symbol));
		if (action != dfa.end())
			return action->second;
		else
			return ACTION(ACTION::Function::Error);
	}
};

} // end namespace ParserGenerator
} // end namespce G

// End g/ParserGenerator/LARm/LAA.h - LAR(m) LookAhead Automaton
