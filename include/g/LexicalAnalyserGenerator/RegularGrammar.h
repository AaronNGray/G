//
// RegularGrammar.h - Regular Grammar and Lexical Regular Expression heirachy classes
//
//   From the Dragon Book Section 3.9 - From a Regular Expression to a DFA
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "nonstd/bitset.h"
#include "g/LexicalAnalyserGenerator/Ranges.h"
#include "g/LexicalAnalyserGenerator/EquivalenceClasses.h"
#include "g/Grammar/Grammar.h"

namespace G {
using namespace Grammar;

namespace LexicalAnalyserGenerator {

using namespace nonstd;

class RegularGrammar : public Grammar {
public:
    typedef char Symbol;
    class RE;

    RegularGrammar() : positionIndex(0), root(NULL) {}
    RegularGrammar(RE* root) : positionIndex(0), root(root) {}
    virtual ~RegularGrammar() { if (root) delete root; }

    class RE {
    public:
		virtual ~RE() {}
		virtual RE *clone() const = 0;

		virtual std::string getTypeName() const = 0;
        virtual std::string toString(const RegularGrammar *parent) const = 0;
        virtual std::string toRE(const RegularGrammar *parent) const = 0;
        virtual std::string prettyPrint(const RegularGrammar *parent, int indent) const = 0;
        virtual std::string toSource(const RegularGrammar *parent, int indent) const = 0;

        virtual bool nullable() const { return false; }
        virtual bool isEnd() const { return false; }

        virtual void index(RegularGrammar* regularGrammar) = 0;

        virtual bitset firstpos() const = 0;
        virtual void followpos(RegularGrammar *parent, bitset&&) = 0;

		virtual bool compare(const RegularGrammar::RE* rhs) const = 0;

        virtual signed int getAction() const { return -1; }
    };

    class Leaf : public RE {
    public:
        Leaf() : position(-1) {}
        virtual ~Leaf() {}

        virtual bitset firstpos() const;
        virtual void index(RegularGrammar* regularGrammar);
        int position;
        virtual LexicalAnalyserGenerator::CharacterClass& getCharacterClass() { return LexicalAnalyserGenerator::CharacterClass::Null; }
        virtual const LexicalAnalyserGenerator::CharacterClass& getCharacterClass() const { return LexicalAnalyserGenerator::CharacterClass::Null; }
    };

    class CharacterClass : public Leaf {
    public:
        CharacterClass(const LexicalAnalyserGenerator::CharacterClass& cc) : Leaf(), characterClass(cc) {}
        virtual ~CharacterClass() {}

		virtual std::string getTypeName() const { return "CharacterClass"; }
		virtual std::string toString(const RegularGrammar *parent) const;
        virtual std::string toRE(const RegularGrammar *parent) const;
        virtual std::string prettyPrint(const RegularGrammar *parent, int indent) const;
        virtual std::string toSource(const RegularGrammar *parent, int indent) const;

        virtual RE *clone() const;

        virtual void followpos(RegularGrammar *parent, bitset&&);

		virtual bool compare(const RE* rhs) const;

        virtual LexicalAnalyserGenerator::CharacterClass& getCharacterClass() { return characterClass; }
        virtual const LexicalAnalyserGenerator::CharacterClass& getCharacterClass() const { return characterClass; }

		//virtual bool compare(const RegularGrammar *parent, const RE* rhs) const;

        LexicalAnalyserGenerator::CharacterClass characterClass;
    };

    class Character : public CharacterClass {
    public:
		virtual std::string getTypeName() const { return "Character"; }
		Character(Symbol s) : CharacterClass(LexicalAnalyserGenerator::CharacterClass(Char(s))) {}
        virtual ~Character() {}
    };

    class End : public Leaf {
    public:
        End(unsigned int action) : Leaf(), action(action) {}
        virtual ~End() {}

