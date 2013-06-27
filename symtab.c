#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include <assert.h>
/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

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

/* the list of line numbers of the source 
 * code in which a variable is referenced
 */
typedef struct LineListRec
{
     int lineno;
     struct LineListRec * next;
} * LineList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
{
     char * name;
     Param param;               /* param list if type==function */
     ExpType type;              /* integer, void, array or function */
     LineList lines;
     int memloc ; /* memory location for variable */
     struct BucketListRec * next;
} * BucketList;

typedef struct ParamRec
{
     ExpType type;
     char* name;
     struct ParamRec* next;
}* Param;


/* the hash table */
static BucketList hashTable[SIZE];

void st_insert_param(char* name, Param param)
{
     int h = hash(name);
     BucketList l =  hashTable[h];
     while ((l != NULL) && (strcmp(name,l->name) != 0))
          l = l->next;
     if (l == NULL)
          return;
     else
     {
          param->next = l->param;
          l->param = param;
     }
}

Param st_get_param(char* name)
{
     int h = hash(name);
     BucketList l =  hashTable[h];
     while ((l != NULL) && (strcmp(name,l->name) != 0))
          l = l->next;
     if( l == NULL)
          return NULL;
     else
          return l->param;
}

Param new_param(TypeExp type, char* name)
{
     Param = (Param)malloc(sizeof(struct ParamRec));
     Param->type = type;
     Param->name = strdup(name);
     Param->next = NULL;
}
/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc, ExpType type)
{
     int h = hash(name);
     BucketList l =  hashTable[h];
     while ((l != NULL) && (strcmp(name,l->name) != 0))
          l = l->next;
     if (l == NULL) /* variable not yet in table */
     {
          l = (BucketList) malloc(sizeof(struct BucketListRec));
          l->name = strdup(name);
          l->type = type;
          l->param = NULL;
          l->lines = (LineList) malloc(sizeof(struct LineListRec));
          l->lines->lineno = lineno;
          l->memloc = loc;
          l->lines->next = NULL;
          l->next = hashTable[h];
          hashTable[h] = l;
     }
     else /* found in table, so just add line number */
     {
          LineList t = l->lines;
          while (t->next != NULL) t = t->next;
          t->next = (LineList) malloc(sizeof(struct LineListRec));
          t->next->lineno = lineno;
          t->next->next = NULL;
     }
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name )
{
     int h = hash(name);
     BucketList l =  hashTable[h];
     while ((l != NULL) && (strcmp(name,l->name) != 0))
          l = l->next;
     if (l == NULL)
          return -1;
     else
          return l->memloc;
}

ExpType st_lookup_type(char *name)
{
     int h = hash(name);
     BucketList l =  hashTable[h];
     while ((l != NULL) && (strcmp(name,l->name) != 0))
          l = l->next;
     if (l == NULL)
          return -1;
     else
          return l->type;
}
/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing)
{
     int i;
     fprintf(listing,"Variable Name  Location   Line Numbers\n");
     fprintf(listing,"-------------  --------   ------------\n");
     for (i=0;i<SIZE;++i)
     {
          if (hashTable[i] != NULL)
          {
               BucketList l = hashTable[i];
               while (l != NULL)
               {
                    LineList t = l->lines;
                    fprintf(listing,"%-14s ",l->name);
                    fprintf(listing,"%-8d  ",l->memloc);
                    while (t != NULL)
                    {
                         fprintf(listing,"%4d ",t->lineno);
                         t = t->next;
                    }
                    fprintf(listing,"\n");
                    l = l->next;
               }
          }
     }
} /* printSymTab */




  /* counter for variable memory locations */
static int location = 0;

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

