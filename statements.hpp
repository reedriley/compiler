#ifndef __STATEMENTS_H
#define __STATEMENTS_H

#include "expressions.hpp"

using namespace llvm;

class StatementAST {
  public:
    virtual ~StatementAST() {}
    virtual void Codegen(llvm::LLVMContext& context, llvm::Function* func, llvm::BasicBlock* &block);
};

class ReturnAST : public StatementAST {
  private:
    ExprAST* expr;
  public:
    ReturnAST(ExprAST* expr) : expr(expr) {}
    virtual void Codegen(llvm::LLVMContext& context, llvm::Function* func, llvm::BasicBlock* &block);
};

#endif
