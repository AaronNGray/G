//
//  g/LexicalAnalyserGenerator/DFA.cpp - Determinate Finite Automata
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include <set>
#include <map>
#include <deque>
#include <iomanip>
#include <cassert>

#include "g/LexicalAnalyserGenerator/DFA.h"
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"

namespace G {
namespace LexicalAnalyserGenerator {

signed int DFA::GenerateRG2DFA(LexicalContext* context) {
    signed int startState = newState();
    this->accept[startState] = -1;
    bitset firstpos = context->firstpos();

    std::set<std::pair<int, bitset>> States;
    std::deque<std::pair<int, bitset>> UnfinishedStates;
    std::map<bitset, int> positionsToState; // followpos -> state

    std::pair<int, bitset> u = std::make_pair(startState, firstpos);
	UnfinishedStates.push_back(u);
    States.insert(u);
	positionsToState[firstpos] = startState;

    while (!UnfinishedStates.empty()) {
        signed int accept = -1;
        std::pair<int, bitset> p = UnfinishedStates.front();
		UnfinishedStates.pop_front();
        signed int state = p.first;
        bitset positions = p.second;
        PositionsForState[state - 1] = positions;
        signed int nextState;        // destination state
/*
		if (state == 190) {
			std::cerr << "state: 190" << nonstd::endl;
		}
*/
		for (unsigned int input = 0; input < getNumberOfInputs(); ++input) {
/*
			if (state == 190) {
				std::cerr << "input = " << input << nonstd::endl;
			}
*/
			// generate new followpos for given position P and input a
			bitset followpos(context->getNumberOfPositions());

			for (bitset::iterator position = positions.begin(), end = positions.end(); position != end; ++position) {
				if (position.isElement()) {
/*
					if (state == 190) {
						std::cerr << "context->move(" << position << ", " << input << ") = " << toStringBool(context->move(position, input)) << nonstd::endl;
					}
*/
					if (context->move(position, input))
						followpos |= context->followpos(position);

					signed int action = context->getAction(position);
					if (action != -1 && (accept == -1 || (accept != -1 && action < accept)))
						accept = action;
				}
			}

			if (!followpos.isEmpty()) {
                // Create new state or get existing state with followpos closure u
                if (positionsToState.find(followpos) == positionsToState.end()) {
					nextState = positionsToState[followpos] = newState();
                    std::pair<int, bitset> w = std::make_pair(nextState, followpos);

					States.insert(w);
					UnfinishedStates.push_back(w);
                }
                else
					nextState = positionsToState[followpos];
            }
            else
				nextState = 0;

            (*table)[state - 1][input] = (isTerminalState(context, followpos) ? -1 : 1) * nextState;
        } // end for inputs
          //    }
        this->accept[state] = accept;
    } // end while (!W.empty())

    return startState;
}

bool DFA::isTerminalState(LexicalContext* context, bitset& followpos) const {
	// check to see if its a terminal state.
	bool terminalState = true;
	for (bitset::iterator position = followpos.begin(), end = followpos.end(); position != end; ++position)
		if (position.isElement())
			terminalState &= context->followpos(position).isEmpty();

	return terminalState;
}

void DFA::OutputDFA(std::ostream &os) {
	for (size_t c = 0; c < getNumberOfInputs(); ++c)
		os << std::setw(6) << c;

	os << std::endl;

	for (int state = 0; state < getNumberOfStates(); ++state) {
		os << std::setw(5) << std::left << state + 1;
		for (size_t ec = 0; ec < getNumberOfInputs(); ++ec) {
			os << std::setw(6) << (signed int)(*table)[state][ec];
		}
		os << "\t" << PositionsForState[state].toString() << std::endl;
	}
}

void DFA::diag(LexicalContext* context) {
    std::cout << "firstpos = " << context->getGrammar()->firstpos().toString() << std::endl;
    std::cout << std::endl;

    std::cout << "Number of Positions = " << context->getGrammar()->getNumberOfPositions() << std::endl;
    std::cout << "Number of Equivanence Classes = " << context->getMachine()->getNumberOfEquivalenceClasses() << std::endl;
    std::cout << std::endl;

    std::cout << "followpos = " << std::endl;
    for (unsigned int p = 0; p < context->getGrammar()->getNumberOfPositions(); ++p) {
        std::cout << p << ": " << context->followpos(p).toString() << "/" << context->followpos(p).size() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "equivalence sets = " << std::endl;
    for (unsigned int p = 0; p < context->getGrammar()->getNumberOfPositions(); ++p) {
        std::cout << p << ": " << context->getEquivalenceSet(p).toString() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "lowers = " << std::endl;
    std::cout << context->getMachine()->getEquivalenceClasses().getLowers().toString() << std::endl;
}

bool compare(const DFA* lhs, const DFA* rhs) {
	bool dfa = compare((Generator::DFA*) lhs, (Generator::DFA*) rhs);
	bool PositionsForState = (lhs->PositionsForState == rhs->PositionsForState);

	bool result = dfa && PositionsForState;

	if (!result) {
		std::cout << "\t\t" "dfa: " << nonstd::endl;
		bool dfa = compare((Generator::DFA*) lhs, (Generator::DFA*) rhs);
		std::cout << "\t\t" "dfa: " << nonstd::generateBoolean(dfa) << nonstd::endl;

		std::cout << "\t\t" "PositionsForState: ";
		bool PositionsForState = (lhs->PositionsForState == rhs->PositionsForState);
		std::cout << nonstd::generateBoolean(dfa) << nonstd::endl;

		std::cout << "\t\t" << nonstd::generateBoolean(result) << nonstd::endl;
	}

	return result;
}

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/DFA.cpp - Determinate Finite Automata
