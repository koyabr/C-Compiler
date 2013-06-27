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


/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4


/* number of reserved words */
#define MAXRESERVED 6

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
typedef enum {TYPE_INTEGER, TYPE_VOID, TYPE_ARRAY, TYPE_BOOLEAN} ExpType;
typedef enum {VARDEC_AST, ARRAYDEC_AST, FUNDEC_AST,
              TYPE_AST,
              PARAMID_AST, PARAMARRAY_AST,
              COMPOUND_AST,
              EXPSTMT_AST, SELESTMT_AST, ITERSTMT_AST, RETSTMT_AST, ASSIGN_AST,
              EXP_AST, VAR_AST, ARRAYVAR_AST,
              FACTOR_AST,
              CALLSTMT_AST} ASTType;

struct VarSymbol {
     char* name;
     ExpType type;
     int offset;
     struct VarSymbol* next;
};
struct SymbolTable {
     int startOffset;
     Scope scope;
     struct VarSymbol* hashTable[SIZE];
     struct SymbolTable* next;
};
struct FunSymbol {
     char* name;
     Scope scope;
     int paramNum;
     struct SymbolTable* symbolTable;
     struct FunSymbol* next;
};
struct ASTNode{
     int lineno;
     struct ASTNode* child[MAXCHILDREN];
     struct ASTNode* sibling;
     ASTType astType;
     struct{
          int op;
          int value;
          char* name;
     } attr;
     struct SymbolTable* symbolTable;
     ExpType type; /* for type checking of exps */
};


typedef struct ASTNode TreeNode;

typedef struct VarSymbol* VarSymbol;

typedef struct FunSymbol* FunSymbol;

typedef struct SymbolTable* SymbolTable;

extern TreeNode *ASTRoot;




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

#endif
