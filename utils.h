/*Utils*/

#ifndef UTILS_H
#define UTILS_H

#include "globals.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
char * copyString( char * );

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * );


#endif
