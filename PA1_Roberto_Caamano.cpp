#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <map>
#include <type_traits>
#include "lex.h"

using namespace std;

static map<Token, string> tokens = {
    // Identifier
    { IDENT, "IDENT" },

    // Integer Consant
    { ICONST, "ICONST" },

    // Real Constant
    { RCONST, "RCONST" },

    // String Constant
    { SCONST, "SCONST" },

    // Reserved words
    { PROGRAM, "PROGRAM" },
    { END, "END" },
    { BEGIN, "BEGIN" },
    { WRITE, "WRITE" },
    { IF, "IF" },
    { INT, "INT" },
    { FLOAT, "FLOAT" },
    { STRING, "STRING" },
    { REPEAT, "REPEAT" },
    
     // Stuff
    { PLUS, "PLUS" },
    { MINUS, "MINUS" },
    { MULT, "MULT" },
    { DIV, "DIV" },
    { REM, "REM" },
    { ASSOP, "ASSOP" },
    { LPAREN, "LPAREN" },
    { RPAREN, "RPAREN" },
    { EQUAL, "EQUAL" },
    { GTHAN, "GTHAN" },

    // Semicol & comma
    { SEMICOL, "SEMICOL" },
    { COMMA, "COMMA" },
};

static map<string, Token> kwmap = {
    // Integer
    {"INT", INT },

    // FLOAT
    {"FLOAT", FLOAT },

    // String
    { "STRING", STRING },

    // Reserved words
    { "PROGRAM", PROGRAM },
    { "END", END },
    { "BEGIN", BEGIN },
    { "WRITE", WRITE },
    { "IF", IF },
    { "REPEAT", REPEAT },
    
};

// identifier or keyword ***
LexItem id_or_kw(const string& lexeme, int linenumber){
    Token t = IDENT;
    auto now = kwmap.find(lexeme);
    if(now != kwmap.end())
        t = now->second;
    return LexItem(t , lexeme, linenumber);
}

ostream& operator<<(ostream& out, const LexItem& tokenToPrint) {
	Token toktype = tokenToPrint.GetToken();
	out << tokens[ toktype ];
	if( toktype == IDENT || toktype == RCONST || toktype == ICONST || toktype == SCONST || toktype == ERR ) {
		out << "(" << tokenToPrint.GetLexeme() << ")";
	}
	return out;
}



LexItem getNextToken(istream& in, int& linenumber){
    
    char cur;
    string lexeme;

    // create lexstate
    enum TokState {START, INSIDEID, INSIDEINT, INSIDEFLOAT, INSIDESTR, COMM, EQUALS} lexstate = START;
    

    while(in.get(cur)){

        if(cur == '\n')
            linenumber++;
        
        switch (lexstate){
        Token t;
        // Initial case
        case START:
            if(isspace(cur))
                continue;
            if(isalpha(cur))
                lexeme = toupper(cur);
            else
                lexeme = cur;
            if(isdigit(cur)){
                lexstate = INSIDEINT;
            }
            else if(isalpha(cur)){
                lexstate = INSIDEID;
            }
            else if(cur == '"'){
                lexstate = INSIDESTR;
            }
            else if(cur == '.'){
                if(isdigit(in.peek()))
                    lexstate = INSIDEFLOAT;
                else{
                    lexeme+=in.peek();
                    return LexItem(ERR,lexeme,linenumber);
                }
            }
            else if(cur == '#'){
                lexstate = COMM;
            }
            else if(cur == '='){
                lexstate = EQUALS;
            }
            else{
                if (cur == '+') 
                    t= PLUS;
        
                else if (cur == '-')
                    t= MINUS;
            
                else if (cur == '*')
                    t= MULT;
            
                else if (cur == '/')
                    t=DIV;
                
                else if (cur == '%')
                    t= REM;
             
                else if (cur == '(')
                    t= LPAREN;
             
                else if (cur == ')')
                    t= RPAREN;
             
                else if (cur == '>')
                    t= GTHAN;

                else if (cur == ',')
                    t = COMMA;

                else if (cur == ';')
                    t = SEMICOL;
                
                else t = ERR;
                return LexItem(t,lexeme,linenumber);
            }
            break;

            // Equals vs double equals
            case EQUALS:
                if(cur=='=')
                    return LexItem(EQUAL, lexeme, linenumber);
                else
                    return LexItem(ASSOP, lexeme, linenumber);
                break;

            // IDENTIFIERS
            case INSIDEID:
                if(isalpha(cur) || isdigit(cur) || cur == '_')
                    lexeme+=toupper(cur);
                else{
                    if(cur == '\n')
                        linenumber--;
                    in.putback(cur);
                    return (id_or_kw(lexeme, linenumber));
                }
                break;

            // Integer constant
            case INSIDEINT:
                if(cur == '.'){
                    lexeme+=cur;
                    if(isdigit(in.peek()))
                        lexstate = INSIDEFLOAT;
                    else
                        return LexItem(ERR, lexeme, linenumber);
                }
                else if(isdigit(cur))
                    lexeme+=cur;
                else if(isalpha(cur)){
                    lexeme+=cur;
                    lexstate = INSIDEID;
                } 
                else{
                    if(cur == '\n')
                        linenumber--;
                    in.putback(cur);
                    return LexItem(ICONST, lexeme, linenumber);   
                }
                break;

            // Real constants
            case INSIDEFLOAT:            
                if(isdigit(cur))
                    lexeme+=cur;
                else if(isalpha(cur)){
                    lexeme+=cur;
                    return LexItem(ERR, lexeme, linenumber);
                }
                else{
                    if(cur == '\n')
                        linenumber--;
                    in.putback(cur);
                    return LexItem(RCONST, lexeme, linenumber);
                }
                break;

            // String constant
            case INSIDESTR:
                if(cur == '\n'){
                    linenumber--;
                    in.putback(cur);
                    return LexItem(ERR , lexeme, linenumber);
                }
                lexeme+=cur;
                if(cur=='"'){
                    lexeme = lexeme.substr(1, lexeme.length()-2);
                    return LexItem(SCONST, lexeme, linenumber);
                }
                break;

            // Comment
            case COMM:
                if(cur=='\n')
                    lexstate=START;
                break;
        }
    }
    // EOF
    if(in.eof())
		return LexItem(DONE, "", linenumber);

    // ERROR
    return LexItem(ERR, "", linenumber);
}