//
//  g/ParserGenerator/Machine.h - Parser Algorithm Factory Interface
//
//  Property and Copyright (c) 2017-2022 Aaron Nathaniel Gray
//

#pragma once

#include <map>
#include <string>
#include "g/Grammar/ContextFreeGrammar.h"
#include "g/ParserGenerator/Machine.h"

namespace G {

using namespace Grammar;

//
//  Usage:
//      ParserGeneratorFactory.Register<LR1>();
//

class FactoryMethod {
public:
	FactoryMethod(Machine* (*create)(ContextFreeGrammar* grammar, bool rowCompressed, unsigned debug)) : create(create) {}
	Machine* Create(ContextFreeGrammar* grammar, bool rowCompressed, unsigned debug) {
		return (*create)(grammar, rowCompressed, debug);
	}
	Machine* (*create)(ContextFreeGrammar* grammar, bool rowCompressed, unsigned debug);
};

class Factory {
public:
	template <class T>
	void Register() {
		methods[T::Name] = new FactoryMethod(T::Create);
	}
	FactoryMethod* getFactoryMethod(std::string type) {
		return methods[type];
	}
	std::map<std::string, FactoryMethod*> methods;
};

} // end namespace G

//  g/ParserGenerator/Machine.h - Parser Algorithm Factory Interface
