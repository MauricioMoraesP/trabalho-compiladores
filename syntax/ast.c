#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "../symbol_table/utils/helpers.h"
#include "utils/dictionary/dictionary.h"

Node *createLeafNode(NSpecies s, int row, Types type, const char *lexeme, int int_val, char car_val)
{
    Node *n = helper_malloc(sizeof(Node), "ao criar nó folha");

    n->species = s;
    n->type = type;
    n->row = row;

    n->data.leaf.lexeme = lexeme ? lexeme : NULL;
    n->data.leaf.int_val = int_val;
    n->data.leaf.char_val = car_val;

    n->next = NULL;
    return n;
}

Node *createUnaryNode(NSpecies s, int row, Types type, Node *child)
{
    Node *n = helper_malloc(sizeof(Node), "ao criar nó unário");

    n->species = s;
    n->type = type;
    n->row = row;

    n->data.unary.n = child;
    n->next = NULL;

    return n;
}

Node *createBinaryNode(NSpecies s, int row, Types type,
                       Node *left, Node *right)
{
    Node *n = helper_malloc(sizeof(Node), "ao criar nó binário");

    n->species = s;
    n->type = type;
    n->row = row;

    n->data.binary.left = left;
    n->data.binary.right = right;

    n->next = NULL;
    return n;
}

Node *createIfElseNode(NSpecies s, int row, Types type, Node *cond, Node *then_b, Node *else_b)
{
    Node *n = helper_malloc(sizeof(Node), "ao criar nó if-else");

    n->species = s;
    n->type = type;
    n->row = row;

    n->data.ifelse.condition_node = cond;
    n->data.ifelse.then_node = then_b;
    n->data.ifelse.else_node = else_b;

    n->next = NULL;
    return n;
}

Node *createNnaryNode(NSpecies s, int row, Types type)
{
    Node *n = helper_malloc(sizeof(Node), "ao criar nó n-nário");
    n->species = s;
    n->type = type;
    n->row = row;

    n->data.nnary.first = NULL;
    n->next = NULL;

    return n;
}

void nnaryAddChild(Node *parent, Node *child)
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

static void printIndent(int indent)
{
    for (int i = 0; i < indent; i++)
        printf(" ");
}

static void printLeafNode(Node *n, int indent)
{
    printIndent(indent);
    printf("Leaf %d (linha %d)\n", n->species, n->row);

    printIndent(indent + 2);
    switch (n->species)
    {
    case NOINT_CONST:
        printf("Valor: %d\n", n->data.leaf.int_val);
        break;
    case NOCAR_CONST:
        printf("Valor: '%c'\n", n->data.leaf.char_val);
        break;
    case NOSTRING_LITERAL:
        printf("String: %s\n", n->data.leaf.lexeme);
        break;
    default:
        printf("Lexema: %s\n", n->data.leaf.lexeme);
        break;
    }
}

static void printUnaryNode(Node *n, int indent, const char *label)
{
    printIndent(indent);
    printf("%s (linha %d)\n", label, n->row);
    printAST(n->data.unary.n, indent + 2);
}

static void printBinaryNode(Node *n, int indent, const char *label)
{
    printIndent(indent);
    printf("%s (linha %d)\n", label, n->row);

    printIndent(indent + 2);
    printf("Left:\n");
    printAST(n->data.binary.left, indent + 4);

    printIndent(indent + 2);
    printf("Right:\n");
    printAST(n->data.binary.right, indent + 4);
}

static void printIfElseNode(Node *n, int indent)
{
    printIndent(indent);
    printf("IF/ELSE (linha %d)\n", n->row);

    printIndent(indent + 2);
    printf("Condicao:\n");
    printAST(n->data.ifelse.condition_node, indent + 4);

    printIndent(indent + 2);
    printf("Entao:\n");
    printAST(n->data.ifelse.then_node, indent + 4);

    if (n->data.ifelse.else_node)
    {
        printIndent(indent + 2);
        printf("Senao:\n");
        printAST(n->data.ifelse.else_node, indent + 4);
    }
}

static void printNnaryNode(Node *n, int indent, const char *label)
{
    printIndent(indent);
    printf("%s (linha %d)\n", label, n->row);

    Node *child = n->data.nnary.first;
    while (child)
    {
        printAST(child, indent + 2);
        child = child->next;
    }
}

static const char *typeName(Types t)
{
    switch (t)
    {
    case TYINT:
        return "TYINT";
    case TYCAR:
        return "TYCAR";
    case TYVOID:
        return "TYVOID";
    }
    return "UNKNOWN";
}

