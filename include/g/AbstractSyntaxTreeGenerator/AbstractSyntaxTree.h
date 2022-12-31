//
//  g/AbstractSyntaxTreeGenerator/AbstractSyntaxTree.h
//
//  Property and Copyright © 2016-2022 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include <iostream>
#include <cassert>
#include "nonstd/vector.h"

namespace G {
namespace AbstractSyntaxTreeGenerator {

class AbstractSyntaxTree {
public:
	AbstractSyntaxTree() {}

	struct __Type__ {
		virtual std::string getType() const = 0;
		virtual std::string getValue() const = 0;
		virtual void check(std::string type) {
			if (getType() != type)
				std::cout << "Found " << getType() << " = " << getValue() << " expecting " << type << std::endl;
		}
	};

	struct Literal : public __Type__ {
		Literal() {}
		virtual std::string getType() const = 0;
		virtual std::string getValue() const = 0;
		//        virtual std::string toString() const = 0;
	};

	struct Identifier : public Literal {
		Identifier() {}
		Identifier(std::string value) : value(value) {}
		virtual std::string getType() const { return "Identifier"; }
		virtual std::string getValue() const { return value; }

		operator std::string() const { return value; }
		//        virtual std::string toString() const { return value; }

		friend bool operator < (const Identifier& lhs, const Identifier& rhs) { return lhs.value < rhs.value; }

	protected:
		std::string value;
	};

	struct Code : public __Type__ {
		Code(std::string code) : code(code) {}

		virtual std::string getType() const { return "Code"; }
		virtual std::string getValue() const { return code; }

		std::string code;
	};
	struct Block : public __Type__ {
		Block(std::string code) : code(code) {}

		virtual std::string getType() const { return "Code"; }
		virtual std::string getValue() const { return ""; }

		std::string code;
	};

	struct Argument : public __Type__ {
		Argument(Identifier* name, Identifier* type) : name(name), type(type) {}
		virtual std::string getType() const { return "Argument"; }
		virtual std::string getValue() const { return ""; }

		Identifier* name;
		Identifier* type;
	};
	struct Arguments : public __Type__, public vector<Argument*> {
		virtual std::string getType() const { return "Arguments"; }
		virtual std::string getValue() const { return ""; }
	};

	struct Type : public __Type__ {
		Type(Identifier* name) : name(name), arguments(nullptr), block(nullptr) {}
		Type(Identifier* name, Block* block) : name(name), arguments(nullptr), block(block) {}
		Type(Identifier* name, Arguments* arguments) : name(name), arguments(arguments), block(nullptr) {}
		Type(Identifier* name, Arguments* arguments, Block* block) : name(name), arguments(arguments), block(block) {}

		virtual std::string getType() const { return "Type"; }
		virtual std::string getValue() const { return ""; }

		Identifier* name;
		Arguments* arguments;
		Block* block;
	};

	struct Types : public __Type__, public vector<Type*> {
		Types() {}

		virtual std::string getType() const { return "Argument"; }
		virtual std::string getValue() const { return ""; }
	};

	struct Datatype : public __Type__ {
		Datatype(Identifier* name, Types* types) : name(name), types(types) {}
		Datatype(Identifier* name, Arguments* arguments) : name(name), arguments(arguments) {}
		Datatype(Identifier* name, Block* block, Types* types) : name(name), block(block), types(types) {}
		Datatype(Identifier* name, Arguments* arguments, Types* types) : name(name), arguments(arguments), types(types) {}
		Datatype(Identifier* name, Block* block, Arguments* arguments, Types* types) : name(name), block(block), arguments(arguments), types(types) {}

		virtual std::string getType() const { return "Datatype"; }
		virtual std::string getValue() const { return ""; }

		Identifier* name;
		Block* block;
		Arguments* arguments;
		Types* types;
	};

	struct Declarations : public __Type__, public vector<Datatype*> {
		Declarations() {}
		Declarations(Datatype* production) {
			push_back(production);
		}
		Declarations(const std::initializer_list<Datatype*> productions) : vector<Datatype*>(productions) {}
		void addDeclaration(Datatype* datattype) {
			assert(datattype != nullptr);
			push_back(datattype);
		}

		virtual std::string getType() const { return "Declarations"; }
		virtual std::string getValue() const { return ""; }
	};

	struct Module : public __Type__ {
		Module(Identifier* name, Declarations* declarations) : name(name), declarations(declarations) {}

		virtual std::string getType() const { return "Module"; }
		virtual std::string getValue() const { return ""; }

		Identifier* name;
		Declarations* declarations;
	};

	struct Root : public __Type__ {
		Root() {}

		virtual std::string getType() const { return "Root"; }
		virtual std::string getValue() const { return ""; }
	};

	Module* newModule(Identifier* name, Declarations* declarations) { return new Module(name, declarations); }

	Declarations* newDeclarations() { return new Declarations; }

	Datatype* newDatatype(Identifier* name, Types* types) { return new Datatype(name, types); }
	Datatype* newDatatype(Identifier* name, Block* block, Types* types) { return new Datatype(name, block, types); }
	Datatype* newDatatype(Identifier* name, Arguments* arguments) { return new Datatype(name, arguments); }
	Datatype* newDatatype(Identifier* name, Arguments* arguments, Types* types) { return new Datatype(name, arguments, types); }
	Datatype* newDatatype(Identifier* name, Block* block, Arguments* arguments, Types* types) { return new Datatype(name, block, arguments, types); }

	Types* newTypes() { return new Types; }

	Type* newType(Identifier* name) { return new Type(name); }
	Type* newType(Identifier* name, Arguments* arguments) { return new Type(name, arguments); }
	Type* newType(Identifier* name, Block* block) { return new Type(name, block); }
	Type* newType(Identifier* name, Arguments* arguments, Block* block) { return new Type(name, arguments, block); }

	Identifier* newIdentifier(std::string name) const { return new Identifier(name); }
	Arguments* newArguments() {
		return new Arguments();
	}
	Argument* newArgument(Identifier* name, Identifier* type) {
		return new Argument(name, type);
	}
	Block* newBlock(std::string code) {
		return new Block(code);
	}
	Code* newCode(std::string code) {
		return new Code(code);
	}

	void OutputHXX(std::ostream& outout) {}
	void OutputCXX(std::ostream& outout) {}
};

} // end namespace AbstractSyntaxTreeGenerator
} // end namespace G

// End g/AbstractSyntaxTreeGenerator/AbstractSyntaxTree.h
