COMPILER = parser
YACC = syntax/header.y
LEX = lexicon/header.l
SEMAN_RIGHT_TEST = \
    tests/semantic/right/fatorialCorreto.g

SEMAN_ERROR_TEST = \
    tests/semantic/errors/fatorialErroLin5TipoRetornado.g

LEX_TEST = \
    tests/lexic/fatorialErroLin15String2linhas.txt

ITENS = \
    syntax/ast.c \
    semantic/utils/helpers.c \
    symbol_table/utils/helpers.c \
    syntax/utils/dictionary/dictionary.c \
    semantic/semantic.c \
    symbol_table/implementation.c
YACC_HEADER_C = syntax/header.tab.c
YACC_HEADER_H = syntax/header.tab.h
LEX_COMPILER = lexicon/lex.yy.c
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

all: $(COMPILER)

$(YACC_HEADER_C) $(YACC_HEADER_H): $(YACC)
	bison -d -o $(YACC_HEADER_C) $(YACC)

$(LEX_COMPILER): $(LEX) $(YACC_HEADER_H)
	flex -o $(LEX_COMPILER) $(LEX)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

syntax/header.tab.o: $(YACC_HEADER_C) $(YACC_HEADER_H)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(YACC_HEADER_C) -o $@

lexicon/lex.yy.o: $(LEX_COMPILER) $(YACC_HEADER_H)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(LEX_COMPILER) -o $@


$(COMPILER): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(COMPILER) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(COMPILER) $(YACC_HEADER_C) $(YACC_HEADER_H) $(LEX_COMPILER) $(OBJS)

test: parser semantic-right semantic-error lex-test

semantic-right:
	@echo "\nTestes códigos sem erro semânticos"
	@for f in $(SEMAN_RIGHT_TEST); do \
		echo "\n[SEM OK] $$f"; \
		./parser $$f || true; \
	done

semantic-error:
	@echo "\nTestes códigos com erro semânticos"
	@for f in $(SEMAN_ERROR_TEST); do \
		echo "\n[SEM ERR] $$f"; \
		./parser $$f || true; \
	done

lex-test:
	@echo "\nTestes Lexico"
	@for f in $(LEX_TEST); do \
		echo "\n[LEX ERR] $$f"; \
		./parser $$f || true; \
	done
