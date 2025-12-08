#ifndef TYPES_H
#define TYPES_H
#include "../symbol_table/structure.h"

/* Tipos de dado possíveis*/
typedef enum
{
    TYINT,
    TYCAR,
    TYVOID
} Types;

/* Espécies/Tokens de nós da AST*/
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

/* Informação armazenada por nós folha */
typedef struct LeafInfo
{
    char *lexeme;
    int int_val;
    char car_val;
} LeafInfo;

typedef struct Node Node;

/* Nó unário */
typedef struct NUnary
{
    Node *n;
} NUnary;

/* Nó binário */
typedef struct NBinary
{
    Node *left;
    Node *right;
} BinaryNode;

/* Nó if-else */
typedef struct IfElseNode
{
    Node *condition_node;
    Node *then_node;
    Node *else_node;
} IfElseNode;

/* Nó com N filhos*/
typedef struct Nnary
{
    Node *first;
} Nnary;

/* Union de dados específicos dependendo do tipo de nó */
typedef union NodeInfo
{
    NUnary unary;
    BinaryNode binary;
    IfElseNode ifelse;
    LeafInfo leaf;
    Nnary nnary;
} NodeInfo;

/* Estrutura dos nós da AST */
struct Node
{
    NSpecies species;
    Types type;
    int row;
    NodeInfo data;
    struct Node *next;
};

#endif
