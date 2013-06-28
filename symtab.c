#include "globals.h"
#include "symtab.h"

/* tables store different symbol tables,
 * incluidng global, local and param.
 */
SymbolTable* tables = NULL;

/* funs store all function symbols */
FunSymbol* funs = NULL;


SymbolTable* newSymbolTable(Scope scope)
{
     SymbolTable* st = (SymbolTable*)malloc(sizeof(SymbolTable));
     ASSERT(st != NULL){
        fprintf(stderr, "Failed to malloc for symbal table.\n");
     }
     st->scope = scope;
     st->startOffset = 0;      
     st->next = NULL;
     return st;
}

SymbolTable* topTable()
{
     return tables;
}

SymbolTable* popTable()
{
     ASSERT(tables != NULL){
        fprintf(stderr, "Pop an empty table list.\n");
     }
     SymbolTable* st = tables;
     tables = tables->next;
     return st;
}
void pushTable(SymbolTable* st)
{
     ASSERT(st != NULL){
      fprintf(stderr, "Push an null table.\n");
     }
     st->next = tables;
     tables = st;
}
/* the hash function */
static int hash ( char * key )
{
     int temp = 0;
     int i = 0;
     while (key[i] != '\0')
     { temp = ((temp << SHIFT) + key[i]) % SIZE;
          ++i;
     }
     return temp;
}



VarSymbol* lookup_var (char * name)
{
     VarSymbol* l;
     int h = hash(name);
     SymbolTable* st = NULL;
     for(st = tables; st!=NULL; st=st->next)
     {
          l =  tables->hashTable[h];
          for(l = tables->hashTable[h]; l!=NULL; l=l->next)
               if(strcmp(l->name, name)==0)
                    return l;
     }
     return NULL;                  /* may be NULL */
}

FunSymbol* lookup_fun(char * name)
{
     FunSymbol* fs = funs;
     for(;fs!=NULL; fs = fs->next)
     {
          if(strcmp(fs->name, name)==0)
               return fs;
     }
     return NULL;
}

/* insert into top symbol table */
void insert_var(char * name, Scope scope, int offset, ExpType type)
{
     int h = hash(name);
     VarSymbol* l =  tables->hashTable[h];
     while ((l != NULL) && (strcmp(name,l->name) != 0))
          l = l->next;
     if (l == NULL) /* variable not yet in table */
     {
          l = (VarSymbol*) malloc(sizeof(VarSymbol));
          ASSERT(l != NULL){
            fprintf(stderr, "Failed to malloc for VarSymbol.\n" );
          }
          l->name = strdup(name);
          l->scope = scope;
          l->type = type;
          l->offset = offset;
          l->next = tables->hashTable[h];
          tables->hashTable[h] = l;
     }
} 

void insert_fun(char* name, SymbolTable* st, int num)
{
     FunSymbol* fs;

     if(lookup_fun(name) != NULL){
        fprintf(stderr, "Duplicate function declarations: %s\n", name);
        return;
     }
     fs = (FunSymbol*)malloc(sizeof(FunSymbol));
     ASSERT(fs != NULL){
        fprintf(stderr, "Failed to malloc for FunSymbol.\n");
     }
     fs->name = strdup(name);
     fs->paramNum = num;
     fs->symbolTable = st;
     fs->next = funs;
     funs = fs;
}
                   



void printSymTab()
{
     /* int i; */
     /* fprintf(listing,"Variable Name  Location   Line Numbers\n"); */
     /* fprintf(listing,"-------------  --------   ------------\n"); */
     /* for (i=0;i<SIZE;++i) */
     /* { */
     /*      if (hashTable[i] != NULL) */
     /*      { */
     /*           BucketList l = hashTable[i]; */
     /*           while (l != NULL) */
     /*           { */
     /*                LineList t = l->lines; */
     /*                fprintf(listing,"%-14s ",l->name); */
     /*                fprintf(listing,"%-8d  ",l->memloc); */
     /*                while (t != NULL) */
     /*                { */
     /*                     fprintf(listing,"%4d ",t->lineno); */
     /*                     t = t->next; */
     /*                } */
     /*                fprintf(listing,"\n"); */
     /*                l = l->next; */
     /*           } */
     /*      } */
     /* } */
} /* printSymTab */


