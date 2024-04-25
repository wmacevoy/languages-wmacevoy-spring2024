#include <iostream>
#include "token.h"
#include "lexer.h"
#include "gtest/gtest.h"

TEST(Lexer,File) {
  auto lexer = calc::Lexer::fromFile("example1.calc");
  ASSERT_EQ(lexer->next()->type,calc::Token::NUM);
  ASSERT_EQ(lexer->next()->type,calc::Token::ADD);
  ASSERT_EQ(lexer->next()->type,calc::Token::NUM);
  ASSERT_EQ(lexer->next()->type,calc::Token::EOL);
  ASSERT_EQ(lexer->next()->type,calc::Token::END);
}

TEST(Lexer,String) {
  auto lexer = calc::Lexer::fromString("1+2\n");
  ASSERT_EQ(lexer->next()->type,calc::Token::NUM);
  ASSERT_EQ(lexer->next()->type,calc::Token::ADD);
  ASSERT_EQ(lexer->next()->type,calc::Token::NUM);
  ASSERT_EQ(lexer->next()->type,calc::Token::EOL);
  ASSERT_EQ(lexer->next()->type,calc::Token::END);
}


