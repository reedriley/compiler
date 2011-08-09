#include "ast.hpp"

static Module *TheModule;
static IRBuilder<> Builder(getGlobalContext());

/* Declarations */
Value *FunctionAST::Codegen() {
  std::vector<const Type*> args;
  FunctionType *FT = FunctionType::get(Type::getDoubleTy(getGlobalContext()), args, false);
  Function *F = Function::Create(FT, Function::ExternalLinkage, name, TheModule);

  if (F->getName() != name) {
    F->eraseFromParent();
    F = TheModule->getFunction(name);

    if (!F->empty()) {
      printf("redefinition of function");
      return NULL;
    }

    if (F->arg_size() != args.size()) {
      printf("redefinition of function with different # args");
      return NULL;
    }
  }

  BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
  Builder.SetInsertPoint(BB);

  Builder.CreateRet(ret->Codegen());

  verifyFunction(*F);

  return F;
}

/* Statements */
Value *ReturnAST::Codegen() {
  return NULL;
}

/* Expressions */
Value *LiteralExprAST::Codegen() {
  return ConstantFP::get(getGlobalContext(), APFloat(val));
}
