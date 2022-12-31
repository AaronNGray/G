//
//	g/ParserGenerator/LL1/LL1.h - LL1 State And table Generation header.
//
//  Property and Copyright (c) 2017 Aaron Nathaniel Gray
//

#pragma once

#include "g/Grammar/ContextFreeGrammar.h"
#include "g/ParserGenerator/Machine.h"
#include "g/Generator/DFA.h"
#include "nonstd/vector.h"
#include <map>

namespace G {
namespace ParserGenerator {

using namespace G::Grammar;

struct LL1 : public Machine {
    LL1(ContextFreeGrammar* grammar, bool rowCompressed = true, unsigned debug = 0) : Machine(rowCompressed, debug), grammar(grammar), dfa(nullptr) {}

	ContextFreeGrammar* grammar;

	typedef ContextFreeGrammar::Terminal Terminal;
	typedef ContextFreeGrammar::Terminals Terminals;
	typedef ContextFreeGrammar::NonTerminal NonTerminal;
	typedef ContextFreeGrammar::NonTerminals NonTerminals;
	typedef ContextFreeGrammar::Production Production;
	typedef ContextFreeGrammar::Productions Productions;


	Terminals& getTerminals() {
		return grammar->getTerminals();
	}
	unsigned getNumberOfTerminals() {
		return grammar->getNumberOfTerminals();
	}
	NonTerminals& getNonTerminals() {
		return grammar->getNonTerminals();
	}
	Productions& getProductions() {
		return grammar->getProductions();
	}

    struct State {
		State(NonTerminal* nonTerminal) : nonTerminal(nonTerminal) {}

		std::string toString(ContextFreeGrammar* grammar, int i) const;

		NonTerminal* nonTerminal;
        std::multimap<Terminal*, Production*> transitions;
	};

    unsigned getNumberOfStates() {
        return states.size();
    }

    void GenerateStatesAndTransitions();

    struct Conflict {
        Conflict(State* state, Terminal* terminal, Production* production) : state(state), terminal(terminal), production(production) {}
        State* state;
        Terminal* terminal;
        Production* production;
	};

    vector<Conflict*> conflicts;

    bool CheckForConflicts();

    unsigned getNumberOfConflicts() {
        return conflicts.size();
    }

	void GenerateDFA();
	void GeneratePushTable();

	struct Symbol {
	    enum Type {
			None,
	        Terminal,
	        NonTerminal,
	        Action
	    } type : 2;
	    unsigned index : 30;
		Symbol() : type(Type::None), index(0) {}
	    Symbol(ContextFreeGrammar::Terminal* terminal) : type(Type::Terminal), index(terminal->getIndex()) {}
	    Symbol(ContextFreeGrammar::NonTerminal* nonTerminal) : type(Type::NonTerminal), index(nonTerminal->getIndex()) {}
		Symbol(Type type, unsigned index) : type(type), index(index) {}
	};

	virtual void Generate();

	virtual void AnalyseStates(std::ostream &os);

	virtual void Output(std::ostream& os) const;

	virtual void OutputIncludesHXX(std::ostream &os, std::string className) const;

	virtual void OutputCodeHXX(std::ostream &os, std::string className) const;
	virtual void OutputCodeCXX(std::ostream &os, std::string className) const;

	virtual void OutputTablesHXX(std::ostream &os, std::string className) const;
	virtual void OutputTablesCXX(std::ostream &os, std::string className) const;

	virtual void OutputTerminals(std::ostream& os) const;
	virtual void OutputNonTerminals(std::ostream& os) const;

	virtual void OutputStates(std::ostream& os) const;


	vector<State*> states;

	Generator::DFA* dfa;
	vector<vector<Symbol>> pushTable;

	virtual bool compare(const Machine* rhs) const;

	static Machine* Create(ContextFreeGrammar* grammar, bool rowCompressed, unsigned debug) { return new LL1(grammar, rowCompressed, debug); }
	static std::string Name;
};

} // end namespace ParserGenerator
} // end namespce G

// End	g/ParserGenerator/LL1/LL1.h - LL1 State And table Generation header.

// TODO: Needs completing
