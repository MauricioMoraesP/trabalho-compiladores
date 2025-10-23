#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

PNode cNodeAST(NodeSpecies species, int row, PNode first_children, PNode second_children, PNode third_children, char *lexem)
{
    PNode node = (PNode)malloc(sizeof(Node));
    if (!node)
    {
        fprintf(stderr, "Erro: falha ao alocar memória para nó AST.\n");
        exit(1);
    }

    node->species = species;
    node->row = row;
    node->lexem = (lexem ? strdup(lexem) : NULL);
    node->constant_value.val_int = 0;
    node->constant_value.val_char = '\0';
    node->child_one = first_children;
    node->child_two = second_children;
    node->child_three = third_children;

    return node;
}

PNode cNodeConstInt(int r, int value)
{
    PNode node = cNodeAST(NODE_INT_CONST, r, NULL, NULL, NULL, NULL);
    node->constant_value.val_int = value;
    return node;
}

PNode cNodeConstChar(int r, char value)
{
    PNode node = cNodeAST(NODE_CHAR_CONST, r, NULL, NULL, NULL, NULL);
    node->constant_value.val_char = value;
    return node;
}

PNode cNodeIdentifier(int r, char *lexem)
{
    return cNodeAST(NODE_IDENTIFICADOR, r, NULL, NULL, NULL, lexem);
}

void freeAST(PNode root)
{
    if (!root)
        return;

    freeAST(root->child_one);
    freeAST(root->child_two);
    freeAST(root->child_three);

    if (root->lexem)
        free(root->lexem);

    free(root);
}

void printAST(PNode root, int lvl)
{
    if (!root)
        return;

    for (int i = 0; i < lvl; i++)
        printf("  ");

    printf("%s", getNodeName(root->species));

    if (root->lexem)
        printf(" (%s)", root->lexem);

    if (root->species == NODE_INT_CONST)
        printf(" = %d", root->constant_value.val_int);
    else if (root->species == NODE_CHAR_CONST)
        printf(" = '%c'", root->constant_value.val_char);

    printf("\n");

    printAST(root->child_one, lvl + 1);
    printAST(root->child_two, lvl + 1);
    printAST(root->child_three, lvl + 1);
}

const char *getNodeName(NodeSpecies type)
{
    switch (type)
    {
    case NODE_PROGRAMA:
        return "NODE_PROGRAMA";
    case NODE_BLOCO:
        return "NODE_BLOCO";
    case NODE_LISTA_COMANDOS:
        return "NODE_LISTA_COMANDOS";
    case NODE_IF:
        return "NODE_IF";
    case NODE_IF_ELSE:
        return "NODE_IF_ELSE";
    case NODE_WHILE:
        return "NODE_WHILE";
    case NODE_ATRIBUICAO:
        return "NODE_ATRIBUICAO";
    case NODE_RETURN:
        return "NODE_RETURN";
    case NODE_LEIA:
        return "NODE_LEIA";
    case NODE_ESCREVA:
        return "NODE_ESCREVA";
    case NODE_ESCREVA_LITERAL:
        return "NODE_ESCREVA_LITERAL";
    case NODE_NOVALINHA:
        return "NODE_NOVALINHA";
    case NODE_CHAMADA_FUNCAO:
        return "NODE_CHAMADA_FUNCAO";
    case NODE_SOMA:
        return "NODE_SOMA";
    case NODE_SUBTRACAO:
        return "NODE_SUBTRACAO";
    case NODE_MULTIPLICACAO:
        return "NODE_MULTIPLICACAO";
    case NODE_DIVISAO:
        return "NODE_DIVISAO";
    case NODE_AND:
        return "NODE_AND";
    case NODE_OR:
        return "NODE_OR";
    case NODE_IGUAL:
        return "NODE_IGUAL";
    case NODE_DIFERENTE:
        return "NODE_DIFERENTE";
    case NODE_MENOR:
        return "NODE_MENOR";
    case NODE_MENOR_IGUAL:
        return "NODE_MENOR_IGUAL";
    case NODE_MAIOR:
        return "NODE_MAIOR";
    case NODE_MAIOR_IGUAL:
        return "NODE_MAIOR_IGUAL";
    case NODE_NEGACAO:
        return "NODE_NEGACAO";
    case NODE_MENOS_UNARIO:
        return "NODE_MENOS_UNARIO";
    case NODE_TIPO_INT:
        return "NODE_TIPO_INT";
    case NODE_TIPO_CAR:
        return "NODE_TIPO_CAR";
    case NODE_IDENTIFICADOR:
        return "NODE_IDENTIFICADOR";
    case NODE_INT_CONST:
        return "NODE_INT_CONST";
    case NODE_CHAR_CONST:
        return "NODE_CHAR_CONST";
    case NODE_STRING_LITERAL:
        return "NODE_STRING_LITERAL";
    case NODE_DECL_FUNCAO:
        return "NODE_DECL_FUNCAO";
    case NODE_DECL_VAR:
        return "NODE_DECL_VAR";
    default:
        return "NODE_DESCONHECIDO";
    }
}
