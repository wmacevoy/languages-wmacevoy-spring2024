#include "token.h"
#include "gtest/gtest.h"

using namespace std;

#define TEST_TOKEN(BUILD,TYPE)					      \
  {								      \
    ASSERT_EQ(strcmp(calc::Token::strtype(calc::Token::TYPE),#TYPE),0); \
    ASSERT_EQ(calc::Token::BUILD->type,calc::Token::TYPE);		\
  }

TEST(Token,Location) {
  string file = "file";
  int32_t line = 17;
  int32_t column = 81;
  calc::Token::Ptr add = calc::Token::add(file,line,column);
  ASSERT_EQ(add->file,file);
  ASSERT_EQ(add->line,line);
  ASSERT_EQ(add->column,column);
}

TEST(Token, Types) {
  TEST_TOKEN(add(),ADD);
  TEST_TOKEN(sub(),SUB);
  TEST_TOKEN(mul(),MUL);
  TEST_TOKEN(div(),DIV);
  TEST_TOKEN(lp(),LP);
  TEST_TOKEN(rp(),RP);
  TEST_TOKEN(num("33.3"),NUM);
  TEST_TOKEN(id("xyz"),ID);  
  TEST_TOKEN(eol(),EOL);
  TEST_TOKEN(end(),END);
}

TEST(Token,Number) {
  calc::Token::Ptr tk = calc::Token::num("33.3");
  ASSERT_NEAR(tk->num(),33.3,1e-12);
}

TEST(Token,ID) {
  calc::Token::Ptr tk = calc::Token::id("xyz");
  ASSERT_EQ(tk->id(),"xyz");
}
