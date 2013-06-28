/*build symbol table
 *make type check
 */

#ifndef SYMTAB_H
#define SYMTAB_H

#include "globals.h"

 /* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* create a new symbol table of certain scope */
SymbolTable* newSymbolTable(Scope s);

/* manipulate the symbol table stack*/
SymbolTable* topTable();
SymbolTable* popTable();
void pushTable(SymbolTable* st);

/* look up for a symbol entry*/
VarSymbol* lookup_var(char * name);
FunSymbol* lookup_fun(char * name);

/* insert symbol entries */
void insert_var(char * name, Scope s, int offset, ExpType type);
void insert_fun(char* name, SymbolTable* st, int num);



/* prints a formatted listing of the symbol table */
void printSymTab(SymbolTable* st);



#endif

