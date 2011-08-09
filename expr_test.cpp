#include "expr_test.hpp"

int main(int argv, char *argc[]) {
  LiteralExprAST expr = LiteralExprAST(1.2);
  expr.Codegen()->dump();
  return 0;
}
