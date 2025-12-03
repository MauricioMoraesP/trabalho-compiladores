#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "../symbol_table/utils/helpers.h"
#include "utils/dictionary/dictionary.h"

/* Cria um nó genérico */
static Node *new_node_generic(NSpecies s, int row, Types type)
{
    Node *n = helper_malloc(sizeof(Node), "ao criar no");
    n->species = s;
    n->type = type;
    n->row = row;
    n->next = NULL;
    return n;
}

/* Cria nó folha*/
Node *create_leaf_node(NSpecies s, int row, Types type, const char *lexeme, int int_val, char car_val)
{
    Node *n = new_node_generic(s, row, type);

    n->data.leaf.lexeme = lexeme ? strdup(lexeme) : NULL;
    n->data.leaf.int_val = int_val;
    n->data.leaf.char_val = car_val;

    return n;
}

/* Cria nó unário */
Node *create_unary_node(NSpecies s, int row, Types type, Node *child)
{
    Node *n = new_node_generic(s, row, type);
    n->data.unary.n = child;
    return n;
}

/* Cria nó binário */
Node *create_binary_node(NSpecies s, int row, Types type, Node *left, Node *right)
{
    Node *n = new_node_generic(s, row, type);
    n->data.binary.left = left;
    n->data.binary.right = right;
    return n;
}

/* Cria nó IF/ELSE */
Node *create_if_else_node(NSpecies s, int row, Types type, Node *cond, Node *then_b, Node *else_b)
{
    Node *n = new_node_generic(s, row, type);
    n->data.ifelse.condition_node = cond;
    n->data.ifelse.then_node = then_b;
    n->data.ifelse.else_node = else_b;
    return n;
}

/* Cria nó N-nário */
Node *create_nnary_node(NSpecies s, int row, Types type)
{
    Node *n = new_node_generic(s, row, type);
    n->data.nnary.first = NULL;
    return n;
}

/* Adiciona filho a nó N-nário */
void nnary_add_child(Node *parent, Node *child)
{
    if (!parent || !child)
        return;

    if (!parent->data.nnary.first)
    {
        parent->data.nnary.first = child;
        child->next = NULL;
        return;
    }

    Node *last = parent->data.nnary.first;
    while (last->next)
        last = last->next;

    last->next = child;
    child->next = NULL;
}

/* Libera recursivamente a AST usando o dicionário */
void free_ast(Node *n)
{
    if (!n)
        return;

    const NodeDictionaryEntry *info = findInfosNode(n->species);

    switch (info->type)
    {
    case NODE_LEAF:
        if (info->has_lexeme && n->data.leaf.lexeme)
            free(n->data.leaf.lexeme);
        break;

    case NODE_UNARY:
        free_ast(n->data.unary.n);
        break;

    case NODE_BINARY:
        free_ast(n->data.binary.left);
        free_ast(n->data.binary.right);
        break;

    case NODE_IFELSE:
        free_ast(n->data.ifelse.condition_node);
        free_ast(n->data.ifelse.then_node);
        free_ast(n->data.ifelse.else_node);
        break;

    case NODE_GENERIC:
        for (Node *c = n->data.nnary.first, *next; c; c = next)
        {
            next = c->next;
            free_ast(c);
        }
        break;
    }

    free(n);
}
