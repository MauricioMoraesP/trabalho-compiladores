#ifndef VALIDATIONS_H
#define VALIDATIONS_H
#include "../header.h"
#include <stdbool.h>

// Protytpes Functions Validations
void verifyStackIsNull(SymbolTableStack *stack, const char *message);
void verifyBurstStack(SymbolTableStack *stack, const char *message);
void verifyStackUnderflow(SymbolTableStack *stack, const char *message);
void ensureSpaceForEntry(SymbolTable *table, const char *messageOnAlloc, const char *messageOnRealloc);
bool verifyStackIsNullSucess(SymbolTableStack *stack, const char *message);
bool symbolExistsInCurrentScope(SymbolTableStack *stack, char *name);
#endif
