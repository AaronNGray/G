//
//  g/Grammar/ExtendedGrammar.h - Extended (BNF) Grammar
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
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
#include "g/Grammar/ContextFreeGrammar.h"

namespace G {
extern Logger* logger;
namespace Grammar {

class ExtendedGrammar : public ContextFreeGrammar {
public:
    ExtendedGrammar(std::string name, Actions* actions) : ContextFreeGrammar(name, actions) { // TODO: initialization
    }
    ExtendedGrammar() : ContextFreeGrammar() {}
    virtual ~ExtendedGrammar() {}	// TODO: Deallocation

    using Literal = ContextFreeGrammar::Literal;

    using Identifier = ContextFreeGrammar::Identifier;
    using StringLiteral = ContextFreeGrammar::StringLiteral;
    using Associativity = ContextFreeGrammar::Associativity;

    struct Visitor;
    struct Context;

    struct Node;
    struct Factor;

    struct Rule;
    struct Productions;
    struct Production;
    struct NamedFactors;
    struct NamedFactor;
    struct OptionalRepetition;
    struct Repetition;
    struct Optional;
    struct Selection;
    struct Sequence;

    struct LowerContext {
        LowerContext(ContextFreeGrammar* grammar, ExtendedGrammar* extendedGrammar) : grammar(grammar), extendedGrammar(extendedGrammar) {}
        ContextFreeGrammar* grammar;
        ExtendedGrammar* extendedGrammar;
    };

    //
    //
    //

    struct Visitor {
        virtual void visit(Node* node, Context* context) = 0;
        virtual void visit(Factor* factor, Context* context) = 0;
        virtual void visit(Terminal* terminal, Context* context) = 0;
        virtual void visit(NonTerminal* nonTerminal, Context* context) = 0;
        virtual void visit(PseudoTerminal* pseudoTerminal, Context* context) = 0;
        virtual void visit(Epsilon* epsilon, Context* context) = 0;
        virtual void visit(End* end, Context* context) = 0;
        virtual void visit(Error* error, Context* context) = 0;

        virtual void visit(Production* production, Context* context) = 0;
        virtual void visit(Productions* productions, Context* context) = 0;
        virtual void visit(Rule* rule, Context* context) = 0;

        virtual void visit(NamedFactors* namedFactors, Context* context) = 0;
        virtual void visit(NamedFactor* namedFactor, Context* context) = 0;

        virtual void visit(OptionalRepetition* optionalRepetition, Context* context) = 0;
        virtual void visit(Repetition* repetition, Context* context) = 0;
        virtual void visit(Optional* optional, Context* context) = 0;
        virtual void visit(Selection* selection, Context* context) = 0;
        virtual void visit(Sequence* sequence, Context* context) = 0;
    };

    //
    //
    //

    struct Node {};

    struct Factor : public Node {
        Factor() {}
        Factor(Symbol* symbol) {}
        virtual ContextFreeGrammar::NonTerminal* lower(LowerContext* context);
        virtual bool isOptional() { return false; }
        virtual bool isRepetition() { return false; }
    };
    using Symbol = ContextFreeGrammar::Symbol;
    using Terminal = ContextFreeGrammar::Terminal;
    using NonTerminal = ContextFreeGrammar::NonTerminal;

    struct Production : public Node {
        Production(size_t index, bool start = false) : index(index), rule(nullptr), rhs(new NamedFactors()), action(nullptr), start(start) {}
        Production(size_t index, Action* action, bool start = false) : index(index), rule(nullptr), rhs(new NamedFactors()), action(action), start(start) {}
        Production(size_t index, Rule* lhsRule, bool start = false) : index(index), rule(lhsRule), rhs(new NamedFactors()), action(nullptr), start(start) {}
        Production(size_t index, Rule* lhsRule, NamedFactors* rhs, bool start = false) : index(index), rule(lhsRule), rhs(rhs), action(nullptr), start(start) {}
        Production(size_t index, NamedFactors* rhs, bool start = false) : index(index), rule(nullptr), rhs(rhs), action(nullptr), start(start) {}
        Production(size_t index, NamedFactors* rhs, Action* action, bool start = false) : index(index), rule(nullptr), rhs(rhs), action(action), start(start) {}

