# Lexical-Analyzer
Lexical analyzer for simple programming language

Based on the language definitions, the lexical rules of the language and the assigned tokens to terminals are as follows:

1: The language has identifiers, referred to by ident terminal, which are defined to be a letter followed by zero or more letters or digit

2: Integer constants, referred to by iconst terminal, are defined as one or more digits

3: Real constants, referred to by rconst terminal, are defined as zero or more digits followed by a decimal point (dot) and one or more digits

4: String literals, referred to by sconst terminal, are defined as a sequence of characters delimited by double quotes, that should all appear on the same line. The assigned token for a string constant is SCONST

5: The reserved words of the language are: program, end, begin, write, if, int, float, string, repeat. These reserved words have the following tokens, respectively: PROGRAM, END, BEGIN, WRITE, IF, INT, FLOAT, STRING and REPEAT

6: The operators of the language are: +, -, *, /, %, =, (, ), ==, >. These operators are for plus, subtract, multiply, divide, remainder, assignment, left parenthesis, right parenthesis, equality, and greater than operations. They have the following tokens, respectively: PLUS, MINUS, MULT, DIV, REM, ASSOP, LPAREN, RPAREN, EQUAL, GTHAN

7: The semicolon and comma characters are terminals with the following tokens: SEMICOL, COMMA

8: A comment is defined by all the characters following the exclamation mark “#” to the end of the line. A comment does not overlap one line. A recognized comment is ignored and does not have a token

9: White spaces are skipped. However, white spaces between tokens are used to improve readability and can be used as a one way to delimit tokens

10: An error will be denoted by the ERR token

11: End of file will be denoted by the DONE token
