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

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int yylineno;
extern char* yytext;


/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

#define MAXCHILDREN 4


typedef enum {VARDEC_AST, ARRAYDEC_AST, FUNDEC_AST,
              TYPE_AST,
              PARAMID_AST, PARAMARRAY_AST,
              COMPOUND_AST,
              EXPSTMT_AST, SELESTMT_AST, ITERSTMT_AST, RETSTMT_AST, ASSIGN_AST,
              EXP_AST, VAR_AST, ARRAYVAR_AST,
              FACTOR_AST,
              CALLSTMT_AST, ARGS_AST, ARGLIST_AST, NUM_AST, ID_AST} 
  ASTType;

typedef struct ASTNode TreeNode;
struct ASTNode{
     int lineno;
     struct ASTNode* child[MAXCHILDREN];
     struct ASTNode* sibling;
     ASTType astType;
     union{
          TokenType op;
          int value;
          char* name;
     } attr;
     ExpType type; /* for type checking of exps */
};

/* For symbol table */
struct symbol{
     char* name;               /* variable's name */
     ExpType type;        /* variable's type */
     int int_value;            /* variable's value if type==INTEGER */
     int num;                  /* length if type==array */
     ExpType array_type; /* type of array variable if type ==array */     
     int mem_location;        /* variable's location in TM memory  */
};

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
extern int Error; 

#endif
