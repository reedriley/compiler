#include "expr_test.hpp"

void foo(double& val) {
  val = 1.4;
}

int main(int argv, char *argc[]) {
  llvm::LLVMContext context;

  double val = 2;
  foo(val);

  LiteralExprAST expr(val);

  FunctionAST func("foo", &expr);
  llvm::Value *result = func.Codegen(context);
  result->dump();
  return 0;
}
