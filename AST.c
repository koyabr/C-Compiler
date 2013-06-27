#include "AST.h"
#include "globals.h"
#include "symtab.h"
static int location = 0;
static SymbolTable CompoundST = NULL;
static SymbolTable ParamST = NULL;
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
struct ASTNode* newVarDec(struct ASTNode* typeSpecifier, char* ID, int lineno)
{
     struct ASTNode* root = newASTNode(VARDEC_AST, lineno);
     root->child[0] = typeSpecifier;
     root->attr.name = strdup(ID);
     root->type = TYPE_INTEGER;
     pushTable(CompoundST);
     VarSymbol vs = st_lookup(root->attr.name);
     if(vs != NULL)
          Error(root, "variable has been declared before");
     else
          st_insert(root->attr.name, lineno, location++, TYPE_INTEGER);
     popTable();
     return root;
}
// var_declaration: type_specifier ID LSB NUMBER RSB SEMI
struct ASTNode* newArrayDec(struct ASTNode* typeSpecifier, char* ID, int size, int lineno)
{
     struct ASTNode* root = newASTNode(ARRAYDEC_AST, lineno);
     root->child[0] = typeSpecifier;
     root->attr.name = strdup(ID);
     root->type = TYPE_ARRAY;
     root->attr.value = size;
     pushTable(CompoundST);
     VarSymbol vs = st_lookup(root->attr.name);
     if(vs != NULL)
          Error(root, "array has been declared before");
     else
     {
          st_insert(root->attr.name, lineno, location, TYPE_ARRAY);
          location += size;
     }
     popTable(CompoundST);
     return root;
}
struct ASTNode* newTypeSpe(ExpType type, int lineno)
{
     struct ASTNode* root = newASTNode(TYPE_AST, lineno);
     root->type = type;
     return root;
}
// fun_declaration: type_specifier ID LBracket params RBracket compound_stmt
struct ASTNode* newFunDec(struct ASTNode* typeSpecifier, char* ID, struct ASTNode* params, struct ASTNode* compound, int lineno)
{
     struct ASTNode* root = newASTNode(FUNDEC_AST, lineno);
     struct ASTNode* temp = NULL;
     root->child[0] = typeSpecifier;
     root->child[1] = params;
     root->child[2] = compound;
     root->attr.name = strdup(ID);
     FunSymbol fs = st_lookup_fun(ID);
     /* check if the function has been declared before */
     if(fs != NULL)
          Error(root, "array has been declared before");
     else
     {
          root->symbolTable = ParamST;
          st_insert_fun(root->attr.name, ParamST, params->attr.value);
          ParamST = newSymbolTable(PARAM);
     }
     /* type check of return and declaration */
     if(root->child[0]->type != root->child[2]->type)
     {
          fprintf(stderr, "%d: return type is conflict with function declaration\n", root->lineno);
     }
     return root;
}
// paramList==NULL => params: VOID
struct ASTNode* newParams(struct ASTNode* paramList)
{
     // params: param_list
     int num = 0;
     struct ASTNode* temp;
     struct ASTNode* root = NULL;
     if(paramList != NULL)
     {
          for(temp=paramList;temp!=NULL;temp++)
               num++;
          paramList->attr.value = num;
          return paramList;
     }
     else
     {
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
struct ASTNode* newParam(struct ASTNode* typeSpecifier, char* ID, int type, int lineno)
{
     // param: type_specifier ID
     struct ASTNode* root = NULL;
     if(type == 0)
     {
          root = newASTNode(PARAMID_AST, lineno);
          root->child[0] = typeSpecifier;
          root->attr.name = strdup(ID);
          pushTable(ParamST);
          if(st_lookup(root->attr.name) != NULL)
               Error(root, "parameter has been declared before");
          else
               st_insert(root->attr.name, lineno, location , TYPE_INTEGER)
          popTable();
          root->type = TYPE_INTEGER;
     }
     else // param: type_specifier ID LSB RSB
     {
          root = newASTNode(PARAMARRAY_AST, lineno);
          root->child[0] = typeSpecifier;
          root->attr.name = strdup(ID);
          pushTable(ParamST);
          if(st_lookup(root->attr.name) != NULL)
               Error(root, "parameter has been declared before");
          else
               st_insert(root->attr.name, lineno, location , TYPE_ARRAY)
          popTable();
          root->type = TYPE_ARRAY;
     }
     return root;
}
struct ASTNode* newCompound(struct ASTNode* localDecs, struct ASTNode* stmtList, int lineno)
{
     struct ASTNode* node = localDecs;
     struct ASTNode* root = newASTNode(COMPOUND_AST, lineno);
     root->child[0] = localDecs;
     root->child[1] = stmtList;
     root->type = stmtList->type;
     root->symbolTable = CompoundST;
     CompoundST = newSymbolTable(LOCAL);
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
// expression_stmt: SEMI
struct ASTNode* newExpStmt(struct ASTNode* expression, int lineno)
{
     struct ASTNode* root = newASTNode(EXPSTMT_AST, lineno);
     root->child[0] =expression;
     root->type = expression->type;
     return root;
}    
struct ASTNode* newSelectStmt(struct ASTNode* expression, struct ASTNode* stmt, struct ASTNode* elseStmt, int lineno)
{
     struct ASTNode* root = newASTNode(SELESTMT_AST, lineno);
     root->child[0] = expression;
     root->child[1] = stmt;
     root->child[2] = elseStmt;
     return root;
}
struct ASTNode* newIterStmt(struct ASTNode* expression,  struct ASTNode* stmt, int lineno)
{
     assert(expression != NULL);
     struct ASTNode* root = newASTNode(ITERSTMT_AST, lineno);
     root->child[0] = expression;
     root->child[1] = stmt;
     return root;
}
// expression=NULL => return_stmt: RETURN SEMI;
struct ASTNode* newRetStmt(struct ASTNode* expression, int lineno)
{
     struct ASTNode* root = newASTNode(RETSTMT_AST, lineno);
     root->child[0] = expression;
     if(expression != NULL)
          root->type = expression->type;
     else
          root->type = TYPE_VOID;
     return root;
}
// assign statement
struct ASTNode* newAssignExp(struct ASTNode* var, struct ASTNode* expression, int lineno)
{
     struct ASTNode* root = newASTNode(ASSIGN_AST, lineno);
     root->child[0] = var;
     root->child[1] = expression;
     if(!(var->type==TYPE_INTEGER && expression->type==TYPE_INTEGER))
          Error(root, "type mismatch");
     return root;
}
struct ASTNode* newExpression(struct ASTNode* simpExp)
{
     return simpExp;
}
struct ASTNode* newVar(char* ID, int lineno)
{
     struct ASTNode* root = newASTNode(VAR_AST, lineno);
     VarSymbol vs = st_lookup(ID);
     if( vs == NULL)
          Error(root, "variable not defined");
     else
          root->attr.name = vs->name;
     return root;
}
struct ASTNode* newArrayVar(char* ID, struct ASTNode* expression, int lineno)
{
     struct ASTNode* root = newASTNode(ARRAYVAR_AST, lineno);
     VarSymbol vs = st_lookup(ID);
     if( vs == NULL)
          Error(root, "variable not defined");
     else
          root->attr.name = vs->name;
     if( vs->type != TYPE_ARRAY)
          Error(root, "variable is not array");
     else
     {
          if(expression->type != TYPE_INTEGER)
               Error(root, "type mismatch");
          else
               root->child[0] = expression;
     }
     return root;
}
struct ASTNode* newSimpExp(struct ASTNode* addExp1, int relop, struct ASTNode* addExp2, int lineno)
{
     struct ASTNode* root = NULL;
     /* simple_expression: additive_expression relop additive_expression */
     if(relop != -1)            
     {
          root = newASTNode(EXP_AST, lineno);
          root->child[0] = addExp1;
          root->child[1] = addExp2;
          root->attr.op = relop;
          if(root->attr.op == PLUS || root->attr.op == MINUS ||
             root->attr.op == MULTI || root->attr.op == DIV)
          {
               if(!(addExp1->type == TYPE_INTEGER && addExp2->type == TYPE_INTEGER))
                    Error(root, "type mismatch");
               else
                    root->type = TYPE_INTEGER;
          }
          else
          {
               if(!(addExp1->type == TYPE_BOOLEAN && addExp2->type ==TYPE_BOOLEAN))
                    Error(root, "type mismatch");
               else
                    root->type = TYPE_BOOLEAN;
          }
             
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
struct ASTNode* newAddExp(struct ASTNode* addExp, int addop, struct ASTNode* term, int lineno)
{
     struct ASTNode* root = newASTNode(EXP_AST, lineno);
     root->child[0] = addExp;
     root->child[1] = term;
     root->attr.op = addop;
     root->type = TYPE_INTEGER;
     if(!(addExp->type == TYPE_INTEGER && term->type == TYPE_INTEGER))
          Error(root, "type mismatch");
     return root;
}
struct ASTNode* newAddOp(int opType)
{
     return NULL;
}
struct ASTNode* newTerm(struct ASTNode* term, int mulop, struct ASTNode* factor, int lineno)
{
     struct ASTNode* root = newASTNode(EXP_AST, lineno);
     root->child[0] = term;
     root->child[1] = factor;
     root->attr.op = mulop;
     root->type = TYPE_INTEGER;
     if(!(term->type == TYPE_INTEGER && factor->type == TYPE_INTEGER))
          Error(root, "type mismatch");
     return root;
}
struct ASTNode* newTermFactor(struct ASTNode* factor)
{
     return factor;
}
struct ASTNode* newCall(char* ID, struct ASTNode* args, int lineno)
{
     struct ASTNode* root = newASTNode(CALLSTMT_AST, lineno);
     root->child[0] = args;
     root->attr.name = strdup(ID);
     /* TODO */
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
struct ASTNode* newASTNode(ASTType type, int lineno)
{
     struct ASTNode* node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
     node->child[0] = NULL;
     node->child[1] = NULL;
     node->child[2] = NULL;
     node->child[3] = NULL;
     node->sibling = NULL;
     node->astType = type;
     node->type = -1;
     node->lineno = lineno;
     return node;
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
