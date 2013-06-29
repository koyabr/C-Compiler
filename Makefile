# Makefile for the C-Minus Compiler
# Author: TZX, HJN, LHY, TJG
#
CC = gcc
CFLAGS = -Wall
LDFLAGS = -ll -ly

LEX = flex
LFLAGS =
YACC = bison
YFLAGS = -d

SRC = main.c scan.c parse.c AST.c symtab.c codegen.c


all: main tm

main: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@ -g
tm: tm.c
	$(CC) $(CFLAGS) $< -o $@


## For Lex and Yacc
scan.c: raw/scan.l globals.h parse.h
	$(LEX) $(LFLAGS) -o $@ $< 


parse.c parse.h: raw/parse.y globals.h AST.h
	$(YACC) $(YFLAGS) -o $@ $< 

##


clean:
	rm -f *.o 
	rm -f scan.c
	rm -f parse.c
	rm -f parse.h
