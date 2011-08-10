#include "ast.hpp"

static Module *TheModule;

/* Declarations */
Value *FunctionAST::Codegen(llvm::LLVMContext& context) {
  IRBuilder<> Builder(context);

  std::vector<const Type*> args;
  FunctionType *FT = FunctionType::get(Type::getDoubleTy(context), args, false);
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

  BasicBlock *BB = BasicBlock::Create(context, "entry", F);
  Builder.SetInsertPoint(BB);

  Builder.CreateRet(ret->Codegen(context));

  verifyFunction(*F);

  return F;
}

/* Statements */
Value *ReturnAST::Codegen(llvm::LLVMContext& context) {
  return NULL;
}

/* Expressions */
Value *LiteralExprAST::Codegen(llvm::LLVMContext& context) {
  return ConstantFP::get(context, APFloat(val));
}
