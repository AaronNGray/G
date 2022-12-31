#include "g/SourceFile.h"

extern Runtime::Lexer* lexer;

int yylex() {
    return lexer->lex();
}
