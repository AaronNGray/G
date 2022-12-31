//
//  Lexer.h - Standard Lexer runtime
//
//  Copyright (c) 2015-2016 Aaron Nathaniel Gray under the MIT License
//

#pragma once
#ifndef __PG__RUNTIME__STACK_H__
#define __PG__RUNTIME__STACK_H__

#include <cassert>
#include <sstream>

template <typename T>
class Stack {
public:
    Stack(size_t size = 1024) : _size(size) {
        stack = new T[_size];
        _top = 0;
        _base = 0;
    }
    ~Stack() {
        delete stack;
    }
    size_t size() const { return _size; }
    size_t elements() const { return _top; }
    void push(T t = T()) {
        stack[_top++] = t;
    }
    void pop(size_t n = 1) {
        if (_top - n < _base)
            throw;
        _top -= n;
    }
    T& operator [] (size_t index) {
        if (_top - index <= 0)
            throw;
        return stack[_top - index - 1];
    }
    T& top() {
        assert(_top > 0);
        return stack[_top - 1];
    }
    std::string toString() {
        std::stringstream ss;

        for (size_t element = _base; element < _top; ++element)
            ss << stack[element] << " ";
        ss << std::endl;

        return ss.str();
    }
protected:
    size_t _size;
    size_t _top;
    size_t _base;
    T* stack;
};

#endif // __PG__RUNTIME__STACK_H__
