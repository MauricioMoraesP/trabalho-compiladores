#ifndef AST_H
#define AST_H
#include "types.h"

Node *create_leaf_node(NSpecies s, int row, Types type, const char *lex, int val, char car_val);
Node *create_unary_node(NSpecies s, int row, Types type, Node *child);
Node *create_binary_node(NSpecies s, int row, Types type, Node *left, Node *right);
Node *create_if_else_node(NSpecies s, int row, Types type, Node *cond, Node *then_node, Node *else_node);
Node *create_nnary_node(NSpecies s, int row, Types type);
void nnary_add_child(Node *parent, Node *child);
void free_ast(Node *n);
#endif
