// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdarg.h>
// #include "utils/helpers.h"
// #include "../syntax/ast.h"
// #include "../symbol_table/structure.h"
// #include "semantic.h"
// #include "../syntax/utils/dictionary/dictionary.h"

// int is_valid_type(DataType type)
// {
//     return (type == INT_TYPE || type == CAR_TYPE);
// }

// int check_if_declared(SymbolTable *table, char *lex)
// {
//     if (!table || !lex)
//     {
//         return 0;
//     }

//     SymbolTable *current_scope = table;

//     while (current_scope != NULL)
//     {
//         SymbolEntry *entry = current_scope->first_entry;
//         while (entry != NULL)
//         {
//             if (entry->lexeme.lex && strcmp(entry->lexeme.lex, lex) == 0)
//             {
//                 return 1;
//             }
//             entry = entry->next_symbol;
//         }
//         current_scope = current_scope->before_scope;
//     }

//     return 0;
// }

// int is_valid_expression(Node *expr)
// {
//     if (expr == NULL)
//     {
//         return 0;
//     }

//     if (expr->type == TYINT)
//     {
//         return 1;
//     }

//     return 0;
// }

// int are_types_compatible(DataType left, DataType right, NodeType operation)
// {
//     // Para operações aritméticas (soma, subtração, multiplicação, divisão)
//     if (operation == NOSOMA || operation == NOSUBTRACAO || operation == NOMULTIPLICACAO || operation == NODIVISAO)
//     {
//         return (left == TYINT && right == TYINT); // Apenas inteiros podem ser usados para essas operações
//     }

//     // Para operações lógicas (AND, OR)
//     if (operation == NOAND || operation == NOOR)
//     {
//         return (left == TYINT && right == TYINT); // Somente inteiros para operações lógicas (tratando int como booleano)
//     }

//     if (operation == NOIGUAL || operation == NODIFERENTE || operation == NOMAIOR || operation == NOMENOR ||
//         operation == NOMAIOR_IGUAL || operation == NOMENOR_IGUAL)
//     {
//         return (left == TYINT && right == TYINT); // Comparações válidas entre inteiros
//     }

//     return 0;
// }
