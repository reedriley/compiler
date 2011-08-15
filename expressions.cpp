#include "expressions.hpp"

Value* LiteralExprAST::Codegen(llvm::LLVMContext& context) {
  return ConstantInt::get(context, APInt(64, val));
}
