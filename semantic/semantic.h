#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "../syntax/ast.h"
#include "../syntax/utils/dictionary/dictionary.h"
#include "../symbol_table/structure.h"

#include <stdio.h>
#include <string.h>

// Função para verificar se o lexema foi declarado na tabela de símbolos
int check_if_declared(SymbolTable *table, char *lex);
int is_valid_type(DataType type);
int is_valid_expression(Node *expr);
int are_types_compatible(DataType left, DataType right, NodeType operation);

#endif
