/***************************
C-minus Compiler -
Compiler Design Course Project
***************************/

#include "globals.h"
#include "utils.h"
#include "scan.h"
#include "parse.h"
#include "symtab.h"
#include "codegen.h"

#define FILE_NAME_LEN 100

FILE* source; /* source code text file */
FILE* listing; /* listing output text file */
FILE* code; /* code text file for TM simulator */
TreeNode * ASTRoot; /*Root of syntax tree*/

/*debug flags*/
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;



int main(int argc, char *argv[])
{
  
    char sourcefile[FILE_NAME_LEN]; /* source code file name */

    if (argc != 2){ 
      fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }

    strcpy(sourcefile,argv[1]) ;
    source = fopen(sourcefile,"r");
    if (!source){ 
      fprintf(stderr,"File %s not found\n",sourcefile);
      exit(1);
    }

    listing = stdout; /* send listing to screen */
    fprintf(listing,"\nC-minus Compiler\ntarget: %s\n",sourcefile);

    yyrestart(source);
    yyparse();

    if (! Error){ 
      fprintf(listing,"\nBuilding Symbol Table...\n");
      buildSymtab(ASTRoot);
      fprintf(listing,"\nChecking Types...\n");
      typeCheck(ASTRoot);
      fprintf(listing,"\nType Checking Finished\n");
    }

    if (! Error){ 
      char * codefile = (char *) calloc(strlen(sourcefile), sizeof(char));
      strcpy(codefile,sourcefile);
      strcat(codefile,".tm");
      code = fopen(codefile,"w");
      if (!code){ 
        fprintf(stderr, "Unable to open %s\n",codefile);
        exit(1);
      }
      codeGen(ASTRoot);
      fclose(code);
    }

    fclose(source);
    return 0;
}


