#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "../syntax/ast.h"
#include "../syntax/utils/dictionary/dictionary.h"
#include "../symbol_table/structure.h"
extern int sem_error;

#include <stdio.h>
#include <string.h>

// Função para verificar se o lexema foi declarado na tabela de símbolos
void analyze_program(Node *ast, SymbolTable *global_scope);
void analyze_function(Node *fun, SymbolTable *global_scope);
void analyze_command(Node *cmd, SymbolTable **scope, Types return_prev);
Types analyze_expression(Node *expr, SymbolTable *scope);
Types analyze_func_call(Node *call, SymbolTable *scope);
#endif
