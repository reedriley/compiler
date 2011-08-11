#include "expressions.hpp"

Value* LiteralExprAST::Codegen(llvm::LLVMContext& context) {
  return ConstantFP::get(context, APFloat(val));
}
