#include "global.h"
struct ASTNode* newProgram(struct ASTNode* decList);
struct ASTNode* newDecList(struct ASTNode* decList, struct ASTNode* declaration); // decList==NULL => declaration
struct ASTNode* newDec(struct ASTNode* declaration, int type);             // type: 0=var, 1=fun
struct ASTNode* newVarDec(struct ASTNode* typeSpecifier, char* ID);
struct ASTNode* newArrayDec(struct ASTNode* typeSpecifier, char* ID, int size);
struct ASTNode* newTypeSpe(enum VarType type);
struct ASTNode* newFunDec(struct ASTNode* typeSpecifier, char* ID, struct ASTNode* params, struct ASTNode* compound);
struct ASTNode* newParams(struct ASTNode* paramList); // paramList==NULL => params: VOID
struct ASTNode* newParamList(struct ASTNode* paramList, struct ASTNode* param); // paramList==NULL => param_list:param
struct ASTNode* newParam(struct ASTNode* typeSpecifier, char* ID, int type); // type: 1=id is array 0=otherwise
struct ASTNode* newCompound(struct ASTNode* localDecs, struct ASTNode* stmtList);
struct ASTNode* newLocalDecs(struct ASTNode* localDecs, struct ASTNode* varDec);
struct ASTNode* newStmtList(struct ASTNode* stmtList, struct ASTNode* stmt);
struct ASTNode* newStmt(struct ASTNode* stmt); // stmt includes 5 types
struct ASTNode* newExpStmt(struct ASTNode* expression); // stmt==NULL => expression_stmt: SEMI
struct ASTNode* newSelectStmt(struct ASTNode* expression, struct ASTNode* stmt, struct ASTNode* elseStmt);
struct ASTNode* newIterStmt(struct ASTNode* expression,  struct ASTNode* stmt);
struct ASTNode* newRetStmt(struct ASTNode* expression); // expression=NULL => return_stmt: RETURN SEMI;
struct ASTNode* newAssignExp(struct ASTNode* var, struct ASTNode* expression); // assign statement
struct ASTNode* newExpression(struct ASTNode* simpExp);
struct ASTNode* newVar(char* ID);
struct ASTNode* newArrayVar(char* ID, struct ASTNode* expression);
// relop==NULL & addExp2==NULL => simple_expression: additive expression
struct ASTNode* newSimpExp(struct ASTNode* addExp1, struct ASTNode* relop, struct ASTNode* addExp2);

struct ASTNode* newRelop(int opType);
struct ASTNode* newAddExp(struct ASTNode* addExp, struct ASTNode* addop, struct ASTNode* term);
struct ASTNode* newAddOp(int opType);
struct ASTNode* newTerm(struct ASTNode* term, struct ASTNode* mulop, struct ASTNode* factor);
struct ASTNode* newTermFactor(struct ASTNode* factor);
struct ASTNode* newMulop(int opType);
struct ASTNode* newFactorExp(struct ASTNode* expression);
struct ASTNode* newFactorVar(struct ASTNode* var);
struct ASTNode* newFactorCall(struct ASTNode* call);
struct ASTNode* newFactorNum(int num);
struct ASTNode* newCall(char* ID, struct ASTNode* args);
struct ASTNode* newArgs(struct ASTNode* argList); // argList=NULL => args:
struct ASTNode* newArgList(struct ASTNode* argList, struct ASTNode* expression); // argList==NULL
