/***************************
Copyright (C) 2010-2013

filename: main.c
date: Thu Jun 06 21:44:36 2013
author: Kohn<3100102881@zju.edu.cn>
comment: Compiler Design Course Project

***************************/

#include "globals.h"
#include "utils.h"
#include "scan.h"
#include "parse.h"
#include "symtab.h"
#include "codegen.h"

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

int Error = FALSE;

TreeNode * ROOT;

int main(int argc, char *argv[])
{
  
  char pgm[120]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  source = fopen(pgm,"r");
  if (source==NULL)
  { fprintf(stderr,"File %s not found\n",pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing,"\nTINY COMPILATION: %s\n",pgm);

  yyrestart(source);
  yyparse();

  if (! Error)
  { fprintf(listing,"\nBuilding Symbol Table...\n");
    buildSymtab(ROOT);
    fprintf(listing,"\nChecking Types...\n");
    typeCheck(ROOT);
    fprintf(listing,"\nType Checking Finished\n");
  }

  if (! Error)
  { char * codefile = (char *) calloc(strlen(pgm), sizeof(char));
    strcpy(codefile,pgm);
    strcat(codefile,".tm");
    code = fopen(codefile,"w");
    if (code == NULL)
    { printf("Unable to open %s\n",codefile);
      exit(1);
    }
    codeGen(ROOT,codefile);
    fclose(code);
  }

  fclose(source);
  return 0;
}


