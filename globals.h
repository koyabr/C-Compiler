#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define ASSERT(x) for(;!(x);assert(x))

#define MAXSTACK 100

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

//#define DEBUG_SYM

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int yylineno;
extern char* yytext;


/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

#define MAXCHILDREN 4


typedef enum{GLOBAL, LOCAL, PARAM} Scope;
/* ExpType is used for type checking */
typedef enum {TYPE_INTEGER, TYPE_VOID, TYPE_ARRAY, TYPE_UNDEFINED} ExpType;

typedef enum {VARDEC_AST, ARRAYDEC_AST, FUNDEC_AST,
              TYPE_AST,
              PARAMID_AST, PARAMARRAY_AST,
              COMPOUND_AST,
              EXPSTMT_AST, SELESTMT_AST, ITERSTMT_AST, RETSTMT_AST, ASSIGN_AST,
              EXP_AST, VAR_AST, ARRAYVAR_AST,
              FACTOR_AST,
              CALLSTMT_AST, NUM_AST} ASTType;

typedef struct var_symbol VarSymbol;
struct var_symbol {
     char* name;
     Scope scope;
     ExpType type;
     int offset;
     struct var_symbol* next;
};

typedef struct symbol_table SymbolTable;
struct symbol_table {
     int startOffset;
     Scope scope;
     VarSymbol* hashTable[SIZE];
     struct symbol_table* next;
};

typedef struct fun_symbol FunSymbol;
struct fun_symbol {
     char* name;
     int offset;
     int paramNum;
     VarSymbol* paramList;
     SymbolTable* symbolTable;
     struct fun_symbol* next;
};

typedef struct ASTNode TreeNode;
struct ASTNode{
     int lineno;
     struct ASTNode* child[MAXCHILDREN];
     struct ASTNode* sibling;
     ASTType astType;
     ExpType type; /* for type checking of exps */
     struct{
          int op;
          int value;
          char* name;
     } attr;
     SymbolTable* symbolTable;

};


extern SymbolTable* CompoundST;
extern SymbolTable* ParamST;
extern SymbolTable* tables;
extern TreeNode *ASTRoot;

void ErrorMsg(TreeNode* t, char* message, char* ID);


/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */

extern int Error;

#endif
