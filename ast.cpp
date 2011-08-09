#include "ast.hpp"

Value *LiteralExprAST::Codegen() {
  return ConstantFP::get(getGlobalContext(), APFloat(val));
}
