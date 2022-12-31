//
//  AST.h - Abstract Syntax Tree base class
//
//  Property and Copyright (c) 2022 Aaron Nathaniel Gray
//

#pragma once

namespace G {

class AST {
public:
    AST() : root(nullptr) {}
    virtual ~AST() {}

    class Root {};
    virtual Root* getRoot() { return root; };
protected:
    Root* root;
};

//  
//  Boilerplate for creating AST's 
//  
//      class anAST : public AST {
//      public:
//          anAST() : AST() {}
//          virtual ~anAST() {}
//  
//          class Root : public AST::Root {
//          public:
//              ...
//          };
// 
//          class aNode : public Root {
//          public:
//              ...
//          };
// 
//          virtual Root* getRoot() { return root; }    // covariant override
//      protected:
//          Root* root; // covariant override
//      };
//  

}