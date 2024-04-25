# Calc

Demonstrates flex/bison using modern C++ to generate a parse tree for a very simple grammar (src/parser.y)

```
program : program EOL statement | statement ;
statement : /* empty */ | e ;
e : e + t | t ;
t : t * f | f ;
f : id | num | ( e ) ;
```

Is is intentionally simple and incomplete (no subtract or divide for example) for extension.

# Structure

Token - represents the teminials of the language.  NumberToken and IdToken are derived from Token
because they represent additional information.  The lexer (built using flex from lexer.fl) converts the input into a sequence of tokens.

ParseTree - represents the nonterminals of the language.  The parser (built using bison from parser.y) converts the sequence of tokens from the lexer into a substitution tree (parse tree) that represent the input as a recursive sequence of terminal/token/leaf substitutions and non-terminal/parsetree/subtree substitutions.

Lexer - built using flex from src/lexer.fl and wrapped as a a class in lexer.h.

Parser - built using bison from src/parser.y and wrapped as a class in parser.h

## Build

make source # first-pass of building source using bison/flex
make all
