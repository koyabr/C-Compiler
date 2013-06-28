/***************************
C-minus Compiler -
Compiler Design Course Project
***************************/

#include "globals.h"
#include "utils.h"
#include "parse.h"
#include "symtab.h"
#include "codegen.h"

#define FILE_NAME_LEN 100

FILE* source; /* source code text file */
FILE* listing; /* listing output text file */
FILE* code; /* code text file for TM simulator */


/*debug flags*/
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

TreeNode * ASTRoot; /*Root of syntax tree*/

SymbolTable* CompoundST; /*Temporary symbol table for compound*/
SymbolTable* ParamST;/* Tempopary symbol table for parameters */



void init()
{
     CompoundST = newSymbolTable(LOCAL);
     ParamST = newSymbolTabl(PARAM);
}
int main(int argc, char *argv[])
{
  
    char sourcefile[FILE_NAME_LEN]; /* source code file name */

    ASSERT(argc == 2){ 
      fprintf(stderr,"usage: %s <filename>\n",argv[0]);
    }

    strcpy(sourcefile,argv[1]) ;
    source = fopen(sourcefile,"r");
    ASSERT(source != NULL){ 
      fprintf(stderr,"File %s not found\n",sourcefile);
    }

    listing = stdout; /* send listing to screen */
    fprintf(listing,"\nC-minus Compiler\ntarget: %s\n",sourcefile);

    yyrestart(source);
    yyparse();
    fprintf(listing,"\nParsing Finished...\n");

    if (! Error){ 
      
      // ??????
      fprintf(listing,"\nSemantic Analysis Finished...\n");
    }

    if (! Error){ 
      char * codefile = (char *) calloc(strlen(sourcefile), sizeof(char));
      strcpy(codefile,sourcefile);
      strcat(codefile,".tm");
      code = fopen(codefile,"w");
      ASSERT(code != NULL){ 
        fprintf(stderr, "Unable to open %s\n",codefile);
      }
      codeGen();
      fclose(code);
      fprintf(listing,"\nCode Generation Finished...\n");
    }

    fclose(source);
    return 0;
}


