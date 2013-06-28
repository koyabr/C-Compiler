#include <stdio.h>
#include "globals.h"
#include "AST.h"
#include <string.h>
#include "symtab.h"

#define FILE_NAME_LEN  100
SymbolTable* CompoundST;
SymbolTable* ParamST;
SymbolTable* tables;

FILE* source; /* source code text file */
FILE* listing; /* listing output text file */
FILE* code; /* code text file for TM simulator */

TreeNode* ASTRoot;

void init()
{
     CompoundST = newSymbolTable(LOCAL);
     ParamST = newSymbolTable(PARAM);
     tables = newSymbolTable(GLOBAL);
}
int main(int argc, char *argv[])
{
     char sourcefile[FILE_NAME_LEN]; /* source code file name */

     if (argc != 2){ 
          fprintf(stderr,"usage: %s <filename>\n",argv[0]);
          source = fopen("./test/test0.cm", "r");
     }
     else
     {
          strcpy(sourcefile,argv[1]) ;
          source = fopen(sourcefile,"r");
     }
     if (!source){ 
          fprintf(stderr,"File %s not found\n",sourcefile);
          exit(1);
     }

     listing = stdout; /* send listing to screen */
     fprintf(listing,"\nC-minus Compiler\ntarget: %s\n",sourcefile);

     init();
     
     yyrestart(source);
     yyparse();
     fprintf(listing,"\nParsing Finished...\n");
     /* Abstract Syntax Tree building and Symbol Table buiding and Type checking Complete */
     /* ================================================================================== */
     


     
     /* char * codefile = (char *) calloc(strlen(sourcefile), sizeof(char)); */
     /* strcpy(codefile,sourcefile); */
     /* strcat(codefile,".tm"); */
     /* code = fopen(codefile,"w"); */
     /* if (!code){  */
     /*      fprintf(stderr, "Unable to open %s\n",codefile); */
     /*      exit(1); */
     /* } */
     /* codeGen(); */
     /* fclose(code); */
     /* fprintf(listing,"\nCode Generation Finished...\n"); */

     fclose(source);

     return 0;
}
