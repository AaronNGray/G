//
//  DFA.h - compile time Determinate Finite Automata class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once
#ifndef __LG__LIB__LEXICAL_ANALYSER_GENERATOR__DFA_H__
#define __LG__LIB__LEXICAL_ANALYSER_GENERATOR__DFA_H__

#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "g/LexicalAnalyserGenerator/LexicalContext.h"
#include "g/LexicalAnalyserGenerator/LexicalMachine.h"

#include "g/Generator/DFA.h"

namespace G {
namespace LexicalAnalyserGenerator {

class DFA : public Generator::DFA {
    DFA();
public:
    DFA(unsigned int inputs) : Generator::DFA(inputs) {
		accept[0] = -1; // State 0 - TODO: Check if needed
    }

	typedef signed int STATE;
	typedef bitset POSITIONS;

	class State {
	public:
		State(STATE index, POSITIONS positions) : index(index), positions(positions) {}

		friend bool operator < (State lhs, State rhs) { return lhs.index < rhs.index; }

		STATE index;
		POSITIONS positions;
	};

	class States {
	public:
		States() : numberOfStates(0) {};

		State newState(POSITIONS positions) {
			State state = State(numberOfStates++, positions);
			states.insert(state);
			return state;
		}

		std::set<State> states;
		STATE numberOfStates;
	};

    signed int GenerateRG2DFA(LexicalContext* lexicalContext);
	bool isTerminalState(LexicalContext* context, bitset& followpos) const;

    void OutputDFA(std::ostream &os);
    void diag(LexicalContext* lexicalContext);

	friend bool compare(const DFA* lhs, const DFA* rhs);

protected:
    std::map<unsigned int, bitset> PositionsForState; // state -> followpos
};

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

#endif // __LG__LIB__LEXICAL_ANALYSER_GENERATOR__DFA_H__

// End DFA.h
