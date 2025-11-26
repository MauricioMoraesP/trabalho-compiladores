#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "../syntax/ast.h"
#include "../syntax/utils/dictionary/dictionary.h"
#include "../symbol_table/structure.h"

extern int semantic_error;

void analyze_semantic(Node *n, SymbolTable *current_scope);

#endif