/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t,
                      void (* preProc) (TreeNode *),
                      void (* postProc) (TreeNode *) )
{
     if (t != NULL)
     {
          preProc(t);
          {
               int i;
               for (i=0; i < MAXCHILDREN; i++)
                    traverse(t->child[i],preProc,postProc);
          }
          postProc(t);
          traverse(t->sibling,preProc,postProc);
     }
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{
     if (t==NULL)
          return;
     else
          return;
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
static void buildSymbolTable( TreeNode * root)
{
     /* TreeNode* t = root; */
     /* while(t!=NULL) */
     /* { */
     /*      switch (t->astType) */
     /*      { */
     /*      case VARDEC_AST: */
     /*           t->child[1]->type = TYPE_INTEGER; */
     /*           t = t->child[1]; */
     /*           if (st_lookup(t->attr.name) == -1) */
     /*                st_insert(t->attr.name,t->lineno,location++, t->type); */
     /*           else */
     /*                decError(t, t->attr.name); */
     /*           break; */
     /*      case ARRAYDEC_AST: */
     /*           t->child[1]->type = TYPE_ARRAY; */
     /*           if (st_lookup(t->child[1]->attr.name) == -1) */
     /*           { */
     /*                st_insert(t->attr.name,t->lineno,location, t->type); */
     /*                location += t->child[2]->attr.value; */
     /*           } */
     /*           else */
     /*                decError(t, t->attr.name); */
     /*           break; */
     /*      case FUNDEC_AST: */
     /*           t->child[1]->type = TYPE_FUNC; */
     /*           if (st_lookup_fun(t->child[1]->attr.name) == NULL) */
     /*           { */
     /*                st_insert_fun(t->child[1]->attr.name, newSymbolTable(PARAM), t->child[2].attr.value); */
     /*                t->symbalTable = st_lookup_fun(t->child[1]->attr.name); */
     /*           } */
     /*           else */
     /*                decError(t, t->attr.name);           */
     /*           break; */
     /*      case PARAMID_AST: */
     /*           t->child[1]->type = TYPE_INTEGER; */
     /*           if (st_lookup(t->child[1]->attr.name) == -1) */
     /*                st_insert(t->attr.name,t->lineno,location++, t->type); */
     /*           else */
     /*                decError(t, t->attr.name);           */
     /*           break; */
     /*      case PARAMARRAY_AST: */
     /*           t->childe[1]->type = TYPE_ARRAY; */
     /*           if (st_lookup(t->attr.name) == -1) */
     /*                st_insert(t->attr.name,t->lineno,location++, t->type); */
     /*           else */
     /*                decError(t, t->attr.name); */
     /*           break; */
     /*      case ID_AST: */
     /*           if(t->type == -1) */
     /*                assert(0); */
     /*      default: */
     /*           break; */
     /*      } */
     /*      t = t->next; */
     /* } */
}

void buildSymtab(TreeNode * syntaxTree)
{
     /* traverse(syntaxTree,insertNode,nullProc); */
     /* if (TraceAnalyze) */
     /* { */
     /*      fprintf(listing,"\nSymbol table:\n\n"); */
     /*      printSymTab(listing); */
     /* } */
}


/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{
     /* Param p; */
     /* ASTNode* ast; */
     /* switch (t->astType) */
     /* { */
     /* case EXP_AST:              /\* + - * / relop *\/ */
     /*      if ( !(t->child[0]->type == TYPE_INTEGER && t->child[1]->type == TYPE_INTEGER) || */
     /*           !(t->child[0]->type != TYPE_BOOLEAN && t->child[1]->type != TYPE_BOOLEAN)) */
     /*           typeError(t,"Op applied to invalid type"); */
     /*      if ((t->attr.op == MINUS) || (t->attr.op == PLUS) || */
     /*          t->attr.op == MULTI || t->attr.op == DIV) */
     /*           t->type = TYPE_INTEGER; */
     /*      else */
     /*           t->type = TYPE_BOOLEAN; */
     /*      break; */
     /* case FUNDEC_AST: */
     /*      p = st_get_param(t->child[1]->name); */
     /*      for(ast = t->child[2]; ast != NULL; ast = ast->sibing) */
     /*      { */
     /*           if(ast->type == PARAMID_AST) */
     /*                st_insert_param(new_param(TYPE_INTEGER, ast->child[1]->name)); */
     /*           else if(ast->type == PARAMARRAY_AST) */
     /*                st_insert_param(new_param(TYPE_ARRAY, ast->child[1]->name)); */
     /*      } */
     /*      if(t->child[3]->type != -1) */
     /*      { */
     /*           if(t->child[0]->type != t->child[3]->type) */
     /*           { */
     /*                fprintf(stderr, "%d: return type is conflict with function declaration\n", t->lineno); */
     /*                Error = TRUE; */
     /*           } */
     /*      } */
     /*      break; */
     /* case RETSTMT_AST: */
     /*      if( t->child[0] == NULL) */
     /*           t->type = TYPE_VOID; */
     /*      else */
     /*      { */
     /*           assert(t->child[0]->type == TYPE_INTEGER); */
     /*           t->type = t->child[0]->type; */
     /*      } */
     /*      break; */
     /* case COMPOUND_AST: */
     /*      for(ast = t; ast->sibling!=NULL; ast=ast->sibling); */
     /*      if(ast->astType == RETSTMT_AST) */
     /*           t->type = ast->type; */
     /*      break; */
     /* case VAR_AST: */
     /* case ARRAYVAR_AST: */
     /*      t->type = TYPE_INTEGER; */
     /*      break; */
     /* case ASSIGN_AST: */
     /*      if(t->child[0]->type != t->child[1]->type) */
     /*           typeError(t, "left and right of = are not in the same type"); */
     /*      break; */
     /* case SELESTMT_AST: */
     /* case ITERSTMT_AST: */
     /*      if(t->child[0]->type != TYPE_BOOLEAN) */
     /*           typeError(t, "condition should be Boolean type"); */
     /*      break; */
     /* default: */
     /*      break; */
     /* } */
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{
     //traverse(syntaxTree,nullProc,checkNode);
}

void Error(TreeNode* t, char* message)
{
     fprintf(stderr,"Error at line %d: %s\n",t->lineno,message);
}
