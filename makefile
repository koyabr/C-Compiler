LEXER = ./raw/lexer.l
PARSER = ./raw/parser.y
OS = WINDOWS
c-: main.c global.h $(LEXER) $(PARSER)
	bison -d $(PARSER)
	flex $(LEXER)
ifeq ($(OS), LINUX)
	gcc main.c parser.tab.c lex.yy.c -o c- -ly
else
	gcc main.c parser.tab.c lex.yy.c -o c-
endif
