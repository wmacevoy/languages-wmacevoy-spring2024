#pragma once

#include "token.h"
#include <iostream>
#include <memory>

namespace calc {
  struct Lexer {
    void *yyscanner;
    std::shared_ptr < std::istream > in;
    std::string file;
    int32_t line;
    int32_t column;
    virtual Token::Ptr next();
    Lexer();
    ~Lexer();

    typedef std::shared_ptr < Lexer > Ptr;

    static Ptr fromFile(const std::string &filename);
    static Ptr fromStdin();
    static Ptr fromString(const std::string &value);
  };
}
