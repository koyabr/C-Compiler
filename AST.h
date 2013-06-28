/*generate a systax tree*/


#ifndef AST_H
#define AST_H

#include "globals.h"

/* Procedure printAST prints a formatted 
 * listing of the syntax tree contents 
 * to the listing file
 */
void printAST(TreeNode* root, int indent);
  /* counter for variable memory locations */

TreeNode* newProgram(TreeNode* decList);
TreeNode* newDecList(TreeNode* decList, TreeNode* declaration); // decList==NULL => declaration
TreeNode* newDec(TreeNode* declaration, int type);             // type: 0=var, 1=fun
TreeNode* newVarDec(TreeNode* typeSpecifier, char* ID, int lineno);
TreeNode* newArrayDec(TreeNode* typeSpecifier, char* ID, int size, int lineno);
TreeNode* newTypeSpe(ExpType type, int lineno);
TreeNode* newFunDec(TreeNode* typeSpecifier, char* ID, TreeNode* params, TreeNode* compound, int lineno);
TreeNode* newParams(TreeNode* paramList); // paramList==NULL => params: VOID
TreeNode* newParamList(TreeNode* paramList, TreeNode* param); // paramList==NULL => param_list:param
TreeNode* newParam(TreeNode* typeSpecifier, char* ID, int type, int lineno); // type: 1=id is array 0=otherwise
TreeNode* newCompound(TreeNode* localDecs, TreeNode* stmtList, int lineno);
TreeNode* newLocalDecs(TreeNode* localDecs, TreeNode* varDec);
TreeNode* newStmtList(TreeNode* stmtList, TreeNode* stmt);
TreeNode* newStmt(TreeNode* stmt); // stmt includes 5 types
TreeNode* newExpStmt(TreeNode* expression,int lineno); // stmt==NULL => expression_stmt: SEMI
TreeNode* newSelectStmt(TreeNode* expression, TreeNode* stmt, TreeNode* elseStmt, int lineno);
TreeNode* newIterStmt(TreeNode* expression,  TreeNode* stmt, int lineno);
TreeNode* newRetStmt(TreeNode* expression, int lineno); // expression=NULL => return_stmt: RETURN SEMI;
TreeNode* newAssignExp(TreeNode* var, TreeNode* expressio, int linenon); // assign statement
TreeNode* newExpression(TreeNode* simpExp);
TreeNode* newVar(char* ID, int lineno);
TreeNode* newArrayVar(char* ID, TreeNode* expression, int lineno);
// relop==NULL & addExp2==NULL => simple_expression: additive expression
TreeNode* newSimpExp(TreeNode* addExp1, int relop, TreeNode* addExp2, int lineno);

TreeNode* newRelop(int opType);
TreeNode* newAddExp(TreeNode* addExp, int addop, TreeNode* term, int lineno);
TreeNode* newAddOp(int opType);
TreeNode* newTerm(TreeNode* term, int mulop, TreeNode* factor, int lineno);
TreeNode* newTermFactor(TreeNode* factor);
TreeNode* newMulop(int opType);
TreeNode* newFactorExp(TreeNode* expression);
TreeNode* newFactorVar(TreeNode* var);
TreeNode* newFactorCall(TreeNode* call);
TreeNode* newFactorNum(int num);
TreeNode* newCall(char* ID, TreeNode* args, int lineno);
TreeNode* newArgs(TreeNode* argList); // argList=NULL => args:
TreeNode* newArgList(TreeNode* argList, TreeNode* expression); // argList==NULL
TreeNode* newASTNode(ASTType asttype, int lineno);
TreeNode* newNumNode(int num, int lineno);
#endif
