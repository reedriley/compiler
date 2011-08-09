#include "expr_test.hh"

int main(int argv, char *argc[]) {
  LiteralExprAST expr = LiteralExprAST(1.2);
  expr.Codegen()->dump();
  return 0;
}
