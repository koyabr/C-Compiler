/*build symbol table
 *make type check
 */

#ifndef SYMTAB_H
#define SYMTAB_H

#include "globals.h"

typedef enum {GLOBAL_VAR, LOCAL_VAR, PARAM_VAR} VarType;

typedef struct symbol Symbol;
struct symbol {
	char *name;
	int offset;
	ExpType expType;/*int void array*/
	VarType varType;/*global, local, param*/
	struct symbol *next;

};

typedef struct symtab SymTab;
struct symtab {
	int size;
	VarType varType;/*global, local, param*/
	Symbol head;
	struct symtab *next;
};

typedef struct symbol_func SymbolFunc;
struct symbol_func {
	char *name;
	ExpType type;

	int address;
	int param_size;
	int var_size;

	SymTab symtab;

	struct symbol_func *next;

};

 /* constructs the symbol table */
void buildSymtab(TreeNode *tree);

/* performs type checking */
void typeCheck(TreeNode *tree);

/* new symboltal of certain scope */
SymbolTable newSymbolTable(Scope s);

 /* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc, ExpType type);
void st_insert_fun(char* name, SymbolTable st, int num);

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
VarSymbol st_lookup( char * name );
FunSymbol st_lookup_fun(char * name);

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing);



#endif

