//
//  runtime/Buffer.h
//
//  Copyright (c) 2015-2016 Aaron Nathaniel Gray under the MIT License
//

#pragma once

#include <string>
#include "nonstd/File.h"

namespace Runtime {

    class Buffer {
    public:
        Buffer(std::string s) : _begin((iterator)s.c_str()), _end(_begin + s.size()), length(s.size()) {}

        template <class F>
        Buffer(File<F> file) {
            length = file.size();
            _begin = new char[length];
            file.read(_begin);
            _end = _begin + length;
        }

        typedef char* iterator;
        typedef const char* const_iterator;
        const_iterator cbegin() const { return _begin; }
        const_iterator cend() const { return _end; }
        iterator begin() const { return _begin; }
        iterator end() const { return _end; }
        size_t size() { return _end - _begin; }

    protected:
        char *_begin;
        char *_end;

        size_t length;
    };

} // End namespace Runtime

// End runtime/Buffer.h
