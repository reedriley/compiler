#include "statements.hpp"

void StatementAST::Codegen(llvm::LLVMContext& context, llvm::Function* func, llvm::BasicBlock* &block) {
  if (block == NULL) {
    // We should report this as a warning or error
    block = BasicBlock::Create(context, "unreachable", func);
  }
}

void ReturnAST::Codegen(llvm::LLVMContext& context, llvm::Function* func, llvm::BasicBlock* &block) {
  StatementAST::Codegen(context, func, block);

  IRBuilder<> builder(context);
  builder.SetInsertPoint(block);
  builder.CreateRet(expr->Codegen(context));

  block = NULL;
}
