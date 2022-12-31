//
//	g/Grammar/ContextFreeGrammar.h - Context Free Grammar
//
//  Property and Copyright (c) 2016, 2017 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include <map>
#include <cassert>
#include <initializer_list>
#include <iostream>

#include "nonstd/bitset.h"
#include "nonstd/vector.h"
#include "g/Actions.h"
#include "g/Logger.h"

#include "g/AST.h"

namespace G {
extern Logger* logger;
namespace Grammar {

using namespace nonstd;

class ContextFreeGrammar : public AST {
public:
	ContextFreeGrammar() : name(), actions(new Actions()), nextTerminalSymbol(2), nextNonTerminalSymbol(1), numberOfProductions(0), startSymbol(nullptr) { // TODO: Check nextNonTerminalSymbol(1)
		addTerminal(&EPSILON);
		addTerminal(&END);
	}

	ContextFreeGrammar(std::string name, Actions* actions = nullptr) : name(name), actions(actions ? actions : new Actions()), nextTerminalSymbol(2), nextNonTerminalSymbol(1), numberOfProductions(0), startSymbol(nullptr) { // TODO: Check nextNonTerminalSymbol(1)
		addTerminal(&EPSILON);
		addTerminal(&END);
	}
	virtual ~ContextFreeGrammar() {}	// TODO: Deallocation

	std::string name;

	enum TypeValue {
		Type__None,
		Type__Literal,
		Type__Identifier,
		Type__StringLiteral,
		Type__Symbol,
		Type__Terminal,
		Type__NonTerminal,
		Type__PseudoTerminal,
		Type__Epsilon,
		Type__End,
		Type__NamedSymbol,
		Type__NamedSymbols,
		Type__Production,
		Type__Productions,
		Type__Rule
	};
	struct Type {
		virtual std::string __getType() = 0;
		virtual std::string __getValue() = 0;
		virtual void check(std::string type) {
			if (__getType() != type)
				std::cout << "Found " << __getType() << " = " << __getValue() << " expecting " << type << std::endl;
		}
	};

	struct Literal : public Type {
		Literal() {}
		virtual std::string getName() const = 0;
		virtual std::string getValue() const = 0;
		virtual std::string toString() const = 0;
		virtual std::string prettyPrint(int indent) const = 0;
		virtual std::string HTMLPrint() const = 0;
	};

	struct Identifier : public Literal {
		Identifier() {}
		Identifier(std::string value) : value(value) {}
		virtual std::string getName() const { return "Identifier"; }
		virtual std::string getValue() const { return value; }
		operator std::string() { return value; }

		virtual std::string __getType() { return "Identifier"; }
		virtual std::string __getValue() { return value; }

		virtual std::string toString() const { return value; }
		virtual std::string prettyPrint(int indent) const;
		virtual std::string HTMLPrint() const;

		virtual bool compare(const Identifier* rhs) const;

		friend bool operator < (const Identifier& lhs, const Identifier& rhs) { return lhs.value < rhs.value; }


	protected:
		std::string value;
	};

	struct StringLiteral : public Literal {
		StringLiteral(std::string value) : value(value) {}
		virtual std::string getName() const { return "Literal"; }
		std::string getValue() const { return value; }

		virtual std::string __getType() { return "Literal"; }
		virtual std::string __getValue() { return value; }

		StringLiteral operator = (const std::string v) { value = v; return *this; }

		operator std::string() { return value; }
		virtual std::string toString() const { return value; }
		virtual std::string prettyPrint(int indent) const;
		virtual std::string HTMLPrint() const;

		virtual bool compare(const StringLiteral* rhs) const;

		friend bool operator < (const StringLiteral& lhs, const StringLiteral& rhs) { return lhs.value < rhs.value; }

	protected:
		std::string value;
	};

	enum Associativity { None, Left, Right };
	typedef unsigned Precedence;

	struct Terminal;
	struct NonTerminal;
	struct Symbol : public virtual Type {
		Symbol() : index(0) {}
		Symbol(size_t index) : index(index) {}
		Symbol(size_t index, Identifier* name) : index(index), name(name->getValue()) {}
		Symbol(size_t index, std::string name) : index(index), name(name) {}
		Symbol(size_t index, Identifier* name, Identifier* type) : index(index), name(name->getValue()), type(type->getValue()) {}
		Symbol(size_t index, std::string name, std::string type) : index(index), name(name), type(type) {}

		void setIndex(size_t _index) { index = _index; }

		virtual bool isTerminal() const = 0;
		virtual bool isNonTerminal() const = 0;
		virtual bool isPseudoTerminal() const { return false; }
		virtual bool isEpsilon() const { return false; }
		virtual bool isEnd() const { return false; }
		virtual bool isError() const { return false; }
		virtual bool nullable() const = 0;
		virtual bool isFinal() const { return false; };
		virtual bitset getFirstSet() const = 0;
		virtual bitset getBitset() { return bitset().set(index); }

		virtual Terminal *asTerminal() { return static_cast<Terminal*>(this); }
		virtual NonTerminal *asNonTerminal() { return static_cast<NonTerminal*>(this); }
		virtual Symbol *asSymbol() { return this; }

		virtual operator Terminal* () { return static_cast<Terminal*>(this); }
		virtual operator NonTerminal* () { return static_cast<NonTerminal*>(this); }

		virtual std::string __getType() = 0;
		virtual std::string __getValue() = 0;

		virtual const size_t getIndex() const { return index; }
		virtual std::string getName() const { return name; }
		virtual std::string getType() const { return type; }
		virtual bool hasType() const { return type != ""; }

