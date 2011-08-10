#ifndef __AST_H
#define __AST_H

#include "llvm/Analysis/Verifier.h"
#include "llvm/DerivedTypes.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Support/IRBuilder.h"

using namespace llvm;

class ExprAST;
class StatementAST;

/* Declarations */
class DeclarationAST {
  public:
    virtual ~DeclarationAST() {}
    virtual Value* Codegen(llvm::LLVMContext& context) = 0;
};

class FunctionAST : public DeclarationAST {
  private:
    std::string name;
    StatementAST* stmt;
  public:
    FunctionAST(std::string name, StatementAST* stmt) : name(name), stmt(stmt) {}
    virtual Value* Codegen(llvm::LLVMContext& context);
};

/* Expressions */
class ExprAST {
  public:
    virtual ~ExprAST() {}
    virtual Value* Codegen(llvm::LLVMContext& context) = 0;
};

class LiteralExprAST : public ExprAST {
  private:
    double val;
  public:
    LiteralExprAST(double val) : val(val) {}
    virtual Value* Codegen(llvm::LLVMContext& context);
};

/* Statements */
class StatementAST {
  public:
    virtual ~StatementAST() {}
    virtual void Codegen(llvm::LLVMContext& context, llvm::BasicBlock* block) = 0;
};

class ReturnAST : public StatementAST {
  private:
    ExprAST* expr;
  public:
    ReturnAST(ExprAST* expr) : expr(expr) {}
    virtual void Codegen(llvm::LLVMContext& context, llvm::BasicBlock* block);
};


#endif
