#ifndef HELPERS_H
#define HELPERS_H

#include "../../symbol_table/structure.h"
#include "../semantic.h"
#include "../semantic.h"

int helper_convert_type(Types t);
void helper_error_message(int line, const char *fmt, ...);
void helper_validation_null_table(SymbolTable *table);
void helper_insert_global_variables(Node *ctx, SymbolTable **scope);
void helper_insert_local_variables(Node *ctx, SymbolTable **scope);
Types helper_type_is_int(Node *expr, SymbolTable *scope, const char *msg);
Types helper_check_binary_same(Node *expr, SymbolTable *scope, const char *msg);
Types helper_check_binary_int(Node *expr, SymbolTable *scope, const char *msg);
Types helper_analyze_atribuition(Node *assign, SymbolTable *scope);
SymbolEntry *table_search_above(SymbolTable *scope, char *name);

#endif