        Rule* getRule() { return rule; }
        void setRule(Rule* lhsRule) { rule = lhsRule; }

        virtual void accept(Visitor* v, Context* context) {
            v->visit(this, context);
        }
        void lower(LowerContext* context);

    protected:
        size_t index;
        Rule* rule;
        NamedFactors* rhs;
        Action* action;
        bool start;
    };
    struct Productions : public Node, public vector<Production*> {
        Productions() {}
        Productions(Production* production) {
            push_back(production);
        }
        Productions(const std::initializer_list<Production*> productions) : vector<Production*>(productions) {}
        void addProduction(Production* production) {
            assert(production != nullptr);
            push_back(production);
        }
        Production* getProduction(size_t index) const { return (*this)[index]; }

        virtual void accept(Visitor* v, Context* context) {
            v->visit(this, context);
        }

    };
    struct Rule : public Node {
        Rule() {}
        Rule(NonTerminal* nonTerminal) : lhs(nonTerminal) {}
        Rule(NonTerminal* nonTerminal, Productions* productions) : lhs(nonTerminal), productions(productions) {
            assert(nonTerminal != nullptr);
            assert(productions != nullptr);
            for (auto production : *productions)
                production->setRule(this);
        }
        ~Rule() { for (auto production : *productions) delete production; }

        NonTerminal* getLHS() const { return lhs; }
        Production* getProduction(size_t production) const { return (*productions)[production]; }
        Productions& getProductions() { return *productions; }

        ContextFreeGrammar::Rule* lower(LowerContext* context);

        virtual void accept(Visitor* v, Context* context) {
            v->visit(this, context);
        }

        NonTerminal* lhs;
        Productions* productions;
    };

    struct NamedFactor : public Node {
        NamedFactor() {}
        NamedFactor(Factor* factor) : name(nullptr), factor(factor) {}
        NamedFactor(Identifier* name, Factor* factor) : name(name), factor(factor) {}

        virtual void accept(Visitor* v, Context* context) {
            v->visit(this, context);
        }
        bool isOptional() { return factor->isOptional(); }

        ContextFreeGrammar::NamedSymbol* lower(LowerContext* context);

        Identifier* name;
        Factor* factor;
    };
    struct NamedFactors : public Node, public vector<NamedFactor*> {
        NamedFactors() {}
        void add(NamedFactor* namedFactor) {
            push_back(namedFactor);
        }

        NamedFactors& getNamedFactors() { return *this; }
        bool hasOptional();

        virtual void accept(Visitor* v, Context* context) {
            v->visit(this, context);
        }
        ContextFreeGrammar::NamedSymbols* lower(LowerContext* context);
    };

    struct OptionalRepetition : public Factor {
        OptionalRepetition(Factor* factor) : factor(factor) {}
        virtual void accept(Visitor* v, Context* context) {
            v->visit(this, context);
        }

        virtual bool isOptional() { return true; }
        virtual bool isRepetition() { return true; }

        virtual ContextFreeGrammar::NonTerminal* lower(LowerContext* context);

        Factor* factor;
    };
    struct Repetition : public Factor {
        Repetition(Factor* factor) : factor(factor) {}
        virtual void accept(Visitor* v, Context* context) {
            v->visit(this, context);
        }

        virtual bool isOptional() { return false; }
        virtual bool isRepetition() { return true; }

        virtual ContextFreeGrammar::NonTerminal* lower(LowerContext* context);

        Factor* factor;
    };
    struct Optional : public Factor {
        Optional(Factor* factor) : factor(factor) {}
        virtual void accept(Visitor* v, Context* context) {
            v->visit(this, context);
        }

        virtual bool isOptional() { return true; }

        virtual ContextFreeGrammar::NonTerminal* lower(LowerContext* context);

        Factor* factor;
    };

