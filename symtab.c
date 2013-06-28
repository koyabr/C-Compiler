#include "globals.h"
#include "symtab.h"

/* tables store different symbol tables,
 * incluidng global, local and param.
 */

/* funs store all function symbols */
FunSymbol* funs = NULL;


SymbolTable* newSymbolTable(Scope scope)
{
     int i;
     SymbolTable* st = (SymbolTable*)malloc(sizeof(SymbolTable));
     ASSERT(st != NULL){
        fprintf(stderr, "Failed to malloc for symbal table.\n");
     }
     st->scope = scope;
     st->startOffset = 0;      
     st->next = NULL;
     for(i = 0;i<SIZE;i++)
          st->hashTable[i] = NULL;
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
     assert(tables != NULL);
     for(st = tables; st!=NULL; st=st->next) /* iteration of all symbol tables in stack */
     {
          for(l = st->hashTable[h]; l!=NULL; l=l->next) /* iteration of all linkedlist in a symboltable */
          {
               if(strcmp(l->name, name)==0)
                    return l;
          }
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
          l->name = (name);
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
                   



void printSymTab(SymbolTable* st)
{
     int i;
     fprintf(listing,"Variable Name  Location   Line Numbers\n");
     fprintf(listing,"-------------  --------   ------------\n");
     VarSymbol* vs = NULL;
     for (i=0;i<SIZE;++i)
     {
          for(vs = st->hashTable[i]; vs != NULL; vs=vs->next)
          {
               fprintf(listing, "%-14s", vs->name);
               fprintf(listing, "%-8d", vs->offset);
               fprintf(listing, "\n");
          }
     }
     fprintf(listing, "\n");
} /* printSymTab */



void ErrorMsg(TreeNode* t, char* message, char* ID)
{
     fprintf(stderr,"Error at line %d: %s %s\n",t->lineno,message, ID);
}
