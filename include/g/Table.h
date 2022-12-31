//
//  g/Table.h - Table class
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/vector.h"
#include "nonstd/Utils.h"
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cassert>

// C++ Hack as no specialization on member functions

template<typename T>
std::string AsString(T value) {
	std::string s = std::to_string(value);
	return s;
}

template<typename T>
std::string AsCXXString(T value) {
	std::string s = std::to_string(value);
	return s;
}

template <typename Element = unsigned int, typename Value = unsigned int>
class FixedArray {
public:
	FixedArray(Element size) : _size(size) {
		assert(size > 0);
		data = new Value[size()];
		clear();
	}
	~FixedArray() { delete data; }

	void clear() {
		for (size_t i = 0; i < size(); ++i)
			data[i] = 0;
	}

	Value& operator [] (Element element) {
		assert(element >= 0 && element < size());
		if (element >= size())
			throw;
		return data[element];
	}
	const Value& operator [] (Element element) const {
		assert(element >= 0 && element < size());
		if (element >= size())
			throw;
		return data[element];
	}
	void Generate(std::ostream &os);

	typedef Value* iterator;
	typedef const Value* const_iterator;

	iterator begin() { return data; }
	iterator end() { return data + _size; }
	const_iterator begin() const { return data; }
	const_iterator end() const { return data + _size; }
	const_iterator cbegin() const { return data; }
	const_iterator cend() const { return data + _size; }

    size_t size() const { return _size; }

    std::string Output(size_t columns) const;

private:
	Element _size;
	Value *data;
};

template <typename Element, typename Value>
std::string FixedArray<Element, Value>::Output(size_t columns) const {
    std::stringstream ss;

    for (size_t column = 0; column < columns; ++column)
        ss << std::setw(8) << (*this)[column];

    return ss.str();
}

template <typename Element = unsigned int, typename Value = unsigned int>
class PairedArray {
public:
	PairedArray() {}
	void add(Element element, Value value) {
		pairs[element] = value;
	}
	Value& operator [] (const Element element) {
		if (pairs.find(element) == pairs.cend())
			pairs[element] = Value();
		return pairs.find(element)->second;
	}
	const Value operator [] (const Element element) const {
		return lookup(element);
	}
    Value lookup(Element element) const {
        auto i = pairs.find(element);
        if (i == pairs.cend())
            return Value();
        else
            return i->second;
    }

	typedef typename std::map<Element, Value>::iterator iterator;
	typedef typename std::map<Element, Value>::const_iterator const_iterator;

	iterator begin() { return pairs.begin(); }
	iterator end() { return pairs.end(); }
	const_iterator begin() const { return pairs.begin(); }
	const_iterator end() const { return pairs.end(); }
	const_iterator cbegin() const { return pairs.cbegin(); }
	const_iterator cend() const { return pairs.cend(); }

	size_t size() const { return pairs.size(); }

    std::string Output(size_t columns) const;

    friend bool operator == (const PairedArray& lhs, const PairedArray& rhs) {
        if (lhs.size() != rhs.size())
            return false;

        for (auto l = lhs.cbegin(), r = rhs.cbegin(); l != lhs.cend(); ++l, ++r)
            if (l->first != r->first || l->second != r->second)
                return false;
        return true;
    }
private:
	std::map<Element, Value> pairs;
};

template <typename Element, typename Value>
std::string PairedArray<Element, Value>::Output(size_t columns) const {
    std::stringstream ss;

    for (size_t column = 0; column < columns; ++column)
        ss << std::setw(8) << (*this)[column];

    return ss.str();
}

template <typename ELEMENT, typename VALUE, ELEMENT BASE = 0, class ROW = PairedArray<ELEMENT, VALUE>>
class Table {
public:
    typedef ELEMENT Element;
    typedef VALUE Value;
    typedef ROW Row;

    Table() = delete;
    Table(Element columns) : columns(columns), Base(BASE) {}
    ~Table() {}


    typedef typename vector<Row>::iterator iterator;
    typedef typename vector<Row>::const_iterator const_iterator;

    iterator begin() { return rows.begin(); }
    iterator end() { return rows.end(); }
    const_iterator begin() const { return rows.begin(); }
    const_iterator end() const { return rows.end(); }
    const_iterator cbegin() const { return rows.begin(); }
    const_iterator cend() const { return rows.end(); }

    size_t size() const { return rows.size() * columns * sizeof(Element); }
    void resize(size_t size) { rows.resize(size); }

    size_t add(Row& row) {
        return rows.add(row);
    }
    size_t index_of(const Row& row) {
        return rows.index_of(row);
    }

    virtual Row& operator [] (Element state) {
        assert(state >= 0);
        return rows[state];
    }
    virtual const Row operator [] (Element state) const {
        assert(state >= 0);
        return rows[state];
    }

    short lookup(size_t state, size_t input) const {
        assert(state < rows.size());
        return rows[state].lookup(input);
    }

