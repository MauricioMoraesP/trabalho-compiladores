#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "helpers.h"

/*Converte o tipo interno Types para o tipo inteiro da tabela de símbolos*/
int helper_convert_type(Types t)
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

/*Imprime mensagem de erro semântico com número da linha e outros argumentos quando necessário*/
void helper_error_message(int line, const char *fmt, ...)
{
    va_list args;
    fprintf(stderr, "[ERRO SEMÂNTICO] Linha %d: ", line);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    sem_error = 1;
}
/*Verifica se a tabela de símbolos foi inicializada*/
void helper_validation_null_table(SymbolTable *table)
{
    if (table == NULL)
    {
        printf("\n A tabela de simbolos nao foi inicializada corretamente.\n");
        exit(1);
    }
}

/*Verifica se ambos os operandos de uma expressão binária são inteiros*/
Types helper_check_binary_int(Node *expr, SymbolTable *scope, const char *msg)
{
    Types left = semantic_expression(expr->data.binary.left, scope);
    Types right = semantic_expression(expr->data.binary.right, scope);

    if (left != TYINT || right != TYINT)
    {
        if (left == TYCAR || right == TYCAR)
            helper_error_message(expr->row, "Expressao combina tipos distintos.");
        else
            helper_error_message(expr->row, "%s", msg);

        sem_error = 1;
        return TYVOID;
    }
    return TYINT;
}
/*Verifica se ambos os operandos de uma expressão binária têm o mesmo tipo*/
Types helper_check_binary_same(Node *expr, SymbolTable *scope, const char *msg)
{
    Types l = semantic_expression(expr->data.binary.left, scope);
    Types r = semantic_expression(expr->data.binary.right, scope);

    if (l != r)
    {
        helper_error_message(expr->row, msg);
        sem_error = 1;
    }
    return TYINT;
}
/*Verifica se a expressão é do tipo inteiro*/
Types helper_type_is_int(Node *expr, SymbolTable *scope, const char *msg)
{
    Types type = semantic_expression(expr, scope);
    if (type != TYINT)
    {
        helper_error_message(expr->row, "%s", msg);
        sem_error = 1;
    }
    return type;
}

/*Analisa uma atribuição e verifica se os tipos são compatíveis*/
Types helper_analyze_atribuition(Node *atr, SymbolTable *scope)
{
    Node *left = atr->data.binary.left;
    Node *right = atr->data.binary.right;

    if (!left || left->species != NOIDENTIFICADOR)
    {
        helper_error_message(atr->row, "Lado esquerdo nao corresponde ao tipo do identificador.");
        sem_error = 1;
        return TYVOID;
    }

    SymbolEntry *sym = table_search_above(scope, left->data.leaf.lexeme);
    if (!sym)
    {
        helper_error_message(atr->row, "Variavel '%s' nao foi declarada.", left->data.leaf.lexeme);
        sem_error = 1;
        return TYVOID;
    }

    Types right_type = semantic_expression(right, scope);
    Types left_type = helper_convert_type(sym->type);

    if (right_type != left_type)
    {
        helper_error_message(atr->row, "Tipos incompativeis para a atribuicao '%s'.", left->data.leaf.lexeme);
        sem_error = 1;
    }

    return left_type;
}
