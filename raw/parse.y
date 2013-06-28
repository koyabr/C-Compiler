/*Yacc Parser*/

%{
#define YYPARSER

#include "globals.h"
#include "AST.h"


%}

/* if else return while int void */
%token IF ELSE RETURN WHILE INT VOID
 /* ( ) { } " [ ] , ; = */
%token LBracket RBracket LBrace RBrace Quote LSB RSB COMMA SEMI ASSIGN


 /* - + * / | & */
%left MINUS PLUS MULTI DIV 
 /* > < >= <= == != */
%left GT LT GE LE EQ NE



%token <value>NUMBER
%token <name>ID


%type <node> program declaration_list declaration var_declaration type_specifier fun_declaration
%type <node> params param_list param compound_stmt local_declarations statement_list statement
%type <node> expression_stmt selection_stmt iteration_stmt return_stmt expression var
%type <node> simple_expression additive_expression term factor call args arg_list
%type <value> relop addop mulop

%union{
     char* name; /* terminal token: for symbol's name */
     int value; /* terminal token: for number */
     struct ASTNode* node; /* unterminal token: abstract syntax tree node */
 }

%%
program: declaration_list			{ASTRoot = $1;}
;

 declaration_list: declaration_list declaration  {$$ = newDecList($1, $2);}
| declaration					{$$ = $1;}
;

declaration: var_declaration			{$$ = $1;}
| fun_declaration				{$$ = $1;}
;

var_declaration: type_specifier ID SEMI 	{$$ = newVarDec($1, $2, yylineno);}
| type_specifier ID LSB NUMBER RSB SEMI		{$$ = newArrayDec($1, $2, $4, yylineno);}
;

type_specifier: INT				{$$ = newTypeSpe(TYPE_INTEGER, yylineno);}
| VOID						{$$ = newTypeSpe(TYPE_VOID, yylineno);}
;

fun_declaration: type_specifier ID LBracket params RBracket compound_stmt {$$ = newFunDec($1, $2, $4, $6, yylineno);}
;

params: param_list				{$$ = newParams($1);}
| VOID						{$$ = newParams(NULL);}
;

param_list: param_list SEMI param		{$$ = newParamList($1, $3);}
| param						{$$ = newParamList(NULL, $1);}
;

param: type_specifier ID			{$$ = newParam($1, $2, 0, yylineno);}
| type_specifier ID LSB RSB			{$$ = newParam($1, $2, 1, yylineno);}
;

compound_stmt: LBrace local_declarations statement_list RBrace	{$$ = newCompound($2, $3, yylineno);}
;

local_declarations: local_declarations var_declaration	{$$ = newLocalDecs($1, $2);}
| 						{$$ = NULL}
;

statement_list: statement_list statement	{$$ = newStmtList($1, $2);}
| 						{$$ = NULL;}
;

statement: expression_stmt			{$$ = newStmt($1);}
| compound_stmt					{$$ = newStmt($1);}
| selection_stmt				{$$ = newStmt($1);}
| iteration_stmt				{$$ = newStmt($1);}
| return_stmt					{$$ = newStmt($1);}
;

expression_stmt: expression SEMI		{$$ = newExpStmt($1, yylineno);}
| SEMI						{$$ = NULL;}
;

selection_stmt: IF LBracket expression RBracket statement	{$$ = newSelectStmt($3,$5,NULL, yylineno);}
| IF LBracket expression RBracket statement ELSE statement	{$$ = newSelectStmt($3,$5,$7, yylineno);}
;

iteration_stmt: WHILE LBracket expression RBracket statement 	{$$ = newIterStmt($3, $5, yylineno);}
;

return_stmt: RETURN SEMI			{$$ = newRetStmt(NULL, yylineno);}
| RETURN expression SEMI			{$$ = newRetStmt($2, yylineno);}
;

expression: var ASSIGN expression		{$$ = newAssignExp($1, $3, yylineno);}
| simple_expression				{$$ = newExpression($1);}
;

var: ID						{$$ = newVar($1, yylineno);}
| ID LSB expression RSB				{$$ = newArrayVar($1, $3, yylineno);}
;

simple_expression: additive_expression relop additive_expression	{$$ = newSimpExp($1, $2, $3, yylineno);}
| additive_expression				{$$ = newSimpExp($1, -1, NULL, yylineno);}
;

relop: GT					{$$ = GT;}
| LT						{$$ = LT;}
| GE						{$$ = GE;}
| LE						{$$ = LE;}
| EQ						{$$ = EQ;}
| NE						{$$ = NE;}
;

additive_expression: additive_expression addop term	{$$ = newAddExp($1, $2, $3, yylineno);}
| term						{$$ = $1;}
;

addop: PLUS					{$$ = PLUS;}
| MINUS						{$$ = MINUS;}
;

term: term mulop factor				{$$ = newTerm($1, $2, $3, yylineno);}
| factor					{$$ = $1;}
;

mulop: MULTI					{$$ = MULTI;}
| DIV						{$$ = DIV;}
;

factor: LBracket expression RBracket 		{$$ = newTermFactor($2);}
| var						{$$ = newTermFactor($1);}
| call						{$$ = newTermFactor($1);}
| NUMBER					{$$ = newTermFactor(newNumNode($1, yylineno));}
;

call: ID LBracket args RBracket			{$$ = newCall($1, $3, yylineno);}
;

args: arg_list					{$$ = newArgs($1);}
| 						{$$ = NULL;}
;

arg_list: arg_list COMMA expression		{$$ = newArgList($1, $3);}
| expression					{$$ = $1;}
;

%%

int yyerror(char *errmsg)
{
     fprintf(stderr, "%d: %s at '%s' \n", yylineno, errmsg, yytext);
     return 0;
}
