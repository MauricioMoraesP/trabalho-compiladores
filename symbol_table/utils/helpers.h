#ifndef HELPERS_H
#define HELPERS_H
#include <stdbool.h>
#include "../structure.h"

void *helper_malloc(size_t size, const char *context_msg);
void helper_not_null(const void *ptr, char *context);
void free_scope_entries(SymbolEntry *entry);

#endif
