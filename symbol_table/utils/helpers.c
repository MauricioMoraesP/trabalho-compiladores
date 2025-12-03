#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "../structure.h"
#include <stdbool.h>
#include <string.h>

void *helper_malloc(size_t size, const char *context_msg)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        fprintf(stderr, "Aviso: Erro de alocacao em %s.\n", context_msg);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void helper_not_null(const void *ptr, char *context)
{
    if (!ptr)
    {
        fprintf(stderr, "Aviso: Ponteiro nulo foi detectado em %s.\n", context);
        exit(EXIT_FAILURE);
    }
}

void free_scope_entries(SymbolEntry *entry)
{
    while (entry)
    {
        SymbolEntry *next = entry->next_symbol;

        if (entry->lexeme.lex)
            free(entry->lexeme.lex);

        if (entry->entry == FUN_ENTRY && entry->data.fun_data.param_types)
            free(entry->data.fun_data.param_types);

        free(entry);
        entry = next;
    }
}