static void decError(TreeNode* t, char* message)
{
     fprintf(listing,"Redefinition error at line %d: %s\n",t->lineno,message);
     Error = TRUE;
}
/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode( TreeNode * t)
{
     switch (t->astType)
     {
     case VARDEC_AST:
          t->child[1]->type = TYPE_INTEGER;
          t = t->child[1];
          if (st_lookup(t->attr.name) == -1)
               /* not yet in table, so treat as new definition */
               st_insert(t->attr.name,t->lineno,location++, t->type);
          else
               decError(t, t->attr.name);
          break;
     case ARRAYDEC_AST:
          t->child[1]->type = TYPE_ARRAY;
          if (st_lookup(t->child[1]->attr.name) == -1)
          {
               st_insert(t->attr.name,t->lineno,location, t->type);
               location += t->child[2]->attr.value;
          }
          else
               decError(t, t->attr.name);
          break;
     case FUNDEC_AST:
          t->child[1]->type = TYPE_FUNC;
          if (st_lookup(t->child[1]->attr.name) == -1)
               st_insert(t->attr.name,t->lineno,location++, t->type);
          else
               decError(t, t->attr.name);          
          break;
     case PARAMID_AST:
          t->child[1]->type = TYPE_INTEGER;
          if (st_lookup(t->child[1]->attr.name) == -1)
               st_insert(t->attr.name,t->lineno,location++, t->type);
          else
               decError(t, t->attr.name);          
          break;
     case PARAMARRAY_AST:
          t->childe[1]->type = TYPE_ARRAY;
          if (st_lookup(t->attr.name) == -1)
               st_insert(t->attr.name,t->lineno,location++, t->type);
          else
               decError(t, t->attr.name);
          break;
     case ID_AST:
          if(t->type == -1)
               assert(0);
     default:
          break;
     }
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{
     traverse(syntaxTree,insertNode,nullProc);
     if (TraceAnalyze)
     {
          fprintf(listing,"\nSymbol table:\n\n");
          printSymTab(listing);
     }
}

static void typeError(TreeNode * t, char * message)
{
     fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
     Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{
     Param p;
     ASTNode* ast;
     switch (t->astType)
     {
     case EXP_AST:              /* + - * / relop */
          if ( !(t->child[0]->type == TYPE_INTEGER && t->child[1]->type == TYPE_INTEGER) ||
               !(t->child[0]->type != TYPE_BOOLEAN && t->child[1]->type != TYPE_BOOLEAN))
               typeError(t,"Op applied to invalid type");
          if ((t->attr.op == MINUS) || (t->attr.op == PLUS) ||
              t->attr.op == MULTI || t->attr.op == DIV)
               t->type = TYPE_INTEGER;
          else
               t->type = TYPE_BOOLEAN;
          break;
     case FUNDEC_AST:
          p = st_get_param(t->child[1]->name);
          for(ast = t->child[2]; ast != NULL; ast = ast->sibing)
          {
               if(ast->type == PARAMID_AST)
                    st_insert_param(new_param(TYPE_INTEGER, ast->child[1]->name));
               else if(ast->type == PARAMARRAY_AST)
                    st_insert_param(new_param(TYPE_ARRAY, ast->child[1]->name));
          }
          if(t->child[3]->type != -1)
          {
               if(t->child[0]->type != t->child[3]->type)
               {
                    fprintf(stderr, "%d: return type is conflict with function declaration\n", t->lineno);
                    Error = TRUE;
               }
          }
          break;
     case RETSTMT_AST:
          if( t->child[0] == NULL)
               t->type = TYPE_VOID;
          else
          {
               assert(t->child[0]->type == TYPE_INTEGER);
               t->type = t->child[0]->type;
          }
          break;
     case COMPOUND_AST:
          for(ast = t; ast->sibling!=NULL; ast=ast->sibling);
          if(ast->astType == RETSTMT_AST)
               t->type = ast->type;
          break;
     case VAR_AST:
     case ARRAYVAR_AST:
          t->type = TYPE_INTEGER;
          break;
     case ASSIGN_AST:
          if(t->child[0]->type != t->child[1]->type)
               typeError(t, "left and right of = are not in the same type");
          break;
     case SELESTMT_AST:
     case ITERSTMT_AST:
          if(t->child[0]->type != TYPE_BOOLEAN)
               typeError(t, "condition should be Boolean type");
          break;
     default:
          break;
     }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{
     traverse(syntaxTree,nullProc,checkNode);
}
