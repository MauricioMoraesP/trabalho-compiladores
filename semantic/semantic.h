#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "../syntax/ast.h"
#include "../syntax/utils/dictionary/dictionary.h"
#include "../symbol_table/structure.h"
#include <stdio.h>
#include <string.h>
extern int sem_error;

// Função para verificar se o lexema foi declarado na tabela de símbolos
void analyze_semantic_program(Node *ast, SymbolTable *global_scope);
void semantic_function(Node *fun, SymbolTable *global_scope);
void semantic_command(Node *cmd, SymbolTable **scope, Types return_prev);
Types semantic_expression(Node *expr, SymbolTable *scope);
Types semantic_func_call(Node *call, SymbolTable *scope);
#endif