		virtual bool compare(const Symbol* rhs) const = 0;

		bool operator == (const Symbol& symbol) { return this == &symbol; } // ???

		virtual std::string toString() const = 0;
		virtual std::string prettyPrint(int indent) const = 0;
		virtual std::string HTMLPrint() const = 0;

		virtual std::string GenerateGrammar() const = 0;
		virtual std::string GenerateSource(std::string name) const = 0;
	protected:
		size_t index;
		std::string name;
		std::string type;
	};

	struct NonTerminal : public Symbol {
		NonTerminal() = delete;
		NonTerminal(size_t index) : Symbol(index) {}

		NonTerminal(size_t index, std::string name) : Symbol(index, name) {}
		NonTerminal(size_t index, std::string name, std::string type) : Symbol(index, name, type) {}

		NonTerminal(size_t index, NonTerminal* nonTerminal) : Symbol(index, nonTerminal->name, nonTerminal->type) {}
		NonTerminal(size_t index, Identifier* name) : Symbol(index, name) {}
		NonTerminal(size_t index, Identifier* name, Identifier* type) : Symbol(index, name, type) {}

		NonTerminal(ContextFreeGrammar* grammar) : Symbol(grammar->allocateNonTerminalSymbol()) {}
		NonTerminal(ContextFreeGrammar* grammar, NonTerminal* nonTerminal) : Symbol(grammar->allocateNonTerminalSymbol(), nonTerminal->name, nonTerminal->type) {}
		NonTerminal(ContextFreeGrammar* grammar, Identifier* name) : Symbol(grammar->allocateNonTerminalSymbol(), name) {}
		NonTerminal(ContextFreeGrammar* grammar, Identifier* name, Identifier* type) : Symbol(grammar->allocateNonTerminalSymbol(), name, type) {}

		virtual bool isTerminal() const { return false; }
		virtual bool isNonTerminal() const { return true; }
		virtual bool nullable() const { return firstSet.get(EPSILON); }
		virtual bitset getFirstSet() const { return firstSet; }
		void setFirstSet(bitset firstset) { firstSet = firstset; }
		bitset& getFollowSet() { return followSet; }
		void setFollowSet(bitset followset) { followSet = followset; }

		virtual std::string __getType() { return "NonTerminal"; }
		virtual std::string __getValue() { return name; }

		virtual std::string toString() const { return name; }
		virtual std::string prettyPrint(int indent) const;
		virtual std::string HTMLPrint() const;

		virtual std::string GenerateGrammar() const;
		virtual std::string GenerateSource(std::string name) const;

		virtual bool compare(const Symbol* rhs) const;

		friend bool operator == (const NonTerminal&, const NonTerminal&);
	protected:
		bitset firstSet;
		bitset followSet;
	};

	struct Terminal : public Symbol {
		Terminal() = delete;

		Terminal(size_t index, Terminal* terminal) : Symbol(index, terminal->name, terminal->type), value(terminal->value), associativity(Associativity::None), precedence(0), final(terminal->final) {}
		Terminal(size_t index, bool final = false) : Symbol(index), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(size_t index, Identifier* name, bool final = false) : Symbol(index, name), value(""), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(size_t index, Identifier* name, Identifier* type, bool final = false) : Symbol(index, name, type), value(""), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(size_t index, Identifier* name, StringLiteral* value, bool final = false) : Symbol(index, name), value(value->getValue()), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(size_t index, Identifier* name, Identifier* type, StringLiteral* value, bool final = false) : Symbol(index, name, type), value(value->getValue()), associativity(Associativity::None), precedence(0), final(final) {}

		Terminal(size_t index, std::string name, bool final = false) : Symbol(index, name), value(""), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(size_t index, std::string name, std::string type, bool final = false) : Symbol(index, name, type), value(""), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(size_t index, std::string name, std::string type, std::string value, bool final = false) : Symbol(index, name, type), value(value), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(size_t index, std::string name, std::string type, std::string value, Associativity associativity, Precedence precedence, bool final = false) : Symbol(index, name, type), value(value), associativity(associativity), precedence(0), final(final) {}

		Terminal(ContextFreeGrammar* grammar) : Symbol(grammar->allocateTerminalSymbol()), associativity(Associativity::None), precedence(0), final(false) {}
		Terminal(ContextFreeGrammar* grammar, bool final = false) : Symbol(grammar->allocateTerminalSymbol()), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(ContextFreeGrammar* grammar, Identifier* name, bool final = false) : Symbol(grammar->allocateTerminalSymbol(), name), value(""), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(ContextFreeGrammar* grammar, Identifier* name, Identifier* type, bool final = false) : Symbol(grammar->allocateTerminalSymbol(), name, type), value(""), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(ContextFreeGrammar* grammar, Identifier* name, StringLiteral* value, bool final = false) : Symbol(grammar->allocateTerminalSymbol(), name), value(value->getValue()), associativity(Associativity::None), precedence(0), final(final) {}
		Terminal(ContextFreeGrammar* grammar, Identifier* name, Identifier* type, StringLiteral* value, bool final = false) : Symbol(grammar->allocateTerminalSymbol(), name, type), value(value->getValue()), associativity(Associativity::None), precedence(0), final(final) {}

		virtual bool isTerminal() const { return true; }
		virtual bool isNonTerminal() const { return false; }
		virtual bool nullable() const { return false; }
		virtual bool isFinal() const { return final; };
		virtual bool isEnd() const { return false; }	// TODO: normalize with isFinal()
		virtual bitset getFirstSet() const {
			bitset firstset;
			firstset.set(getIndex());
			return firstset;
		}
		explicit operator bitset () { return getFirstSet(); }

