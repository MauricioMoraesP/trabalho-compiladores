#ifndef HELPERS_H
#define HELPERS_H

#include "../../symbol_table/structure.h"
#include "../semantic.h"

typedef enum
{
    FROM_TYPES,
    FROM_DATATYPE
} ConvertDirection;

int helper_convert_type(Types t);
void helper_error_message(int line, const char *fmt, ...);
void helper_validation_null_table(SymbolTable *table);
Types helper_type_is_int(Node *expr, SymbolTable *scope, const char *msg);
Types helper_check_binary_same(Node *expr, SymbolTable *scope, const char *msg);
Types helper_check_binary_int(Node *expr, SymbolTable *scope, const char *msg);
Types helper_analyze_atribuition(Node *assign, SymbolTable *scope);
#endif
