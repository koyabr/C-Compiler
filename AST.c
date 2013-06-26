#include "AST.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
struct ASTNode* newProgram(struct ASTNode* decList)
{
     return decList;
}
// decList==NULL => declaration
struct ASTNode* newDecList(struct ASTNode* decList, struct ASTNode* declaration)
{
     struct ASTNode* root = NULL;
     struct ASTNode* node = decList;
     assert(declaration != NULL);
     // declaration_list: declaration_list declaration
     if(decList != NULL)
     {
          while(node->sibling != NULL)
               node = node->sibling;
          node->sibling = declaration;
          root = decList;
     }
     else                       // declaration_list: declaration
     {
          root = declaration;
     }
     return root;
}
// type: 0=var, 1=fun
struct ASTNode* newDec(struct ASTNode* declaration, int type)
{
     return declaration;
}
// var_declaration: type_specifier ID SEMI
struct ASTNode* newVarDec(struct ASTNode* typeSpecifier, char* ID)
{
     struct ASTNode* root = newASTNode(VARDEC_AST);
     root->child[0] = typeSpecifier;
     root->child[1] = newIDNode(ID);
     return root;
}
// var_declaration: type_specifier ID LSB NUMBER RSB SEMI
struct ASTNode* newArrayDec(struct ASTNode* typeSpecifier, char* ID, int size)
{
     struct ASTNode* root = newASTNode(ARRAYDEC_AST);
     root->child[0] = typeSpecifier;
     root->child[1] = newIDNode(ID);
     root->child[2] = newNumNode(size);
     return root;
}
struct ASTNode* newTypeSpe(ExpType type)
{
     struct ASTNode* root = newASTNode(TYPE_AST);
     root->type = type;
     return root;
}
// fun_declaration: type_specifier ID LBracket params RBracket compound_stmt
struct ASTNode* newFunDec(struct ASTNode* typeSpecifier, char* ID, struct ASTNode* params, struct ASTNode* compound)
{
     struct ASTNode* root = newASTNode(FUNDEC_AST);
     root->child[0] = typeSpecifier;
     root->child[1] = newIDNode(ID);
     root->child[2] = params;
     root->child[3] = compound;
     return root;
}
// paramList==NULL => params: VOID
struct ASTNode* newParams(struct ASTNode* paramList)
{
     // params: param_list
     struct ASTNode* root = NULL;
     if(paramList != NULL)
     {
          return paramList;
     }
     else
     {
          /* root = newASTNode(TYPE_AST); */
          /* root->type = TYPE_VOID; */
          return NULL;
     }
}
// paramList==NULL => param_list:param
struct ASTNode* newParamList(struct ASTNode* paramList, struct ASTNode* param)
{
     // param_list: param_list SEMI param
     struct ASTNode* node = paramList;
     if(paramList != NULL)
     {
          while(node->sibling != NULL)
               node = node->sibling;
          node->sibling = param;
          return paramList;
     }
     else // param_list: param
     {
          return param;
     }
}
// type: 1=id is array 0=otherwise
struct ASTNode* newParam(struct ASTNode* typeSpecifier, char* ID, int type)
{
     // param: type_specifier ID
     struct ASTNode* root = NULL;
     if(type == 0)
     {
          root = newASTNode(PARAMID_AST);
          root->child[0] = typeSpecifier;
          root->child[1] = newIDNode(ID);
     }
     else // param: type_specifier ID LSB RSB
     {
          root = newASTNode(PARAMARRAY_AST);
          root->child[0] = typeSpecifier;
          root->child[1] = newIDNode(ID);
     }
     return root;
}
struct ASTNode* newCompound(struct ASTNode* localDecs, struct ASTNode* stmtList)
{
     struct ASTNode* node = localDecs;
     struct ASTNode* root = newASTNode(COMPOUND_AST);
     root->child[0] = localDecs;
     root->child[1] = stmtList;
}
struct ASTNode* newLocalDecs(struct ASTNode* localDecs, struct ASTNode* varDec)
{
     struct ASTNode* node = localDecs;
     if(localDecs == NULL)
          return varDec;
     while(node->sibling != NULL)
          node = node->sibling;
     node->sibling = varDec;
     return localDecs;
}
struct ASTNode* newStmtList(struct ASTNode* stmtList, struct ASTNode* stmt)
{
     struct ASTNode* node = stmtList;
     if(stmtList == NULL)
          return stmt;
     while(node->sibling != NULL)
          node = node->sibling;
     node->sibling = stmt;
     return stmtList;
}
// stmt includes 5 type
struct ASTNode* newStmt(struct ASTNode* stmt)
{
     return stmt;
}
// stmt==NULL => expression_stmt: SEMI
struct ASTNode* newExpStmt(struct ASTNode* expression)
{
     struct ASTNode* root = newASTNode(EXPSTMT_AST);
     root->child[0] =expression;
     return root;
}    
struct ASTNode* newSelectStmt(struct ASTNode* expression, struct ASTNode* stmt, struct ASTNode* elseStmt)
{
     struct ASTNode* root = newASTNode(SELESTMT_AST);
     root->child[0] = expression;
     root->child[1] = stmt;
     root->child[2] = elseStmt;
     return root;
}
struct ASTNode* newIterStmt(struct ASTNode* expression,  struct ASTNode* stmt)
{
     assert(expression != NULL);
     struct ASTNode* root = newASTNode(ITERSTMT_AST);
     root->child[0] = expression;
     root->child[1] = stmt;
     return root;
}
// expression=NULL => return_stmt: RETURN SEMI;
struct ASTNode* newRetStmt(struct ASTNode* expression)
{
     struct ASTNode* root = newASTNode(RETSTMT_AST);
     root->child[0] = expression;
     return root;
}
// assign statement
struct ASTNode* newAssignExp(struct ASTNode* var, struct ASTNode* expression)
{
     struct ASTNode* root = newASTNode(ASSIGN_AST);
     root->child[0] = var;
     root->child[1] = expression;
     return root;
}
struct ASTNode* newExpression(struct ASTNode* simpExp)
{
     return simpExp;
}
struct ASTNode* newVar(char* ID)
{
     struct ASTNode* root = newASTNode(VAR_AST);
     root->child[0] = newIDNode(ID);
     return root;
}
struct ASTNode* newArrayVar(char* ID, struct ASTNode* expression)
{
     struct ASTNode* root = newASTNode(ARRAYVAR_AST);
     root->child[0] = newIDNode(ID);
     root->child[1] = expression;
     return root;
}
struct ASTNode* newSimpExp(struct ASTNode* addExp1, int relop, struct ASTNode* addExp2)
{
     struct ASTNode* root = NULL;
     /* simple_expression: additive_expression relop additive_expression */
     if(relop != -1)            
     {
          root = newASTNode(EXP_AST);
          root->child[0] = addExp1;
          root->child[1] = addExp2;
          root->attr.op = relop;
     }
     else                       /* simple_expression: additive_expression  */
     {
          root = addExp1;
     }
     return root;
}
struct ASTNode* newRelop(int opType)
{
     return NULL;
}
struct ASTNode* newAddExp(struct ASTNode* addExp, int addop, struct ASTNode* term)
{
     struct ASTNode* root = newASTNode(EXP_AST);
     root->child[0] = addExp;
     root->child[1] = term;
     root->attr.op = addop;
     return root;
}
struct ASTNode* newAddOp(int opType)
{
     return NULL;
}
struct ASTNode* newTerm(struct ASTNode* term, int mulop, struct ASTNode* factor)
{
     struct ASTNode* root = newASTNode(EXP_AST);
     root->child[0] = term;
     root->child[1] = factor;
     root->attr.op = mulop;
     return root;
}
struct ASTNode* newTermFactor(struct ASTNode* factor)
{
     return factor;
}
struct ASTNode* newCall(char* ID, struct ASTNode* args)
{
     struct ASTNode* root = newASTNode(CALLSTMT_AST);
     root->child[0] = newIDNode(ID);
     root->child[1] = args;
     return root;
}
struct ASTNode* newArgs(struct ASTNode* argList)
{
     return argList;
}
struct ASTNode* newArgList(struct ASTNode* argList, struct ASTNode* expression)
{
     struct ASTNode* node = argList;
     while(node->sibling != NULL)
          node = node->sibling;
     node->sibling = expression;
     return argList;
}
struct ASTNode* newASTNode(ASTType type)
{
     struct ASTNode* node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
     node->child[0] = NULL;
     node->child[1] = NULL;
     node->child[2] = NULL;
     node->child[3] = NULL;
     node->sibling = NULL;
     node->astType = type;
     return node;
}
struct ASTNode* newIDNode(char* ID)
{
     struct ASTNode* root = newASTNode(ID_AST);
     root->attr.name = strdup(ID);
     return root;
}
struct ASTNode* newNumNode(int num)
{
     struct ASTNode* root = newNumNode(NUM_AST);
     root->attr.value = num;
     return root;
}
void printNodeKind(struct ASTNode* node)
{
     if(node == NULL)
           return;
     switch(node->astType)
     {
     case VARDEC_AST:
          printf("Var declaration \n");
          break;
     case ARRAYDEC_AST:
          printf("Array declaration \n");
          break;
     case FUNDEC_AST:
          printf("Function declaration \n");
          break;
     case TYPE_AST:
          printf("Type specifier \n");
          break;
     case PARAMID_AST:
          printf("Param of ID \n");
          break;
     case PARAMARRAY_AST:
          printf("Param of Array \n");
          break;
     case COMPOUND_AST:
          printf("Counpound statements \n");
          break;
     case EXPSTMT_AST:
          printf("Expression statement\n");
          break;
     case SELESTMT_AST:
          printf("Select statement\n");
          break;
     case ITERSTMT_AST:
          printf("Iteration statement\n");
          break;
     case RETSTMT_AST:
          printf("Return statement\n");
          break;
     case ASSIGN_AST:
          printf("Assign statement\n");
          break;
     case EXP_AST:
          printf("Expression \n");
          break;
     case VAR_AST:
          printf("Var \n");
          break;
     case ARRAYVAR_AST:
          printf("Array var ASt\n");
          break;
     case FACTOR_AST:
          printf("Factor \n");
          break;
     case CALLSTMT_AST:
          printf("Call stement \n");
          break;
     case ARGS_AST:
          printf("Args\n");
          break;
     case ARGLIST_AST:
          printf("Arg List \n");
          break;
     case NUM_AST:
          printf("Number AST: %d\n", node->attr.value);
          break;
     case ID_AST:
          printf("ID AST: %s\n", node->attr.name);
          break;
     default:
          printf("No such AST type\n");
          break;
     }
}
void printAST(struct ASTNode* root, int indent)
{
     struct ASTNode* node = root;
     int i;
     while(node != NULL)
     {
          for (i = 0; i<indent; ++i)
          {
               printf("  ");
          }
          printNodeKind(node);
          printAST(node->child[0], indent+4);
          printAST(node->child[1], indent+4);
          printAST(node->child[2], indent+4); 
          printAST(node->child[3], indent+4);         
          node = node->sibling;
     }
}