		Symbol* asSymbol() { return static_cast<Symbol*>(this); }

		virtual std::string __getType() { return "Terminal"; }
		virtual std::string __getValue() { return name; }

		virtual std::string getValue() const { return value; }
		virtual bool hasValue() const { return value != ""; }

		void setPrecedence(unsigned _prededence) { precedence = _prededence; }
		void setAssociativity(Associativity _associativity) { associativity = _associativity; }

		unsigned getPrecedence() const { return precedence; }
		Associativity getAssociativity() const { return associativity; }

		virtual std::string toString() const;
		virtual std::string prettyPrint(int indent) const;
		virtual std::string HTMLPrint() const;

		virtual std::string GenerateGrammar() const;
		virtual std::string GenerateSource(std::string name) const;

		virtual bool compare(const Symbol* rhs) const;

	protected:
		std::string value;
		unsigned precedence;
		Associativity associativity;
		bool final;
	};

	struct PseudoTerminal : public Terminal {
		PseudoTerminal(size_t index, bool final = false) : Terminal(index, final) {}
		PseudoTerminal(size_t index, Identifier* name, StringLiteral* value, bool final = false) : Terminal(index, name, value, final) {}
		virtual bool isPseudoTerminal() const { return true; }
	};

	struct Epsilon : public PseudoTerminal {
		Epsilon() : PseudoTerminal(0, new Identifier("EPSILON"), new StringLiteral("epsilon")) {}
		virtual bool isEpsilon() const { return true; }
		virtual bool nullable() const { return true; }

		virtual std::string prettyPrint(int indent) const;
		virtual std::string HTMLPrint() const;

		virtual bool compare(const Symbol* rhs) const;

		operator size_t() { return index; }
	};
	static Epsilon EPSILON;  // TODO: deal with constness
	static Terminal* getEpsilon() { return &EPSILON; }

	struct End : public Terminal {
		End() : Terminal(1, new Identifier("END"), new StringLiteral("$"), true) {}
		virtual bool isEnd() const { return true; }

		virtual std::string prettyPrint(int indent) const;
		virtual std::string HTMLPrint() const;

		virtual bool compare(const Symbol* rhs) const;

		operator size_t() { return index; }
	};

	static End END;  // TODO: deal with constness
	static Terminal* getEnd() { return &END; }

	struct Error : public PseudoTerminal {
		Error() : PseudoTerminal(65535, new Identifier("ERROR"), new StringLiteral("ERROR"), true) {}
		virtual bool isError() const { return true; }
		operator size_t() { return index; }
	};

	static Error ERROR;
	static Error* getErrorSymbol() { return &ERROR; }

	struct NamedSymbol : public virtual Type {
		NamedSymbol() = delete;
		NamedSymbol(Identifier* name, Symbol* symbol) : name(name), symbol(symbol) {}
		NamedSymbol(Symbol* symbol) : name(nullptr), symbol(symbol) {}
		~NamedSymbol() {}

		std::string getName() const { if (name) return name->getValue(); else return ""; }
		std::string getType() const { if (symbol) return symbol->getType(); else return ""; }
		Identifier* getIdentifier() const { return name; }
		Symbol* getSymbol() const { return symbol; }

		bool isTerminal() const { return symbol->isTerminal(); }
		bool isNonTerminal() const { return symbol->isNonTerminal(); }  // TODO: deal with constness ???
		bool isFinal() { return symbol->isFinal(); }
		bool nullable() const { return symbol->nullable(); }
		bool isEpsilon() const { return symbol->isEpsilon(); }

		virtual Terminal *asTerminal() { return symbol->asTerminal(); }
		virtual const Terminal *asTerminal() const { return symbol->asTerminal(); }
		virtual NonTerminal *asNonTerminal() { return symbol->asNonTerminal(); }
		virtual const NonTerminal *asNonTerminal() const { return symbol->asNonTerminal(); }

		bitset getFirstSet() const { return symbol->getFirstSet(); }
		size_t getIndex() const { return symbol->getIndex(); }

		virtual std::string __getType() { return "NamedSymbol"; }
		virtual std::string __getValue() { return name->toString() + ":" + symbol->toString(); }

		std::string toString() const { return symbol->toString(); }
		std::string prettyPrint(int indent) const;
		std::string HTMLPrint() const;

		std::string GenerateGrammar() const;
		std::string GenerateSource(std::string name) const;

		virtual bool compare(const NamedSymbol* rhs) const;

	protected:
		Identifier* name;
		Symbol* symbol;
	};

	class NamedSymbols : public virtual Type, public vector<NamedSymbol*> {
	public:
		NamedSymbols() {}
		NamedSymbols(const std::initializer_list<NamedSymbol*> namedSymbols) : vector<NamedSymbol*>(namedSymbols) {}
		NamedSymbols* clone();

		void addSymbol(NamedSymbol* symbol) { push_back(symbol); }
		Symbol* getSymbol(size_t position) const { return this->operator[](position)->getSymbol(); }
		size_t getLength() const { return size(); }
		bool isEpsilon() const {
			return size() == 0 || (*this)[0]->isEpsilon();
		}

		const NamedSymbols& getNamedSymbols() const { return *this; }

		virtual std::string __getType() { return "NamedSymbols"; }
		virtual std::string __getValue() { return "none"; }

		std::string toString() const;
		std::string prettyPrint(int indent) const;
		std::string HTMLPrint() const;

		std::string GenerateGrammar() const;
		std::string GenerateSource(std::string name) const;

		virtual bool compare(const NamedSymbols* rhs) const;
	};

