#include "declarations.hpp"

static Module* TheModule;

Value* FunctionAST::Codegen(llvm::LLVMContext& context) {
  IRBuilder<> Builder(context);

  std::vector<const Type*> args;
  FunctionType* FT = FunctionType::get(Type::getDoubleTy(context), args, false);
  Function* F = Function::Create(FT, Function::ExternalLinkage, name, TheModule);

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

  BasicBlock* cur_block = BasicBlock::Create(context, "", F);

  std::vector<StatementAST*>::iterator p;
  for (p = stmts.begin(); p != stmts.end(); p++) {
    (*p)->Codegen(context, F, cur_block);
  }

  verifyFunction(*F);

  return F;
}
