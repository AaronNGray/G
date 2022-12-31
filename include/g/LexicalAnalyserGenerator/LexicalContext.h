//
//  LexicalContext.h - Lexical Context class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <string>

#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "g/LexicalAnalyserGenerator/LexicalMachine.h"
#include "g/LexicalAnalyserGenerator/DFA.h"

namespace G {
namespace LexicalAnalyserGenerator {

class LexicalContext {
public:
	LexicalContext(const LexicalContext& context) : machine(context.machine), regularGrammar(context.regularGrammar), compressed(context.compressed), name(context.name), className(context.className)
	{}

    LexicalContext(LexicalMachine* machine, RegularGrammar* regularGrammar, bool compress = true, std::string name = "", std::string className = "")
        : machine(machine), regularGrammar(regularGrammar), name(name), className(name), compressed(compress)
    {}
	LexicalContext(LexicalMachine* machine, RegularGrammar* regularGrammar, std::string name, bool compress = true)
		: machine(machine), regularGrammar(regularGrammar), name(name), className(name), compressed(compress)
	{}
	LexicalContext(const std::string name, RegularGrammar* regularGrammar, bool compress = true)
		: machine(nullptr), name(name), regularGrammar(regularGrammar), className(name), compressed(compress)
	{}
	LexicalContext(const char* name, RegularGrammar* regularGrammar, bool compress = true)
		: machine(nullptr), name(name), regularGrammar(regularGrammar), className(name), compressed(compress)
	{}
	~LexicalContext() {
        if (regularGrammar) delete regularGrammar;
    }

    std::string getName() { return name; }
    std::string getclassName() { return className; }
    LexicalMachine* getMachine() { return machine; }
    RegularGrammar* getGrammar() { return regularGrammar; }

    void setName(std::string _name) { name = _name; }
    void setClassName(std::string _className) { className = _className; }
    void setMachine(LexicalMachine* _machine) { machine = _machine; }
    void setGrammar(RegularGrammar* grammar) { regularGrammar = grammar; }

    void Index();
    void GenerateFollowPos();
    void Generate(DFA* dfa);

    void GenerateSourceH(std::ostream &os) const;
    void GenerateSourceCXX(std::ostream &os) const;

	void Dump(std::ostream &output, unsigned indent = 0) const;

    unsigned int getStartState() { return startState; }

    int getNumberOfPositions() const {
        return regularGrammar->getNumberOfPositions();
    }
	unsigned int getPositionToSet(unsigned int position) {
		return positionToSet[position];
	}

    void addEquivalenceSets();
    void addEquivalenceSet(CharacterClass& cc, unsigned int position);

    bitset& getEquivalenceSet(unsigned int set) {
    	return machine->getEquivalenceSet(set);
    }
	unsigned int getNumberOfEquivalenceSets() {
	    return machine->getNumberOfEquivalenceSets();
	}

    bool move(unsigned int position, unsigned int input) {
        if (compressed)
            return getEquivalenceSet(positionToSet[position])[machine->getInputFromColumn(input)].isElement();
        else
            return getEquivalenceSet(positionToSet[position])[input].isElement();
    }

    bitset firstpos() const {
        return regularGrammar->firstpos();
    }
    bitset followpos(unsigned int p) const {
        return regularGrammar->followpos(p);
    }

    signed int getAction(unsigned int position) {
        return regularGrammar->isEnd(position) ? regularGrammar->getAction(position) : -1;
    }

    void diag() {
        std::cout << "context:" << name << std::endl;
        regularGrammar->diag();
    }

	friend bool compare(const LexicalContext* lhs, const LexicalContext* rhs);

private:
    std::string name;
    std::string className;

    RegularGrammar* regularGrammar;

    std::map<unsigned int, unsigned int> positionToSet;

    LexicalMachine* machine;
    unsigned int startState;
    bool compressed;
};

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End LexicalContext.h - Lexical Context class
