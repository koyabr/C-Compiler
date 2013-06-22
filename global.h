#ifndef GLOBAL_H
#define GLOBAL_H
#define SIZE 101
#define SHIFT 4
#define ID_NAME_SIZE 128
enum VarType{TYPE_INTEGER, TYPE_ARRAY, TYPE_VOID};
enum ASTType{PROG_AST, DECLIST_AST, DEC_AST, VARDEC_AST, FUNDEC_AST, TYPESPE_AST, PARAMS_AST,
      PARAMLIST_AST, PARAM_AST, COMPOUND_AST, LOCALDEC_AST, STMTLIST_AST, STMT_AST,
      EXPSTMT_AST, SELESTMT_AST, ITERSTMT_AST, RETSTMT_AST, EXP_AST, VAR_AST, SIMPEXP_AST,
      RELOP_AST, ADDEXP_AST, ADDOP_AST, TERM_AST, MULOP_AST, FACTOR_AST, CALL_AST, ARGS_AST,
             ARGLIST_AST};
struct symbol{
     char* name;                /* variable's name */
     enum VarType type;              /* variable's type */
     int int_value;             /* variable's value if type==INTEGER */
     int num;                   /* length if type==array */
     enum VarType array_type;         /* type of array variable if type ==array */     
     int mem_location;          /* variable's location in TM memory  */
};
/* Node struct of Abstract Syntax Tree */
struct ASTNode{
     struct ASTNode* child;
     struct ASTNode* sibling;
     struct ASTNode* parent;
     enum ASTType type;
};
#endif
