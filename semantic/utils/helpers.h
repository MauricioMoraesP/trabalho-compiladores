#ifndef HELPERS_H
#define HELPERS_H

#include "../../symbol_table/structure.h"
#include "../semantic.h"

typedef enum
{
    FROM_TYPES,
    FROM_DATATYPE
} ConvertDirection;

int convert_type(Types t);
void error_message(int line, const char *fmt, ...);
void validation_null_table(SymbolTable *table);
Types require_int(Node *expr, SymbolTable *scope, const char *msg);
Types check_binary_same(Node *expr, SymbolTable *scope, const char *msg);
Types check_binary_int(Node *expr, SymbolTable *scope, const char *msg);
Types analyze_assignment(Node *assign, SymbolTable *scope);
#endif
