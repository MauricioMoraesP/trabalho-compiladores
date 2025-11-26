#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "helpers.h"

int convert_type(int value, ConvertDirection dir)
{
    if (dir == FROM_TYPES)
    {
        if (value == TYINT)
            return INT_TYPE;
        if (value == TYCAR)
            return CAR_TYPE;
    }
    else
    {
        if (value == INT_TYPE)
            return TYINT;
        if (value == CAR_TYPE)
            return TYCAR;
    }

    printf("Valor de tipo inválido!\n");
    exit(1);
}

void error_message(int line, const char *message)
{
    printf("\n[ERRO SEMÂNTICO] Linha %d: %s\n", line, message);
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