#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "../syntax/ast.h"
#include "../syntax/utils/dictionary/dictionary.h"
#include "../symbol_table/structure.h"
#include <stdio.h>
#include <string.h>
extern int sem_error;

Types analyze_semantic_program(Node *node, SymbolTable **scope, Types expected_return);

#endif