	struct Rule;
	struct Production : public virtual Type {
		Production(size_t index, bool start = false) : rule(nullptr), index(index), rhs(new NamedSymbols()), associativity(Associativity::None), prededence(), action(-1), start(start) {}
		Production(size_t index, int action, bool start = false) : rule(nullptr), index(index), rhs(new NamedSymbols()), action(action), associativity(Associativity::None), prededence(), start(start) {}
		Production(size_t index, Rule* lhsRule, bool start = false) : index(index), rule(lhsRule), rhs(new NamedSymbols()), associativity(Associativity::None), prededence(), action(-1), start(start) {}
		Production(size_t index, Rule* lhsRule, NamedSymbols* rhs, bool start = false) : index(index), rule(lhsRule), rhs(rhs), associativity(Associativity::None), prededence(), action(-1), start(start) {}
		Production(size_t index, NamedSymbols* rhs, bool start = false) : rule(nullptr), index(index), rhs(rhs), associativity(Associativity::None), prededence(), action(-1), start(start) {}
		Production(size_t index, NamedSymbols* rhs, int action, bool start = false) : rule(nullptr), index(index), rhs(rhs), associativity(Associativity::None), prededence(), action(action), start(start) {}

		Production(Rule* rule, NamedSymbols* namedSymbols) : rule(rule), index(), rhs(namedSymbols), associativity(Associativity::None), prededence(), action(-1), start(false) {}	// TODO: check/modify
		Production(size_t index, NamedSymbols namedSymbols) : rule(nullptr), index(index), rhs(new NamedSymbols(namedSymbols)), associativity(Associativity::None), prededence(), action(-1), start(false) {}	// TODO: check/modify
		Production(size_t index, NamedSymbols namedSymbols, int action) : rule(nullptr), index(index), rhs(new NamedSymbols(namedSymbols)), associativity(Associativity::None), prededence(), action(action), start(false) {}	// TODO: check/modify

		~Production() { for (auto symbol : *rhs) delete symbol; }

		void addSymbol(Identifier* name, Symbol* symbol) { rhs->push_back(new NamedSymbol(name, symbol)); }
		void addSymbol(NamedSymbol* namedSymbol) { rhs->push_back(namedSymbol); }

		NonTerminal* getLHS() const { return rule->getLHS(); }
		NamedSymbols& getRHS() const { return *rhs; }

		Rule* getRule() { return rule; }
		void setRule(Rule* lhsRule) { rule = lhsRule; }

		Symbol* getSymbol(size_t position) const {
			if (position < rhs->size())
				return rhs->getSymbol(position);
			else
				return nullptr;
		}
		Symbol* operator [] (size_t position) const {
			return getSymbol(position);
		}

		size_t getIndex() { return index; }
		void setIndex(size_t _index) { index = _index; }

		void setStart(bool value = true) { start = value; }

		std::string getType() const { return (type != "") ? type : getLHS()->getType(); }
		void setType(std::string _type) { type = _type; }

		bool nullable() const { return rhs->size() == 0; }

		bool isNullable() const {
			for (const_iterator ri = cbegin(); ri != cend(); ++ri)
				if (!(*ri)->nullable())
					return false;
			return true;
		}
		bool isEpsilon() const {
			return rhs->isEpsilon();
		}
		bool isStart() const { return start; }

		unsigned getPrecedence() { return prededence; }
		void setPrecedence(unsigned _prededence) { prededence = _prededence; }
		Associativity getAssociativity() { return associativity; }
		void setAssociativity(Associativity _associativity) { associativity = _associativity; }

		int getAction() const { return action; }

		size_t size() const { return rhs->size(); }

		typedef vector<NamedSymbol*>::iterator iterator;
		typedef vector<NamedSymbol*>::const_iterator const_iterator;
		typedef vector<NamedSymbol*>::reverse_iterator reverse_iterator;
		typedef vector<NamedSymbol*>::const_reverse_iterator const_reverse_iterator;

		iterator begin() { return rhs->begin(); }
		iterator last() { return rhs->last(); }
		iterator end() { return rhs->end(); }
		reverse_iterator rbegin() { return rhs->rbegin(); }
		reverse_iterator rend() { return rhs->rend(); }
		const_iterator cbegin() const { return rhs->cbegin(); }
		const_iterator cend() const { return rhs->cend(); }
		const_reverse_iterator crbegin() const { return rhs->crbegin(); }
		const_reverse_iterator crend() const { return rhs->crend(); }

		bitset FIRST();
		void GenerateSelectSet(ContextFreeGrammar::Rule* rule);
		bitset getSelectSet() { return selectSet; }

		void GeneratePrecedenceAndAsscoiativity();

		void GenerateAttributes(Actions* actions, bool isUnion);
		std::string GenerateAttributeEnum(int indent);

		void dump(std::ostream& os);

		virtual std::string __getType() { return "Production"; }
		virtual std::string __getValue() { return toString(); }

		operator std::string() const {
			return toString();
		}
		std::string toString() const;
		std::string prettyPrint(int indent) const;
		std::string HTMLPrint() const;

		std::string GenerateGrammar() const;
		std::string GenerateSource(std::string name) const;

		virtual bool compare(const Production* rhs) const;

	protected:
		Rule* rule;
		NamedSymbols* rhs;
		std::string type;
		unsigned prededence;
		Associativity associativity;
		int action; // TODO: return to 'typedef int Action'

		size_t index;
		bool start;
		bitset selectSet;

		vector<std::string> attributes;
		vector<std::string> types;
	};