    struct Selection : public Factor, public vector<Factor*> {
        Selection() {}
        void add(Factor* factor) {
            push_back(factor);
        }
        virtual void accept(Visitor* v, Context* context) {
            v->visit(this, context);
        }

        virtual ContextFreeGrammar::NonTerminal* lower(LowerContext* context);
    };
    struct Sequence : public Factor, public vector<Factor*> {
        Sequence() {}
        void add(Factor* factor) {
            push_back(factor);
        }
        virtual void accept(Visitor* v, Context* context) {
            v->visit(this, context);
        }
        virtual ContextFreeGrammar::NonTerminal* lower(LowerContext* context);
    };

    //
    //
    //

    using Action = ContextFreeGrammar::Action;
    using Code = ContextFreeGrammar::Code;

    typedef vector<Terminal*> Terminals;
    typedef vector<NonTerminal*> NonTerminals;
    typedef vector<Rule*> Rules;

    typedef Rules::iterator iterator;
    typedef Rules::const_iterator const_iterator;
    iterator begin() { return rules.begin(); }
    iterator end() { return rules.end(); }
    const_iterator cbegin() const { return rules.cbegin(); }
    const_iterator cend() const { return rules.cend(); }

    //
    //  Factory Methods
    //

    Identifier* newIdentifier(std::string name) const { return new Identifier(name); }
    StringLiteral* newStringLiteral(std::string name) const { return new StringLiteral(name); }

    Terminal* newTerminal(Identifier* name) {
        return new Terminal(nextTerminalSymbol++, name);
    }
    Terminal* newTerminal(Identifier* name, Identifier* type) {
        return new Terminal(nextTerminalSymbol++, name, type);
    }
    Terminal* newTerminal(Identifier* name, StringLiteral* value, bool final = false) {	// TODO: why final on this ?
        return new Terminal(nextTerminalSymbol++, name, value, final);
    }
    Terminal* newTerminal(Identifier* name, Identifier* type, StringLiteral* value) {
        return new Terminal(nextTerminalSymbol++, name, type, value);
    }
    NonTerminal* newNonTerminal(Identifier* name) {
        return new NonTerminal(nextNonTerminalSymbol++, name, name);
    }
    NonTerminal* newNonTerminal(Identifier* name, Identifier* type) {
        return new NonTerminal(nextNonTerminalSymbol++, name, type);
    }

