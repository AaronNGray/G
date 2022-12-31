//
//  runtime/Pairs.h
//
//  Copyright (c) 2015-2016 Aaron Nathaniel Gray under the MIT License
//

#pragma once

#ifndef __RUNTIME__PAIRS_H__
#define __RUNTIME__PAIRS_H__

#include <initializer_list>

namespace Runtime {

typedef unsigned short Input;

template<typename Value>
struct Pair {
    Input input;
    Value state;
};

template<typename Value>
struct Pairs {
    Pairs(std::initializer_list<Pair<Value>> il) : pairs(il.size()) {
        pair = new Pair<Value>[pairs];
        Pair<Value>* p = pair;
        for (auto ili : il)
            *p++ = ili;
    }

    Value lookup(Input input) {
        Pair<Value>* pair = this->pair;
        for (size_t pairs = this->pairs; pairs > 0; --pairs) {
            if (pair->input == input)
                return pair->state;
            ++pair;
        };
        return Value();
    }

    //private:
    size_t pairs;
    Pair<Value>* pair;
};

} // End namespace Runtime

#endif // __RUNTIME__PAIRS_H__
