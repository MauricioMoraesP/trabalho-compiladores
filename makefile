NOME_DO_PROJETO = parser
YACC_SRC = syntax/header.y
LEX_SRC = lexicon/header.l
C_SRCS = \
    syntax/ast.c \
    semantic/utils/helpers.c \
    symbol_table/utils/helpers.c \
    syntax/utils/dictionary/dictionary.c \
    semantic/semantic.c \
    symbol_table/implementation.c
YACC_OUT = syntax/header.tab.c
YACC_HEADER = syntax/header.tab.h
LEX_OUT = lexicon/lex.yy.c
CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-result -g -fno-omit-frame-pointer -fstack-protector-strong
LDFLAGS = -lfl
INCLUDES = -I.
OBJS = \
    syntax/ast.o \
    semantic/utils/helpers.o \
    symbol_table/utils/helpers.o \
    syntax/utils/dictionary/dictionary.o \
    semantic/semantic.o \
    symbol_table/implementation.o \
    syntax/header.tab.o \
    lexicon/lex.yy.o

.PHONY: all clean

all: $(NOME_DO_PROJETO)

$(YACC_OUT) $(YACC_HEADER): $(YACC_SRC)
	bison -d -o $(YACC_OUT) $(YACC_SRC)

$(LEX_OUT): $(LEX_SRC) $(YACC_HEADER)
	flex -o $(LEX_OUT) $(LEX_SRC)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

syntax/header.tab.o: $(YACC_OUT) $(YACC_HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(YACC_OUT) -o $@

lexicon/lex.yy.o: $(LEX_OUT) $(YACC_HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(LEX_OUT) -o $@


$(NOME_DO_PROJETO): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NOME_DO_PROJETO) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(NOME_DO_PROJETO) $(YACC_OUT) $(YACC_HEADER) $(LEX_OUT) $(OBJS)