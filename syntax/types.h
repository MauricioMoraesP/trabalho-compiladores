#ifndef TYPES_H
#define TYPES_H

#include "../symbol_table/structure.h"

typedef enum
{
    TYINT,
    TYCAR,
    TYVOID
} Types;

typedef enum
{
    NODECL_VAR,
    NODECL_FUNCAO,
    NOCHAMADA_FUNCAO,
    NOATRIBUICAO,
    NOBLOCO,
    NOIF,
    NOIF_ELSE,
    NOWHILE,
    NORETURN,
    NOWRITE,
    NOREAD,
    NONEWLINE,
    NOWRITE_LITERAL,
    NOSOMA,
    NOMULTIPLICACAO,
    NOSUBTRACAO,
    NODIVISAO,
    NOOR,
    NOAND,
    NOIGUAL,
    NODIFERENTE,
    NOMENOR,
    NOMENOR_IGUAL,
    NOMAIOR,
    NOMAIOR_IGUAL,
    NONEGACAO,
    NOMENOS_UNARIO,
    NOIDENTIFICADOR,
    NOINT_CONST,
    NOCAR_CONST,
    NOSTRING_LITERAL,
    NOLISTA_COMANDOS,
    NOPROGRAMA,
    NOLISTA_EXPR,
    NOLISTA_DECL,
    NOFUNC_COMPONENTS,
    NOLISTA_PARAMS
} NSpecies;

typedef struct LeafInfo
{
    char *lexeme;
    int int_val;
    char char_val;
} LeafInfo;

typedef struct Node Node;

typedef struct NUnary
{
    Node *n;
} NUnary;

typedef struct NBinary
{
    Node *left;
    Node *right;
} BinaryNode;

typedef struct IfElseNode
{
    Node *condition_node;
    Node *then_node;
    Node *else_node;
} IfElseNode;

typedef struct Nnary
{
    Node *first;
} Nnary;

typedef union NodeInfo
{
    NUnary unary;
    BinaryNode binary;
    IfElseNode ifelse;
    LeafInfo leaf;
    Nnary nnary;
} NodeInfo;

struct Node
{
    NSpecies species;
    Types type;
    int row;
    NodeInfo data;

    struct Node *next;
};

#endif
