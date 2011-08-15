#include "expr_test.hpp"
#include "gtest/gtest.h"

void foo(int& val) {
  val = 1;
}

TEST(BasicTest, Passing) {
  EXPECT_TRUE(true);
  EXPECT_FALSE(false);
}

TEST(BasicTest, Passing2) {
  EXPECT_TRUE(true);
  EXPECT_FALSE(false);
}

int main(int argv, char* argc[]) {
  llvm::LLVMContext context;

  int val = 2;
  foo(val);

  LiteralExprAST expr(val), expr2(2);
  ReturnAST ret(&expr), ret2(&expr2);

  std::vector<StatementAST*> stmts;
  stmts.push_back(&ret);
  stmts.push_back(&ret2);

  FunctionAST func("main", stmts);
  llvm::Value* result = func.Codegen(context);
  result->dump();

  testing::InitGoogleTest(&argv, argc);
  return RUN_ALL_TESTS();
}
