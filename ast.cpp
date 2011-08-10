#include "ast.hpp"

static Module* TheModule;

/* Declarations */
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

  BasicBlock* entry = BasicBlock::Create(context, "entry", F);
  BasicBlock* retBlock = BasicBlock::Create(context, "ret", F);
  BasicBlock* ret2Block = BasicBlock::Create(context, "ret", F);

  Builder.SetInsertPoint(entry);
  Builder.CreateBr(retBlock);

  stmt->Codegen(context, retBlock);
  stmt->Codegen(context, ret2Block);

  verifyFunction(*F);

  return F;
}

/* Statements */
void ReturnAST::Codegen(llvm::LLVMContext& context, llvm::BasicBlock* block) {
  IRBuilder<> builder(context);
  builder.SetInsertPoint(block);
  builder.CreateRet(expr->Codegen(context));
}

/* Expressions */
Value* LiteralExprAST::Codegen(llvm::LLVMContext& context) {
  return ConstantFP::get(context, APFloat(val));
}
