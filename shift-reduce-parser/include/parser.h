#pragma once

#include <memory>
#include "token.h"
#include "lexer.h"
#include "parsetree.h"

namespace calc {
  struct Parser {
    Lexer::Ptr lexer;
    
    void *yyps;

    ParseTree::Ptr parse();
    
    Parser(Lexer::Ptr _lexer);

    virtual ~Parser();

    ParseTree::Ptr result;

    typedef std::shared_ptr < Parser > Ptr;
  };
}
