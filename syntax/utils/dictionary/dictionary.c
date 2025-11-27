#include <stddef.h>
#include "dictionary.h"
#define NODE_DICTIONARY_SIZE (sizeof(NODE_DICTIONARY) / sizeof(NODE_DICTIONARY[0]))
#define NODE_SPECIES_END -1
#define N_GROUPS (sizeof(NODE_GROUPS) / sizeof(NODE_GROUPS[0]))

// Grupo de tipos de Nós.
const NodeDictionaryEntry NODE_DICTIONARY[] = {
    {NODECL_VAR, "DeclVar", NODE_GENERIC, -1, 0},
    {NODECL_FUNCAO, "DeclFunc", NODE_GENERIC, -1, 0},
    {NOCHAMADA_FUNCAO, "ChamadaFunc", NODE_GENERIC, -1, 0},
    {NOATRIBUICAO, "Atribuicao", NODE_BINARY, 2, 0},
    {NOBLOCO, "Bloco", NODE_GENERIC, -1, 0},
    {NOIF, "If", NODE_BINARY, 2, 0},
    {NOIF_ELSE, "IfElse", NODE_IFELSE, 3, 0},
    {NOWHILE, "While", NODE_BINARY, 2, 0},
    {NORETURN, "Return", NODE_UNARY, 1, 0},
    {NOWRITE, "Write", NODE_UNARY, 1, 0},
    {NOREAD, "Read", NODE_UNARY, 1, 0},
    {NONEWLINE, "NewLine", NODE_GENERIC, -1, 0},
    {NOWRITE_LITERAL, "WriteLiteral", NODE_UNARY, 1, 0},
    {NOSOMA, "Add", NODE_BINARY, 2, 0},
    {NOSUBTRACAO, "Sub", NODE_BINARY, 2, 0},
    {NOMULTIPLICACAO, "Mul", NODE_BINARY, 2, 0},
    {NODIVISAO, "Div", NODE_BINARY, 2, 0},
    {NOAND, "And", NODE_BINARY, 2, 0},
    {NOOR, "Or", NODE_BINARY, 2, 0},
    {NOIGUAL, "Eq", NODE_BINARY, 2, 0},
    {NODIFERENTE, "Neq", NODE_BINARY, 2, 0},
    {NOMENOR, "Lt", NODE_BINARY, 2, 0},
    {NOMENOR_IGUAL, "Leq", NODE_BINARY, 2, 0},
    {NOMAIOR, "Gt", NODE_BINARY, 2, 0},
    {NOMAIOR_IGUAL, "Geq", NODE_BINARY, 2, 0},
    {NONEGACAO, "Not", NODE_UNARY, 1, 0},
    {NOMENOS_UNARIO, "UnaryMinus", NODE_UNARY, 1, 0},
    {NOIDENTIFICADOR, "Ident", NODE_LEAF, 0, 1},
    {NOINT_CONST, "IntConst", NODE_LEAF, 0, 0},
    {NOCAR_CONST, "CharConst", NODE_LEAF, 0, 0},
    {NOSTRING_LITERAL, "StringLiteral", NODE_LEAF, 0, 1},
    {NOLISTA_COMANDOS, "ListaComando", NODE_GENERIC, -1, 0},
    {NOPROGRAMA, "Programa", NODE_GENERIC, -1, 0},
    {NOLISTA_EXPR, "ListaExpr", NODE_GENERIC, -1, 0},
    {NOLISTA_DECL, "ListaDeclVar", NODE_GENERIC, -1, 0},
    {NOLISTA_PARAMS, "ListaParametros", NODE_GENERIC, -1, 0},
    {NOFUNC_COMPONENTS, "ComponentesFunc", NODE_GENERIC, -1, 0},
    {(NSpecies)-1, NULL, 0, 0, 0},
};

const NodeDictionaryEntry *findInfosNode(const NSpecies s)
{
    for (int i = 0; NODE_DICTIONARY[i].species != -1; i++)
    {
        if (NODE_DICTIONARY[i].species == s)
            return &NODE_DICTIONARY[i];
    }
    return NULL;
}
