//
//  ColumnMap.h - DFA input Comumn Map
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include "g/LexicalAnalyserGenerator/EquivalenceClasses.h"
#include "nonstd/DefaultValues.h"

namespace G {
namespace LexicalAnalyserGenerator {

//
// class StaticArray<Type,Size> - mimics a C array
//

template <class Type, size_t Size, Type DefaultValue = nonstd::traits<Type>::DefaultValue>
class StaticArray {
public:
    StaticArray() {
        for (auto i = begin(); i != end(); ++i)
            *i = DefaultValue;
    }
	Type& operator [] (size_t index) {
		if (index >= 0 && index < Size)
			return array[index];
		else
			throw;
	}
	const Type& operator [] (size_t index) const {
		if (index >= 0 && index < Size)
			return array[index];
		else
			throw;
	}
	size_t size() const { return Size; }
    typedef Type* iterator;
    typedef const Type* const_iterator;
    iterator begin() { return array; }
    iterator end() { return array + Size; }
    const_iterator cbegin() { return array; }
    const_iterator cend() { return array + Size; }

	template <class TYPE, size_t SIZE, TYPE DEFAULTVALUE = nonstd::traits<TYPE>::DefaultValue>
	friend bool compare(const StaticArray<TYPE, SIZE, DEFAULTVALUE>* lhs, const StaticArray<TYPE, SIZE, DEFAULTVALUE>* rhs) {
		if (lhs->size() != rhs->size())
			return false;
		for (size_t index = 0; index < lhs->size(); ++index)
			if ((*lhs)[index] != (*rhs)[index])
				return false;
		return true;
	}

private:
    Type array[Size];
};

class ColumnMap : public StaticArray<signed int, 256, -1> {
public:
    ColumnMap(EquivalenceClasses& equivalenceClasses, bool compressed = true);

	void OutputColumnMapCXX(std::ostream &os, std::string className);
	void OutputColumnMap(std::ostream &os);

    //StaticArray<signed int, 256, -1> result;
    //unsigned int result[256];
};

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End ColumnMap.h - DFA input Comumn Map
