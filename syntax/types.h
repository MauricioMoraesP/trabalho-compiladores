typedef enum
{
    NODE_PROGRAMA,
    NODE_BLOCO,
    NODE_LISTA_COMANDOS,
    NODE_IF,
    NODE_IF_ELSE,
    NODE_WHILE,
    NODE_ATRIBUICAO,
    NODE_RETURN,
    NODE_LEIA,
    NODE_ESCREVA,
    NODE_ESCREVA_LITERAL,
    NODE_NOVALINHA,
    NODE_CHAMADA_FUNCAO,

    NODE_SOMA,
    NODE_SUBTRACAO,
    NODE_MULTIPLICACAO,
    NODE_DIVISAO,
    NODE_AND,
    NODE_OR,

    NODE_IGUAL,
    NODE_DIFERENTE,
    NODE_MENOR,
    NODE_MENOR_IGUAL,
    NODE_MAIOR,
    NODE_MAIOR_IGUAL,

    NODE_NEGACAO,
    NODE_MENOS_UNARIO,

    NODE_TIPO_INT,
    NODE_TIPO_CAR,
    NODE_IDENTIFICADOR,
    NODE_INT_CONST,
    NODE_CHAR_CONST,
    NODE_STRING_LITERAL,

    NODE_DECL_FUNCAO,
    NODE_DECL_VAR

} NodeSpecies;

typedef struct Node Node;

struct Node
{
    NodeSpecies species;
    int row;
    char *lexem;
    union
    {
        int val_int;
        char val_char;
    } constant_value;
    Node *child_one;
    Node *child_two;
    Node *child_three;
};

typedef Node *PNode;