void printAST(Node *node, int indent)
{
    if (!node)
        return;

    const NodeDictionaryEntry *info = findInfosNode(node->species);

    printIndent(indent);

    if (info)
        printf("%s (linha %d, tipo=%s)\n", info->name, node->row, typeName(node->type));
    else
        printf("UnknownNode (linha %d)\n", node->row);

    /* ---------------------- LEAF ---------------------- */
    if (info && info->type == NODE_LEAF)
    {
        printIndent(indent + 1);

        switch (node->species)
        {
        case NOINT_CONST:
            printf("Valor int: %d\n", node->data.leaf.int_val);
            break;
        case NOCAR_CONST:
            printf("Valor char: '%c'\n", node->data.leaf.char_val);
            break;
        case NOSTRING_LITERAL:
            printf("String: \"%s\"\n", node->data.leaf.lexeme);
            break;
        default:
            printf("Lexema: %s\n", node->data.leaf.lexeme ? node->data.leaf.lexeme : "(null)");
            break;
        }
        return;
    }

    /* ---------------------- UNARY ---------------------- */
    if (info && info->type == NODE_UNARY)
    {
        printAST(node->data.unary.n, indent + 1);
        return;
    }

    /* ---------------------- BINARY ---------------------- */
    if (info && info->type == NODE_BINARY)
    {
        printIndent(indent + 1);
        printf("Left:\n");
        printAST(node->data.binary.left, indent + 2);

        printIndent(indent + 1);
        printf("Right:\n");
        printAST(node->data.binary.right, indent + 2);
        return;
    }

    /* ---------------------- IF/ELSE ---------------------- */
    if (info && info->type == NODE_IFELSE)
    {
        printIndent(indent + 1);
        printf("Condicao:\n");
        printAST(node->data.ifelse.condition_node, indent + 2);

        printIndent(indent + 1);
        printf("Entao:\n");
        printAST(node->data.ifelse.then_node, indent + 2);

        if (node->data.ifelse.else_node)
        {
            printIndent(indent + 1);
            printf("Senao:\n");
            printAST(node->data.ifelse.else_node, indent + 2);
        }
        return;
    }

    /* ---------------------- NNARY ---------------------- */
    if (info && info->type == NODE_GENERIC)
    {
        Node *child = node->data.nnary.first;
        while (child)
        {
            printAST(child, indent + 1);
            child = child->next;
        }
        return;
    }

    /* fallback */
    Node *child = node->data.nnary.first;
    while (child)
    {
        printAST(child, indent + 1);
        child = child->next;
    }
}

/* =====================================================================
   FREE AST
   ===================================================================== */
void freeAST(Node *n)
{
    if (!n)
    {
        printf("[freeAST] Nó nulo recebido, nada a liberar.\n");
        return;
    }

    printf("[freeAST] Liberando nó %p, tipo %d, linha %d\n", (void *)n, n->species, n->row);

    switch (n->species)
    {
    case NOINT_CONST:
    case NOCAR_CONST:
    case NOSTRING_LITERAL:
    case NOIDENTIFICADOR:
        if (n->data.leaf.lexeme)
        {
            printf("  [freeAST] Nó folha com lexema '%s' em %p, liberando lexema %p\n",
                   n->data.leaf.lexeme, (void *)n, (void *)n->data.leaf.lexeme);
            free(n->data.leaf.lexeme);
        }
        else
        {
            printf("  [freeAST] Nó folha sem lexema em %p\n", (void *)n);
        }
        break;

    case NONEGACAO:
    case NOMENOS_UNARIO:
        printf("  [freeAST] Nó unário, liberando filho %p\n", (void *)n->data.unary.n);
        freeAST(n->data.unary.n);
        break;

    case NOWHILE:
    case NOSOMA:
    case NOSUBTRACAO:
    case NOMULTIPLICACAO:
    case NODIVISAO:
    case NOOR:
    case NOAND:
    case NOIGUAL:
    case NODIFERENTE:
    case NOMENOR:
    case NOMENOR_IGUAL:
    case NOMAIOR:
    case NOMAIOR_IGUAL:
    case NOATRIBUICAO:
        printf("  [freeAST] Nó binário, liberando left %p e right %p\n",
               (void *)n->data.binary.left, (void *)n->data.binary.right);
        freeAST(n->data.binary.left);
        freeAST(n->data.binary.right);
        break;

    case NOIF_ELSE:
        printf("  [freeAST] Nó IF-ELSE, liberando condition %p, then %p, else %p\n",
               (void *)n->data.ifelse.condition_node,
               (void *)n->data.ifelse.then_node,
               (void *)n->data.ifelse.else_node);
        freeAST(n->data.ifelse.condition_node);
        freeAST(n->data.ifelse.then_node);
        freeAST(n->data.ifelse.else_node);
        break;

    default:
        printf("  [freeAST] Nó n-ário, percorrendo filhos...\n");
        for (Node *c = n->data.nnary.first, *next; c; c = next)
        {
            next = c->next;
            printf("    [freeAST] Liberando filho %p\n", (void *)c);
            freeAST(c);
        }
        break;
    }

    if (n->species == NOBLOCO)
    {
        printf("[freeAST] Liberando NOBLOCO final na linha %d, endereço %p\n", n->row, (void *)n);
    }

    printf("[freeAST] Free nó %p concluído\n\n", (void *)n);
    free(n);
}