    Rule* newRule(Identifier* lhs, Productions* productions) {
        Rule* rule = nullptr;
        assert(lhs != nullptr);
        assert(productions != nullptr);
        NonTerminal* nonTerminal = getNonTerminal(lhs);

        if (nonTerminal != nullptr)
            rule = new Rule(nonTerminal, productions);
        else {
            logger->LogError(new UndefinedSymbolErrorObject(lhs->getName()));
            rule = new Rule();
        }

        return rule;
    }
    Rule* newRule(NonTerminal* lhs, Productions* productions) {
        assert(lhs != nullptr);
        assert(productions != nullptr);
        return new Rule(lhs, productions);
    }
    Rule* newRule(Identifier* lhs) {
        assert(lhs != nullptr);
        NonTerminal* nonTerminal = getNonTerminal(lhs);
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
    Production* newProduction(NamedFactors* namedNamedFactors, bool start = false) {
        Production* production = new Production(numberOfProductions++, namedNamedFactors, start);
        productions.push_back(production);
        return production;
    }
    Production* newProduction(NamedFactors* namedNamedFactors, Action* action, bool start = false) {
        Production* production = new Production(numberOfProductions++, namedNamedFactors, action, start);  // TODO: fix action hack !!
        productions.push_back(production);
        return production;
    }
    Production* newProduction(Action* action, bool start = false) {
        Production* production = new Production(numberOfProductions++, action, start);  // TODO: fix action hack !!
        productions.push_back(production);
        return production;
    }

    NamedFactors* newNamedFactors() { return new NamedFactors(); }
    //NamedFactors* newNamedSymbols(const std::initializer_list<NamedFactors*> namedSymbols) { return new NamedFactors(namedSymbols); }

//    Symbol* newSymbol(Identifier* identifier) { return newNonTerminal(identifier); }

    NamedFactor* newNamedFactor(Identifier* name, Factor* factor) {
        return new NamedFactor(name, factor);
    }
    NamedFactor* newNamedFactor(Factor* factor) {
        return new NamedFactor(factor);
    }

    OptionalRepetition* newOptionalRepetition(Factor* factor) {
        return new OptionalRepetition(factor);
    }
    Repetition* newRepetition(Factor* factor) {
        return new Repetition(factor);
    }
    Optional* newOptional(Factor* factor) {
        return new Optional(factor);
    }

    Selection* newSelection() {
        return new Selection();
    }
    Sequence* newSequence() {
        return new Sequence();
    }

    Code* newCode(std::string code, unsigned line) {
        return new Code(code, line);
    }

    //
    //  Accessors
    //

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
/*
    Terminal* getEpsilon() {
        return identifierToTerminal["EPSILON"];
    }
*/
    Symbol* getSymbol(Identifier* name) {
        Symbol* symbol;

        if ((symbol = getNonTerminal(name)) != nullptr)
            return symbol;
        if ((symbol = getTerminal(name)) != nullptr)
            return symbol;
        // TODO: Symbol not found error
        //std::cerr << "Error: Symbol '" << name->getValue() << "' not found." << std::endl;
        //assert(false);
        return ContextFreeGrammar::getErrorSymbol(); // TODO: Need dummy symbol instead of nullptr
    }

    Rule* getRule(NonTerminal* nonTerminal) {
        return nonTerminalToRule[nonTerminal];
    }
    Rule* getRule(size_t index) {
        return rules[index];
    }
    Rule* getRule(std::string name) {
        return nonTerminalToRule[getNonTerminal(name)];
    }


    Productions* getProductions(NonTerminal* nonTerminal) {
        return getRule(nonTerminal)->productions;       // TODO: bug if erroro in .pg file
    }

    NonTerminals& getNonTerminalSymbols() {
        return nonTerminals;
    }

    void setStartSymbol(NonTerminal* start) {
        startSymbol = start;
    }
    NonTerminal* getStartSymbol() {
        return startSymbol;
    }
    NonTerminal* getDefaultStartSymbol();
    Productions& getProductions() {
        return productions;
    }

    Production* getStartProduction() {
        return getProductions(startSymbol)->getProduction(0);
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
    //
    //

    void addTerminal(Terminal* terminal) {
        stringLiteralToTerminal[terminal->getValue()] = terminal;
        identifierToTerminal[terminal->getName()] = terminal;
        terminals.push_back(terminal);
        symbols.push_back(terminal);
    }

    void addNonTerminal(NonTerminal* nonTerminal) {
        identiferToNonTerminal[nonTerminal->getName()] = nonTerminal;
        nonTerminals.push_back(nonTerminal);
        symbols.push_back(nonTerminal);
    }

    void addRule(Rule* rule) {
        rules.push_back(rule);
        nonTerminalToRule[rule->getLHS()] = rule;
    }

    Actions* getActions() const { return actions; }

    void GenerateAttributes(Actions* actions, bool _union);

    void dump(std::ostream& os);

    void GenerateFirstSets();
    void GenerateFollowSets();
    std::string PrintFirstSets();
    std::string PrintFollowSets();

    void CheckGrammar();
    void SetStartProduction();
    bool isAugmentedGrammar();
    void AugmentGrammar();

    void GeneratePrecedences();

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

    Rules& getRules() {
        return rules;
    }

    virtual ContextFreeGrammar *lower();

    size_t numberOfSymbols;
    size_t nextTerminalSymbol;
    size_t nextNonTerminalSymbol;
    size_t numberOfProductions;

    Symbols symbols;
    Terminals terminals;
    NonTerminals nonTerminals;
    Rules rules;
    Productions productions;

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

// End g/Grammar/ExtendedGrammar.h - Extended (BNF) Grammar
