#include "token.h"

namespace calc {
  Token::Token(const std::string &_text, Type _type,
	       const std::string &_file, int32_t _line, int32_t _column)
    : text(_text), type(_type), file(_file), line(_line), column(_column) {}

  Token::~Token() {}

  double Token::num() const {
    throw std::range_error("not a num");
  }

  std::string Token::id() const {
    throw std::range_error("not an id");
  }
  
  Token::Ptr Token::add(const std::string &_file, int32_t _line, int32_t _column) {
    return Ptr(new Token("+",ADD,_file,_line,_column));
  }
      
  Token::Ptr Token::sub(const std::string &_file, int32_t _line, int32_t _column) {
    return Ptr(new Token("-",SUB,_file,_line,_column));    
  }
  Token::Ptr Token::mul(const std::string &_file, int32_t _line, int32_t _column) {
    return Ptr(new Token("*",MUL,_file,_line,_column));
  }
  Token::Ptr Token::div(const std::string &_file, int32_t _line, int32_t _column) {
    return Ptr(new Token("/",DIV,_file,_line,_column));
  }
  Token::Ptr Token::lp(const std::string &_file, int32_t _line, int32_t _column) {
    return Ptr(new Token("(",LP,_file,_line,_column));
  }
  Token::Ptr Token::rp(const std::string &_file, int32_t _line, int32_t _column) {
    return Ptr(new Token(")",RP,_file,_line,_column));
  }
  Token::Ptr Token::num(const std::string &_text, const std::string &_file, int32_t _line, int32_t _column) {
    return Ptr(new NumberToken(_text,_file,_line,_column));
  }
  Token::Ptr Token::id(const std::string &_text, const std::string &_file, int32_t _line, int32_t _column) {
    return Ptr(new IdToken(_text,_file,_line,_column));
  }
  Token::Ptr Token::eol(const std::string &_file, int32_t _line, int32_t _column) {
    return Ptr(new Token("<EOL>",EOL,_file,_line,_column));
  }

  Token::Ptr Token::end(const std::string &_file, int32_t _line, int32_t _column) {
    return Ptr(new Token("<EOL>",END,_file,_line,_column));
  }

  const char *Token::strtype(Type type) {
    switch(type) {
    case ADD: return "ADD";
    case SUB: return "SUB";
    case MUL: return "MUL";
    case DIV: return "DIV";
    case RP: return "RP";
    case LP: return "LP";
    case NUM: return "NUM";
    case ID: return "ID";      
    case EOL: return "EOL";
    case END: return "END";
    default: return "?";
    }
  }

  void Token::print(std::ostream &out) const {
    out << "Token(" << text << "," << strtype(type) << "," << file << "," << line << "," << column << ")";
  }

  NumberToken::NumberToken(const std::string &_text, 
	       const std::string &_file, int32_t _line, int32_t _column)
    : Token(_text,Token::NUM,_file,_line,_column) {}

  NumberToken::~NumberToken() {}
  
  double NumberToken::num() const {
    return atof(text.c_str());
  }

  void NumberToken::print(std::ostream &out) const {
    out << "NumberToken(" << text << "," << Token::strtype(type) << "," << file << "," << line << "," << column << ")";
  }


  IdToken::IdToken(const std::string &_text, 
	       const std::string &_file, int32_t _line, int32_t _column)
    : Token(_text,Token::ID,_file,_line,_column) {}

  IdToken::~IdToken() {}
  
  std::string IdToken::id() const {
    return text;
  }

  void IdToken::print(std::ostream &out) const {
    out << "IdToken(" << text << "," << Token::strtype(type) << "," << file << "," << line << "," << column << ")";
  }
  

  std::ostream& operator<<(std::ostream &out, const Token::Ptr &token) {
    token->print(out);
    return out;
  }
}
