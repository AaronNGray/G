//
//	lib/set.h - set class header
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

#pragma once

#include <vector>
#include <set>

template <class T>
class set : public std::vector<T> {
public:
    set() : std::vector<T>() {}
    set(std::initializer_list<T> ts) : std::vector<T>(ts) {}
    void insert(T& v) {
        if (std::find(std::vector<T>::cbegin(), std::vector<T>::cend(), v) == std::vector<T>::cend())
            std::vector<T>::push_back(v);
    }
    bool is_member(T v) { return std::find(std::vector<T>::cbegin(), std::vector<T>::cend(), v) != std::vector<T>::cend(); }

    //T& operator [] (size_t index)
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    iterator last() { return std::vector<T>::end() - 1; }
    const_iterator clast() const { return std::vector<T>::end() - 1; }
};

template <class T>
class set<T*> : public std::vector<T*> {
public:
    set() : std::vector<T*>() {}
    set(std::initializer_list<T> ts) : std::vector<T>(ts) {}
    void insert(T* v) {
        if (!is_member(v))
            std::vector<T*>::push_back(v);
    }
    bool is_member(T* v) {
        return std::find_if(std::vector<T*>::cbegin(), std::vector<T*>::cend(), [v](T* tp) { return *tp == *v; }) != std::vector<T*>::cend();
    }

//    T* operator [] (size_t index) { return nullptr;  }
    typedef typename std::vector<T*>::iterator iterator;
    typedef typename std::vector<T*>::const_iterator const_iterator;

    iterator last() { return std::vector<T*>::end() - 1; }
    const_iterator clast() const { return std::vector<T*>::end() - 1; }
};
