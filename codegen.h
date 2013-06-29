/*CODEGEN*/

#ifndef CODEGEN_H
#define CODEGEN_H

#include "globals.h"

/*data register*/
#define zero 0
#define ax 1
#define bx 2

/*pointer register*/
#define sp 4
#define bp 5
#define gp 6
#define pc 7


/* code emitting utilities */

/* prints a comment line with comment c in the code file
 */
void emitComment( char * c );

/* emits a register-only TM instruction
 * op = the opcode
 * r = target register
 * s = 1st source register
 * t = 2nd source register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRO( char *op, int r, int s, int t, char *c);

/* emits a register-to-memory TM instruction
 * op = the opcode
 * r = target register
 * d = the offset
 * s = the base register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM( char * op, int r, int d, int s, char *c);

/* skips "howMany" code locations for later backpatch. 
 * It also returns the current code position
 */
int emitSkip( int howMany);

/* backs up to loc = a previously skipped location
 */
void emitBackup( int loc);

/* restores the current code position to the highest previously unemitted position
 */
void emitRestore(void);


/* generate standard prelude */
void emitPrelude();

/* generate codes for input() */
void emitInput();

/* generate codes for output() */
void emitOutput();

/* emit one instruction to get the address of a symbol */
void emitGetAddr(VarSymbol* var);

/* emits 5 instructions to call a function*/
void emitCall(FunSymbol* fun);




/* recursively generates code by tree traversal */
void cGen( TreeNode * tree);

/* primary function
 * visit the syntax tree and generate codes
 */
void codeGen();


#endif