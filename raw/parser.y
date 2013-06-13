%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "parser.tab.h"
     extern int yylineno;
     extern char* yytext;
     %}

/* if else return while int void */
%token IF ELSE RETURN WHILE INT VOID
 /* ( ) { } " [ ] , ; \n =  */
%token LBracket RBracket LBrace RBrace Quote LSB RSB COMMA SEMI NEWLINE ASSIGN
%token BLANK

 /* - + * / | &  */
%left MINUS PLUS MULTI DIV OR AND
 /* > < >= <= == || && */
%left B S BE SE EQ COR CAND NE


%token <value>NUMBER
%token <name>ID


%type <sym> expression var simple_expression additive_expression term factor call type_specifier


%union{
     char* name;                /* terminal token: for symbol's name */
     int value;                 /* terminal token: for number */
     struct symbol sym;         /* unterminal token: symbol */
 }

%%
program: declaration_list			{}
;

declaration_list: declaration_list declaration 	{}
| declaration					{}
;

declaration: var_declaration			{}
| fun_declaration				{}
;

var_declaration: type_specifier ID SEMI 	{insert($2, $1.type);}
| type_specifier ID LSB NUMBER RSB SEMI		{insertArray($2, $1.type + ARRAY, $4);}
;

type_specifier: INT				{$1.type = INTEGER;}
| VOID						{$1.type = VOID;}
;

fun_declaration: type_specifier ID LBracket params RBracket compound_stmt {}
;

params: param_list				{}
| VOID						{}
;

param_list: param_list SEMI param		{}
| param						{}
;

param: type_specifier ID			{}
| type_specifier ID LSB RSB			{}
;

compound_stmt: LBrace local_declarations statement_list RBrace	{}
;

local_declarations: local_declarations var_declaration	{}
| 						{}
;

statement_list: statement_list statement	{}
| 						{}
;

statement: expression_stmt			{}
| compound_stmt					{}
| selection_stmt				{}
| iteration_stmt				{}
| return_stmt					{}
;

expression_stmt: expression SEMI		{}
| SEMI						{}
;

selection_stmt: IF LBracket expression RBracket statement	{}
| IF LBracket expression RBracket statement ELSE statement	{}
;

iteration_stmt: WHILE LBracket expression RBracket statement 	{}
;

return_stmt: RETURN SEMI			{}
| RETURN expression SEMI			{}
;

expression: var ASSIGN expression		{}
| simple_expression				{}
;

var: ID						{}
| ID LSB expression RSB				{}
;

simple_expression: additive_expression relop additive_expression	{}
| additive_expression				{}
;

relop: B					{}
| S						{}
| BE						{}
| SE						{}
| EQ						{}
| COR						{}
| CAND						{}
| NE						{}
;

additive_expression: additive_expression addop term	{}
| term						{}
;

addop: PLUS					{}
| MINUS						{}
;

term: term mulop factor				{}
| factor					{}
;

mulop: MULTI					{}
| DIV						{}
;

factor: LBracket expression RBracket 		{}
| var						{}
| call						{}
| NUMBER					{}
;

call: ID LBracket args RBracket			{}
;

args: arg_list					{}
| 						{}
;

arg_list: arg_list COMMA expression		{}
| expression					{}
;

%%

yyerror(char *errmsg)
{
     fprintf(stderr, "%d: %s at '%s' \n", yylineno, errmsg, yytext);
}
