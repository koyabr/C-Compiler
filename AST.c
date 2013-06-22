#include "AST.h"
#include "global.h"
#include <stdio.h>
struct ASTNode* newProgram(struct ASTNode* decList){return NULL;}
struct ASTNode* newDecList(struct ASTNode* decList, struct ASTNode* declaration){return NULL;} // decList==NULL => declaration
struct ASTNode* newDec(struct ASTNode* declaration, int type){return NULL;}             // type: 0=var, 1=fun
struct ASTNode* newVarDec(struct ASTNode* typeSpecifier, char* ID){return NULL;}
struct ASTNode* newArrayDec(struct ASTNode* typeSpecifier, char* ID, int size){return NULL;}
struct ASTNode* newTypeSpe(enum VarType type){return NULL;}
struct ASTNode* newFunDec(struct ASTNode* typeSpecifier, char* ID, struct ASTNode* params, struct ASTNode* compound){return NULL;}
struct ASTNode* newParams(struct ASTNode* paramList){return NULL;} // paramList==NULL => params: VOID
struct ASTNode* newParamList(struct ASTNode* paramList, struct ASTNode* param){return NULL;} // paramList==NULL => param_list:param
struct ASTNode* newParam(struct ASTNode* typeSpecifier, char* ID, int type){return NULL;} // type: 1=id is array 0=otherwise
struct ASTNode* newCompound(struct ASTNode* localDecs, struct ASTNode* stmtList){return NULL;}
struct ASTNode* newLocalDecs(struct ASTNode* localDecs, struct ASTNode* varDec){return NULL;}
struct ASTNode* newStmtList(struct ASTNode* stmtList, struct ASTNode* stmt){return NULL;}
struct ASTNode* newStmt(struct ASTNode* stmt){return NULL;} // stmt includes 5 type
struct ASTNode* newExpStmt(struct ASTNode* expression){return NULL;} // stmt==NULL => expression_stmt: SEMI
struct ASTNode* newSelectStmt(struct ASTNode* expression, struct ASTNode* stmt, struct ASTNode* elseStmt){return NULL;}
struct ASTNode* newIterStmt(struct ASTNode* expression,  struct ASTNode* stmt){return NULL;}
struct ASTNode* newRetStmt(struct ASTNode* expression){return NULL;} // expression=NULL => return_stmt: RETURN SEMI;
struct ASTNode* newAssignExp(struct ASTNode* var, struct ASTNode* expression){return NULL;} // assign statement
struct ASTNode* newExpression(struct ASTNode* simpExp){return NULL;}
struct ASTNode* newVar(char* ID){return NULL;}
struct ASTNode* newArrayVar(char* ID, struct ASTNode* expression){return NULL;}
struct ASTNode* newSimpExp(struct ASTNode* addExp1, struct ASTNode* relop, struct ASTNode* addExp2){return NULL;}
struct ASTNode* newRelop(int opType){return NULL;}
struct ASTNode* newAddExp(struct ASTNode* addExp, struct ASTNode* addop, struct ASTNode* term){return NULL;}
struct ASTNode* newAddOp(int opType){return NULL;}
struct ASTNode* newTerm(struct ASTNode* term, struct ASTNode* mulop, struct ASTNode* factor){return NULL;}
struct ASTNode* newTermFactor(struct ASTNode* factor){return NULL;}
struct ASTNode* newMulop(int opType){return NULL;}
struct ASTNode* newFactorExp(struct ASTNode* expression){return NULL;}
struct ASTNode* newFactorVar(struct ASTNode* var){return NULL;}
struct ASTNode* newFactorCall(struct ASTNode* call){return NULL;}
struct ASTNode* newFactorNum(int num){return NULL;}
struct ASTNode* newCall(char* ID, struct ASTNode* args){return NULL;}
struct ASTNode* newArgs(struct ASTNode* argList){return NULL;} // argList=NULL => args
struct ASTNode* newArgList(struct ASTNode* argList, struct ASTNode* expression){return NULL;}