	class Productions : public virtual Type, public vector<Production*> {
	public:
		Productions() {}
		Productions(Production* production) {
			push_back(production);
		}
		Productions(const std::initializer_list<Production*> productions) : vector<Production*>(productions) {}

		~Productions() {
/*
			for (auto production : getProductions())
				delete production;
*/
		}

		void addProduction(Production* production) {
			assert(production != nullptr);
			push_back(production);
		}
		Production* getProduction(size_t index) const { return (*this)[index]; }
		const Productions& getProductions() const { return *this; }

		void GenerateAttributes(Actions* actions, bool _union);
		void dump(std::ostream& os);

		std::string GenerateGrammar() const;
		std::string GenerateSource(std::string name) const;

		virtual std::string __getType() { return "Productions"; }
		virtual std::string __getValue() { return "none"; }

		virtual bool compare(const Productions* rhs) const;

	};

	struct Rule : public virtual Type {
		Rule() : lhs(nullptr), productions(new Productions) {}
		Rule(NonTerminal* nonTerminal) : lhs(nonTerminal), productions(new Productions) {}
		Rule(NonTerminal* nonTerminal, Productions* ps) : lhs(nonTerminal), productions(new Productions) {
			assert(nonTerminal != nullptr);
			assert(productions != nullptr);
			for (auto production : *ps) {
				production->setRule(this);
				productions->add(production);
			}
		}
		Rule(NonTerminal* nonTerminal, Identifier* type, Productions* ps) : lhs(nonTerminal), productions(new Productions) {
			assert(nonTerminal != nullptr);
			assert(productions != nullptr);
			for (auto production : *ps) {
				production->setRule(this);
				production->setType(type->getValue());
				productions->add(production);
			}
		}
		Rule(NonTerminal* nonTerminal, std::initializer_list<Production*> pil) : lhs(nonTerminal), productions(new Productions) {
			assert(nonTerminal != nullptr);
			for (auto production : pil) {
				production->setRule(this);
				productions->add(production);
			}
		}
		~Rule() { for (auto production : *productions) delete production; }

		void addProduction(Production* production) {
			production->setRule(this);
			productions->add(production);
		}
		void addProductions(Productions* ps) {
			for (auto production : *ps) {
				production->setRule(this);
				productions->add(production);
			}
		}
		void addProductions(Productions* ps, Identifier* type) {
			for (auto production : *ps) {
				production->setRule(this);
				production->setType(type->getValue());
				productions->add(production);
			}
		}

		NonTerminal* getLHS() const { return lhs; }
		Productions& getProductions() { return *productions; }
		Production* getProduction(size_t production) const { return (*productions)[production]; }

		bitset getFirstSet() const { return lhs->getFirstSet(); }
		bitset getFollowSet() const { return lhs->getFollowSet(); }
		void setFirstSet(bitset firstset) { lhs->setFirstSet(firstset); }
		void GenerateSelectSets();

		bool isNullable() const {
			for (const_iterator ri = cbegin(); ri != cend(); ++ri)
				if (!(*ri)->isNullable())
					return false;
			return true;
		}
		void GenerateAttributes(Actions* actions, bool _union);

		virtual std::string __getType() { return "Rule"; }
		virtual std::string __getValue() { return getLHS()->toString(); }

		void dump(std::ostream& os);
		std::string toString() const;
		std::string prettyPrint(int indent) const;
		std::string HTMLPrint() const;

		typedef vector<Production*>::iterator iterator;
		typedef vector<Production*>::const_iterator const_iterator;
		iterator begin() { return productions->begin(); }
		iterator end() { return productions->end(); }
		const_iterator cbegin() const { return productions->cbegin(); }
		const_iterator cend() const { return productions->cend(); }

		Production* operator [] (size_t index) { return (*productions)[index]; }

		std::string GenerateGrammar() const;
		std::string GenerateSource(std::string name) const;

		virtual bool compare(const Rule* rhs) const;

	protected:
		//size_t index;
		NonTerminal* lhs;
		Productions* productions;
	};

	typedef ::Action Action;
/*
	struct Action : public Type {
		Action(int action) : action(action) {}

		int getAction() { return action; }

		virtual std::string __getType() { return "Action"; }
		virtual std::string __getValue() { return std::to_string(action); }

	protected:
		int action;
	};
*/
	struct Code : public Type {
		Code(std::string code, unsigned line) : code(code), line(line) {}

		std::string getCode() { return code; }
		unsigned getLine() { return line; }

		virtual std::string __getType() { return "Code"; }
		virtual std::string __getValue() { return code; }

	protected:
		std::string code;
		unsigned line;
	};

 	class Terminals : public std::vector<Terminal*> {
 	public:
 		Terminals() {}
 		Terminals(const std::initializer_list<Terminal*> terminals) : std::vector<Terminal*>(terminals) {}

 		bool compare(const Terminals* rhs) const;
		friend bool compare(const Terminals* lhs, const Terminals* rhs);
 	};

 	class NonTerminals : public std::vector<NonTerminal*> {
 	public:
 		NonTerminals() {}
 		NonTerminals(const std::initializer_list<NonTerminal*> nonTerminals) : std::vector<NonTerminal*>(nonTerminals) {}

 		bool compare(const NonTerminals* rhs) const;
		friend bool compare(const NonTerminals* lhs, const NonTerminals* rhs);
	};

	class Rules : public std::vector<Rule*> {
	public:
		Rules() {}
		Rules(const std::initializer_list<Rule*> rules) : std::vector<Rule*>(rules) {}

		bool compare(const Rules* rhs) const;
	};


