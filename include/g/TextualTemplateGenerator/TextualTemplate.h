//
//  g/TextualTemplateGenerator/TextualTemplate.h
//
//  Property and Copyright (c) 2016 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include "nonstd/vector.h"

namespace G {
namespace TextualTemplateGenerator {

class TextualTemplate {
public:
	TextualTemplate() {}
	struct Node {
		virtual std::string __getType() = 0;
		virtual std::string __getValue() = 0;
		virtual void check(std::string type) {
			if (__getType() != type)
				std::cout << "Found " << __getType() << " = " << __getValue() << " expecting " << type << std::endl;
		}
	};

	struct Literal : public Node {
		Literal() {}
		virtual std::string getName() const = 0;
		virtual std::string getValue() const = 0;
		virtual std::string toString() const = 0;
	};

	struct Identifier : public Literal {
		Identifier() {}
		Identifier(std::string value) : value(value) {}
		virtual std::string getName() const { return "Identifier"; }
		virtual std::string getValue() const { return value; }

		virtual std::string __getType() { return "Identifier"; }
		virtual std::string __getValue() { return value; }

		operator std::string() const { return value; }
		virtual std::string toString() const { return value; }

		friend bool operator < (const Identifier& lhs, const Identifier& rhs) { return lhs.value < rhs.value; }

	protected:
		std::string value;
	};

	struct StringLiteral : public Literal {
		StringLiteral(std::string value) : value(value) {}
		virtual std::string getName() const { return "Literal"; }
		std::string getValue() const { return value; }

		virtual std::string __getType() { return "Literal"; }
		virtual std::string __getValue() { return value; }

		StringLiteral operator = (const std::string v) { value = v; return *this; }

		operator std::string() const { return value; }
		virtual std::string toString() const { return value; }

		friend bool operator < (const StringLiteral& lhs, const StringLiteral& rhs) { return lhs.value < rhs.value; }

	protected:
		std::string value;
	};

	struct QualifiedName {
		QualifiedName() {}
		~QualifiedName() {
			for (auto identifer : name)
				delete identifer;
		}
		void append(Identifier* identifier) {
			name.push_back(identifier);
		}
		std::string toString() const {
			std::stringstream ss;
			for (auto identifier = name.cbegin(); identifier != name.cend(); ++identifier) {
				ss << (*identifier)->toString();
				if (identifier != name.clast())
					ss << "::";
			}
			return ss.str();
		}
		operator std::string() {
			return toString();
		}
		virtual void Output(std::ostream &os) const {
			os << toString();
		}
		vector<Identifier*> name;
	};

	struct Name : public Identifier {};
	struct Type : public QualifiedName {};

	struct Argument {
		Argument(Identifier* name, QualifiedName* type) : name(name), type(type) {}
		Argument(Identifier* name, Type* type) : name(name), type(type) {}
		std::string toString() const;
		Identifier* name;
		QualifiedName* type;
	};
	struct Arguments {
		Arguments(vector<Argument*>* arguments) : arguments(arguments) {}
		Arguments(Arguments* arguments) : arguments(arguments->arguments) {}
		Arguments() : arguments(new vector<Argument*>()) {}
		void append(Argument* argument) { arguments->append(argument); }
		std::string toString() const;
		vector<Argument*>* arguments;
	};

	struct Code : public Type {
		Code(std::string code) : code(code) {}
		Code(Code* code) : code(code->code) {}

		virtual std::string __getType() { return "Code"; }
		virtual std::string __getValue() { return code; }

		virtual std::string Output() const = 0;

		std::string code;
	};

	struct CodeBlock : public Code {
		CodeBlock(Code* code) : Code(code) {}
		CodeBlock(std::string code) : Code(code) {}

		virtual std::string __getType() { return "CodeBlock"; }

		virtual std::string Output() const;
	};

	struct ActionCode : public Code {
		ActionCode(Code* code) : Code(code) {}
		ActionCode(std::string action) : Code(action) {}

		virtual std::string __getType() { return "ActionCode"; }

		virtual std::string Output() const;
	};

	struct Parameter : public Code {
		Parameter(Code* code) : Code(code) {}
		Parameter(std::string parameter) : Code(parameter) {}

		virtual std::string __getType() { return "Parameter"; }

		virtual std::string Output() const;
	};

