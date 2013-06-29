#include "globals.h"
#include "utils.h"
#include "parse.h"
#include "symtab.h"
#include "AST.h"


TreeNode * ASTRoot; /*Root of syntax tree*/

static int GLOBAL_ST = TRUE; /* record current scope */

/* Add declaration as sibling*/
TreeNode* newDecList(TreeNode* decList, TreeNode* declaration)
{

     TreeNode* node = decList;

     while(node->sibling != NULL)
          node = node->sibling;
     node->sibling = declaration;


     return decList;
}


TreeNode* newVarDec(TreeNode* typeSpecifier, char* ID, int lineno)
{

     ASSERT(typeSpecifier->type == TYPE_INTEGER){
          fprintf(stderr, "Error: @line %d, type specifier of variable %s must be int.\n", lineno, ID);
     }

     if(!GLOBAL_ST){
          pushTable(CompoundST);
     }

     ASSERT(lookup_var_top(ID) == NULL){
          fprintf(stderr, "Error: @line %d, duplicate declarations of variable %s.\n", lineno, ID);
     }

     TreeNode* root = newASTNode(VARDEC_AST, lineno);
     root->child[0] = typeSpecifier;
     root->attr.name = strdup(ID);
     root->type = TYPE_INTEGER;

     if(!GLOBAL_ST){
          insert_var(root->attr.name, LOCAL, tables->size++, TYPE_INTEGER);
          popTable();
     }
     else{
          insert_var(root->attr.name, GLOBAL, tables->size++, TYPE_INTEGER);
     }

     return root;
}
// var_declaration: type_specifier ID LSB NUMBER RSB SEMI
TreeNode* newArrayDec(TreeNode* typeSpecifier, char* ID, int size, int lineno)
{

     ASSERT(typeSpecifier->type == TYPE_INTEGER){
          fprintf(stderr, "Error: @line %d, type specifier of variable %s must be int.\n", lineno, ID);
     }

     if(!GLOBAL_ST){
          pushTable(CompoundST);
     }

     ASSERT(lookup_var_top(ID) == NULL){
          fprintf(stderr, "Error: @line %d, duplicate declarations of variable %s.\n", lineno, ID);
     }

     TreeNode* root = newASTNode(ARRAYDEC_AST, lineno);
     root->child[0] = typeSpecifier;
     root->attr.name = strdup(ID);
     root->type = TYPE_ARRAY;
     root->attr.value = size;


     if(!GLOBAL_ST){
          insert_var(root->attr.name, LOCAL, tables->size++, TYPE_ARRAY);
          popTable();
     }
     else{
          insert_var(root->attr.name, GLOBAL, tables->size++, TYPE_ARRAY);
     }

     return root;
}


TreeNode* newTypeSpe(ExpType type, int lineno)
{
     TreeNode* root = newASTNode(TYPE_AST, lineno);
     root->type = type;
     return root;
}


TreeNode* newFunDec(TreeNode* typeSpecifier, char* ID, TreeNode* params, TreeNode* compound, int lineno)
{
     ASSERT(typeSpecifier->type == compound->type){
          fprintf(stderr, "Error: @line %d, return type mis-match declaration for function %s.\n", lineno, ID);

     }

     ASSERT(lookup_fun(ID) == NULL){
          fprintf(stderr, "Error: @line %d, duplicate declarations of function %s.\n", lineno, ID);
     }

     TreeNode* root = newASTNode(FUNDEC_AST, lineno);
     root->child[0] = typeSpecifier;
     root->child[1] = params;
     root->child[2] = compound;
     root->attr.name = strdup(ID);
     root->type = typeSpecifier->type;

     /* print symbol table to test */
     #ifdef DEBUG_SYM
          fprintf(listing, "symbol table of function: %s\n", root->attr.name);
          printSymTab(ParamST);
     #endif


     insert_fun(root->attr.name, ParamST, ParamST->size, root->type);

     ParamST = newSymbolTable(PARAM);

     GLOBAL_ST = TRUE;
     return root;
}

TreeNode* newParams(TreeNode* paramList)
{
     GLOBAL_ST = FALSE;
     return paramList;
}