	typedef Rules::iterator iterator;
	typedef Rules::const_iterator const_iterator;
	iterator begin() { return rules.begin(); }
	iterator end() { return rules.end(); }
	const_iterator cbegin() const { return rules.cbegin(); }
	const_iterator cend() const { return rules.cend(); }

	//
	//
	//

	ContextFreeGrammar(Terminals terminals, NonTerminals nonTerminals, Productions productions, NonTerminal* startSymbol) :
		terminals(terminals), nonTerminals(nonTerminals), productions(productions), nextTerminalSymbol(2), numberOfSymbols(2), nextNonTerminalSymbol(1), numberOfProductions(0), /* actions(), */ startSymbol(startSymbol)
	{
		for (auto terminal : terminals)
			terminal->setIndex(nextTerminalSymbol++);
		for (auto nonTerminal : nonTerminals)
			nonTerminal->setIndex(nextNonTerminalSymbol++);
		for (auto production : productions)
			production->setIndex(numberOfProductions++);
	}

	//
	//  Factory Methods
	//

	template <class T, typename... Args>
	T* create(Args... args) {
		return new T(this, args...);
	}

	size_t allocateTerminalSymbol() { return nextTerminalSymbol++; }
	size_t allocateNonTerminalSymbol() { return nextNonTerminalSymbol++; }

	//
	//
	//

	Identifier* newIdentifier(std::string name) const { return new Identifier(name); }
	StringLiteral* newStringLiteral(std::string name) const { return new StringLiteral(name); }

	Terminal* newTerminal(Terminal* terminal) {
		return new Terminal(nextTerminalSymbol++, terminal);
	}
	Terminal* newTerminal(Identifier* name) {
		return new Terminal(nextTerminalSymbol++, name);
	}
	Terminal* newTerminal(std::string name) {
		return new Terminal(nextTerminalSymbol++, name);
	}
	Terminal* newTerminal(Identifier* name, Identifier* type) {
		return new Terminal(nextTerminalSymbol++, name, type);
	}
	Terminal* newTerminal(std::string name, std::string type) {
		return new Terminal(nextTerminalSymbol++, name, type);
	}
	Terminal* newTerminal(Identifier* name, StringLiteral* value, bool final = false) {
		return new Terminal(nextTerminalSymbol++, name, value, final);
	}
	Terminal* newTerminal(Identifier* name, Identifier* type, StringLiteral* value) {
		return new Terminal(nextTerminalSymbol++, name, type, value);
	}
	Terminal* newTerminal(std::string name, std::string type, std::string value) {
		return new Terminal(nextTerminalSymbol++, name, type, value);
	}
	Terminal* newTerminal(std::string name, std::string type, std::string value, Associativity associativity, unsigned precedence, bool final = false) {
		return new Terminal(nextTerminalSymbol++, name, type, value, associativity, precedence, final);
	}

	NonTerminal* newNonTerminal(NonTerminal* nonTerminal) {
		return new NonTerminal(nextNonTerminalSymbol++, nonTerminal);
	}
	NonTerminal* newNonTerminal(Identifier* name) {
		return new NonTerminal(nextNonTerminalSymbol++, name, name);
	}
	NonTerminal* newNonTerminal(std::string name) {
		return new NonTerminal(nextNonTerminalSymbol++, name, name);
	}
	NonTerminal* newNonTerminal(Identifier* name, Identifier* type) {
		return new NonTerminal(nextNonTerminalSymbol++, name, type);
	}
	NonTerminal* newNonTerminal(std::string name, std::string type) {
		return new NonTerminal(nextNonTerminalSymbol++, name, type);
	}

	NonTerminal* createNonTerminal(Identifier* name) {
		NonTerminal* nonTerminal = newNonTerminal(name);
		addNonTerminal(nonTerminal);
		return nonTerminal;
	}
	NonTerminal* findOrCreateNonTerminal(Identifier* name) {
		NonTerminal* nonTerminal = getNonTerminal(name);
		if (nonTerminal)
			return nonTerminal;
		else
			return createNonTerminal(name);
	}

	Rule* newRule(Identifier* lhs, Productions* productions) {
		assert(lhs != nullptr);
		assert(productions != nullptr);
		NonTerminal* nonTerminal = getNonTerminal(lhs);

		if (nonTerminal == nullptr || nonTerminal->asSymbol() == getErrorSymbol()) {
			nonTerminal = newNonTerminal(lhs);
			addNonTerminal(nonTerminal);
		}

		return new Rule(nonTerminal, productions);
	}
	Rule* newRule(NonTerminal* lhs, Productions* productions) {
		assert(lhs != nullptr);
		assert(productions != nullptr);
		Rule* production = new Rule(lhs, productions);
		return production;
	}
/*
	Rule* newRule(NonTerminal* lhs, Identifier* type, Productions* productions) {
		assert(lhs != nullptr);
		assert(productions != nullptr);
		Rule* production = new Rule(lhs, type, productions);
		return production;
	}
*/
	Rule* newRule(Identifier* lhs, Identifier* type, Productions* productions) {
		assert(lhs != nullptr);
		assert(productions != nullptr);
		Rule* production = new Rule(findOrCreateNonTerminal(lhs), type, productions);
		return production;
	}

	Rule* newRule(NonTerminal* lhs, std::initializer_list<Production*> productions) {
		assert(lhs != nullptr);
		Rule* production = new Rule(lhs, productions);
		return production;
	}

	Rule* newRule(Identifier* lhs) {
		assert(lhs != nullptr);
		NonTerminal* nonTerminal = getNonTerminal(lhs);
		return new Rule(nonTerminal);
	}
	Rule* newRule(NonTerminal* nonTerminal) {
		return new Rule(nonTerminal);
	}

