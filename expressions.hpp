#ifndef __EXPRESSIONS_H
#define __EXPRESSIONS_H

#include "llvm/Analysis/Verifier.h"
#include "llvm/DerivedTypes.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Support/IRBuilder.h"

using namespace llvm;

class ExprAST {
  public:
    virtual ~ExprAST() {}
    virtual Value* Codegen(llvm::LLVMContext& context) = 0;
};

class LiteralExprAST : public ExprAST {
  private:
    int val;
  public:
    LiteralExprAST(int val) : val(val) {}
    virtual Value* Codegen(llvm::LLVMContext& context);
};

#endif
