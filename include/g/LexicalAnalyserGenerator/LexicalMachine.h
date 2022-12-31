//
//  LexicalMachine.h - Lexical Machine class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include <vector>

#include "nonstd/File.h"
#include "nonstd/Debug.h"

#include "g/LexicalAnalyserGenerator/EquivalenceClasses.h"
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "g/LexicalAnalyserGenerator/ColumnMap.h"
#include "g/Actions.h"

namespace G {
namespace LexicalAnalyserGenerator {

class DFA;
class LexicalContext;
class LexicalGenerator;

class LexicalMachine {
    friend class LexicalContext;
public:
	LexicalMachine(LexicalGenerator* lexicalGenerator, std::string name, std::string className = "", bool compress = true, bool debug = true);
	LexicalMachine(std::string name, bool debug, std::initializer_list<LexicalContext*> contexts, std::initializer_list<Action> actions, bool lineDirectives = true, bool compress = true);
	~LexicalMachine();

    bool diagnostics;
    bool compressed;
    bool debug;

    std::string getName() { return name; }
    std::string getclassName() { return className; }

    void setRootType(std::string _rootTypeName) {
        rootTypeName = _rootTypeName;
    }
	std::string getRootType() {
		return rootTypeName;
	}
    void setBaseClass(std::string _baseClass) {
        baseClass = _baseClass;
    }
	std::string getBaseClass() {
		return baseClass;
	}
	void setValueType(std::string _valueType) {
        valueType = _valueType;
    }
	std::string getValueType() {
		return valueType;
	}
	void setReturnType(std::string _returnType) {
        returnType = _returnType;
    }
	std::string getReturnType() {
		return returnType;
	}

	void setLexicalGenerator(LexicalGenerator* lexicalGenerator) { this->lexicalGenerator = lexicalGenerator;  }
    LexicalGenerator* getLexicalGenerator() { return lexicalGenerator; }

    std::vector<LexicalContext*>& getContexts() { return contexts; }

    void setName(std::string _name) { name = _name; }
    void setClassName(std::string _className) { className = _className; }

    unsigned int addContext(LexicalContext* lexicalContext);
    Action* addAction(const char* action, unsigned int line);
    void setStartContext(std::string name);
    LexicalContext* getContext(std::string name);

    //

    void GenerateFollowPos();
    void Generate();
    void GenerateColumnMap();

    void OutputColumnMap(std::ostream &os) {
        columnMap->OutputColumnMap(os);
    }

    void OutputCXX(std::ostream &os, std::string className);
    void OutputH(std::ostream &os, std::string className);

    void OutputContextEnumH(std::ostream &os);
    void OutputContexts(std::ostream &os);
    void OutputContextCXX(std::ostream &os, std::string className);

    void OutputAcceptCXX(std::ostream &os, std::string className);

    void OutputCodeCXX(std::ostream &os, std::string className);

    void GenerateSourceH(std::ostream &os) const;
    void GenerateSourceCXX(std::ostream &os) const;

	void Dump(std::ostream &os, unsigned indent = 0) const;

    //

	class Identifier {
	public:
		Identifier(std::string identifier) : identifier(identifier) {}
		operator std::string() { return identifier; }
		operator const char *() { return identifier.c_str(); }
		std::string identifier;
	};

	Identifier* newIdentifier(std::string _identifier) {
		Identifier* identifier = new Identifier(_identifier);
		identifiers.push_back(identifier);
		return identifier;
	}

    void AddEquivalenceSets();

    unsigned int addEquivalenceSet(CharacterClass& cc) {
        return equivalenceClasses.add(cc);
    }

    //

    EquivalenceClasses& getEquivalenceClasses() { return equivalenceClasses; }
    EquivalenceSets& getEquivalenceSets() { return equivalenceClasses.getEquivalenceSets(); }

	EquivalenceSet& getEquivalenceSet(unsigned int set) { return equivalenceClasses.getEquivalenceSet(set); }
	unsigned int getNumberOfEquivalenceSets() { return equivalenceClasses.getNumberOfEquivalenceSets(); }

    DFA *getDFA() { return dfa; }

    void GenerateEquivalenceClasses();

    unsigned int getNumberOfInputs() {
        return compressed ? equivalenceClasses.getNumberOfColumns() : equivalenceClasses.getNumberOfInputs();
    }
    unsigned int getNumberOfColumns() {
        return equivalenceClasses.getNumberOfColumns();
    }
    unsigned int getNumberOfEquivalenceClasses() {
        return equivalenceClasses.getNumberOfEquivalenceClasses();
    }

    unsigned int getInputFromColumn(unsigned int input) {
        return equivalenceClasses.getInputFromColumn(input);
    }
    unsigned int getClassIndexToSetIndex(unsigned int classIndex) {
        return equivalenceClasses.getClassIndexToSetIndex(classIndex);
    }

    //

    void diag();

	friend bool compare(const LexicalMachine* lhs, const LexicalMachine* rhs);

private:
    std::string name;
    std::string className;
    std::string baseClassName;

    std::string rootTypeName;
    std::string baseClass;
    std::string valueType;
    std::string returnType;

    LexicalGenerator* lexicalGenerator;

    vector<LexicalContext*> contexts;
    std::map<std::string, LexicalContext*> nameToContext;
    //LexicalContext* startContext;
    std::string startContextName;

	vector<Identifier*> identifiers;
    Actions actions;

    EquivalenceClasses equivalenceClasses;
    DFA* dfa;
    ColumnMap* columnMap;
};

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End LexicalMachine.h - Lexical Machine class
