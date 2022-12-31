//
//	runtime/parser/Tables.h
//
//  Property and Copyright © 2016 Aaron Nathaniel Gray
//

#pragma once

#include <limits>
#include <algorithm>

template <typename T>
struct State {
    enum Action { SHIFT, REDUCE, ACCEPT, LOOKAHEAD, ERROR };
    State(Action action, T state) {
        switch(action) {
        case SHIFT:
            value = state;
            break;
        case REDUCE:
            std::numeric_limits<T>::max();
        case ACCEPT:
            value = 0;
        case LOOKAHEAD:
            value = -state;
            break;
        case ERROR:
            value = std::numeric_limits<T>::min();
        break;
        }
    }
    bool isShift() { return value > 0 && value < std::numeric_limits<T>::max(); }
    bool isReduce() { return value == std::numeric_limits<T>::max(); }
    bool isAccept() { return value == 0; }
    bool isLookahead() { return value < 0 && value > std::numeric_limits<T>::min(); }
    bool isError() { return value == std::numeric_limits<T>::min(); }

    size_t getState() { return std::abs(state); }
    T value;
};

// End runtime/parser/Tables.h
