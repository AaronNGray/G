//
//  g/LexicalAnalyserGenerator/LexicalMachine.h - Lexical Analyser Machine
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/LexicalAnalyserGenerator/LexicalMachine.h"
#include "g/LexicalAnalyserGenerator/LexicalContext.h"
#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "g/LexicalAnalyserGenerator/ColumnMap.h"
#include "g/LexicalAnalyserGenerator/DFA.h"
#include "nonstd/File.h"
#include "nonstd/Utils.h"

#include <string>
#include <iomanip>

namespace G {
namespace LexicalAnalyserGenerator {

LexicalMachine::LexicalMachine(LexicalGenerator* lexicalGenerator, std::string name, std::string className, bool compress, bool debug) : equivalenceClasses(), lexicalGenerator(lexicalGenerator), name(name), className(className), compressed(compress), debug(debug) {
	rootTypeName = "void";
	baseClassName = "Runtime::Lexer";
	valueType = "int";
	returnType = "int";

	baseClass = baseClassName;
	compressed = true;
	diagnostics = false;

	startContextName = "INITIAL";

	columnMap = nullptr;
}

LexicalMachine::LexicalMachine(std::string name, bool debug, std::initializer_list<LexicalContext*> contexts, std::initializer_list<Action> actions, bool lineDirectives, bool compress)
	: equivalenceClasses(), lexicalGenerator(nullptr), name(name), debug(debug), contexts(contexts), actions(Actions(actions, lineDirectives)), dfa(nullptr), compressed(compress)
{
	if (className == "")
		className = name +  "Lexer";

	rootTypeName = "void";
	baseClassName = "Runtime::Lexer";
	valueType = "int";
	returnType = "int";

	baseClass = baseClassName;
	compressed = true;
	diagnostics = false;

	startContextName = "INITIAL";

	for (auto context : contexts)
		context->setMachine(this);

	columnMap = nullptr;
}

LexicalMachine::~LexicalMachine() {
    for (auto context : contexts)
        delete context;
	for (auto identifier : identifiers)
		delete identifier;
}

unsigned int LexicalMachine::addContext(LexicalContext* lexicalContext) {
    nameToContext[lexicalContext->getName()] = lexicalContext;
    contexts.push_back(lexicalContext);
    return contexts.size() - 1;
}

Action* LexicalMachine::addAction(const char* action, unsigned int line) {
    return actions.addAction(action, line);
}

void LexicalMachine::setStartContext(std::string name) {
    startContextName = name;
}

LexicalContext* LexicalMachine::getContext(std::string name) {
    return nameToContext[name];
}


void LexicalMachine::GenerateFollowPos() {
    for (auto context : contexts)
        context->GenerateFollowPos();
}

void LexicalMachine::AddEquivalenceSets() {
    for (auto context : contexts)
        context->addEquivalenceSets();
}

void LexicalMachine::GenerateEquivalenceClasses() {
    equivalenceClasses.Generate();
}

void LexicalMachine::GenerateColumnMap() {
    columnMap = new ColumnMap(equivalenceClasses);
 //   columnMap->Generate();
}

void LexicalMachine::Generate() {
    for (auto context : contexts)
        context->Index();

    for (auto context : contexts)
        context->GenerateFollowPos();

    for (auto context : contexts)
        context->addEquivalenceSets();

	//std::cout << "EquivalenceSets:" << std::endl;
    //std::cout << getEquivalenceSets().toString2() << nonstd::endl;

    GenerateEquivalenceClasses();

	//std::cout << "EquivalenceClasses:" << std::endl;
	//std::cout << getEquivalenceClasses().toString2() << nonstd::endl;

    if (false)
        for (auto context : contexts)
            context->diag();

    dfa = new DFA(getNumberOfInputs());

    for (auto context : contexts)
        context->Generate(dfa);

    //if (compressed)
        GenerateColumnMap();
}

void LexicalMachine::diag() {
    for (auto context : contexts)
        context->diag();
}


void LexicalMachine::OutputCXX(std::ostream &os, std::string className) {
    columnMap->OutputColumnMapCXX(os, className);
    dfa->OutputDFACXX(os, className);
    os << nonstd::endl;
    dfa->OutputAcceptCXX(os, className);
    os << nonstd::endl;
    actions.OutputActionsCXX(os, className, lexicalGenerator->getFilename(), returnType);
    actions.OutputActionDispatcherCXX(os, className);
    OutputCodeCXX(os, className);
    OutputContextCXX(os, className);
}

static std::string generateType(unsigned int values, bool _signed = false) {
    if (values < (_signed ? (unsigned int)128 : (unsigned int)254))
        return _signed ? "signed char" : "unsigned char";
    else
        return _signed ? "signed short" : "unsigned short";
}

void LexicalMachine::OutputH(std::ostream &os, std::string className) {
    os << "class " << className << " : public " << baseClass << " {" << nonstd::endl;

    os << "public:" << nonstd::endl;
    //os << "\t" << className << "(std::string s, " << valueType << "& currentValue, " << rootTypeName << "* root, bool debug = false) : " << baseClass << "(s, debug), currentValue(currentValue), root(root) {}" << nonstd::endl;
    os << "\t" << "template <class F>" << nonstd::endl;
    os << "\t" << className << "(File<F>& file, " << valueType << "& currentValue, " << rootTypeName << "* root, bool debug = false) : " << baseClass << "(file, debug), currentValue(currentValue), root(root) {}" << nonstd::endl;

    os << "\t" << "int lex(State state = -1) { return " << baseClass << "::lex(state); }" << nonstd::endl;

    OutputContextEnumH(os);
    os << "\t" << "static std::map<Context, std::string> ContextNames;" << nonstd::endl;
    os << "\t" << "static " << generateType(dfa->getNumberOfInputs()) << " " << "ec[128]" << ";" << nonstd::endl;
    os << "\t" << "static " << generateType(dfa->getNumberOfStates(), true) << " " << "dfa[" << dfa->getNumberOfStates() << "][" << dfa->getNumberOfInputs() << "]" << ";" << nonstd::endl;
    os << "\t" << "static " << generateType(dfa->getNumberOfStates(), true) << " " << "accept[" << dfa->getNumberOfStates() << "];" << nonstd::endl;
    os << nonstd::endl;

    actions.OutputActionsHXX(os, className, returnType);


    if (debug) {
        os << "\t" << "virtual void push(State state);" << nonstd::endl;
        os << "\t" << "virtual void pop();" << nonstd::endl;
        os << nonstd::endl;
    }
    os << nonstd::endl;
    os << "\t" << "virtual int dispatch(int action);" << nonstd::endl;
    os << "\t" << "State next(State state, Input input);" << nonstd::endl;
    os << "\t" << "int getAcceptAction(State state);" << nonstd::endl;

    os << nonstd::endl;
    os << "\t" << rootTypeName << "* root;" << nonstd::endl;
    os << "\t" << valueType << "& currentValue;" << nonstd::endl;
    os << "};" << nonstd::endl << nonstd::endl;
}

void LexicalMachine::OutputContextEnumH(std::ostream &os) {
    os << "\t" << "enum Context {" << nonstd::endl;
    for (auto context : contexts) {
        std::string name = context->getName() != "" ? context->getName() : "Start";
        os << "\t\t" << name << " = " << context->getStartState() << "," << nonstd::endl;
    }
    os << "\t\t" << "Last" << nonstd::endl;
    os << "\t};" << nonstd::endl;
}

void LexicalMachine::OutputContextCXX(std::ostream &os, std::string className) {
    os << "std::map<" << className << "::Context, std::string> " << className << "::ContextNames = {" << nonstd::endl;
    for (auto context = contexts.begin(); context != contexts.end(); ++context) {
        std::string name = (*context)->getName();
        name = name != "" ? name : "Start";
        os << "\t{ " << name << ", \"" << name << "\" }";
        if (context != contexts.last())
            os << ",";
        os << nonstd::endl;
    }
    os << "};" << nonstd::endl;
}

void LexicalMachine::OutputContexts(std::ostream &os) {
    for (auto context : contexts) {
        std::string name = context->getName() != "" ? context->getName() : "Start";
        os << name << ": " << context->getStartState() << nonstd::endl;
    }
}

void LexicalMachine::OutputCodeCXX(std::ostream &os, std::string className) {
    os << className << "::State " << className << "::next(State state, Input input) {" << nonstd::endl;
    os << "\t" << "if (state <= 0)" << nonstd::endl;
    os << "\t\t" << "return 0;" << nonstd::endl;
    os << "\t" << "if (input < 0 || input > 127)" << nonstd::endl;
    os << "\t\t" << "return 0;" << nonstd::endl;
    os << "\t" << "int column = ec[input];" << nonstd::endl;
    os << "\t" << "if (column == -1)" << nonstd::endl;
    os << "\t\t" << "return -1;" << nonstd::endl;
    os << "\t" << "return dfa[state - 1][column];" << nonstd::endl;
    os << "\t" << "}" << nonstd::endl;
    os << nonstd::endl;
    os << "int " << className << "::getAcceptAction(State state) {" << nonstd::endl;
    os << "\t" << "return accept[state];" << nonstd::endl;
    os << "}" << nonstd::endl;
    os << nonstd::endl;
/*
    if (debug) {
        os << "void " << className << "::push(" << className << "::State state) {" << nonstd::endl;
        os << "\tstd::cerr << \"push \" << ContextNames[(Context)state] << nonstd::endl;" << nonstd::endl;
        os << "\t" << baseClass << "::push(state);" << nonstd::endl;
        os << "}" << nonstd::endl;
        os << "void " << className << "::pop() {" << nonstd::endl;
        os << "\t" << baseClass << "::pop();" << nonstd::endl;
        os << "\tstd::cerr << \"pop \" << ContextNames[(Context)startState] << nonstd::endl;" << nonstd::endl;
        os << "}" << nonstd::endl;
    }
*/
}

void LexicalMachine::Dump(std::ostream &output, unsigned indent) const {
	output << Indent(indent) << "diagnostics = " << diagnostics << std::endl;
	output << Indent(indent) << "compressed = " << compressed << std::endl;
	output << Indent(indent) << "debug = " << debug << std::endl;

	output << Indent(indent) << "name = " << name << std::endl;
	output << Indent(indent) << "className = " << className << std::endl;
	output << Indent(indent) << "baseClassName = " << baseClassName << std::endl;

	output << Indent(indent) << "rootTypeName = " << rootTypeName << std::endl;
	output << Indent(indent) << "baseClass = " << baseClass << std::endl;
	output << Indent(indent) << "valueType = " << valueType << std::endl;
	output << Indent(indent) << "returnType = " << returnType << std::endl;

//	output << Indent(indent) << "startContext = " << startContext << std::endl;

	output << Indent(indent) << "equivalenceClasses = " << equivalenceClasses.print() << std::endl;

	output << Indent(indent) << "startContextName = " << startContextName << std::endl;
	output << Indent(indent) << "contexts = [" << std::endl;
	for (auto context : contexts) {
		output << Indent(indent + 4) << "{" << std::endl;
		context->Dump(output, indent + 4);
		output << Indent(indent + 4) << "}" << std::endl;
	}
	output << Indent(indent) << "]" << std::endl;

	output << Indent(indent) << "columnMap = " << columnMap << std::endl;

	//output << Indent(indent) << "actions = ";
	//actions.Dump(output, indent + 2);

	/*
	LexicalGenerator* lexicalGenerator;

	std::map<std::string, LexicalContext*> nameToContext;
	LexicalContext* startContext;

	Actions actions;

	DFA* dfa;
	ColumnMap* columnMap;
*/

}

bool compare(const LexicalMachine* lhs, const LexicalMachine* rhs) {

	bool name = (lhs->name == rhs->name);
	bool className = (lhs->className == rhs->className);
	bool baseClassName = (lhs->baseClassName == rhs->baseClassName);
	bool rootTypeName = (lhs->rootTypeName == rhs->rootTypeName);
	bool baseClass = (lhs->baseClass == rhs->baseClass);
	bool valueType = (lhs->valueType == rhs->valueType);
	bool returnType = (lhs->returnType == rhs->returnType);

	bool context = true;
	if (lhs->contexts.size() == rhs->contexts.size())
		for (unsigned c = 0; c < lhs->contexts.size(); ++c)
			context &= compare(lhs->contexts[c], rhs->contexts[c]);

	//bool nameToContext = (lhs->nameToContext == rhs->nameToContext);
	/*
		std::cout << "\t" "startContext" << nonstd::endl;
		bool startContext = (lhs->startContext == rhs->startContext);
		if (startContext)
			std::cout << "\t\t" << "true" << nonstd::endl;
		else
			std::cout << "\t\t" << "false" << nonstd::endl;
	*/
	bool startContextName = (lhs->startContextName == rhs->startContextName);
	bool actions = lhs->actions == rhs->actions;
	bool equivalenceClasses = compare(lhs->equivalenceClasses, rhs->equivalenceClasses);
	bool dfa = (lhs->dfa && rhs->dfa) ? compare(lhs->dfa, rhs->dfa) : true;
	bool columnMap;
	if (lhs->columnMap != nullptr || rhs->columnMap != nullptr)
		columnMap = compare(lhs->columnMap, rhs->columnMap);
	else
		columnMap = true;

	bool result = name &&
		className &&
		baseClassName &&
		rootTypeName &&
		baseClass &&
		valueType &&
		returnType &&
		context &&
	//	nameToContext &&
		//startContext &&
		startContextName &&
		actions &&
		equivalenceClasses &&
		dfa &&
		columnMap;

	if (!result) {
		std::cout << "\t" "name: " << nonstd::generateBoolean(name) << " - \"" << lhs->name << "\" - \"" <<  rhs->name << "\"" << nonstd::endl;

		std::cout << "\t" "className: " << nonstd::generateBoolean(className) << nonstd::endl;

		if (!className) {
			std::cout << "\t    \"" << lhs->className << "\"" << nonstd::endl;
			std::cout << "\t    \"" << rhs->className << "\"" << nonstd::endl;
		}

		std::cout << "\t" "baseClassName: " << nonstd::generateBoolean(baseClassName) << nonstd::endl;

		std::cout << "\t" "rootTypeName: " << nonstd::generateBoolean(rootTypeName) << nonstd::endl;
		std::cout << "\t" "baseClass: " << nonstd::generateBoolean(baseClass) << nonstd::endl;
		std::cout << "\t" "valueType: " << nonstd::generateBoolean(valueType) << nonstd::endl;
		std::cout << "\t" "returnType: " << nonstd::generateBoolean(returnType) << nonstd::endl;
		if (lhs->contexts.size() == rhs->contexts.size()) {
			for (unsigned c = 0; c < lhs->contexts.size(); ++c) {
				std::cout << "\t    " "context[" << lhs->contexts[c]->getName() << "]:";
				bool result = compare(lhs->contexts[c], rhs->contexts[c]);
				std::cout << nonstd::generateBoolean(result) << nonstd::endl;
				context &= result;
			}
		}
		else {
			std::cout << "\t" "contexts:" << "false" << " " << lhs->contexts.size() << " != " << rhs->contexts.size() << nonstd::endl;
		}
		std::cout << "\t" "context: " << nonstd::generateBoolean(context) << nonstd::endl;
	//	std::cout << "\t" "nameToContext: " << nonstd::generateBoolean(nameToContext) << nonstd::endl;
		/*
		std::cout << "\t" "startContext" << nonstd::endl;
		bool startContext = (lhs->startContext == rhs->startContext);
		if (startContext)
		std::cout << "\t\t" << "true" << nonstd::endl;
		else
		std::cout << "\t\t" << "false" << nonstd::endl;
		*/
		std::cout << "\t" "startContextName: " << nonstd::generateBoolean(startContextName) << nonstd::endl;
		std::cout << "\t" "actions: " << nonstd::generateBoolean(actions) << nonstd::endl;
		std::cout << "\t" "equivalenceClasses: " << nonstd::generateBoolean(equivalenceClasses) << nonstd::endl;
		std::cout << "\t" "dfa: " << nonstd::generateBoolean(dfa) << nonstd::endl;
		std::cout << "\t" "columnMap: " << nonstd::generateBoolean(columnMap) << nonstd::endl;
	}
	return result;
}

}; // end namespace Lexical AnalyserGenerator
}; // end namespace G

// End g/LexicalAnalyserGenerator/LexicalMachine.h - Lexical Analyser Machine
