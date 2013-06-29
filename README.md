C-Compiler
==========

A simple compiler aim at C-minus language and TM vitrual machine.

File Structure
==============

1. main.c 
  -- main code file

2. globals.h
  -- define data structures and macros

3. raw/scan.l raw/parse.y
  -- lex and yacc source code for quick scanning & parsing

4. AST.c
  -- define routine functions for parsing a syntax tree, making type-check and error-handling at meanwhile.

5. symtab.c
  -- define data structures for symbol tables (for variables & functions)

6. codegen.c
  -- code generator, which recursively generates TM-machine code by syntax tree travesal.

Usage
=====

1. To compile the compiler:

    `make clean`
    `make`
    
2. To compile for C-minus code:

    `main [filepath]`
    e.g. `main test1.cm`
    
3. To run TM codes:

    `tm [filepath]`
    e.g. `tm test1.cm.tm`
    
    

