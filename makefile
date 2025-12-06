# Create exec compiler

EXEC = parser
SYNTAX = syntax/header.y
LEXER = lexicon/header.l

ITENS = \
    syntax/ast.c \
    semantic/utils/helpers.c \
    symbol_table/utils/helpers.c \
    syntax/utils/dictionary/dictionary.c \
    semantic/semantic.c \
    symbol_table/implementation.c

SYNTAX_HEADER_C = syntax/header.tab.c
SYNTAX_HEADER_H = syntax/header.tab.h
LEXER_EXEC = lexicon/lex.yy.c

CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-result -g -fno-omit-frame-pointer -fstack-protector-strong  -I.


OBJS = \
    syntax/ast.o \
    semantic/utils/helpers.o \
    symbol_table/utils/helpers.o \
    syntax/utils/dictionary/dictionary.o \
    semantic/semantic.o \
    symbol_table/implementation.o \
    syntax/header.tab.o \
    lexicon/lex.yy.o

all: $(EXEC)

$(SYNTAX_HEADER_C) $(SYNTAX_HEADER_H): $(SYNTAX)
	bison -d -o $(SYNTAX_HEADER_C) $(SYNTAX)

$(LEXER_EXEC): $(LEXER) $(SYNTAX_HEADER_H)
	flex -o $(LEXER_EXEC) $(LEXER)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

syntax/header.tab.o: $(SYNTAX_HEADER_C) $(SYNTAX_HEADER_H)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SYNTAX_HEADER_C) -o $@

lexicon/lex.yy.o: $(LEXER_EXEC) $(SYNTAX_HEADER_H)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(LEXER_EXEC) -o $@


$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXEC) $(OBJS) -lfl

clear:
	rm -f $(EXEC) $(SYNTAX_HEADER_C) $(SYNTAX_HEADER_H) $(LEXER_EXEC) $(OBJS)



# Test compiler script bash

SEMAN_RIGHT_REST := $(wildcard tests/semantic/right/*.g)
SEMAN_ERROR_TEST := $(wildcard tests/semantic/errors/*.g)
LEXER_TEST := $(wildcard tests/lexic/*.txt)

test: parser semantic-right semantic-error lex-test

semantic-right:
	@echo "\nTestes códigos sem erro semânticos"
	@for f in $(SEMAN_RIGHT_REST); do \
		echo "\n[SEMANTIC RIGHT] $$f"; \
		./parser $$f || true; \
	done

semantic-error:
	@echo "\nTestes códigos com erro semânticos"
	@for f in $(SEMAN_ERROR_TEST); do \
		echo "\n[SEMANTIC ERROR] $$f"; \
		./parser $$f || true; \
	done

lex-test:
	@echo "\nTestes Lexico"
	@for f in $(LEXER_TEST); do \
		echo "\n[LEXERIC ERROR] $$f"; \
		./parser $$f || true; \
	done
