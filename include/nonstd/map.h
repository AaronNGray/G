#pragma once

#include <map>

template <class Key, class T, class Compare = std::less<Key>>
class map : public std::map<Key, T, Compare> {
public:
	const T& operator[](Key key) {
		typename std::map<Key, T, Compare>::iterator it;
		if ((it = std::map<Key, T, Compare>::find(key)) != std::map<Key, T, Compare>::end())
			return it->second;
		else
			return T();
	}
/*
	T& operator[](Key key) {
		return std::map<Key, T>::operator[](key);
	}
*/
};
/*
template <class Key, class T>
class map<Key, T*> : public std::map<Key, T*> {
public:
	const T* operator[](Key key) const {
		iterator it;
		if ((it = find(key)) != end())
			return it->second;
		else
			return nullptr;
	}
	T*& operator[](Key key) {
		return std::map<Key, T*>::operator[](key);
	}
};
*/

// TODO: is this really needed ?
