#include "statements.hpp"

void ReturnAST::Codegen(llvm::LLVMContext& context, llvm::BasicBlock* block) {
  IRBuilder<> builder(context);
  builder.SetInsertPoint(block);
  builder.CreateRet(expr->Codegen(context));
}
