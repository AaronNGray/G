# G stands for Generator
G is a source to source compiler compiler with a code parser and generator initially to be written in C++

Tools :-
 - LG - Lexical Analyser Generator
 - PG - Parser Generator
 - AG - AST Generator
 - TTG - Textual Template Generator
 - GG - Generator Generator
 - TG - Template Generator
 - G - Generator

Libraries :-
  - LexicalAnalyserGenreator
  - ParserGenerator
  - ASTGenerator
  - TextualTemplateGenerator
  - LexicalGenerator
  - GeneratorGenerator
  - TemplateGenerator

## LG - Lexical Analyser Generator ##

A 'lex' style lexical analyser generator. Takes a .lg file and generates a lexical analyser library.

Uses Two "new" alogorithms :-
 - The Dragon Book Algorithm 3.5 that converts a Regular Expression into a DFA
 - Equivanance classes from analysing input sysmbols

## PG - Parser Generator ##

A 'YACC' style Parser Generator. Takes a .pg file and generates a parser library.

 - [ ] LL(1)
 - [ ] SLR
 - [ ] LR(0)
 - [ ] LR(1)
 - [x] LALR(1)
 - [ ] LAR(m)
 - [ ] RNGLR
 - [ ] SPPF
 - [ ] Pakrat
 - [ ] Recursive Descent with Backtracking and Memorization

## AG - AST Generator ##

An Augented ADT (Algebraic Data Type) AST generator augmented with methods. Takes a .ag file and generates a AST code.

## TTG - Textual Template Generator ##

A Template Genrator that converts templates into methods. This is a short term hack to tidy up the code generator code.

## GG - Generator Generator ##

The Generator Generator takes a Grammar and generates methods that convert an AST into text using a library generated by the the Lexical Generator library. Takes. .gg files and generates the generator code.

## TG - Template Generator ##

Template generator generates AST's from a grammar augmented with templating syntax generating methods that generate instance AST's. This allows clean syntatic templating.

## G - Generate ##

G will tie together all the libraries together and does what all the tools do using *.g format files. G will combine lexical specifications and grammar specifications into one specificiation. And will also allow higherlevel modular grammars to be defined.
# Instillation

# Build

Requires :-
  - Visual Studio 2022

  - Premake 5 for Windows

  - gtest-1.7.0

    `git clone https://github.com/AaronNGray/gtest-1.7.0.git`

    In same parent directory as G.

  - WinFlexBison

    `git clone https://github.com/AaronNGray/winflexbison.git`

    put on PATH.

Git clone

 - G

    `git clone https://github.com/AaronNGray/G.git`

## Build

 - Run premake :-

    `premake5 vs2022`

  - Build desired Solution(s) of G in Visual Studio
