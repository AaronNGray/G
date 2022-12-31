//
//  runtime/parser/Parser.h - LR Parser runtime
//
//  Property and Copyright (c) 2015-2016 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include "runtime/lexer/Lexer.h"
#include "runtime/Stack.h"
#include "nonstd/File.h"
#include "nonstd/Utils.h"

namespace Runtime {

typedef short State;
typedef unsigned short Input;

template<typename STATETYPE = short, class VALUETYPE = int>
class Parser
{
public:
    typedef STATETYPE State;
    typedef VALUETYPE ValueType;

    Parser(Lexer* lexer, ValueType& lookaheadValue, bool debug = false) : lexer(lexer), lookaheadValue(lookaheadValue), debug(debug) {}
    virtual ~Parser() { delete lexer; }

    bool parse();

    struct Action {
        enum Function : unsigned {
            Shift,
            Reduce,
            Accept,
            Error
        };

        Action() {}
        Action(Function action, size_t value) : action(action), value(value) {}
        Action(Function action) : action(action), value(0) {}

        Function action : 2;
        unsigned int value : 30;

        operator enum Function() { return action; }
        unsigned getValue() { return value; }
        State getState() { return value; }

        std::string toString() {
            switch (action) {
            case Shift:
                return "Shift" + std::string(", ") + std::to_string(value);
            case Reduce:
                return "Reduce" + std::string(", ") + std::to_string(value);
            case Accept:
                return "Accept";
            case Error:
                return "Error";
            }
        }
    };

    std::string AsString(Action value) {
        std::string s = value.toString();
        return s;
    }

    typedef short NonTerminal;
    typedef short Terminal;
    virtual State getStates() = 0;
    virtual Action nextState(State state, Input input) = 0;
    virtual State nextGoto(State state, NonTerminal lhs) = 0;
    virtual int getAcceptAction(size_t production) = 0;
    virtual void dispatch(int action) = 0;
    virtual size_t getNumberOfRHSSymbols(size_t production) = 0;
    virtual NonTerminal getLHSSymbolIndex(size_t production) = 0;
    virtual size_t getNumberOfTerminals() = 0;
    virtual std::string getTerminalName(size_t index) = 0;
    virtual std::string getNonTerminalName(size_t index) = 0;
    virtual void reportError(State state, Input input) = 0;
    virtual std::string toString(Input input, ValueType value) { return ""; }

    State shift(State state, State prevState, Input input, ValueType value = ValueType()) {
        stateStack.push(state);
        valueStack.push(value);

        State nextState = stateStack.top();

        if (debug) {
            std::cout << "shift: State " << prevState << " shift on '" << getTerminalName(input) << "' (" << input << ") to state " << nextState << std::endl;
            std::cout << "stack: " << stateStack.toString() << std::endl;
        }

        return nextState;
    }
    State reduce(State state, Input input, unsigned production, ValueType value) {
        size_t numberOfRHSSymbols = getNumberOfRHSSymbols(production);

        if (debug)
            std::cout << "State " << state << " pop " << numberOfRHSSymbols << nonstd::endl;

        stateStack.pop(numberOfRHSSymbols);
        valueStack.pop(numberOfRHSSymbols);

        State baseState = stateStack.top();
        State nextState = nextGoto(baseState, getLHSSymbolIndex(production));

        stateStack.push(nextState);
        valueStack.push(value);

        if (debug) {
            std::cout << "reduce: production " << production << " on '" << getTerminalName(input) << "' (" << input << ") by '" << getNonTerminalName(getLHSSymbolIndex(production)) << "' (" << getLHSSymbolIndex(production) << ") in state " << baseState << " go to state " << nextState << std::endl;
            std::cout << "stack: " << stateStack.toString() << std::endl;
        }

        return nextState;
    }
    bool error(State state, Input input) {
        reportError(state, input);
        return true;
    }

protected:
    bool debug;
    Lexer* lexer;
    Stack<State> stateStack;
    Stack<ValueType> valueStack;
    ValueType currentValue;
    ValueType& lookaheadValue;
};

template<typename State, class Base>
bool Parser<State, Base>::parse() {

    State currentState = 1;
    State previousState = currentState;
    Action action;

    if (debug)
        std::cout << "Push state: " << currentState << std::endl;

    stateStack.push(currentState);
    valueStack.push();

    if (debug)
        std::cout << stateStack.toString() << std::endl;

    Input input = lexer->lex();

    if (debug)
        std::cout << "Read: " << getTerminalName(input) << std::endl;

    if (input == Lexer::ERROR)
        goto error;

    while (true) {
        previousState = currentState;
        action = nextState(currentState, input);

        switch (action) {
            case Action::Function::Shift: {
                if (action.getState() == 0 || action.getState() > getStates())
                    goto error;

                currentState = shift(action.getState(), currentState, input, lookaheadValue);

                input = lexer->lex();

                if (debug) {
                    std::cout << "Read: " << getTerminalName(input) << std::endl;
                }

                if (input == Lexer::ERROR)
                    goto error;

                break;
            }
            case Action::Function::Reduce: {
                unsigned production = action.getValue();
                size_t function = getAcceptAction(production);
                size_t rhsSymbols = getNumberOfRHSSymbols(production);

                if (function != -1)
                    dispatch(function);
                else
                    currentValue = valueStack[rhsSymbols ? rhsSymbols - 1 : 0];  // $$ = $1;

                currentState = reduce(currentState, input, action.getValue(), currentValue);

                if (currentState == 0)
                    goto error;
                break;
            }
            case Action::Function::Accept: {
                if (debug)
                    std::cout << "State " << currentState << " Accept" << std::endl;
                return true;
            }
            default:
            case Action::Function::Error: {
            error:
                if (debug)
                    std::cout << "Error" << std::endl;
                if (error(previousState, input))
                    return false;
                break;
            }
        }
    };
}

} // End namespace runtime

// End runtime/parser/Parser.h - LR Parser runtime
