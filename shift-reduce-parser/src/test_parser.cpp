#include <iostream>
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "gtest/gtest.h"

TEST(Parser,Example1) {
  auto lexer = calc::Lexer::fromFile("example1.calc");
  calc::Parser::Ptr parser(new calc::Parser(lexer));

  calc::ParseTree::Ptr parsetree = parser->parse();

  calc::ParseTree::Vars vars;

  vars["X"] = 10.0;
  ASSERT_EQ(parsetree->eval(vars), 3.0);
}


TEST(Parser,FromString) {
  auto lexer = calc::Lexer::fromString("(Cat+Dog)*X+18.0");
  calc::Parser::Ptr parser(new calc::Parser(lexer));

  calc::ParseTree::Ptr parsetree = parser->parse();

  calc::ParseTree::Vars vars;

  double X = 10.0;
  double Cat = 9.0;
  double Dog = 7;

  vars["X"] = X;
  vars["Cat"] = Cat;
  vars["Dog"] = Dog;

  ASSERT_EQ(parsetree->eval(vars), (Cat+Dog)*X+18.0);
}

