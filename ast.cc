#include "ast.hh"

Value *LiteralExprAST::Codegen() {
  return ConstantFP::get(getGlobalContext(), APFloat(val));
}
