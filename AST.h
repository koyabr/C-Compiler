/*generate a systax tree
 *also perform type check
 */


#ifndef AST_H
#define AST_H

#include "globals.h"


/* make a new raw AST tree node */
TreeNode* newASTNode(ASTType asttype, int lineno);

TreeNode* newDecList(TreeNode* decList, TreeNode* declaration); // decList==NULL => declaration
TreeNode* newDec(TreeNode* declaration, int type);             // type: 0=var, 1=fun
TreeNode* newVarDec(TreeNode* typeSpecifier, char* ID, int lineno);
TreeNode* newArrayDec(TreeNode* typeSpecifier, char* ID, int size, int lineno);
TreeNode* newTypeSpe(ExpType type, int lineno);
TreeNode* newFunDec(TreeNode* funHead, TreeNode* funBody, int lineno);
TreeNode* newFunHead(TreeNode* typeSpecifier, char* ID, TreeNode* params, int lineno);
TreeNode* newParamList(TreeNode* paramList, TreeNode* param); // paramList==NULL => param_list:param
TreeNode* newParam(TreeNode* typeSpecifier, char* ID, int type, int lineno); // type: 1=id is array 0=otherwise
TreeNode* newCompound(TreeNode* localDecs, TreeNode* stmtList, int lineno);
TreeNode* newLocalDecs(TreeNode* localDecs, TreeNode* varDec);
TreeNode* newStmtList(TreeNode* stmtList, TreeNode* stmt, int lineno);
TreeNode* newExpStmt(TreeNode* expression,int lineno); // stmt==NULL => expression_stmt: SEMI
TreeNode* newSelectStmt(TreeNode* expression, TreeNode* stmt, TreeNode* elseStmt, int lineno);
TreeNode* newIterStmt(TreeNode* expression,  TreeNode* stmt, int lineno);
TreeNode* newRetStmt(TreeNode* expression, int lineno); // expression=NULL => return_stmt: RETURN SEMI;


TreeNode* newAssignExp(TreeNode* var, TreeNode* expressio, int linenon);


TreeNode* newVar(char* ID, int lineno);
TreeNode* newArrayVar(char* ID, TreeNode* expression, int lineno);


TreeNode* newSimpExp(TreeNode* addExp1, int relop, TreeNode* addExp2, int lineno);
TreeNode* newAddExp(TreeNode* addExp, int addop, TreeNode* term, int lineno);
TreeNode* newTerm(TreeNode* term, int mulop, TreeNode* factor, int lineno);
TreeNode* newNumNode(int num, int lineno);
TreeNode* newCall(char* ID, TreeNode* args, int lineno);
TreeNode* newArgList(TreeNode* argList, TreeNode* expression); 


/* prints a formatted listing of the syntax tree contents */
void printAST(TreeNode* root, int indent);


#endif
