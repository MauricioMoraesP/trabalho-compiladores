#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "helpers.h"

int convert_type(Types t)
{

    switch (t)
    {
    case TYINT:
        return INT_TYPE;
    case TYCAR:
        return CAR_TYPE;
    default:
        return INT_TYPE;
    }
}

#include <stdarg.h>

void error_message(int line, const char *fmt, ...)
{
    va_list args;
    fprintf(stderr, "\n[ERRO SEMÂNTICO] Linha %d: ", line);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    sem_error = 1;
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

Types check_binary_int(Node *expr, SymbolTable *scope, const char *msg)
{
    Types l = analyze_expression(expr->data.binary.left, scope);
    Types r = analyze_expression(expr->data.binary.right, scope);

    if (l != TYINT || r != TYINT)
    {
        error_message(expr->row, msg);
        sem_error = 1;
    }
    return TYINT;
}

Types check_binary_same(Node *expr, SymbolTable *scope, const char *msg)
{
    Types l = analyze_expression(expr->data.binary.left, scope);
    Types r = analyze_expression(expr->data.binary.right, scope);

    if (l != r)
    {
        error_message(expr->row, msg);
        sem_error = 1;
    }
    return TYINT;
}

Types require_int(Node *expr, SymbolTable *scope, const char *msg)
{
    Types t = analyze_expression(expr, scope);
    if (t != TYINT)
    {
        error_message(expr->row, "%s", msg);
        sem_error = 1;
    }
    return t;
}

Types analyze_assignment(Node *assign, SymbolTable *scope)
{
    Node *left = assign->data.binary.left;
    Node *right = assign->data.binary.right;

    if (!left || left->species != NOIDENTIFICADOR)
    {
        error_message(assign->row, "Atribuição inválida: lado esquerdo deve ser identificador.");
        sem_error = 1;
        return TYVOID;
    }

    SymbolEntry *sym = table_search_up(scope, left->data.leaf.lexeme);
    if (!sym)
    {
        error_message(assign->row, "Variável '%s' não declarada.", left->data.leaf.lexeme);
        sem_error = 1;
        return TYVOID;
    }

    Types rt = analyze_expression(right, scope);
    Types lt = convert_type(sym->type);

    if (rt != lt)
    {
        error_message(assign->row, "Atribuição com tipo incompatível para '%s'.", left->data.leaf.lexeme);
        sem_error = 1;
    }

    return lt;
}
