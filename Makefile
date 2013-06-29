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

OBJS = main.o utils.o scan.o parse.o AST.o symtab.o codegen.o 


all: main tm

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -g
tm: tm.c
	$(CC) $(CFLAGS) $< -o $@

# For different objs

main.o: main.c globals.h utils.h parse.h symtab.h codegen.h
	$(CC) $(CFLAGS) -c $< -o $@ -g

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c $< -o $@

scan.o: scan.c globals.h parse.h
	$(CC) $(CFLAGS) -c $< -o $@ -g

parse.o: parse.c parse.h
	$(CC) $(CFLAGS) -c $< -o $@ -g

AST.o: AST.c AST.h
	$(CC) $(CFLAGS) -c $< -o $@ -g

## For Lex and Yacc
scan.c: raw/scan.l globals.h parse.h
	$(LEX) $(LFLAGS) -o $@ $< 


parse.c parse.h: raw/parse.y globals.h AST.h
	$(YACC) $(YFLAGS) $< -o $@

##


symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c $< -o $@ -g

codegen.o: codegen.c codegen.h
	$(CC) $(CFLAGS) -c $< -o $@ -g


clean:
	rm -f *.o 
	rm -f scan.c
	rm -f parse.c
