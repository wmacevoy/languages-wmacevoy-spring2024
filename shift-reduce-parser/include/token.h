#pragma once

#include <memory>
#include <string>
#include <stdint.h>

#include "calc_token.h"

namespace calc {
  struct Token {
    // These values are defined from %token in parser.y, so we use those values
    // here so the parser understands our token values.  These are the "terminals"
    enum Type {
	       ADD=CALC_TOKEN_ADD,
	       SUB=CALC_TOKEN_SUB,
	       MUL=CALC_TOKEN_MUL,
	       DIV=CALC_TOKEN_DIV,
	       LP=CALC_TOKEN_LP,
	       RP=CALC_TOKEN_RP,
	       NUM=CALC_TOKEN_NUM,
	       ID=CALC_TOKEN_ID,
	       EOL=CALC_TOKEN_EOL,
	       END=CALC_TOKEN_YYEOF // EOF conflicts with C constant
    };

    std::string text;
    Type type;
    std::string file;
    int32_t line;
    int32_t column;

    // convert to simple name "NUM" for NUM type, etc.
    static const char *strtype(enum Type type);

    virtual ~Token();
    Token(const std::string &_text,
	  Type _type,
	  const std::string &_file="",
	  int32_t _line=0,
	  int32_t _column=0);
    typedef std::shared_ptr < Token > Ptr;

    virtual double num() const; // only for NUM tokens
    virtual std::string id() const; // only for ID tokens

    // builders for each of the tokens we have
    static Ptr add(const std::string &_file="", int32_t _line = 0, int32_t _column = 0);
    static Ptr sub(const std::string &_file="", int32_t _line = 0, int32_t _column = 0);
    static Ptr mul(const std::string &_file="", int32_t _line = 0, int32_t _column = 0);
    static Ptr div(const std::string &_file="", int32_t _line = 0, int32_t _column = 0);
    static Ptr lp(const std::string &_file="", int32_t _line = 0, int32_t _column = 0);
    static Ptr rp(const std::string &_file="", int32_t _line = 0, int32_t _column = 0);
    static Ptr num(const std::string &_text, const std::string &_file="", int32_t _line = 0, int32_t _column = 0);
    static Ptr id(const std::string &_text, const std::string &_file="", int32_t _line = 0, int32_t _column = 0);    
    static Ptr eol(const std::string &_file="", int32_t _line = 0, int32_t _column = 0);
    static Ptr end(const std::string &_file="", int32_t _line = 0, int32_t _column = 0);

    virtual void print(std::ostream &out) const;
    // create token table
  };

  struct NumberToken : Token {
    NumberToken(const std::string &_text,
		const std::string &_file="",
		int32_t _line=0,
		int32_t _column=0);
    virtual double num() const;
    virtual void print(std::ostream &out) const;    
    virtual ~NumberToken();
  };

  struct IdToken : Token {
    IdToken(const std::string &_text,
		const std::string &_file="",
		int32_t _line=0,
		int32_t _column=0);
    virtual std::string id() const;
    virtual void print(std::ostream &out) const;    
    virtual ~IdToken();
  };
  
  std::ostream& operator<<(std::ostream &out, const Token::Ptr &token);
}