	struct Block {
		Block() {};
		void append(Code* code) { list.append(code); }
		virtual std::string Output() const;
		vector<Code*> list;
	};

	struct Template {
		Template() : name(nullptr) {}
		Template(QualifiedName* name) : name(name) {}
		virtual std::string OutputHXX() const = 0;
		virtual std::string OutputCXX() const = 0;
		QualifiedName* name;
	};

	struct ClassTemplate : public Template {
		ClassTemplate() : Template(), arguments(nullptr), block(nullptr) {}
		ClassTemplate(QualifiedName* name) : Template(name), arguments(nullptr), block(nullptr) {}
		ClassTemplate(QualifiedName* name, Block* block) : Template(name), arguments(nullptr), block(block) {}
		ClassTemplate(QualifiedName* name, Arguments* arguments, Block* block) : Template(name), arguments(arguments), block(block) {}
		virtual std::string OutputHXX() const;
		virtual std::string OutputCXX() const;
		Arguments* arguments;
		Block* block;
	};

	struct FunctionTemplate : public Template {
		FunctionTemplate() : Template(), arguments(nullptr), block(nullptr) {}
		FunctionTemplate(QualifiedName* name) : Template(name), arguments(nullptr), block(nullptr) {}
		FunctionTemplate(QualifiedName* name, Block* block) : Template(name), arguments(nullptr), block(block) {}
		FunctionTemplate(QualifiedName* name, Arguments* arguments, Block* block) : Template(name), arguments(arguments), block(block) {}
		virtual std::string OutputHXX() const;
		virtual std::string OutputCXX() const;
		Arguments* arguments;
		Block* block;
	};

	struct Templates {
		Templates(vector<Template*>* templates) : templates(templates) {}
		Templates() : templates(new vector<Template*>()) {}
		void append(Template* _template) { templates->append(_template); }
		virtual std::string OutputHXX() const;
		virtual std::string OutputCXX() const;
		vector<Template*>* templates;
	};

	struct Module {
		Module(Identifier* name) : name(name) {}
		Module(Identifier* name, Templates* templates) : name(name), templates(templates) {}
		virtual std::string OutputHXX() const;
		virtual std::string OutputCXX() const;
		Identifier* name;
		Templates* templates;
	};

	//
	//  Factory Functions
	//

	Module* newModule(Identifier* name) {
		return new Module(name);
	}
	Module* newModule(Identifier* name, Templates* templates) {
		return new Module(name, templates);
	}

	Type* newType() {
		return new Type();
	}

	Templates* newTemplates() {
		return new Templates();
	}

	Template* newClassTemplate(QualifiedName* name, Arguments* arguments, Block* block) {
		return new ClassTemplate(name, arguments, block);
	}
	Template* newClassTemplate(QualifiedName* name, Block* block) {
		return new ClassTemplate(name, block);
	}

	Template* newFunctionTemplate(QualifiedName* name, Arguments* arguments, Block* block) {
		return new FunctionTemplate(name, arguments, block);
	}
	Template* newFunctionTemplate(QualifiedName* name, Block* block) {
		return new FunctionTemplate(name, block);
	}

	Arguments* newArguments(Arguments* arguments) {
		return new Arguments(arguments);
	}

	Arguments* newArguments() {
		return new Arguments();
	}

	Argument* newArgument(Identifier* name, QualifiedName* type) {
		return new Argument(name, type);
	}
	Argument* newArgument(Identifier* name, Type* type) {
		return new Argument(name, type);
	}

	Block* newBlock() {
		return new Block();
	}

	Code* newCodeBlock(Code* code) {
		return new CodeBlock(code);
	}
	Code* newCodeBlock(std::string code) {
		return new CodeBlock(code);
	}

	Code* newActionCode(Code* code) {
		return new ActionCode(code);
	}
	Code* newActionCode(std::string code) {
		return new ActionCode(code);
	}

	Code* newParameter(Code* code) {
		return new Parameter(code);
	}
	Code* newParameter(std::string code) {
		return new Parameter(code);
	}

	Identifier* newIdentifier(std::string name) const { return new Identifier(name); }
	StringLiteral* newStringLiteral(std::string name) const { return new StringLiteral(name); }

	Module* module;

	std::string OutputHXX() const;
	std::string OutputCXX() const;
};

} // end namespace TextualTemplateGenerator
} // end namespace G

// End g/TextualTemplateGenerator/TextualTemplate.h
