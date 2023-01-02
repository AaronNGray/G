#include "g/ParserGenerator/ParserGenerator.h"
#include "g/Actions.h"

using namespace G::ParserGenerator;

ContextFreeGrammar* TTG_bootstrap() {
ContextFreeGrammar* TTG = new ContextFreeGrammar("TTG");

	ContextFreeGrammar::Terminal *KEYWORD_MODULE = TTG->addTerminal("KEYWORD_MODULE","", "module", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_CODE = TTG->addTerminal("KEYWORD_CODE","", "code", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_HEADER = TTG->addTerminal("KEYWORD_HEADER","", "header", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_TEMPLATE = TTG->addTerminal("KEYWORD_TEMPLATE","", "template", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_CLASS = TTG->addTerminal("KEYWORD_CLASS","", "class", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_FUNCTION = TTG->addTerminal("KEYWORD_FUNCTION","", "function", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *KEYWORD_METHOD = TTG->addTerminal("KEYWORD_METHOD","", "method", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_CURLY_BRACE = TTG->addTerminal("OPERATOR_OPEN_CURLY_BRACE","", "{", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_CURLY_BRACE = TTG->addTerminal("OPERATOR_CLOSE_CURLY_BRACE","", "}", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_DOUBLE_CURLY_BRACE = TTG->addTerminal("OPERATOR_OPEN_DOUBLE_CURLY_BRACE","", "{{", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_DOUBLE_CURLY_BRACE = TTG->addTerminal("OPERATOR_CLOSE_DOUBLE_CURLY_BRACE","", "}}", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_PARENTHSIS = TTG->addTerminal("OPERATOR_OPEN_PARENTHSIS","", "(", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_PARENTHSIS = TTG->addTerminal("OPERATOR_CLOSE_PARENTHSIS","", ")", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_OPEN_DOUBLE_PARENTHSIS = TTG->addTerminal("OPERATOR_OPEN_DOUBLE_PARENTHSIS","", "((", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_CLOSE_DOUBLE_PARENTHSIS = TTG->addTerminal("OPERATOR_CLOSE_DOUBLE_PARENTHSIS","", "))", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_SEMICOLON = TTG->addTerminal("OPERATOR_SEMICOLON","", ";", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_COLON = TTG->addTerminal("OPERATOR_COLON","", ":", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_DOUBLE_COLON = TTG->addTerminal("OPERATOR_DOUBLE_COLON","", "::", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *OPERATOR_COMMA = TTG->addTerminal("OPERATOR_COMMA","", ",", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *IDENTIFIER = TTG->addTerminal("IDENTIFIER","Identifier", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *STRING_LITERAL = TTG->addTerminal("STRING_LITERAL","StringLiteral", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *TOKEN_PARAMETER = TTG->addTerminal("TOKEN_PARAMETER","Code", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *TOKEN_CODE = TTG->addTerminal("TOKEN_CODE","Code", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *TOKEN_ACTIONCODE = TTG->addTerminal("TOKEN_ACTIONCODE","Code", "", ContextFreeGrammar::None, 0, false);
	ContextFreeGrammar::Terminal *NEWLINE = TTG->addTerminal("NEWLINE","", "", ContextFreeGrammar::None, 0, false);

	ContextFreeGrammar::Terminal *EPSILON = TTG->getTerminal("EPSILON");
	ContextFreeGrammar::Terminal *END = TTG->getTerminal("END");

	ContextFreeGrammar::NonTerminal *TextualTemplateGrammar = TTG->addNonTerminal("TextualTemplateGrammar", "Module");
	ContextFreeGrammar::NonTerminal *Templates = TTG->addNonTerminal("Templates", "Templates");
	ContextFreeGrammar::NonTerminal *Template = TTG->addNonTerminal("Template", "Template");
	ContextFreeGrammar::NonTerminal *TemplateClass = TTG->addNonTerminal("TemplateClass", "Template");
	ContextFreeGrammar::NonTerminal *TemplateFunction = TTG->addNonTerminal("TemplateFunction", "Template");
	ContextFreeGrammar::NonTerminal *Arguments = TTG->addNonTerminal("Arguments", "Arguments");
	ContextFreeGrammar::NonTerminal *Argument = TTG->addNonTerminal("Argument", "Argument");
	ContextFreeGrammar::NonTerminal *QualifiedName = TTG->addNonTerminal("QualifiedName", "QualifiedName");
	ContextFreeGrammar::NonTerminal *Type = TTG->addNonTerminal("Type", "QualifiedName");
	ContextFreeGrammar::NonTerminal *Block = TTG->addNonTerminal("Block", "Block");
	ContextFreeGrammar::NonTerminal *Parameter = TTG->addNonTerminal("Parameter", "Code");
	ContextFreeGrammar::NonTerminal *SubBlocks = TTG->addNonTerminal("SubBlocks", "Block");
	ContextFreeGrammar::NonTerminal *SubBlock = TTG->addNonTerminal("SubBlock", "Code");
	ContextFreeGrammar::NonTerminal *S_ = TTG->addNonTerminal("S'", "S'");

	TTG->setStartSymbol(S_);
	TTG->addRule(TextualTemplateGrammar, {
		TTG->addProduction({
			TTG->newNamedSymbol(KEYWORD_MODULE),
			TTG->newNamedSymbol("name", IDENTIFIER),
			TTG->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			TTG->newNamedSymbol("templates", Templates),
			TTG->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE)
		}, 0)
	});
	TTG->addRule(Templates, {
		TTG->addProduction({
			TTG->newNamedSymbol(Templates),
			TTG->newNamedSymbol(Template)
		}, 1),
		TTG->addProduction({
			TTG->newNamedSymbol(Template)
		}, 2)
	});
	TTG->addRule(Template, {
		TTG->addProduction({
			TTG->newNamedSymbol(TemplateClass)
		}, 3),
		TTG->addProduction({
			TTG->newNamedSymbol(TemplateFunction)
		}, 4)
	});
	TTG->addRule(TemplateClass, {
		TTG->addProduction({
			TTG->newNamedSymbol(KEYWORD_TEMPLATE),
			TTG->newNamedSymbol(KEYWORD_CLASS),
			TTG->newNamedSymbol("name", Type),
			TTG->newNamedSymbol(OPERATOR_OPEN_PARENTHSIS),
			TTG->newNamedSymbol(OPERATOR_CLOSE_PARENTHSIS),
			TTG->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			TTG->newNamedSymbol("block", Block),
			TTG->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE),
			TTG->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 5),
		TTG->addProduction({
			TTG->newNamedSymbol(KEYWORD_TEMPLATE),
			TTG->newNamedSymbol(KEYWORD_CLASS),
			TTG->newNamedSymbol("name", Type),
			TTG->newNamedSymbol(OPERATOR_OPEN_PARENTHSIS),
			TTG->newNamedSymbol("arguments", Arguments),
			TTG->newNamedSymbol(OPERATOR_CLOSE_PARENTHSIS),
			TTG->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			TTG->newNamedSymbol("block", Block),
			TTG->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE),
			TTG->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 6)
	});
	TTG->addRule(TemplateFunction, {
		TTG->addProduction({
			TTG->newNamedSymbol(KEYWORD_TEMPLATE),
			TTG->newNamedSymbol(KEYWORD_FUNCTION),
			TTG->newNamedSymbol("class", Type),
			TTG->newNamedSymbol(OPERATOR_DOUBLE_COLON),
			TTG->newNamedSymbol("name", IDENTIFIER),
			TTG->newNamedSymbol(OPERATOR_OPEN_PARENTHSIS),
			TTG->newNamedSymbol(OPERATOR_CLOSE_PARENTHSIS),
			TTG->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			TTG->newNamedSymbol("block", Block),
			TTG->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE),
			TTG->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 7),
		TTG->addProduction({
			TTG->newNamedSymbol(KEYWORD_TEMPLATE),
			TTG->newNamedSymbol(KEYWORD_FUNCTION),
			TTG->newNamedSymbol("class", Type),
			TTG->newNamedSymbol(OPERATOR_DOUBLE_COLON),
			TTG->newNamedSymbol("name", IDENTIFIER),
			TTG->newNamedSymbol(OPERATOR_OPEN_PARENTHSIS),
			TTG->newNamedSymbol("arguments", Arguments),
			TTG->newNamedSymbol(OPERATOR_CLOSE_PARENTHSIS),
			TTG->newNamedSymbol(OPERATOR_OPEN_CURLY_BRACE),
			TTG->newNamedSymbol("block", Block),
			TTG->newNamedSymbol(OPERATOR_CLOSE_CURLY_BRACE),
			TTG->newNamedSymbol(OPERATOR_SEMICOLON)
		}, 8)
	});
	TTG->addRule(Arguments, {
		TTG->addProduction({
			TTG->newNamedSymbol("arguments", Arguments),
			TTG->newNamedSymbol(OPERATOR_COMMA),
			TTG->newNamedSymbol("argument", Argument)
		}, 9),
		TTG->addProduction({
			TTG->newNamedSymbol("argument", Argument)
		}, 10)
	});
	TTG->addRule(Argument, {
		TTG->addProduction({
			TTG->newNamedSymbol("name", IDENTIFIER),
			TTG->newNamedSymbol(OPERATOR_COLON),
			TTG->newNamedSymbol("type", Type)
		}, 11)
	});
	TTG->addRule(Type, {
		TTG->addProduction({
			TTG->newNamedSymbol("type", Type),
			TTG->newNamedSymbol(OPERATOR_DOUBLE_COLON),
			TTG->newNamedSymbol("identifier", IDENTIFIER)
		}, 12),
		TTG->addProduction({
			TTG->newNamedSymbol("identifier", IDENTIFIER)
		}, 13)
	});
	TTG->addRule(Block, {
		TTG->addProduction({
			TTG->newNamedSymbol("subBlocks", SubBlocks)
		}, 14)
	});
	TTG->addRule(SubBlocks, {
		TTG->addProduction({
			TTG->newNamedSymbol("subBlocks", SubBlocks),
			TTG->newNamedSymbol("subBlock", SubBlock)
		}, 15),
		TTG->addProduction({
			TTG->newNamedSymbol("subBlock", SubBlock)
		}, 16)
	});
	TTG->addRule(SubBlock, {
		TTG->addProduction({
			TTG->newNamedSymbol("block", TOKEN_CODE)
		}, 17),
		TTG->addProduction({
			TTG->newNamedSymbol("block", TOKEN_ACTIONCODE)
		}, 18),
		TTG->addProduction({
			TTG->newNamedSymbol("parameter", TOKEN_PARAMETER)
		}, 19)
	});
	TTG->addRule(S_, {
		TTG->addProduction({
			TTG->newNamedSymbol(TextualTemplateGrammar),
			TTG->newNamedSymbol(END)
		}, -1)
	});
	return TTG;
}

Actions bootstrapActions = {
	{ 0, "{ root->module = root->newModule(valueStack[3].Identifier, valueStack[1].Templates); }", 113},
	{ 1, "{ currentValue.Templates = valueStack[1].Templates; valueStack[1].Templates->append(valueStack[0].Template); }", 117},
	{ 2, "{ currentValue.Templates = root->newTemplates(); currentValue.Templates->append(valueStack[0].Template); }", 118},
	{ 3, "{ currentValue.Template = valueStack[0].Template; }", 122},
	{ 4, "{ currentValue.Template = valueStack[0].Template; }", 123},
	{ 5, "{\n\t\tcurrentValue.Template = root->newClassTemplate(valueStack[6].QualifiedName, valueStack[2].Block);\n\t}", 127},
	{ 6, "{\n\t\tcurrentValue.Template = root->newClassTemplate(valueStack[7].QualifiedName, valueStack[5].Arguments, valueStack[2].Block);\n    }", 130},
	{ 7, "{\n\t\tvalueStack[8].QualifiedName->append(valueStack[6].Identifier);\n\t\tcurrentValue.Template = root->newFunctionTemplate(valueStack[8].QualifiedName, valueStack[2].Block);\n\t}", 136},
	{ 8, "{\n\t\tvalueStack[9].QualifiedName->append(valueStack[7].Identifier);\n\t\tcurrentValue.Template = root->newFunctionTemplate(valueStack[9].QualifiedName, valueStack[5].Arguments, valueStack[2].Block);\n    }", 140},
	{ 9, "{\n\t\tvalueStack[2].Arguments->append(valueStack[0].Argument);\n\t}", 147},
	{ 10, "{\n\t\tcurrentValue.Arguments = root->newArguments(); currentValue.Arguments->append(valueStack[0].Argument);\n\t}", 150},
	{ 11, "{\n\t\tcurrentValue.Argument = root->newArgument(valueStack[2].Identifier, valueStack[0].QualifiedName);\n\t}", 156},
	{ 12, "{\n\t\tcurrentValue.QualifiedName = valueStack[2].QualifiedName; valueStack[2].QualifiedName->append(valueStack[0].Identifier);\n\t}", 162},
	{ 13, "{\n\t\tcurrentValue.QualifiedName = root->newType(); currentValue.QualifiedName->append(valueStack[0].Identifier);\n\t}", 165},
	{ 14, "{ currentValue.Block = valueStack[0].Block; }", 171},
	{ 15, "{ valueStack[1].Block->append(valueStack[0].Code); currentValue.Block = valueStack[1].Block; }", 175},
	{ 16, "{ currentValue.Block = root->newBlock(); currentValue.Block->append(valueStack[0].Code); }", 176},
	{ 17, "{ currentValue.Code = root->newCodeBlock(valueStack[0].Code); }", 180},
	{ 18, "{ currentValue.Code = root->newActionCode(valueStack[0].Code); }", 181},
	{ 19, "{ currentValue.Code = root->newParameter(valueStack[0].Code); }", 182}
};

ParserGenerator<ContextFreeGrammar, ParserGeneratorParser>* ttg_ParserGenerator = new ParserGenerator<ContextFreeGrammar, ParserGeneratorParser>("ttg", 
ttg_bootstrap(), &bootstrapActions,
"TextualTemplate",
"ValueType",
"true",
"void",
  {
    { "\n\t#include <io.h>\n\t#include <iostream>\n\t#include <cassert>\n\t#include \"g/Logger.h\"\n\t#include \"g/TextualTemplateGenerator/TextualTemplate.h\"\n\n\tusing namespace G::TextualTemplateGenerator;\n\n    union ValueType {\n\t\tTextualTemplate::Module *Module;\n\t\tTextualTemplate::Templates *Templates;\n\t\tTextualTemplate::Template *Template;\n\t\tTextualTemplate::QualifiedName* QualifiedName;\n\t\tTextualTemplate::Type* Type;\n\t\tTextualTemplate::Arguments* Arguments;\n\t\tTextualTemplate::Argument* Argument;\n\t\tTextualTemplate::Name* Name;\n\t\tTextualTemplate::Block* Block;\n    \tTextualTemplate::Identifier *Identifier;\n    \tTextualTemplate::StringLiteral *StringLiteral;\n    \tTextualTemplate::Code *Code;\n    };\n\n    extern ValueType currentValue;\n\textern Logger *logger;\n    using namespace Runtime;\n", 9, "C:\\Users\\aaron\\Projects\\G\\latest\\G\\src\\tools\\ttg\\ttg.pg" }
  }, 
  {
    { "\n\t#include \"ttg.lg.h\"\n\tValueType currentValue;\n", 38, "C:\\Users\\aaron\\Projects\\G\\latest\\G\\src\\tools\\ttg\\ttg.pg" },
    { "\n\tvoid ttgParser::reportError(State state, Input input) {\n\t\tstd::string report = std::string(\"Found \") + Terminals[input] + \" Expecting \";\n\n\t\tPair<Action>* pair = ShiftReduce_states[state - 1]->pair;\n\t\tif (pair) {\n\t\t\tfor (size_t pairs = ShiftReduce_states[state - 1]->pairs; pairs > 0; --pairs) {\n                report += std::string(Terminals[pair->input]) + ((pairs > 1) ? \", \" : \"\");\n\t\t\t\t++pair;\n\t\t\t}\n\t\t}\n\t\telse\n            report += std::string(\"<nothing>\");\n        report += std::string(\" in state \") + std::to_string(state) + \".\\\n\";\n\n\t\tlogger->LogError(new SyntaxErrorObject(report, lexer->getLineNumber(), lexer->getCharacter()));\n\t}\n", 42, "C:\\Users\\aaron\\Projects\\G\\latest\\G\\src\\tools\\ttg\\ttg.pg" }
  });

// End C:\Users\aaron\Projects\G\latest\G\src\tools\ttg\ttg.lexer.cpp
