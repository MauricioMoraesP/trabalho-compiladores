#ifndef HELPERS_H
#define HELPERS_H
#include <stdbool.h>

// Auxiliador para alocar memoria.
void *helper_malloc(size_t size, const char *context_msg);
// Validador de entrada.
void helper_not_null(const void *ptr, char *context);

#endif
