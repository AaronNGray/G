#include "g/ParserGenerator/ParserGenerator.h"
#include "g/Actions.h"

using namespace G::ParserGenerator;

ContextFreeGrammar* AG_bootstrap() {
ContextFreeGrammar* AG = new ContextFreeGrammar("AG");

	ContextFreeGrammar::Terminal *KEYWORD_MODULE = AG->addTerminal("KEYWORD_MODULE","", "module", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_CODE = AG->addTerminal("KEYWORD_CODE","", "code", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_HEADER = AG->addTerminal("KEYWORD_HEADER","", "header", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_DATATYPE = AG->addTerminal("KEYWORD_DATATYPE","", "datatype", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_CURLY_BRACE = AG->addTerminal("OPERATOR_OPEN_CURLY_BRACE","", "{", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_CURLY_BRACE = AG->addTerminal("OPERATOR_CLOSE_CURLY_BRACE","", "}", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_PARENTHSIS = AG->addTerminal("OPERATOR_OPEN_PARENTHSIS","", "(", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_PARENTHSIS = AG->addTerminal("OPERATOR_CLOSE_PARENTHSIS","", ")", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_SEMICOLON = AG->addTerminal("OPERATOR_SEMICOLON","", ";", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_COLON = AG->addTerminal("OPERATOR_COLON","", ":", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_COMMA = AG->addTerminal("OPERATOR_COMMA","", ",", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_EQUALS = AG->addTerminal("OPERATOR_EQUALS","", "=", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_BAR = AG->addTerminal("OPERATOR_BAR","", "|", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *Identifier = AG->addTerminal("Identifier","Identifier", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *Code = AG->addTerminal("Code","Code", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *NEWLINE = AG->addTerminal("NEWLINE","", "", ContextFreeGrammar::None, 0, false);

	ContextFreeGrammar::Terminal *EPSILON = AG->getTerminal("EPSILON");
	ContextFreeGrammar::Terminal *END = AG->getTerminal("END");

	ContextFreeGrammar::NonTerminal *AbstractSyntaxTree = AG->addNonTerminal("AbstractSyntaxTree", "AbstractSyntaxTree");
	ContextFreeGrammar::NonTerminal *OptDeclarations = AG->addNonTerminal("OptDeclarations", "Declarations");
	ContextFreeGrammar::NonTerminal *Declarations = AG->addNonTerminal("Declarations", "Declarations");
	ContextFreeGrammar::NonTerminal *Declaration = AG->addNonTerminal("Declaration", "Datatype");
	ContextFreeGrammar::NonTerminal *OptTypes = AG->addNonTerminal("OptTypes", "Types");
	ContextFreeGrammar::NonTerminal *Types = AG->addNonTerminal("Types", "Types");
	ContextFreeGrammar::NonTerminal *Type = AG->addNonTerminal("Type", "Type");
	ContextFreeGrammar::NonTerminal *Arguments = AG->addNonTerminal("Arguments", "Arguments");
	ContextFreeGrammar::NonTerminal *Argument = AG->addNonTerminal("Argument", "Argument");
	ContextFreeGrammar::NonTerminal *Block = AG->addNonTerminal("Block", "Block");
	ContextFreeGrammar::NonTerminal *S_ = AG->addNonTerminal("S'", "S'");

	AG->setStartSymbol(S_);
	AG->addRule(AbstractSyntaxTree, {
		AG->addProduction({
			AG->newNamedSymbol(KEYWORD_MODULE),
			AG->newNamedSymbol("name", Identifier),
			AG->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			AG->newNamedSymbol("body", OptDeclarations),
			AG->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE)
		}, 0)
	});
	AG->addRule(OptDeclarations, {
		AG->addProduction({
			AG->newNamedSymbol(Declarations)
		}, 1),
		AG->addProduction({}, 2)
	});
	AG->addRule(Declarations, {
		AG->addProduction({
			AG->newNamedSymbol(Declarations),
			AG->newNamedSymbol(Declaration)
		}, 3),
		AG->addProduction({
			AG->newNamedSymbol(Declaration)
		}, 4)
	});
	AG->addRule(Declaration, {
		AG->addProduction({
			AG->newNamedSymbol(KEYWORD_DATATYPE),
			AG->newNamedSymbol("name", Identifier),
			AG->newNamedSymbol("types", OptTypes),
			AG->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 5),
		AG->addProduction({
			AG->newNamedSymbol(KEYWORD_DATATYPE),
			AG->newNamedSymbol("name", Identifier),
			AG->newNamedSymbol("block", Block),
			AG->newNamedSymbol("types", OptTypes),
			AG->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 6),
		AG->addProduction({
			AG->newNamedSymbol(KEYWORD_DATATYPE),
			AG->newNamedSymbol("name", Identifier),
			AG->newNamedSymbol(OPERATOR_OPEN_PARENTHSIS),
			AG->newNamedSymbol("arguments", Arguments),
			AG->newNamedSymbol(OPERATOR_CLOSE_PARENTHSIS),
			AG->newNamedSymbol("types", OptTypes),
			AG->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 7),
		AG->addProduction({
			AG->newNamedSymbol(KEYWORD_DATATYPE),
			AG->newNamedSymbol("name", Identifier),
			AG->newNamedSymbol("block", Block),
			AG->newNamedSymbol(OPERATOR_OPEN_PARENTHSIS),
			AG->newNamedSymbol("arguments", Arguments),
			AG->newNamedSymbol(OPERATOR_CLOSE_PARENTHSIS),
			AG->newNamedSymbol("types", OptTypes),
			AG->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 8)
	});
	AG->addRule(OptTypes, {
		AG->addProduction({
			AG->newNamedSymbol(OPERATOR_EQUALS),
			AG->newNamedSymbol(Types)
		}, 9),
		AG->addProduction({}, 10)
	});
	AG->addRule(Types, {
		AG->addProduction({
			AG->newNamedSymbol(Types),
			AG->newNamedSymbol(OPERATOR_BAR),
			AG->newNamedSymbol(Type)
		}, 11),
		AG->addProduction({
			AG->newNamedSymbol(Type)
		}, 12)
	});
	AG->addRule(Type, {
		AG->addProduction({
			AG->newNamedSymbol("name", Identifier)
		}, 13),
		AG->addProduction({
			AG->newNamedSymbol("name", Identifier),
			AG->newNamedSymbol("block", Block)
		}, 14),
		AG->addProduction({
			AG->newNamedSymbol("name", Identifier),
			AG->newNamedSymbol(OPERATOR_OPEN_PARENTHSIS),
			AG->newNamedSymbol("arguments", Arguments),
			AG->newNamedSymbol(OPERATOR_CLOSE_PARENTHSIS)
		}, 15),
		AG->addProduction({
			AG->newNamedSymbol("name", Identifier),
			AG->newNamedSymbol(OPERATOR_OPEN_PARENTHSIS),
			AG->newNamedSymbol("arguments", Arguments),
			AG->newNamedSymbol(OPERATOR_CLOSE_PARENTHSIS),
			AG->newNamedSymbol("block", Block)
		}, 16)
	});
	AG->addRule(Arguments, {
		AG->addProduction({
			AG->newNamedSymbol(Arguments),
			AG->newNamedSymbol(OPERATOR_COMMA),
			AG->newNamedSymbol(Argument)
		}, 17),
		AG->addProduction({
			AG->newNamedSymbol(Argument)
		}, 18)
	});
	AG->addRule(Argument, {
		AG->addProduction({
			AG->newNamedSymbol("name", Identifier),
			AG->newNamedSymbol(OPERATOR_COLON),
			AG->newNamedSymbol("type", Identifier)
		}, 19)
	});
	AG->addRule(Block, {
		AG->addProduction({
			AG->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			AG->newNamedSymbol("block", Block),
			AG->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE)
		}, 20)
	});
	AG->addRule(S_, {
		AG->addProduction({
			AG->newNamedSymbol(AbstractSyntaxTree),
			AG->newNamedSymbol(END)
		}, -1)
	});
	return AG;
}

Actions bootstrapActions = {
	{ 0, "{ root->newModule(valueStack[3].Identifier, valueStack[1].Declarations); }", 91},
	{ 1, "{ currentValue.Declarations = valueStack[0].Declarations; }", 95},
	{ 2, "{ currentValue.Declarations = nullptr; }", 96},
	{ 3, "{ currentValue.Declarations = valueStack[1].Declarations; valueStack[1].Declarations->add(valueStack[0].Datatype); }", 100},
	{ 4, "{ currentValue.Declarations = root->newDeclarations(); }", 101},
	{ 5, "{ currentValue.Datatype = root->newDatatype(valueStack[2].Identifier, valueStack[1].Types); }", 105},
	{ 6, "{ currentValue.Datatype = root->newDatatype(valueStack[3].Identifier, valueStack[2].Block, valueStack[1].Types); }", 106},
	{ 7, "{ currentValue.Datatype = root->newDatatype(valueStack[5].Identifier, valueStack[3].Arguments, valueStack[1].Types); }", 107},
	{ 8, "{ currentValue.Datatype = root->newDatatype(valueStack[6].Identifier, valueStack[5].Block, valueStack[3].Arguments, valueStack[1].Types); }", 108},
	{ 9, "{ currentValue.Types = valueStack[0].Types; }", 112},
	{ 10, "{ currentValue.Types = nullptr; }", 113},
	{ 11, "{ valueStack[2].Types->add(valueStack[0].Type);}", 117},
	{ 12, "{ currentValue.Types = root->newTypes(); currentValue.Types->add(valueStack[0].Type); }", 118},
	{ 13, "{ currentValue.Type = root->newType(valueStack[0].Identifier); }", 122},
	{ 14, "{ currentValue.Type = root->newType(valueStack[1].Identifier, valueStack[0].Block); }", 123},
	{ 15, "{ currentValue.Type = root->newType(valueStack[3].Identifier, valueStack[1].Arguments); }", 124},
	{ 16, "{ currentValue.Type = root->newType(valueStack[4].Identifier, valueStack[2].Arguments, valueStack[0].Block);}", 125},
	{ 17, "{ currentValue.Arguments = valueStack[2].Arguments; valueStack[2].Arguments->add(valueStack[0].Argument); }", 129},
	{ 18, "{ currentValue.Arguments = root->newArguments(); }", 130},
	{ 19, "{ currentValue.Argument = root->newArgument(valueStack[2].Identifier, valueStack[0].Identifier); }", 134},
	{ 20, "{ currentValue.Block = valueStack[1].Block; }", 138}
};

ParserGenerator<ContextFreeGrammar, ParserGeneratorParser>* ag_ParserGenerator = new ParserGenerator<ContextFreeGrammar, ParserGeneratorParser>("ag", 
ag_bootstrap(), &bootstrapActions,
"AbstractSyntaxTree",
"ValueType",
"true",
"void",
  {
    { "\n\t#include <io.h>\n\t#include <iostream>\n\t#include <cassert>\n\t#include \"g/Logger.h\"\n\t#include \"g/AbstractSyntaxTreeGenerator/AbstractSyntaxTree.h\"\n\t\n\tusing namespace G::AbstractSyntaxTreeGenerator;\n\n\textern Logger* logger;\n\n\tunion ValueType {\n\t\tAbstractSyntaxTree::Root *Root;\n\t\tAbstractSyntaxTree::Module *Module;\n\t\tAbstractSyntaxTree::Declarations *Declarations;\n\t\tAbstractSyntaxTree::Datatype *Datatype;\n\t\tAbstractSyntaxTree::Types* Types;\n\t\tAbstractSyntaxTree::Type* Type;\n\t\tAbstractSyntaxTree::Arguments* Arguments;\n\t\tAbstractSyntaxTree::Argument* Argument;\n\t\tAbstractSyntaxTree::Block* Block;\n    \tAbstractSyntaxTree::Identifier *Identifier;\n    \tAbstractSyntaxTree::Code *Code;\n\t};\n\n    extern ValueType currentValue;\n    using namespace Runtime;\n", 3, "C:\\Users\\aaron\\Projects\\G\\latest\\G\\src\\tools\\ag\\ag.pg" }
  }, 
  {
    { "\n\t#include \"ag.lg.h\"\n\tValueType currentValue;\n", 32, "C:\\Users\\aaron\\Projects\\G\\latest\\G\\src\\tools\\ag\\ag.pg" },
    { "\n\tvoid agParser::reportError(State state, Input input) {\n\t\tstd::string report = std::string(\"Found \") + Terminals[input] + \" Expecting \";\n\n\t\tPair<Action>* pair = ShiftReduce_states[state - 1]->pair;\n\t\tif (pair) {\n\t\t\tfor (size_t pairs = ShiftReduce_states[state - 1]->pairs; pairs > 0; --pairs) {\n                report += std::string(Terminals[pair->input]) + ((pairs > 1) ? \", \" : \"\");\n\t\t\t\t++pair;\n\t\t\t}\n\t\t}\n\t\telse\n            report += std::string(\"<nothing>\");\n        report += std::string(\" in state \") + std::to_string(state) + \".\\\n\";\n\n\t\tlogger->LogError(new SyntaxErrorObject(report, lexer->getLineNumber(), lexer->getCharacter()));\n\t}\n", 36, "C:\\Users\\aaron\\Projects\\G\\latest\\G\\src\\tools\\ag\\ag.pg" }
  });

// End C:\Users\aaron\Projects\G\latest\G\src\tools\ag\ag.lexer.cpp
