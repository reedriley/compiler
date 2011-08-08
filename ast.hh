#ifndef __AST_HH
#define __AST_HH

/* TODO: See if it's safe to remove these... */
#define __STDC_LIMIT_MACROS 1
#define __STDC_CONSTANT_MACROS 1

#include "llvm/DerivedTypes.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Support/IRBuilder.h"

using namespace llvm;

class ExprAST {
  public:
    virtual ~ExprAST() {}
    virtual Value *Codegen() = 0;
};

class IntegerExprAST : public ExprAST {
  private:
    int val;
  public:
    IntegerExprAST(int val) : val(val) {}
    virtual Value *Codegen();
};

#endif
