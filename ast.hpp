#ifndef __AST_H
#define __AST_H

#include "llvm/DerivedTypes.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Support/IRBuilder.h"

using namespace llvm;

class ExprAST;

/* Declarations */
class DeclarationAST {
  public:
    virtual ~DeclarationAST() {}
    virtual Value *Codegen(llvm::LLVMContext& context) = 0;
};

class FunctionAST : public DeclarationAST {
  private:
    std::string name;
    ExprAST *ret;
  public:
    FunctionAST(std::string name, ExprAST *ret) : name(name), ret(ret) {}
    virtual Value *Codegen(llvm::LLVMContext& context);
};

/* Expressions */
class ExprAST {
  public:
    virtual ~ExprAST() {}
    virtual Value *Codegen(llvm::LLVMContext &context) = 0;
};

class LiteralExprAST : public ExprAST {
  private:
    double val;
  public:
    LiteralExprAST(double val) : val(val) {}
    virtual Value *Codegen(llvm::LLVMContext &context);
};

/* Statements */
class StatementAST {
  public:
    virtual ~StatementAST() {}
    virtual Value *Codegen(llvm::LLVMContext &context) = 0;
};

class ReturnAST : public StatementAST {
  private:
    ExprAST *expr;
  public:
    ReturnAST(ExprAST *expr) : expr(expr) {}
    virtual Value *Codegen(llvm::LLVMContext &context);
};


#endif
