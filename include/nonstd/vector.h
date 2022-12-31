//
//  vector.h - auto sizing 'vector' class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once
#ifndef __LG__LIB__VECTOR_H__
#define __LG__LIB__VECTOR_H__

#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <initializer_list>

template<typename T, size_t BASE = 0>
class vector : public std::vector<T> {
public:
    using std::vector<T>::vector;

    using typename std::vector<T>::iterator;
    using typename std::vector<T>::const_iterator;

    using std::vector<T>::begin;
    using std::vector<T>::end;
    using std::vector<T>::cbegin;
    using std::vector<T>::cend;

	iterator last() { return end() - 1; }
	const_iterator last() const { return end() - 1; }
    const_iterator clast() const { return cend() - 1; }

    using std::vector<T>::size;
    using std::vector<T>::capacity;

	size_t base() const {
		return BASE;
	}

#ifndef SHOW_REALLACATION
    using std::vector<T>::resize;
#else
    void resize(size_t _size) {
        size_t old_capacity = capacity();
        std::vector<T>::resize(_size);
        if (old_capacity != capacity())
            std::cerr << "Growing vector from " << old_capacity << " to " << capacity() << std::endl;
    }
#endif
    T& operator [] (size_t index) {
        if (index + 1 - BASE > size())
            resize(index + 1 - BASE);
        return std::vector<T>::operator[](index - BASE);
    }
    const T operator [] (size_t index) const {
        if (index + 1 - BASE <= size())
            return std::vector<T>::operator[](index - BASE);
        else
            return T();
    }
	signed index_of(const T& value) const {
		auto i = std::find(cbegin(), cend(), value);
		if (i != cend())
			return std::distance(cbegin(), i) + BASE;
		else
			return -1;
	}
	bool exists(const T& value) {
		return std::find(cbegin(), cend(), value) != cend();
	}
	size_t add(const T value = T()) {
        std::vector<T>::push_back(value);
        return size() - 1 + BASE;
    }
    size_t append(const T value = T()) {
        std::vector<T>::push_back(value);
        return size() - 1 + BASE;
    }
    std::string toString() const;
};

template<typename T, size_t Base>
std::string vector<T, Base>::toString() const {
    std::stringstream ss;

    for (size_t element = Base; element < size() + Base; ++element) {
        ss << (*this)[element];
        if (element < size() + Base)
            ss << std::string(",");
        ss << std::endl;
    }

    return ss.str();
}

#endif // __LG__LIB__VECTOR_H__

// End vector.h
