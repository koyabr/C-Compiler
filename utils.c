/*Utils Implementation*/


#include "utils.h"

void ErrorMsg(TreeNode* t, char* message)
{
     fprintf(stderr,"Error at line %d: %s\n",t->lineno,message);
}