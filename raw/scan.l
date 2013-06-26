/* Lex Scanner */

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"
#include "scanner.h"
#include "parser.h"
%}
%option noyywrap
%option yylineno

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

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

{number} {
	yylval.value = atoi(yytext); 
	return NUMBER;
	}

identifier {
	yylval.name = strdup(yytext);
	return ID;
	}

whitespace {/* skip */}

. {printf("MISS MATCH: %c\n", yytext[0]);}
%%
