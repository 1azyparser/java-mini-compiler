%{
#include <iostream>
#include "Token.h"
#include "Node.h"
#include "Parser.h"

using std::cout;
using std::endl;
using std::cerr;

extern int yylineno;
int yylex();
%}


%%
"public" { return PUBLIC; }
"static" { return STATIC; }
"void" { return VOID; }
"main" { return MAIN; }
"String" { return STRING; }
"class" { return CLASS; }
"extends" { return EXTENDS; }
"return" { return RETURN; }
"int" { return TYPE_INT; }
"boolean" { return TYPE_BOOLEAN; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"System.out.println" { return PRINT_LINE; }
"this" { return THIS; }
"new" { return NEW; }
"true" {
    yylval.token = new Token(yylineno, TokenType::BOOLEAN, "true");
    return LITERAL_BOOLEAN;
}
"false" {
    yylval.token = new Token(yylineno, TokenType::BOOLEAN, "false");
    return LITERAL_BOOLEAN;
}
"length" { return LENGTH; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.token = new Token(yylineno, TokenType::ID, yytext);
    return IDENTIFIER;
}
[0-9]+ {
    yylval.token = new Token(yylineno, TokenType::INT, yytext);
    return LITERAL_INTEGER;
}
"&&" { return OP_LOGICAL_AND; }
"!"|"<"|"+"|"-"|"*"|"="|"["|"]"|"("|")"|"{"|"}"|";"|","|"." { return yytext[0]; }

"\n" { yylineno++; }
"//".* { /* skip a comment line */ }
"/*"(.|"\n")*"*\\" { yylineno++; }
[" "\r\t]+ { /* skip whitespaces */ }
. {
    cerr << "line " << yylineno << " ";
    cerr << "unexpected token: '" << yytext << "'" << endl;
}
%%

int yywrap() {
    return 1;
}
