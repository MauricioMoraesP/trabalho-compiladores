#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "helpers.h"

int convert_type(Types t)
{

    switch (t)
    {
    case TYINT:
        return INT_TYPE;
    case TYCAR:
        return CAR_TYPE;
    default:
        return INT_TYPE;
    }
}

#include <stdarg.h>

void error_message(int line, const char *fmt, ...)
{
    va_list args;

    printf("\n[ERRO SEMÂNTICO] Linha %d: ", line);

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
    exit(1);
}

void validation_null_table(SymbolTable *table)
{
    if (table == NULL)
    {
        printf("\n A tabela de símbolos não foi inicializada corretamente.\n");
        exit(1);
    }
}