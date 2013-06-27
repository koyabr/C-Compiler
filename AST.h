/*generate a systax tree*/


#ifndef AST_H
#define AST_H

#include "globals.h"

/* Procedure printAST prints a formatted 
 * listing of the syntax tree contents 
 * to the listing file
 */
void printAST(TreeNode* root, int indent);

TreeNode* newProgram(TreeNode* decList);
TreeNode* newDecList(TreeNode* decList, TreeNode* declaration); // decList==NULL => declaration
TreeNode* newDec(TreeNode* declaration, int type);             // type: 0=var, 1=fun
TreeNode* newVarDec(TreeNode* typeSpecifier, char* ID);
TreeNode* newArrayDec(TreeNode* typeSpecifier, char* ID, int size);
TreeNode* newTypeSpe(ExpType type);
TreeNode* newFunDec(TreeNode* typeSpecifier, char* ID, TreeNode* params, TreeNode* compound);
TreeNode* newParams(TreeNode* paramList); // paramList==NULL => params: VOID
TreeNode* newParamList(TreeNode* paramList, TreeNode* param); // paramList==NULL => param_list:param
TreeNode* newParam(TreeNode* typeSpecifier, char* ID, int type); // type: 1=id is array 0=otherwise
TreeNode* newCompound(TreeNode* localDecs, TreeNode* stmtList);
TreeNode* newLocalDecs(TreeNode* localDecs, TreeNode* varDec);
TreeNode* newStmtList(TreeNode* stmtList, TreeNode* stmt);
TreeNode* newStmt(TreeNode* stmt); // stmt includes 5 types
TreeNode* newExpStmt(TreeNode* expression); // stmt==NULL => expression_stmt: SEMI
TreeNode* newSelectStmt(TreeNode* expression, TreeNode* stmt, TreeNode* elseStmt);
TreeNode* newIterStmt(TreeNode* expression,  TreeNode* stmt);
TreeNode* newRetStmt(TreeNode* expression); // expression=NULL => return_stmt: RETURN SEMI;
TreeNode* newAssignExp(TreeNode* var, TreeNode* expression); // assign statement
TreeNode* newExpression(TreeNode* simpExp);
TreeNode* newVar(char* ID);
TreeNode* newArrayVar(char* ID, TreeNode* expression);
// relop==NULL & addExp2==NULL => simple_expression: additive expression
TreeNode* newSimpExp(TreeNode* addExp1, int relop, TreeNode* addExp2);

TreeNode* newRelop(int opType);
TreeNode* newAddExp(TreeNode* addExp, int addop, TreeNode* term);
TreeNode* newAddOp(int opType);
TreeNode* newTerm(TreeNode* term, int mulop, TreeNode* factor);
TreeNode* newTermFactor(TreeNode* factor);
TreeNode* newMulop(int opType);
TreeNode* newFactorExp(TreeNode* expression);
TreeNode* newFactorVar(TreeNode* var);
TreeNode* newFactorCall(TreeNode* call);
TreeNode* newFactorNum(int num);
TreeNode* newCall(char* ID, TreeNode* args);
TreeNode* newArgs(TreeNode* argList); // argList=NULL => args:
TreeNode* newArgList(TreeNode* argList, TreeNode* expression); // argList==NULL
TreeNode* newASTNode(ASTType asttype);
TreeNode* newIDNode(char* ID);
TreeNode* newNumNode(int num);


#endif