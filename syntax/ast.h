#ifndef AST_H
#define AST_H
#include "types.h"

PNode cNodeAST(NodeSpecies species, int row, PNode first_children, PNode second_children, PNode third_children, char *lexem);
PNode cNodeConstInt(int r, int value);
PNode cNodeConstChar(int r, char value);
PNode cNodeIdentifier(int r, char *lexem);
void freeAST(PNode root);
void printAST(PNode root, int lvl);

#endif