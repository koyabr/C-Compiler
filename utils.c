/*Utils Implementation*/


#include "utils.h"

void ErrorMsg(TreeNode* t, char* message, char* ID)
{
     fprintf(stderr,"Error at line %d: %s %s\n",t->lineno,message, ID);
     Error = TRUE;
}