		virtual std::string getTypeName() const { return "End"; }
		virtual std::string toString(const RegularGrammar *parent) const;
        virtual std::string toRE(const RegularGrammar *parent) const;
        virtual std::string prettyPrint(const RegularGrammar *parent, int indent) const;
        virtual std::string toSource(const RegularGrammar *parent, int indent) const;

        virtual RE *clone() const;

        virtual bool nullable() const { return false; }
        virtual void followpos(RegularGrammar *parent, bitset&&);
        virtual bool isEnd() const { return true; }
        virtual signed int getAction() const { return action; }

		virtual bool compare(const RE* rhs) const;

		unsigned int action;
    };

    class Sequence : public RE {
    public:
        Sequence(RE *_re1, RE *_re2) : re1(_re1), re2(_re2) {}
        virtual ~Sequence() {
            if (re1) delete re1;
            if (re2) delete re2;
        }

		virtual std::string getTypeName() const { return "Sequence"; }
		virtual std::string toString(const RegularGrammar *parent) const;
        virtual std::string toRE(const RegularGrammar *parent) const;
        virtual std::string prettyPrint(const RegularGrammar *parent, int indent) const;
        virtual std::string toSource(const RegularGrammar *parent, int indent) const;

        virtual RE *clone() const;

        virtual bool nullable() const { return re1->nullable() && re2->nullable(); }
        virtual void index(RegularGrammar* regularGrammar);
        virtual bitset firstpos() const;
        virtual void followpos(RegularGrammar *parent, bitset&&);

		virtual bool compare(const RE* rhs) const;

        RE *re1;
        RE *re2;
    };

    class Selection : public RE {
    public:
        Selection(RE *_re1, RE *_re2) : re1(_re1), re2(_re2) {}
        virtual ~Selection() {
            if (re1) delete re1;
            if (re2) delete re2;
        }

		virtual std::string getTypeName() const { return "Selection"; }
		virtual std::string toString(const RegularGrammar *parent) const;
        virtual std::string toRE(const RegularGrammar *parent) const;
        virtual std::string prettyPrint(const RegularGrammar *parent, int indent) const;
        virtual std::string toSource(const RegularGrammar *parent, int indent) const;

        virtual RE *clone() const;

        virtual bool nullable() const { return re1->nullable() || re2->nullable(); }
        virtual void index(RegularGrammar* regularGrammar);
        virtual bitset firstpos() const;
        virtual void followpos(RegularGrammar *parent, bitset&&);

		virtual bool compare( const RE* rhs) const;

		RE *re1;
        RE *re2;
    };

    class Kleene : public RE {
    public:
        Kleene(RE *_re) : re(_re) {}
        virtual ~Kleene() { if (re) delete re; }

		virtual std::string getTypeName() const { return "Kleen"; }
		virtual std::string toString(const RegularGrammar *parent) const;
        virtual std::string toRE(const RegularGrammar *parent) const;
        virtual std::string prettyPrint(const RegularGrammar *parent, int indent) const;
        virtual std::string toSource(const RegularGrammar *parent, int indent) const;

        virtual RE *clone() const;

        virtual bool nullable() const { return true; }
        virtual void index(RegularGrammar* regularGrammar);
        virtual bitset firstpos() const;
        virtual void followpos(RegularGrammar *parent, bitset&&);

		virtual bool compare(const RE* rhs) const;

		RE *re;
    };

    class Optional : public RE {
    public:
        Optional(RE *_re) : re(_re) {}
        virtual ~Optional() { if (re) delete re; }

		virtual std::string getTypeName() const { return "Optional"; }
		virtual std::string toString(const RegularGrammar *parent) const;
        virtual std::string toRE(const RegularGrammar *parent) const;
        virtual std::string prettyPrint(const RegularGrammar *parent, int indent) const;
        virtual std::string toSource(const RegularGrammar *parent, int indent) const;

        virtual RE *clone() const;

