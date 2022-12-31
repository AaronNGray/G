//
//  lib/List.h
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

#pragma once
#ifndef __G__LIB__LIST__H__
#define __G__LIB__LIST__H__

#include <vector>

template <typename T>
struct List {
    List() {}
    List(List<T*>* list) : list(list) {}

    void append(T* v) {
        list->push_back(V);
    }
    std::vector<T*>* list;
};

#endif // __G__LIB__LIST__H__
