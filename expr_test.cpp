#include "expr_test.hpp"

void foo(double& val) {
  val = 1.4;
}

int main(int argv, char* argc[]) {
  llvm::LLVMContext context;

  double val = 2;
  foo(val);

  LiteralExprAST expr(val), expr2(2);
  ReturnAST ret(&expr), ret2(&expr2);

  std::vector<StatementAST*> stmts;
  stmts.push_back(&ret);
  stmts.push_back(&ret2);

  FunctionAST func("foo", stmts);
  llvm::Value* result = func.Codegen(context);
  result->dump();
  return 0;
}
