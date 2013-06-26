#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdio.h>
#define SIZE 101
#define SHIFT 4
#define ID_NAME_SIZE 128
typedef enum {TYPE_INTEGER, TYPE_VOID, TYPE_ARRAY} ExpType;
typedef enum {VARDEC_AST, ARRAYDEC_AST, FUNDEC_AST, /* decalration: variable, array, function */
              TYPE_AST,                             /* variable type */
              PARAMID_AST, PARAMARRAY_AST,          /* parameter */
              COMPOUND_AST,
              /* statement type */
              CALLSTMT_AST,EXPSTMT_AST, SELESTMT_AST, ITERSTMT_AST, RETSTMT_AST, ASSIGN_AST, 
              EXP_AST, VAR_AST, ARRAYVAR_AST,
              FACTOR_AST,
              /* immediate & ID */
              NUM_AST, ID_AST}ASTType;
struct symbol{
     char* name;               /* variable's name */
     ExpType type;        /* variable's type */
     int int_value;            /* variable's value if type==INTEGER */
     int num;                  /* length if type==array */
     ExpType array_type; /* type of array variable if type ==array */     
     int mem_location;        /* variable's location in TM memory  */
};

struct symbolNode{
     char* name;
     int line;
     struct symbolNode* next;
};
/* Node struct of Abstract Syntax Tree */
struct ASTNode{
     struct ASTNode* child[4];
     struct ASTNode* sibling;
     ASTType astType;
     union{
          int op;
          int value;
          char* name;
     } attr;
     ExpType type; /* for type checking of exps */
};
struct ASTNode* ASTRoot;
#endif
