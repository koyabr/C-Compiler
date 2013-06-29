/* Lex Scanner */

%{
#include "globals.h"
#include "parse.h"
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

">" {return GT;}
"<" {return LT;}
">=" {return GE;}
"<=" {return LE;}
"==" {return EQ;}
"!=" {return NE;}

{number} {
	yylval.value = atoi(yytext); 
	return NUMBER;
	}

{identifier} {
	yylval.name = strdup(yytext);
	return ID;
	}

{whitespace} {/* skip */}

. {fprintf(stderr, "MISS MATCH: %c\n", yytext[0]);}
%%
