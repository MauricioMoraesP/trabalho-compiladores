#include <stdlib.h>
#include <stdio.h>
#include "validations.h"
#include "../header.h"
#include <stdbool.h>

// Verify if the stack is not initialized and report an error if it is null
void verifyStackIsNull(SymbolTableStack *stack, const char *message)
{
    if (stack == NULL)
    {
        printf("Erro: %s\n", message);
        exit(EXIT_FAILURE);
    }
}

// Verify if the stack has reached its maximum capacity (burst)
void verifyBurstStack(SymbolTableStack *stack, const char *message)
{
    if ((stack)->top >= SCOPE - 1)
    {
        printf("Erro: %s\n", message);
        exit(EXIT_FAILURE);
    }
}
// Verify if the stack is empty before performing operations (underflow check)
void verifyStackUnderflow(SymbolTableStack *stack, const char *message)
{
    if (stack->top == -1)
    {
        printf("Erro: %s\n", message);
        exit(EXIT_FAILURE);
    }
}

// Ensure there is enough memory allocated for a new entry in the symbol table
// Print messages on allocation or reallocation failure
void ensureSpaceForEntry(SymbolTable *table, const char *messageOnAlloc, const char *messageOnRealloc)
{
    if (table->entries == NULL)
    {
        table->entries = malloc(sizeof(SymbolEntry));
        if (!table->entries)
        {
            printf("Erro: %s\n", messageOnAlloc);
            exit(EXIT_FAILURE);
        }
        table->count = 0;
    }
    else
    {
        table->entries = realloc(table->entries,
                                 sizeof(SymbolEntry) * (table->count + 1));
        if (!table->entries)
        {
            printf("Erro: %s\n", messageOnRealloc);
            exit(EXIT_FAILURE);
        }
    }
}

// Check if the stack is null and return true if it is (used for successful verification)
bool verifyStackIsNullSucess(SymbolTableStack *stack, const char *message)
{
    if (stack == NULL)
    {
        printf("Sucesso: %s\n", message);
        return true;
    }
    return false;
}

// Checking if the symbol exists in the scope.
bool symbolExistsInCurrentScope(SymbolTableStack *stack, char *name)
{
    if (stack->top == -1)
        return false;

    SymbolTable *currentTable = stack->tables[stack->top];
    if (currentTable == NULL || currentTable->entries == NULL)
        return false;

    for (int i = 0; i < currentTable->count; i++)
    {
        if (strcmp(currentTable->entries[i].lexeme.lex, name) == 0)
        {
            return true;
        }
    }
    return false;
}