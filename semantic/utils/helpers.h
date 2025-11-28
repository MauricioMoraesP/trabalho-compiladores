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

#endif
