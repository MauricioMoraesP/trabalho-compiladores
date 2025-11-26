#ifndef AST_H
#define AST_H

#include "types.h"
Node *createLeafNode(NSpecies s, int row, Types type, const char *lex, int val, char car_val);
Node *createUnaryNode(NSpecies s, int row, Types type, Node *child);
Node *createBinaryNode(NSpecies s, int row, Types type, Node *left, Node *right);
Node *createIfElseNode(NSpecies s, int row, Types type, Node *cond, Node *then_node, Node *else_node);
Node *createNnaryNode(NSpecies s, int row, Types type);
void nnaryAddChild(Node *parent, Node *child);
const char *getNodeName(NSpecies s);
void printAST(Node *n, int lvl);
void freeAST(Node *n);

#endif
