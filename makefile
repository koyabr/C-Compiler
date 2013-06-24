LEXER = ./raw/lexer.l
PARSER = ./raw/parser.y
OS = WINDOWS
GCC = gcc
c-: main.c global.h $(LEXER) $(PARSER) AST.h AST.c
	bison -d $(PARSER)
	flex $(LEXER)
ifeq ($(OS), LINUX)
	$(GCC) main.c parser.tab.c lex.yy.c AST.c -g -o c- -ly
else
	$(GCC) main.c parser.tab.c lex.yy.c AST.c -g -o c-
endif
