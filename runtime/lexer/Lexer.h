//
//  runtime/lexer/Lexer.h - Standard Lexer runtime
//
//  Copyright (c) 2015-2016 Aaron Nathaniel Gray under the MIT License
//

#pragma once

#include "runtime/Buffer.h"
#include <stack>

namespace Runtime {

class Lexer {
public:
    Lexer(std::string s, bool debug = false) : startState(1), line(1), character(1), buffer(s), _begin(buffer.begin()), _end(buffer.begin()), _lastAccept(), debug(debug) {}
    template <class F> Lexer(File<F> file, bool debug = false) : startState(1), line(1), character(1), filename(file.getFilename().toString()), buffer(file), _lastAccept(), debug(debug) {
        _begin = buffer.begin();
        _end = buffer.begin();
    }

    typedef signed int State;
    typedef signed char Input;

    static const int ERROR;
    static const int IGNORE;
    static const int END;

    int lex(State state = -1);
    virtual State next(State startState, Input input) = 0;
    virtual int getAcceptAction(State state) = 0;
    virtual int dispatch(State state) = 0;

    typedef char* iterator;
    typedef const char* const_iterator;
    const_iterator cbegin() const { return _begin; }
    const_iterator cend() const { return _end; }
    iterator begin() const { return _begin; }
    iterator end() const { return _end; }
    size_t size() { return _end - _begin; }

    std::string text() { return std::string(begin(), end()); }

    bool terminate();
    Input peek();
    void advance();
    void accept();
    void rewind();
    void forward();

    virtual unsigned getLineNumber() { return line; }
    virtual unsigned getCharacter() { return character; }
    virtual void newLine() { ++line; character = 1; }

    virtual void jump(State state) { startState = state; }
    virtual void push(State state) {
        stack.push(startState);
        startState = state;
    }
    virtual void pop() {
        startState = stack.top();
        stack.pop();
    }
    State getContext() { return startState; }

    State startState;
    bool debug;

protected:
    unsigned line;
    unsigned character;
    Buffer::iterator _begin;  // BUG: Set incorrectly on an IDENTIFIER
    Buffer::iterator _end;
    Buffer::iterator _lastAccept;
    Buffer buffer;
	std::string filename;
    std::stack<State> stack;
};

} // end namespace Runtime

// End runtime/lexer/Lexer.h - Standard Lexer runtime
