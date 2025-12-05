COMPILER = parser
YACC = syntax/header.y
LEX = lexicon/header.l

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

clear:
	rm -f $(COMPILER) $(YACC_HEADER_C) $(YACC_HEADER_H) $(LEX_COMPILER) $(OBJS)



SEMAN_RIGHT_REST := $(wildcard tests/semantic/right/*.g)
SEMAN_ERROR_TEST := $(wildcard tests/semantic/errors/*.g)
LEX_TEST := $(wildcard tests/lexic/*.txt)

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
	@for f in $(LEX_TEST); do \
		echo "\n[LEXIC ERROR] $$f"; \
		./parser $$f || true; \
	done
