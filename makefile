# Nome do executável
EXEC = parser

# Fontes
BISON_SRC = syntax/header.y
FLEX_SRC = lexicon/header.l
AST_SRC = syntax/ast.c  # ajuste para o caminho correto

# Saídas do Bison e Flex
BISON_OUT = syntax/header.tab.c
BISON_HEADER = syntax/header.tab.h
FLEX_OUT = lexicon/lex.yy.c

# Objetos
OBJ = syntax/header.tab.o lexicon/lex.yy.o ast.o

# Compilador e flags
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lfl
INCLUDES = -I.

# Regra principal
all: $(EXEC)

# Gerar arquivos do Bison
$(BISON_OUT) $(BISON_HEADER): $(BISON_SRC)
	bison -d -o $(BISON_OUT) $(BISON_SRC)

# Gerar arquivos do Flex
$(FLEX_OUT): $(FLEX_SRC) $(BISON_HEADER)
	flex -o $(FLEX_OUT) $(FLEX_SRC)

# Compilar executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXEC) $(OBJ) $(LDFLAGS)

# Regras genéricas para .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Ajuste para compilar ast.o corretamente
ast.o: $(AST_SRC) $(BISON_HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(AST_SRC) -o $@

# Limpeza
clean:
	rm -f $(EXEC) $(BISON_OUT) $(BISON_HEADER) $(FLEX_OUT) $(OBJ)
