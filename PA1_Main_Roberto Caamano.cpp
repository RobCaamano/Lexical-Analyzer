// Roberto Caamano
// Project Assignment 1

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <map>
#include <type_traits>
#include <list>
#include "lex.h"

using namespace std;

int main(int argc, char** argv){
    // Open file in read mode
    istream *input = &cin;
    ifstream inFile;

    if(argc<=1){
        cout<<"NO SPECIFIED INPUT FILE NAME.\n";
        exit(-1);
    }

    // Create flags as bools
    bool v = false, ident = false, strconst = false, iconst = false, fconst = false;

    // Check flags
    for(int i =1; i<argc; i++){
        string flags = argv[i];
        if(flags == "-v"){
            v = true;
        }else if(flags =="-ident"){
            ident = true;
        }else if(flags == "-strconst"){
            strconst = true;
        }else if(flags == "-iconst"){
            iconst = true;
        }else if(flags == "-fconst"){
            fconst = true;
        }else if(flags[0] == '-'){
            cout<< "UNRECOGNIZED FLAG " << flags <<"\n";
            exit(-1);
        }else if (i == 1){
            inFile.open(flags);
            if( inFile.is_open() == false ){
                cout << "CANNOT OPEN the File "<< flags <<"\n";
                exit(-1);
            }else {
                input = &inFile;
            }
        }else{
            cout << "ONLY ONE FILE NAME ALLOWED\n";
            exit(-1);
        }
    }

    int linenumber = 1;
    int cur = 0;
    LexItem lex;

    // List of each type
    list<string> idents;
    list<float> rconsts;
    list<int> iconsts;
    list<string> strconsts;

    while((lex = getNextToken(*input, linenumber))!= ERR && lex!= DONE){
        cur++;

        // Check v flag and type
        if(v)
            cout << lex << endl;
        if(lex.GetToken()==IDENT)
            idents.push_back(lex.GetLexeme());
        if(lex.GetToken()==RCONST)
            rconsts.push_back(stof(lex.GetLexeme()));
        if(lex.GetToken()==ICONST)
            iconsts.push_back(stoi(lex.GetLexeme()));
        if(lex.GetToken()==SCONST)
            strconsts.push_back(lex.GetLexeme());
    }

    if(lex.GetToken()==ERR){
        cout << "Error in line " << linenumber << " (" << lex.GetLexeme() << ")\n";
        return 0;
    }

    // Return num lines
    cout << "Lines: " << linenumber-1 << "\n";
    if(cur >= 1){
        cout<<"Tokens: " << cur << "\n";
    }

    // Check v, ident, strconst, iconst, fconst

    if(strconst && strconsts.size() > 0){
        strconsts.unique();
        strconsts.sort();
        cout << "STRINGS:\n";
        for(string i : strconsts)
            cout <<"\""<< i <<"\"\n";
    }

    if(iconst && iconsts.size() > 0){
        iconsts.sort();
        iconsts.unique();
        cout << "INTEGERS:\n";
        for(int i : iconsts)
            cout << i << "\n";
    }

    if(fconst && rconsts.size() > 0){
        rconsts.unique();
        rconsts.sort();
        cout << "REALS:\n";
        for(float i : rconsts)
            cout << i << "\n";
    }

    if(ident){
        idents.sort();
        idents.unique();
        cout << "IDENTIFIERS:\n";
        for(string i : idents){
            cout << i;
            if(i.compare(idents.back()))
                cout <<", ";
        }
        cout << "\n";
    } 
    return 0;

}