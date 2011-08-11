#ifndef __DECLARATIONS_H
#define __DECLARATIONS_H

#include "statements.hpp"

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

#endif
