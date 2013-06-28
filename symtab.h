/*build symbol table
 *make type check
 */

#ifndef SYMTAB_H
#define SYMTAB_H

#include "globals.h"


 /* constructs the symbol table */
void buildSymtab(TreeNode *tree);

/* performs type checking */
void typeCheck(TreeNode *tree);

/* new symbol table of certain scope */
SymbolTable* newSymbolTable(Scope s);

SymbolTable* popTable();

void pushTable(SymbolTable* st);

/* insert symbol entries */
void insert_var(char * name, Scope s, int offset, ExpType type);
void insert_fun(char* name, SymbolTable* st, int num);

/* look up for a symbol entry*/
VarSymbol* lookup_var(char * name);
FunSymbol* lookup_fun(char * name);

/* prints a formatted listing of the symbol table contents to the listing file */
void printSymTab(SymbolTable* st);



#endif