	Productions* newProductions() { return new Productions(); }
	Productions* newProductions(Production* production) { return new Productions(production); }
	Productions* newProductions(const std::initializer_list<Production*> productions) { return new Productions(productions); }

	Production* newProduction(bool start = false) {
		Production* production = new Production(numberOfProductions++, start);
		productions.push_back(production);
		return production;
	}
	Production* newProduction(NamedSymbols* namedSymbols, bool start = false) {
		Production* production = new Production(numberOfProductions++, namedSymbols, start);
		productions.push_back(production);
		return production;
	}
	Production* newProduction(NamedSymbols* namedSymbols, int action, bool start = false) {
		Production* production = new Production(numberOfProductions++, namedSymbols, action, start);  // TODO: fix action hack !!
		productions.push_back(production);
		return production;
	}
	Production* newProduction(int action, bool start = false) {
		Production* production = new Production(numberOfProductions++, action, start);  // TODO: fix action hack !!
		productions.push_back(production);
		return production;
	}
	Production* addProduction(NamedSymbols namedSymbols, unsigned action) {
		Production* production = new Production(numberOfProductions++, namedSymbols, action);
		productions.push_back(production);
		return production;
	}

	NamedSymbols* newNamedSymbols() { return new NamedSymbols(); }
	NamedSymbols* newNamedSymbols(const std::initializer_list<NamedSymbol*> namedSymbols) { return new NamedSymbols(namedSymbols); }

	Symbol* newSymbol(Identifier* identifier) { return newNonTerminal(identifier); }

	NamedSymbol* newNamedSymbol(std::string name, Symbol* symbol) {
		return new NamedSymbol(new Identifier(name), symbol);
	}
	NamedSymbol* newNamedSymbol(Identifier* name, Symbol* symbol) {
		return new NamedSymbol(name, symbol);
	}
	NamedSymbol* newNamedSymbol(Symbol* symbol) {
		return new NamedSymbol(symbol);
	}

	int addAction(std::string action, unsigned line) {
		return actions->addAction(action.c_str(), line)->getIndex();
	}

	Code* newCode(std::string code, unsigned line) {
		return new Code(code, line);
	}

	//
	//
	//

	void addTerminal(Terminal* terminal) {
		stringLiteralToTerminal[terminal->getValue()] = terminal;
		identifierToTerminal[terminal->getName()] = terminal;
		terminals.push_back(terminal);
		symbols.push_back(terminal);
	}

	Terminal* addTerminal(std::string name, std::string type, std::string value, Associativity associativity, unsigned precedence, bool final = false) {
		Terminal* terminal = newTerminal(name, type, value, associativity, precedence, final);
		addTerminal(terminal);
		return terminal;
	}

	void addNonTerminal(NonTerminal* nonTerminal) {
		identiferToNonTerminal[nonTerminal->getName()] = nonTerminal;
		nonTerminals.push_back(nonTerminal);
		symbols.push_back(nonTerminal);
	}

	void addRule(Rule* rule) {
		assert(rule != nullptr);
		rules.push_back(rule);
		nonTerminalToRule[rule->getLHS()] = rule;
	}

	//

	Terminal* addTerminal(std::string name) {
		Terminal* terminal = newTerminal(name);
		addTerminal(terminal);
		return terminal;
	}
	Terminal* addTerminal(std::string name, std::string type) {
		Terminal* terminal = newTerminal(name, type, type);     // TODO: Check
		addTerminal(terminal);
		return terminal;
	}
	Terminal* addTerminal(std::string name, std::string type, std::string value) {
		Terminal* terminal = newTerminal(name, type, value);
		addTerminal(terminal);
		return terminal;
	}

	NonTerminal *addNonTerminal(std::string name) {
		NonTerminal *nonTerminal = newNonTerminal(name, name);
		addNonTerminal(nonTerminal);
		return nonTerminal;
	}

	NonTerminal *addNonTerminal(std::string name, std::string type) {
		NonTerminal *nonTerminal = newNonTerminal(name, type);
		addNonTerminal(nonTerminal);
		return nonTerminal;
	}

	Rule *addRule(NonTerminal* lhs, std::initializer_list<Production*> productions) {
		Rule *rule = newRule(lhs, productions);
		addRule(rule);
		return rule;
	}

	//
	//  Accessors
	//

	Terminals& getTerminals() {
		return terminals;
	}
	const Terminals& getTerminals() const {
		return terminals;
	}
	unsigned getNumberOfTerminals() const {
		return terminals.size();
	}
	NonTerminals& getNonTerminals() {
		return nonTerminals;
	}
	const NonTerminals& getNonTerminals() const {
		return nonTerminals;
	}
	unsigned getNumberOfNonTerminals() const {
		return nonTerminals.size();
	}
	Productions& getProductions() {
		return productions;
	}
	const Productions& getProductions() const {
		return productions;
	}
	Rules& getRules() {
		return rules;
	}
	const Rules& getRules() const {
		return rules;
	}

	NonTerminal* getNonTerminal(Identifier* name) {
		return identiferToNonTerminal[*name];
	}
	NonTerminal* getNonTerminal(std::string name) {
		return identiferToNonTerminal[Identifier(name)];
	}
	Terminal* getTerminal(StringLiteral* value) {
		return stringLiteralToTerminal[*value];
	}
	Terminal* getTerminal(Identifier* name) {   // TODO: Deal with undefined returned as nulls
		return identifierToTerminal[*name];
	}
	Terminal* getTerminal(std::string name) {
		return identifierToTerminal[Identifier(name)];
	}

