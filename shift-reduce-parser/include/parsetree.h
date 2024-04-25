#pragma once

#include <variant>
#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <map>
#include "token.h"

namespace calc {
  struct ParseTree {
    // these are the "non-terminals"
    enum Type { PROGRAM, STATEMENT, E, T, F };
    Type type;
    // convert to simple name "E" for E type, etc.    
    static const char *strtype(Type type);
    typedef std::shared_ptr < ParseTree > Ptr;

    // productions like e -> e ADD t have terminals (token pointers) and nonterminals (parsetree pointers),
    // so is represented as a vector of "substitutions" of token/trees.
    typedef std::variant < Token::Ptr , ParseTree::Ptr > Sub;
    std::vector < Sub > subs;

    //
    // Vars (eventually) is how to have information about values like ID's
    // evaluator is a way to evaluate a parse tree given vars as map of
    // assignments
    //
    typedef std::map < std::string , double > Vars;
    typedef std::function < double (const ParseTree &,Vars &) > Evaluator;
    Evaluator evaluator;
    double eval(Vars &vars) const;

    ParseTree(Type _type, Evaluator _evaluator);
    ParseTree(Type _type, Evaluator _evaluator,Sub sub0);
    ParseTree(Type _type, Evaluator _evaluator,Sub sub0, Sub sub1);
    ParseTree(Type _type, Evaluator _evaluator,Sub sub0, Sub sub1, Sub sub2);

    // program -> program EOL statement | statement
    static Ptr program_ps(Sub program, Sub EOL, Sub statement);
    static Ptr program_s(Sub statement);
    
    // statement -> empty | E
    static Ptr statement_empty();
    static Ptr statement_e(Sub e);

    // E->E '+' T | T    
    static Ptr e_add(Sub e,Sub add,Sub t); 
    static Ptr e_t(Sub t);                 

    // T->T '*' F | F
    static Ptr t_mul(Sub t,Sub mul,Sub f);    
    static Ptr t_f(Sub f);

    // F->'(' E ')' | num | id
    static Ptr f_e(Sub lp, Sub e, Sub rp);
    static Ptr f_num(Sub num);
    static Ptr f_id(Sub id);
  };
}
