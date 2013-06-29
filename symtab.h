/*build symbol tables
 * and function tables
 */

#ifndef SYMTAB_H
#define SYMTAB_H

#include "globals.h"

/* the hash function */
int hash ( char * key );

/* initialize symbol tables*/
void initTable();

/* create a new symbol table of certain scope */
SymbolTable* newSymbolTable(Scope s);

/* manipulate the symbol table stack*/
SymbolTable* topTable();
SymbolTable* popTable();
void pushTable(SymbolTable* st);

/* look up for a symbol entry*/
VarSymbol* lookup_var_top(char* name);
VarSymbol* lookup_var(char * name);
FunSymbol* lookup_fun(char * name);

/* insert symbol entries */
int insert_var(char * name, Scope s, int offset, ExpType type);
int insert_fun(char* name, SymbolTable* st, int num, ExpType type);



/* prints a formatted listing of the symbol table */
void printSymTab(SymbolTable* st);



#endif

