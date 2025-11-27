# Nome do executável
EXEC = parser

# Arquivos fontes
BISON_SRC = syntax/header.y
FLEX_SRC = lexicon/header.l
AST_SRC = syntax/ast.c
SEMANTIC_HELPERS_SRC = semantic/utils/helpers.c
SYMBOL_HELPERS_SRC = symbol_table/utils/helpers.c
DICTIONARY_SRC = syntax/utils/dictionary/dictionary.c
SEMANTIC_SRC = semantic/semantic.c
SYMBOL_TABLE_SRC = symbol_table/implementation.c

# Arquivos gerados pelo Bison e Flex
BISON_OUT = syntax/header.tab.c
BISON_HEADER = syntax/header.tab.h
FLEX_OUT = lexicon/lex.yy.c

# Objetos
OBJ = \
    semantic/utils/helpers.o \
    symbol_table/helpers.o \
    syntax/header.tab.o \
    lexicon/lex.yy.o \
    ast.o \
    dictionary.o \
    semantic.o \
    symbol_table.o

# Compilador e flags
# CC = gcc
# CFLAGS = -Wall -Wextra -Wno-unused-result -g \
#          -fsanitize=address,undefined \
#          -fno-omit-frame-pointer \
#          -fstack-protector-strong
# LDFLAGS = -lfl -fsanitize=address,undefined
# INCLUDES = -I.
CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-result -g \
         -fno-omit-frame-pointer \
         -fstack-protector-strong
LDFLAGS = -lfl
INCLUDES = -I.

# Regra padrão
all: $(EXEC)

# --- Bison ---
$(BISON_OUT) $(BISON_HEADER): $(BISON_SRC)
	bison -d -o $(BISON_OUT) $(BISON_SRC)

# --- Flex ---
$(FLEX_OUT): $(FLEX_SRC) $(BISON_HEADER)
	flex -o $(FLEX_OUT) $(FLEX_SRC)

# --- Objetos ---
semantic/utils/helpers.o: $(SEMANTIC_HELPERS_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

symbol_table/helpers.o: $(SYMBOL_HELPERS_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

syntax/header.tab.o: $(BISON_OUT) $(BISON_HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(BISON_OUT) -o $@

lexicon/lex.yy.o: $(FLEX_OUT) $(BISON_HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(FLEX_OUT) -o $@

ast.o: $(AST_SRC) $(BISON_HEADER) symbol_table/helpers.o
	$(CC) $(CFLAGS) $(INCLUDES) -c $(AST_SRC) -o $@

dictionary.o: $(DICTIONARY_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(DICTIONARY_SRC) -o $@

semantic.o: $(SEMANTIC_SRC) semantic/utils/helpers.o symbol_table/helpers.o
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SEMANTIC_SRC) -o $@

symbol_table.o: $(SYMBOL_TABLE_SRC) symbol_table/helpers.o
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SYMBOL_TABLE_SRC) -o $@

# --- Compilação do executável ---
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXEC) $(OBJ) $(LDFLAGS)

# Limpeza dos arquivos gerados
clean:
	rm -f $(EXEC) $(BISON_OUT) $(BISON_HEADER) $(FLEX_OUT) $(OBJ)