    virtual Element getNumberOfRows() const { return rows.size(); }
    virtual Element getNumberOfColumns() const { return columns; }
    Element base() const { return Base; }

    void Generate(std::ostream &os, std::string className);

    //Table RowCompress();

    virtual std::string toString() const;
    virtual std::string OutputRow(size_t row, size_t start, size_t columns) const;
    virtual std::string OutputRowCXX(size_t row, size_t start, size_t columns) const;

    virtual std::string OutputPairsHXX(std::string className, std::string name, std::string type) const;
    virtual std::string OutputPairsCXX(std::string className, std::string name, std::string type) const;

    template <typename _ELEMENT, typename _VALUE, _ELEMENT _BASE, class _ROW>
	friend bool compare(const Table<_ELEMENT, _VALUE, _BASE, _ROW>* lhs, const Table<_ELEMENT, _VALUE, _BASE, _ROW>* rhs); // VS2017 BUG
	//friend bool compare(Table* lhs, Table* rhs);

protected:
    vector<Row, BASE> rows;
    Element columns;
    Element Base;
};

template <typename Element, typename Value, Element Base, class Row>
std::string Table<Element, Value, Base, Row>::OutputRow(size_t row, size_t start, size_t columns) const {
    std::stringstream ss;

    for (size_t column = start; column < columns + start; ++column) {
        std::string s = AsCXXString((*this)[row][column]);
        ss << std::setw(8) << s;
    }

    return ss.str();
}

template <typename Element, typename Value, Element Base, class Row>
std::string Table<Element, Value, Base, Row>::OutputRowCXX(size_t row, size_t start, size_t columns) const {
    std::stringstream ss;

    for (size_t column = start; column < columns + start; ++column) {
        std::string s = AsCXXString((*this)[row][column]);
        ss << std::setw(8) << s;
    }

    return ss.str();
}


template <typename Element, typename Value, Element Base, class Row>
std::string Table<Element, Value, Base, Row>::toString() const {
    std::stringstream ss;

    for (size_t c = 0; c < getNumberOfColumns(); ++c)
        ss << "\t" << c;

    ss << nonstd::endl;

    for (Element r = Base; r < getNumberOfRows() + Base; ++r) {
        ss << r;
        for (Element c = 0; c < getNumberOfColumns(); ++c) {
            ss << "\t" << AsString((*this)[r][c]) << ((c != getNumberOfColumns() - 1) ? "," : "");
        }
        ss << nonstd::endl;
    }
    return ss.str();
}


template <typename Element, typename Value, Element Base, class Row>
std::string Table<Element, Value, Base, Row>::OutputPairsHXX(std::string className, std::string name, std::string type) const {
    std::stringstream ss;
    ss << "\t" << "static Pairs<" << type << "> " << name << "_states[" << getNumberOfRows() << "];" << nonstd::endl;
    return ss.str();
}

template <typename Element, typename Value, Element Base, class Row>
std::string Table<Element, Value, Base, Row>::OutputPairsCXX(std::string className, std::string name, std::string type) const {
    std::stringstream ss;

    ss << "Pairs<" << type << "> " << className << "::" << name << "_states[" << getNumberOfRows() << "] = { " << nonstd::endl;
    for (Element r = Base; r <= getNumberOfRows(); ++r) {
        auto row = (*this)[r];
        auto size = row.size();
        ss << "\t/* " << r << " */";
        ss << "\t{ ";
        for (auto pair : row) {
            ss << "{" << pair.first << ", " << AsCXXString(pair.second) << "}";
            if (--size)
                ss << ", ";
        }
        if (r < getNumberOfRows())
            ss << "},";
        else
            ss << "}";
        ss << nonstd::endl;
    }
    ss << "};" << nonstd::endl;

    return ss.str();
}
/*
template <typename Element = unsigned int, typename Value = unsigned int, Element Base = 0, class Row = PairedArray<Element, Value>>
bool compare(const Table<Element, Value, Base, Row>* lhs, const Table<Element, Value, Base, Row>* rhs) {
	return true;
}
*/
template <typename Element = unsigned int, typename Value = unsigned int, Element Base = 0, class Row = PairedArray<Element, Value>>
bool compare(Table<Element, Value, Base, Row>* lhs, Table<Element, Value, Base, Row>* rhs) {
	return true;
}

template <typename Element = size_t, typename Value = size_t, Element Base = 0, class Row = PairedArray<Element, Value>>
class CompressedTable : public Table<Element, Value, Base, Row> {
public:
    CompressedTable(Table<Element, Value, Base, Row>* table);
/*
    virtual Row& operator [] (Element state) {
        assert(state >= 0);
        signed int row = states[state];
        if (row != -1)
            return rows[row];
        else
            return Row();
    }
*/
    virtual const Row operator [] (Element state) const {
        assert(state >= 0);
        signed int row = states[state];
        if (row != -1)
            return Table<Element, Value, Base, Row>::rows[row];
        else
            return Row();
    }