	Symbol* getSymbol(Identifier* name) {
		Symbol* symbol;

		if ((symbol = getNonTerminal(name)) != nullptr)
			return symbol;
		else if ((symbol = getTerminal(name)) != nullptr)
			return symbol;
		else
			return ContextFreeGrammar::getErrorSymbol();
	}
	Symbol* findOrCreateSymbol(Identifier* name) {
		Symbol* symbol = getSymbol(name);
		if (symbol != getErrorSymbol())
			return symbol;
		else {
			symbol = newNonTerminal(name);
			addNonTerminal(symbol->asNonTerminal());
			return symbol;
		}
	}

	Productions& getProductions(NonTerminal* nonTerminal) {
		return getRule(nonTerminal)->getProductions();       // TODO: bug if erroro in .pg file
	}

	Rule* getRule(NonTerminal* nonTerminal) {
		auto ri = nonTerminalToRule.find(nonTerminal);
		if (ri != nonTerminalToRule.end())
			return ri->second;
		else
			return nullptr;
		//return nonTerminalToRule[nonTerminal];
	}
	Rule* getRule(size_t index) {
		return rules[index];
	}
	Rule* getRule(std::string name) {
		auto ri = nonTerminalToRule.find(getNonTerminal(name));
		if (ri != nonTerminalToRule.end())
			return ri->second;
		else
			return nullptr;

		//return nonTerminalToRule[getNonTerminal(name)];
	}
	Rule* findOrCreateRule(Identifier* name) {
		NonTerminal* nonTerminal = getNonTerminal(name);
		Rule* rule = getRule(nonTerminal);
		if (rule)
			return rule;
		else
			return newRule(nonTerminal);
	}
	Rule* findOrCreateRule(Identifier* name, Productions* productions) {
		NonTerminal* nonTerminal = findOrCreateNonTerminal(name);
		Rule* rule = getRule(nonTerminal);
		if (rule) {
			for (auto production : *productions)
				rule->addProduction(production);
			return rule;
		}
		else
			return newRule(nonTerminal, productions);
	}
	Rule* findOrCreateRule(Identifier* name, Identifier* type, Productions* productions) {
		NonTerminal* nonTerminal = findOrCreateNonTerminal(name);
		Rule* rule = getRule(nonTerminal);
		if (rule) {
			for (auto production : *productions) {
				production->setType(type->getValue());
				rule->addProduction(production);
			}
			return rule;
		}
		else
			return newRule(name, type, productions);
	}

	NonTerminals& getNonTerminalSymbols() {
		return nonTerminals;
	}

	void setStartSymbol(NonTerminal* start) {
		startSymbol = start;
	}
	NonTerminal* getStartSymbol() const {
		return startSymbol;
	}
	NonTerminal* getDefaultStartSymbol();

	Production* getStartProduction() {
		return getProductions(startSymbol).getProduction(0);
	}

	size_t getNumberOfTerminalSymbols() {
		return nextTerminalSymbol;          // TODO: Check !!!
	}
	size_t getNumberOfNonTerminalSymbols() {
		return nextNonTerminalSymbol - 1;
	}
	size_t getNumberOfSymbols() {
		return getNumberOfTerminalSymbols() + getNumberOfNonTerminalSymbols();
	}

	//

	Actions* getActions() const { return actions; }
	void setActions(Actions* actions) {
		this->actions = actions;
	}


	void GenerateAttributes(Actions* actions, bool _union);

	void dump(std::ostream& os);

	void GenerateFirstSets();
	void GenerateFollowSets();
	void GenerateSelectSets();

	std::string PrintFirstSets();
	std::string PrintFollowSets();

	void CheckGrammar();
	void SetStartProduction();
	bool isAugmentedGrammar();
	void AugmentGrammar();

	void GeneratePrecedences();

	std::string GenerateGrammar() const;
	void GenerateSourceH(std::string name, std::ostream& output) const;
	void GenerateSourceCXX(std::string name, std::ostream& output) const;

	std::string prettyPrint(int indent = 0) const;
	std::string HTMLPrint(std::string name) const;

	class Symbols : public vector<Symbol*> {};

	void GenerateTerminalNamesAsVector() {
		for (auto terminal : terminals)
			terminalNames.push_back(terminal->getValue() != "" ? std::string("\"" + terminal->getValue() + "\"") : terminal->getName());
	}
	vector<std::string>& getTerminalNamesAsVector() {
		return terminalNames;
	}

	friend bool compare(const ContextFreeGrammar* lhs, const ContextFreeGrammar* rhs);

protected:
	size_t numberOfSymbols;
	size_t nextTerminalSymbol;
	size_t nextNonTerminalSymbol;
	size_t numberOfProductions;

	Symbols symbols;
	Terminals terminals;
	NonTerminals nonTerminals;
	Productions productions;
	Rules rules;

	Actions* actions;

	NonTerminal* startSymbol;

	vector<std::string> terminalNames;
	std::map<Identifier, NonTerminal*> identiferToNonTerminal;
	std::map<StringLiteral, Terminal*> stringLiteralToTerminal;
	std::map<Identifier, Terminal*> identifierToTerminal;
	std::map<NonTerminal*, Rule*> nonTerminalToRule;
};

} // end namespace G
} // end namespace Grammar

// TODO: Change Production::action from int to Action*
// TODO: normalize and look at StringLiteral, Identifier and std::string
// TODO: look at Type
// TODO: rename *::nullable's to *::isNullable ?

// End g/Grammar/ContextFreeGrammar.h - Context Free Grammar