TreeNode* newParamList(TreeNode* paramList, TreeNode* param)
{
     // param_list: param_list SEMI param
     TreeNode* node = paramList;
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

 
TreeNode* newParam(TreeNode* typeSpecifier, char* ID, int isArray, int lineno)
{

     ASSERT(typeSpecifier->type == TYPE_INTEGER){
          fprintf(stderr, "Error: @line %d, type specifier of param %s must be int.\n", lineno, ID);
     }

     pushTable(ParamST);
     ASSERT(lookup_var_top(ID) == NULL){
          fprintf(stderr, "Error: @line %d, duplicate declarations of variable %s.\n", lineno, ID);
     }
    
     TreeNode* root;
     if(!isArray) // param: type_specifier ID
     {
          root = newASTNode(PARAMID_AST, lineno);
          root->child[0] = typeSpecifier;
          root->attr.name = strdup(ID);
          root->type = TYPE_INTEGER;

          insert_var(root->attr.name, PARAM, ParamST->size++ , TYPE_INTEGER);
          
          
     }
     else // param: type_specifier ID []
     {
          root = newASTNode(PARAMARRAY_AST, lineno);
          root->child[0] = typeSpecifier;
          root->attr.name = strdup(ID);
          root->type = TYPE_ARRAY;

          insert_var(root->attr.name, PARAM, ParamST->size++ , TYPE_ARRAY);
       
     }

     popTable();
     return root;
}
TreeNode* newCompound(TreeNode* localDecs, TreeNode* stmtList, int lineno)
{

     TreeNode* root = newASTNode(COMPOUND_AST, lineno);
     root->child[0] = localDecs;
     root->child[1] = stmtList;

     /* assign type of Return to Compound */
     if(stmtList != NULL && stmtList->type != TYPE_UNDEFINED) /* has return stmt */
          root->type = stmtList->type;
     else
          root->type = TYPE_VOID;
     

     /* DEBUG: print symbol table of this compount statement */
#ifdef DEBUG_SYM
     fprintf(listing, "symbo table of Compound\n");
     printSymTab(CompoundST);
#endif
     
     root->symbolTable = CompoundST;
     CompoundST = newSymbolTable(LOCAL);
     return root;
}
TreeNode* newLocalDecs(TreeNode* localDecs, TreeNode* varDec)
{
     TreeNode* node = localDecs;
     if(localDecs == NULL)
          return varDec;
     while(node->sibling != NULL)
          node = node->sibling;
     node->sibling = varDec;
     return localDecs;
}
TreeNode* newStmtList(TreeNode* stmtList, TreeNode* stmt, int lineno)
{
     TreeNode* node = stmtList;
     if(stmtList == NULL)
          return stmt;

     /*
     if(stmt->type != TYPE_UNDEFINED)       
     {
          if(stmtList->type == TYPE_UNDEFINED) 
               stmtList->type = stmt->type; 
          else
               ASSERT(stmtList->type == stmt->type){
                    fprintf(stderr, "Error: @line %d, return type mis-match.\n", lineno);

               }
     }
     */
     

     while(node->sibling != NULL)
          node = node->sibling;
     node->sibling = stmt;

     return stmtList;
}

/* if-else*/
TreeNode* newSelectStmt(TreeNode* expression, TreeNode* stmt, TreeNode* elseStmt, int lineno)
{

     ASSERT(expression->type == TYPE_INTEGER){
          fprintf(stderr, "Error: @line %d, test condition expression not integer.\n", lineno);
     }


     TreeNode* root = newASTNode(SELESTMT_AST, lineno);
     root->child[0] = expression;
     root->child[1] = stmt;
     root->child[2] = elseStmt;


     return root;
}

/*while*/
TreeNode* newIterStmt(TreeNode* expression,  TreeNode* stmt, int lineno)
{

     ASSERT(expression->type == TYPE_INTEGER){
          fprintf(stderr, "Error: @line %d, test condition expression not integer.\n", lineno);
     }
     
     TreeNode* root = newASTNode(ITERSTMT_AST, lineno);
     root->child[0] = expression;
     root->child[1] = stmt;


     return root;
}

/*return*/
TreeNode* newRetStmt(TreeNode* expression, int lineno)
{
     TreeNode* root = newASTNode(RETSTMT_AST, lineno);
     root->child[0] = expression;
     if(expression != NULL)
          root->type = expression->type;
     else
          root->type = TYPE_VOID;
     return root;
}

/* var = expression */
TreeNode* newAssignExp(TreeNode* var, TreeNode* expression, int lineno)
{

     ASSERT(var->type==TYPE_INTEGER && expression->type==TYPE_INTEGER){
          fprintf(stderr, "Error: @line %d, only can assign int to int.\n", lineno);
     }

     TreeNode* root = newASTNode(ASSIGN_AST, lineno);
     root->child[0] = var;
     root->child[1] = expression;
     root->type = TYPE_INTEGER;

     return root;
}

/*Use variables (not declaration)*/
TreeNode* newVar(char* ID, int lineno)
{
     
     
     /*Check declaration*/
     pushTable(CompoundST);
     VarSymbol* vs = lookup_var(ID); 
     ASSERT(  vs != NULL){
          fprintf(stderr, "Error: @line %d, variable %s not defined before.\n", lineno, ID);
     }
     popTable();

     TreeNode* root = newASTNode(VAR_AST, lineno);
     root->attr.name = vs->name;
     root->type = vs->type;
     
     return root;
}
TreeNode* newArrayVar(char* ID, TreeNode* expression, int lineno)
{

     ASSERT(expression->type == TYPE_INTEGER){
          fprintf(stderr, "Error: @line %d, array %s: index is not integer.\n", lineno, ID);

     }

     

     /*Check declaration */
     pushTable(CompoundST);
     VarSymbol* vs = lookup_var(ID);
     ASSERT(  vs != NULL){
          fprintf(stderr, "Error: @line %d, variable %s not defined before.\n", lineno, ID);
     }
     popTable();

          
     ASSERT( vs->type == TYPE_ARRAY){
          fprintf(stderr, "Error: @line %d, variable %s is not an array.\n", lineno, ID);
     }


     TreeNode* root = newASTNode(ARRAYVAR_AST, lineno);
     root->child[0] = expression;
     root->attr.name = vs->name;
     root->type = TYPE_INTEGER; /*array element must be int*/
     
     return root;
}
TreeNode* newSimpExp(TreeNode* addExp1, int relop, TreeNode* addExp2, int lineno)
{

     ASSERT(addExp1->type == TYPE_INTEGER && addExp2->type == TYPE_INTEGER){
          fprintf(stderr, "Error: @line %d, only can compare integers.\n", lineno);
     }

     TreeNode* root = newASTNode(EXP_AST, lineno);
     root->child[0] = addExp1;
     root->child[1] = addExp2;
     root->attr.op = relop;
     root->type = TYPE_INTEGER;/*use int as boolean*/


     return root;
}

TreeNode* newAddExp(TreeNode* addExp, int addop, TreeNode* term, int lineno)
{
     ASSERT(addExp->type == TYPE_INTEGER && term->type == TYPE_INTEGER){
          fprintf(stderr, "Error: @line %d, only can calculate integers.\n", lineno);
     }

     TreeNode* root = newASTNode(EXP_AST, lineno);
     root->child[0] = addExp;
     root->child[1] = term;
     root->attr.op = addop;
     root->type = TYPE_INTEGER;

     return root;
}

TreeNode* newTerm(TreeNode* term, int mulop, TreeNode* factor, int lineno)
{
     ASSERT(term->type == TYPE_INTEGER && factor->type == TYPE_INTEGER){
          fprintf(stderr, "Error: @line %d, only can calculate integers.\n", lineno);

     }

     TreeNode* root = newASTNode(EXP_AST, lineno);
     root->child[0] = term;
     root->child[1] = factor;
     root->attr.op = mulop;
     root->type = TYPE_INTEGER;


     return root;
}

TreeNode* newNumNode(int value, int lineno)
{
     TreeNode* root = newASTNode(NUM_AST, lineno);
     root->attr.value = value;
     root->type = TYPE_INTEGER;

     return root;
}

TreeNode* newCall(char* ID, TreeNode* args, int lineno)
{
     FunSymbol* fun;
     VarSymbol* var;
     TreeNode* tmp = args;
     /* Check declaration */
     fun = lookup_fun(ID);
     ASSERT(fun != NULL){
          fprintf(stderr, "Error: @line %d, call function %s which is not defined.\n", lineno, ID);
     }
     /*Check parameters*/
     var = fun->symbolTable->varList;

     while(var && tmp){
          ASSERT(var->type == tmp->type){
          fprintf(stderr, "Error: @line %d, call function %s : parameter type mis-match.\n", lineno, ID);
          }
          var = var->next_FIFO;
          tmp = tmp->sibling;
     }

     ASSERT(!var && !tmp){
          fprintf(stderr, "Error: @line %d, call function %s : parameter number mis-match.\n", lineno, ID);
     }

     /*Check finished*/
     TreeNode* root = newASTNode(CALL_AST, lineno);
     root->child[0] = args;
     root->attr.name = strdup(ID);
     root->type = fun->type;

     return root;
}

/* Add the exp as sibling*/
TreeNode* newArgList(TreeNode* argList, TreeNode* expression)
{
     TreeNode* node = argList;
     while(node->sibling != NULL)
          node = node->sibling;
     node->sibling = expression;
     return argList;
}
TreeNode* newASTNode(ASTType type, int lineno)
{
     int i;

     TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
     ASSERT(node != NULL){
          fprintf(stderr, "Failed to malloc for TreeNode @line%d.\n", lineno);
     }

     for(i=0; i<MAXCHILDREN; ++i){
          node->child[i] = NULL;
     }
     node->sibling = NULL;
     node->astType = type;
     node->type = TYPE_UNDEFINED;
     node->lineno = lineno;
     return node;
}

void printNodeKind(TreeNode* node)
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
     case CALL_AST:
          printf("Call stement \n");
          break;
     default:
          printf("No such AST type\n");
          break;
     }
}
void printAST(TreeNode* root, int indent)
{
     TreeNode* node = root;
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
