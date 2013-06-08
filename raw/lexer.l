%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "parser.tab.h"
%}
%option noyywrap
%option yylineno


%%

"if" {return IF;}
"else" {return ELSE;}
"return" {return RETURN;}
"while" {return WHILE;}
"=" {return ASSIGN;}

"int" {return INT;}
"void" {return VOID;}

"(" return LBracket;
")" {return RBracket;}
"{" {return LBrace;}
"}" {return RBrace;}
"\"" {return Quote;}
"[" {return LSB;}
"]" {return RSB;}
"," {return COMMA;}
";" {return SEMI;}
"\n" {}

"-" {return MINUS;}
"+" {return PLUS;}
"*" {return MULTI;}
"/" {return DIV;}
"|" {return OR;}
"&" {return AND;}

">" {return B;}
"<" {return S;}
">=" {return BE;}
"<=" {return SE;}
"==" {return EQ;}
"!=" {return NE;}
"||" {return COR;}
"&&" {return CAND;}

[0-9]+ {yylval.value = atoi(yytext); return NUMBER;}
[a-zA-Z][a-zA-Z]* {yylval.name = strdup(yytext);return ID;}
[ \t]*
. {printf("MISS MATCH: %c\n", yytext[0]);}
%%
