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
    std::vector<StatementAST*> stmts;
  public:
    FunctionAST(std::string name, std::vector<StatementAST*> stmts) : name(name), stmts(stmts) {}
    virtual Value* Codegen(llvm::LLVMContext& context);
};

#endif
