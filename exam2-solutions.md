# Languages Exam 2

1. What does the expression `(a|b)(ab)*(ba)?` match?

* Either an "a" or a "b"
* Zero or more "ab"'s
* An optional "ba"

So a, b, aba, bba, aab, bab, ...

2. Tokens are usually described by regular expressions.  But what are tokens for?

They are the "atoms" of a compiler.  They are the leaf nodes of the parse tree.  The scanner transforms a sequence of characters (unicode codepoints) into a sequence of tokens.  The parser then uses the grammar to structure this into a parse tree for the language.

3. What is a grammar?

A set of substitution rules that define a language.  They are of the form 

NonTerminal --> string of terminal / NonTerminals

There is a top nonterminal "Start", and the set of strings that define the langage are all substitutions that end up with only terminals.

4. Make a parse tree for `(32-43)*cats*lives` using following grammar

```C
E --> T + E | T - E | T
T --> F * T | F / T | F
F --> number | id | ( E )
number --> /[0-9]+/
id --> /[a-z]+/
```

```C
        E
        |
        T
        |
  F     *      T
  |            |
 (E)       F   *   T
  |        |       |
 T-E    id(cats)   F
 |  \              |
 F   T             id(lives)
 |    \
 n(32) F
        \
         n(43)
```

5. What are the two main kinds of parsers?

Recursive descent, which are hand made and breaks on left recursive grammars.

Shift-reduce, which are built with tool assistance (like flex/bison), and are inefficient
on right recursive grammars.

6. What is the role of UTF-8 in the first phase of a compiler?

UTF-8 is the standard byte encoding of unicode.  Most text data is saved as UTF-8.  Scanners read bytes from files and use UTF-8 to convert these to a sequence of code points, which then can be used to match regular expressions to create the sequence of tokens (non-terminals) suitable for a parser.

7. JSON is a popular language for system communications like REST APIs.  Why is it an incomplete language?

If it were complete, then it would be a terrible security risk - it would be easy to deny-of-service just by sending some api a message with code that created infinite data or an infinite loop.

8. Garbage collectors are very convenient.  Why are languages with garbage collectors unsuitble for real-time systems?

Garbage collection takes an arbitrary amount of time at arbitraty points of execution, so it is impossible to account for how long it will take to run, and so unsuitable for real time systems.

9. Logic/constraint langugages is one category of programming languages.  What are two others?

Procedural
Object-Oriented
Functional

10. Why is rust an interesting language?

It is both memory safe and efficient.  All other memory safe languages have a garbage collector and so cannot be used in real-time or system critical applications (like kernel or drivers).