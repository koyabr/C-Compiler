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

OBJS = main.o  parse.o symtab.o scan.o ast.o


all: main tm

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main -g
tm: tm.c
	$(CC) $(CFLAGS) tm.c -o tm

# For different objs

main.o: test.c globals.h  parse.h symtab.h 
	$(CC) $(CFLAGS) -c test.c -o main.o -g

scan.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c -o scan.o -g

parse.o: parse.c parse.h
	$(CC) $(CFLAGS) -c parse.c -g

ast.o: AST.c AST.h
	$(CC) $(CFLAGS) -c AST.c -g

## For Lex and Yacc
lex.yy.c: raw/scan.l globals.h parse.h
	$(LEX) $(LFLAGS) raw/scan.l


parse.c: raw/parse.y globals.h AST.h
	$(YACC) $(YFLAGS) raw/parse.y -o parse.c -g

##


symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c -g


clean:
	del *.o 