        virtual bool nullable() const { return true; }
        virtual void index(RegularGrammar* regularGrammar);
        virtual bitset firstpos() const;
        virtual void followpos(RegularGrammar *parent, bitset&&);

		virtual bool compare(const RE* rhs) const;

		RE *re;
    };

    //

    RE* getRoot() {
        return root;
    }
    void setRoot(RE* re) {
        root = re;
    }

    //

    unsigned int getNumberOfPositions() const {
        return positionIndex;
    }

    bitset& getPosition(unsigned int position) {
        return pos[position];
    }

    //

    static bool nullable(RE* re) {
        return re->nullable();
    }
    static bitset firstpos(RE* re) {
        return re->firstpos();
    }
    void followpos(RE* re, bitset&& rel) {
        re->followpos(this, std::move(rel));
    }

    //

    bool nullable() {
        if (root)
            return root->nullable();
        else
            return true;
    }

    void Index() {
        root->index(this);
    }

    bitset firstpos() {
        if (root)
            return root->firstpos();
        else
            return bitset::EmptySet();
    }
    void followpos() {
        if (root)
            root->followpos(this, bitset::EmptySet());
    }

    bitset &followpos(unsigned int position) {
        return pos[position];
    }

    //

    Leaf* getLeafFromPos(unsigned int position) {
        return static_cast<Leaf*>(leafFromPos[position]);   // CHECK: cast
    }

    const Leaf* getLeafFromPos(unsigned int position) const {
        if (position >= getNumberOfPositions())
            throw;
        return static_cast<const Leaf *>(leafFromPos.find(position)->second);
    }

    //

    LexicalAnalyserGenerator::CharacterClass& getCharacterClassFromPos(unsigned int position) {
        return getLeafFromPos(position)->getCharacterClass();
    }

    const LexicalAnalyserGenerator::CharacterClass& getCharacterClassFromPos(unsigned int position) const {
        return getLeafFromPos(position)->getCharacterClass();
    }

    bool isEnd(unsigned int position) const {
        return getLeafFromPos(position)->isEnd();
    }

    signed int getAction(unsigned int position) const {
        return getLeafFromPos(position)->getAction();
    }

    //

    void diag();

    //

    std::string toString()  const {
        return root->toString(this);
    }
    std::string toRE()  const {
        return root->toRE(this);
    }
    std::string prettyPrint(int indent = 0)  const {
        return root->prettyPrint(this, indent);
    }
    std::string toSource(int indent = 0) const;

    //

    std::string toString(RE* re) const {
        return re->toString(this);
    }
    std::string toRE(RE* re) const {
        return re->toRE(this);
    }
    std::string prettyPrint(RE* re, int indent = 0) const {
        return re->prettyPrint(this, indent);
    }

    // Factory Methods
    // TODO: make non static
    static RE* newCharacter(Symbol symbol) {
        return new Character(symbol);
    }
    static RE* newCharacterClass(const LexicalAnalyserGenerator::CharacterClass& cc) {
        return new CharacterClass(cc);
    }
    static RE* newEnd(unsigned int action) {
        return new End(action);
    }
    static RE* newSequence(RE *re1, RE *re2) {
        return new Sequence(re1, re2);
    }
    static RE* newSelection(RE *re1, RE *re2) {
        return new Selection(re1, re2);
    }
    static RE* newKleene(RE *re) {
        return new Kleene(re);
    }
    static RE* newOptional(RE *re) {
        return new Optional(re);
    }

	friend bool compare(const RegularGrammar* lhs, const RegularGrammar* rhs);

private:
    RE *root;
    unsigned int positionIndex;
    std::vector<bitset> pos;					// Indexed by position
    std::map<unsigned int, RE*> leafFromPos;
};

}; // end namespace LexicalAnalyserGenerator
}; // end namespace G

// End RegularGrammar.h - Regular Grammar and Lexical Regular Expression heirachy classes
