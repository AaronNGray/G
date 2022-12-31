#include "gtest/gtest.h"
#include "g/AST.h"

using namespace G;

class anAST : public AST {
public:
    anAST() : AST() {}
    virtual ~anAST() {}

    class Root : public AST::Root {
    public:

    };

    class aNode : public Root {
    public:

    };

    virtual Root* getRoot() { return root; }    // covariant override
protected:
    Root* root; // covariant override
};

TEST(AST, new) {
    anAST* ast = new anAST();

    EXPECT_TRUE(ast == ast);
}
