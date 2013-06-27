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

OBJS = main.o utils.o scan.o parse.o symtab.o codegen.o


all: main tm

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main
tm: tm.c
	$(CC) $(CFLAGS) tm.c -o tm

# For different objs
main.o: main.c globals.h utils.h scan.h parse.h symtab.h codegen.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

scan.o: scan.c
	$(CC) $(CFLAGS) -c scan.c

parse.o: parse.c parse.h
	$(CC) $(CFLAGS) -c parse.c

## For Lex and Yacc
scan.c: scan.l globals.h parse.h
	$(LEX) $(LFLAGS) raw/scan.l -o scan.c

parse.c: parse.y globals.h AST.h
	$(YACC) $(YFLAGS) raw/parse.y -o parse.c
##


symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c


codegen.o: codegen.c codegen.h
	$(CC) $(CFLAGS) -c codegen.c

clean:
	rm -f *.o