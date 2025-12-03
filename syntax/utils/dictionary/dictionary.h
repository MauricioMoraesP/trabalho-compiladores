#ifndef NODE_DICTIONARY_H
#define NODE_DICTIONARY_H
#include "../../types.h"

// Dicionário de Nós.
typedef enum
{
    NODE_LEAF,
    NODE_UNARY,
    NODE_BINARY,
    NODE_IFELSE,
    NODE_GENERIC
} NodeType;

typedef struct
{
    NSpecies species;
    const char *name;
    NodeType type;
    int numb_children;
    int has_lexeme;
} NodeDictionaryEntry;

const NodeDictionaryEntry *findInfosNode(NSpecies s);

#endif
