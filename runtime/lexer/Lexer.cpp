//
//  Lexer.cpp - Standard Lexer runtime
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "Lexer.h"
#include <iostream>
#include <sstream>

//
//  runtime/lexer/Lexer.h - Standard Lexer runtime
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "nonstd/File.h"
#include "runtime/lexer/Lexer.h"
#include "nonstd/Utils.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <map>

namespace Runtime {

int Lexer::lex(State state) {
    if (state == -1)
        state = startState;

    State lastAcceptState = -1;
    State laststate;
    Input input;
    int action;
    int ret;

    _begin = _lastAccept = _end;  // pickup from the end of the last invocation

    while (true) {
        if (peek() == END)
            return END;

        while ((state = next(laststate = state, input = peek())) > 0) {
			if (debug)
				std::cout << laststate << ", " << toString(input) << "@" << std::hex << (int) _end << " -> " << std::dec << state << std::endl;
            if (getAcceptAction(state) != -1) {
                lastAcceptState = state;
                accept();
            }
            advance();
        };

		if (debug)
			std::cout << laststate << ", " << toString(input) << "@" << std::hex << (int) _end << " -> " << std::dec << state << std::endl;

        state = -state;

        if (state == 0)
            state = laststate;
        else
            advance();

        action = getAcceptAction(state);

        if (action == -1) {
            if (lastAcceptState == -1)
                return ERROR;
            state = lastAcceptState;
            rewind();
            advance();
            action = getAcceptAction(state);
        }

        ret = dispatch(action);

        if (ret == IGNORE)
            state = startState;
        else
            return ret;

        forward();
    }
}

typename Lexer::Input Lexer::peek() {
    if (end() != buffer.end())
        return *end();
    else
        return END;
}

void Lexer::advance() {
    ++_end;
}

void Lexer::forward() {
    _begin = _end;
}

void Lexer::rewind() {
    _end = _lastAccept;
}

void Lexer::accept() {
    character += _end - _lastAccept;
    _lastAccept = _end;
}

#ifndef BISON

const int Lexer::END = 1;
const int Lexer::IGNORE = -1;
const int Lexer::ERROR = -2;

#else

const int Lexer::ERROR = -2;
const int Lexer::IGNORE = -1;
const int Lexer::END = 0;

#endif

} // end namespace Runtime

// End Lexer.cpp - Standard Lexer runtime
