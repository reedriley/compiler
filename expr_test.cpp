#include "expr_test.hpp"

int main(int argv, char *argc[]) {
  LiteralExprAST expr(1.2);
  FunctionAST func("foo", &expr);
  func.Codegen()->dump();
  return 0;
}
