#ifndef __AST_HH
#define __AST_HH

#include "llvm/DerivedTypes.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Support/IRBuilder.h"

using namespace llvm;

/* Declarations */
class DeclarationAST {
  public:
    virtual ~DeclarationAST() {}
};

/* Statements */
class StatementAST {
  public:
    virtual ~StatementAST() {}
};

/* Expressions */
class ExprAST {
  public:
    virtual ~ExprAST() {}
    virtual Value *Codegen() = 0;
};

class LiteralExprAST : public ExprAST {
  private:
    double val;
  public:
    LiteralExprAST(double val) : val(val) {}
    virtual Value *Codegen();
};

#endif
