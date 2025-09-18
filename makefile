EXEC = parser

BISON_SRC = syntax/header.y
FLEX_SRC = lexicon/header.l
BISON_OUT = syntax/header.tab.c
BISON_HEADER = syntax/header.tab.h
FLEX_OUT = lexicon/lex.yy.c

CC = gcc
CFLAGS = -Wall
LDFLAGS = -lfl

all: $(EXEC)

$(BISON_OUT) $(BISON_HEADER): $(BISON_SRC)
	bison -d -o $(BISON_OUT) $(BISON_SRC)

$(FLEX_OUT): $(FLEX_SRC) $(BISON_HEADER)
	flex -o $(FLEX_OUT) $(FLEX_SRC)

$(EXEC): $(BISON_OUT) $(FLEX_OUT)
	$(CC) $(CFLAGS) -o $(EXEC) $(BISON_OUT) $(FLEX_OUT) $(LDFLAGS)

clean:
	rm -f $(EXEC) $(BISON_OUT) $(BISON_HEADER) $(FLEX_OUT)
