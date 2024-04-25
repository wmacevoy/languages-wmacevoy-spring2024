#include <sstream>
#include <iostream>

#include "parsetree.h"

namespace calc {

  const char *ParseTree::strtype(Type type) {
    switch(type) {
    case PROGRAM: return "PROGRAM";
    case STATEMENT: return "STATEMENT";
    case E: return "E";
    case T: return "T";
    case F: return "F";
    default: return "?";
    }
  }
  
  double ParseTree::eval(Vars &vars) const { return evaluator(*this,vars); }
  
  ParseTree::ParseTree(Type _type, Evaluator _evaluator)
    : type(_type), evaluator(_evaluator), subs(0)
  {
  }

  ParseTree::ParseTree(Type _type, Evaluator _evaluator, Sub sub0)
    : type(_type), evaluator(_evaluator), subs(1)
  {
    subs.at(0)=sub0;
  }  
  ParseTree::ParseTree(Type _type, Evaluator _evaluator, Sub sub0, Sub sub1)
    : type(_type), evaluator(_evaluator), subs(2)
  {
    subs.at(0)=sub0;
    subs.at(1)=sub1;
  }  

  ParseTree::ParseTree(Type _type, Evaluator _evaluator, Sub sub0, Sub sub1, Sub sub2)
    : type(_type), evaluator(_evaluator), subs(3)
  {
    subs.at(0)=sub0;
    subs.at(1)=sub1;
    subs.at(2)=sub2;
  }

// safety check that sub if parsetree of given type
#define IS_PT(sub,TYPE) if (!std::holds_alternative<calc::ParseTree::Ptr>(sub) || !std::get<calc::ParseTree::Ptr>(sub) || std::get<calc::ParseTree::Ptr>(sub)->type != calc::ParseTree::TYPE) { std::ostringstream msg; msg << #sub << " is not " << calc::ParseTree::strtype(calc::ParseTree::TYPE) << " parse tree"; throw std::range_error(msg.str()); }

// safety check that sub is token of given type
#define IS_TK(sub,TYPE) if (!std::holds_alternative<calc::Token::Ptr>(sub) || !std::get<calc::Token::Ptr>(sub) || std::get<calc::Token::Ptr>(sub)->type != calc::Token::TYPE) { std::ostringstream msg; msg << #sub << " is not " << calc::Token::strtype(calc::Token::TYPE) << " token"; throw std::range_error(msg.str()); }

  // program -> program EOL statement
  ParseTree::Ptr ParseTree::program_ps(Sub program, Sub eol, Sub statement) {
    IS_PT(program,PROGRAM); IS_TK(eol,EOL); IS_PT(statement,STATEMENT);
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       // extract sub-tree components
		       int i=0;
		       auto &program = std::get<ParseTree::Ptr>(pt.subs[i++]);
		       auto &eol = std::get<Token::Ptr>(pt.subs[i++]);
		       auto &statement = std::get<ParseTree::Ptr>(pt.subs[i++]);

		       double value = program->eval(vars);
		       if (statement->subs.size() > 0) {
			 value = statement->eval(vars);
		       }
		       return value;
		     };
    return Ptr(new ParseTree(PROGRAM,evaluator,program,eol,statement));
  }

  // program -> statement
  ParseTree::Ptr ParseTree::program_s(Sub statement) {
    IS_PT(statement,STATEMENT);
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       // extract sub-tree components
		       int i=0;
		       auto &statement = std::get<ParseTree::Ptr>(pt.subs[i++]);

		       return statement->eval(vars);
		     };
    return Ptr(new ParseTree(PROGRAM,evaluator,statement));
  }

  // statement -> empty
  ParseTree::Ptr ParseTree::statement_empty() {
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       return 0.0;
		     };
    return Ptr(new ParseTree(STATEMENT,evaluator));
  }
  
  // statement -> e
  ParseTree::Ptr ParseTree::statement_e(Sub e) {
    IS_PT(e,E);    
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       // extract sub-tree components
		       int i=0;
		       auto &e = std::get<ParseTree::Ptr>(pt.subs[i++]);
		       double value = e->eval(vars);
		       std::cout << value << std::endl;
		       return value;
		     };
    return Ptr(new ParseTree(STATEMENT,evaluator,e));
  }

  // E->E+T
  ParseTree::Ptr ParseTree::e_add(Sub e, Sub add, Sub t) {
    IS_PT(e,E); IS_TK(add,ADD); IS_PT(t,T);
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       // extract sub-tree components
		       int i=0;
		       auto &e = std::get<ParseTree::Ptr>(pt.subs[i++]);
		       auto &add = std::get<Token::Ptr>(pt.subs[i++]);
		       auto &t = std::get<ParseTree::Ptr>(pt.subs[i++]);

		       return e->eval(vars) + t->eval(vars);
		     };

    return Ptr(new ParseTree(E,evaluator,e,add,t));
  }

  // E->T
  ParseTree::Ptr ParseTree::e_t(Sub t) {
    IS_PT(t,T);
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       // extract sub-tree components
		       int i=0;
		       auto &t = std::get<ParseTree::Ptr>(pt.subs[i++]);

		       return t->eval(vars);
		     };
    return Ptr(new ParseTree(E,evaluator,t));
  }

  // T->T*F
  ParseTree::Ptr ParseTree::t_mul(Sub t, Sub mul, Sub f) {
    IS_PT(t,T); IS_TK(mul,MUL); IS_PT(f,F);
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       // extract sub-tree components
		       int i=0;
		       auto &t = std::get<ParseTree::Ptr>(pt.subs[i++]);
		       auto &mul = std::get<Token::Ptr>(pt.subs[i++]);
		       auto &f = std::get<ParseTree::Ptr>(pt.subs[i++]);

		       return t->eval(vars) * f->eval(vars);
		     };

    return Ptr(new ParseTree(T,evaluator,t,mul,f));
  }

  // T->F
  ParseTree::Ptr ParseTree::t_f(Sub f) {
    IS_PT(f,F);
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       // extract sub-tree components
		       int i=0;
		       auto &f = std::get<ParseTree::Ptr>(pt.subs[i++]);

		       return f->eval(vars);
		     };
    return Ptr(new ParseTree(T,evaluator,f));
  }

  // F->num
  ParseTree::Ptr ParseTree::f_num(Sub num) {
    IS_TK(num,NUM);
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       // extract sub-tree components
		       int i=0;
		       auto &num = std::get<Token::Ptr>(pt.subs[i++]);

		       return num->num();
		     };
    return Ptr(new ParseTree(F,evaluator,num));
  }

  // F->id
  ParseTree::Ptr ParseTree::f_id(Sub id) {
    IS_TK(id,ID);
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       // extract sub-tree components
		       int i=0;
		       auto &id = std::get<Token::Ptr>(pt.subs[i++]);

		       return vars[id->id()];
		     };
    return Ptr(new ParseTree(F,evaluator,id));
  }

  // F->e
  ParseTree::Ptr ParseTree::f_e(Sub lp,Sub e,Sub rp) {
    IS_TK(lp,LP); IS_PT(e,E); IS_TK(rp,RP);
    auto evaluator = [](const ParseTree &pt, Vars &vars) {
		       // extract sub-tree components
		       int i=0;
		       auto &lp = std::get<Token::Ptr>(pt.subs[i++]);
		       auto &e = std::get<ParseTree::Ptr>(pt.subs[i++]);
		       auto &rp = std::get<Token::Ptr>(pt.subs[i++]);		       

		       return e->eval(vars);
		     };
    return Ptr(new ParseTree(F,evaluator,lp,e,rp));
  }
  
}
