//
//	lib/deque.h
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

#pragma once
#ifndef __LIB_DEQUE_h_
#define __LIB_DEQUE_h_

#include <deque>

template <class T>
class deque : public std::deque<T> {
public:
    deque() : std::deque<T>() {}
    deque(size_t size) : std::deque<T>(size) {}
    deque(set<T> set) : std::deque<T>(set.size()) {
        std::copy(set.begin(), set.end(), std::deque<T>::begin());
    }
    T pop_front() {
        T t = std::deque<T>::front();
        std::deque<T>::pop_front();
        return t;
    }
    T& find(const T& v) {
        auto si = std::find(std::deque<T>::cbegin(), std::deque<T>::cend(), v) != std::deque<T>::cend();
        if (si != std::deque<T>::cend())
            return *si;
        else
            return nullptr;
    }
    bool is_member(const T& t);
};

template <class T>
bool deque<T>::is_member(const T& item) {
	return (std::find(std::deque<T>::cbegin(), std::deque<T>::cend(), item) != std::deque<T>::cend());
}

template <class T>
class deque<T*> : public std::deque<T*> {
public:
    deque() : std::deque<T*>() {}
    void insert(T* v) {
        if (!is_member(v))
            push_back(v);
    }
    T* pop_front() {
        T* t = std::deque<T*>::front();
        std::deque<T*>::pop_front();
        return t;
    }

    typedef typename std::deque<T*>::iterator iterator;
    typedef typename std::deque<T*>::const_iterator const_iterator;


    iterator begin() {
        return std::deque<T*>::begin();
    }
    iterator end() {
        return std::deque<T*>::end();
    }

    const_iterator cbegin() const {
        return std::deque<T*>::cbegin();
    }
    const_iterator cend() const {
        return std::deque<T*>::cend();
    }


    bool is_member(T* v) {
        return std::find_if(cbegin(), cend(), [v](T* tp) { return *tp == *v; }) != cend();
    }
    //T& operator [] (size_t index)
};

#endif // __LIB_DEQUE_h_