    virtual Element getNumberOfRows() const { return states.size(); }
    Element getNumberOfCompressedRows() const { return Table<Element, Value, Base, Row>::getNumberOfRows(); }

    virtual std::string toString() const;

    virtual std::string OutputRow(size_t row, size_t start, size_t columns) const;
    virtual std::string OutputRowCXX(size_t row, size_t start, size_t columns) const;

    virtual std::string OutputPairsHXX(std::string className, std::string name, std::string type) const;
    virtual std::string OutputPairsCXX(std::string className, std::string name, std::string type) const;
protected:
    vector<signed int, Base> states;
};

template <typename Element, typename Value, Element Base, class Row>
CompressedTable<Element, Value, Base, Row>::CompressedTable(Table<Element, Value, Base, Row>* table) : Table<Element, Value, Base, Row>(table->getNumberOfColumns()) {
    states.resize(table->getNumberOfRows());
    for (typename Table<Element, Value, Base, Row>::Element r = Base; r < table->getNumberOfRows() + Base; ++r) {
        auto row = (*table)[r];

        if (row.size() == 0)
            states[r] = -1;
        else {
            signed int i = Table<Element, Value, Base, Row>::index_of(row);
            if (i == -1)
                states[r] = Table<Element, Value, Base, Row>::add(row);
            else
                states[r] = i;
        }
    }
}

template <typename Element, typename Value, Element Base, class Row>
std::string CompressedTable<Element, Value, Base, Row>::OutputRow(size_t row, size_t start, size_t columns) const {
    std::stringstream ss;

    for (size_t column = 0; column < columns; ++column) {
        std::string s = AsString((*this)[row][column + start]);
        ss << std::setw(8) << s;
    }

    return ss.str();
}

template <typename Element, typename Value, Element Base, class Row>
std::string CompressedTable<Element, Value, Base, Row>::OutputRowCXX(size_t row, size_t start, size_t columns) const {
    std::stringstream ss;

    for (size_t column = start; column < columns + start; ++column) {
        Value value = (*this)[row][column];
        if (value != Value()) {
            std::string s = AsCXXString(value);
            ss << std::setw(8) << s;
        }
    }

    return ss.str();
}

template <typename Element, typename Value, Element Base, class Row>
std::string CompressedTable<Element, Value, Base, Row>::OutputPairsHXX(std::string className, std::string name, std::string type) const {
    std::stringstream ss;

    for (Element r = Base; r < getNumberOfCompressedRows() + Base; ++r) {
        auto row = (*this)[r];
        ss << "\t" << "static Pairs<" << type << "> " << name << "_row_" << r << ";" << nonstd::endl;
    }
    ss << "\t" << "static Pairs<" << type << ">* " << name << "_states[" << states.size() << "];" << nonstd::endl;

    return ss.str();
}

template <typename Element, typename Value, Element Base, class Row>
std::string CompressedTable<Element, Value, Base, Row>::OutputPairsCXX(std::string className, std::string name, std::string type) const {
    std::stringstream ss;

    for (Element r = Base; r < getNumberOfCompressedRows() + Base; ++r) {
        auto row = Table<Element, Value, Base, Row>::rows[r];
        ss << "Pairs<" << type << "> " << className << "::" << name << "_row_" << r << " = { ";
		for (auto pair = row.begin(); pair != row.end(); ++pair) {
            if (pair->second != Value()) {
                ss << "{" << pair->first << ", " << AsCXXString(pair->second) << "}";
				auto next = pair;
                if (++next != row.end())	// TODO: solve properly
                    ss << ", ";
            }
        }
        ss << " };" << nonstd::endl;
    }
    ss << "Pairs<" << type << ">* " << className << "::" << name << "_states[" << states.size() << "] = { " << nonstd::endl;
    for (size_t state = Base; state < states.size() + Base; ++state) {
        if (states[state] != -1)
            ss << "\t" << "&" << name << "_row_" << states[state];
        else
            ss << "\t" << "nullptr";
        if (state < states.size())
            ss << ",";
        ss << "\t\t//" << state << nonstd::endl;
    }
    ss << "};" << nonstd::endl;

    return ss.str();
}

template <typename Element, typename Value, Element Base, class Row>
std::string CompressedTable<Element, Value, Base, Row>::toString() const {
    std::stringstream ss;

    for (size_t c = 0; c < Table<Element, Value, Base, Row>::getNumberOfColumns(); ++c)
        ss << "\t" << c;

    ss << nonstd::endl;

    for (Element r = Base; r < getNumberOfRows() + Base; ++r) {
        ss << r;
        for (Element c = 0; c < Table<Element, Value, Base, Row>::getNumberOfColumns(); ++c) {
            ss << "\t" << AsString((*this)[states[r]][c]) << ((c != Table<Element, Value, Base, Row>::getNumberOfColumns() - 1) ? "," : "");
        }
        ss << nonstd::endl;
    }
    return ss.str();
}

// End g/Table.h
