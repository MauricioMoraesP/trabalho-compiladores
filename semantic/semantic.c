#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "semantic.h"
#include "../syntax/ast.h"
#include "../symbol_table/structure.h"
#include "utils/helpers.h"
#include "../syntax/utils/dictionary/dictionary.h"

static Types current_return_type = TYVOID;
static SymbolTable *global_scope_ref = NULL;

void analyze_semantic_program(Node *root, SymbolTable *globals)
{
    if (!root || !globals)
        return;

    if (root->species != NOPROGRAMA)
    {
        helper_error_message(root->row, "O nó raiz precisa ser NOPROGRAMA.");
        return;
    }

    global_scope_ref = globals;
    for (Node *n = root->data.unary.n; n; n = n->next)
    {
        switch (n->species)
        {
        case NODECL_FUNCAO:
            semantic_function(n, globals);
            break;

        case NOBLOCO:
            create_new_scope(&globals);
            semantic_command(n, &globals, TYVOID);
            remove_current_scope(&globals);
            break;

        case NODECL_VAR:
            helper_insert_global_variables(n, &globals);
            break;

        default:
            semantic_command(n, &globals, TYVOID);
            break;
        }
    }
}

void semantic_function(Node *fun, SymbolTable *globals)
{
    if (!fun)
        return;

    Types prev_type = current_return_type;
    current_return_type = fun->type;

    create_new_scope(&globals);
    SymbolTable *local = globals;

    Node *first = fun->data.nnary.first;
    Node *params = first ? first->next : NULL;
    Node *components = params ? params->next : NULL;

    if (params && (params->species == NOLISTA_DECL || params->species == NOLISTA_PARAMS))
    {
        int position = 0;
        for (Node *p = params->data.nnary.first; p; p = p->next)
        {
            if (p->species != NOIDENTIFICADOR)
                continue;

            char *name = p->data.leaf.lexeme;
            Types t = p->type;

            if (table_search_name(local, name))
                helper_error_message(p->row, "Parametro '%s' definido duas vezes.", name);
            else
                insert_parameter(local, name, helper_convert_type(t), position++);
        }
    }

    if (components)
        semantic_command(components, &local, current_return_type);

    current_return_type = prev_type;
    remove_current_scope(&globals);
}

void semantic_command(Node *cmd, SymbolTable **scope, Types expected)
{
    if (!cmd || !scope || !*scope)
        return;

    switch (cmd->species)
    {
    case NOBLOCO:
    {
        create_new_scope(scope);

        for (Node *c = cmd->data.nnary.first; c; c = c->next)
            semantic_command(c, scope, expected);

        remove_current_scope(scope);
        break;
    }

    case NODECL_VAR:
        if (*scope != global_scope_ref)
            helper_insert_local_variables(cmd, scope);
        break;

    case NOATRIBUICAO:
        helper_analyze_atribuition(cmd, *scope);
        break;

    case NOIF:
        helper_type_is_int(cmd->data.binary.left, *scope, "A condicao do 'se' precisa ser inteira.");
        semantic_command(cmd->data.ifelse.then_node, scope, expected);
        break;

    case NOIF_ELSE:
        helper_type_is_int(cmd->data.binary.left, *scope, "A condicao do 'se-entao' deve ser int.");
        semantic_command(cmd->data.ifelse.then_node, scope, expected);
        semantic_command(cmd->data.ifelse.else_node, scope, expected);
        break;

    case NOWHILE:
        helper_type_is_int(cmd->data.binary.left, *scope, "Condicao do 'enquanto' deve ser inteira.");
        semantic_command(cmd->data.binary.right, scope, expected);
        break;

    case NORETURN:
    {
        Node *exp = cmd->data.unary.n;
        Types t = semantic_expression(exp, *scope);

        if (t != TYVOID && t != expected)
            helper_error_message(cmd->row, "Tipo retornado nao corresponde ao tipo da funcao.");
        break;
    }

    case NOCHAMADA_FUNCAO:
        semantic_expression(cmd, *scope);
        break;

    case NOWRITE:
        semantic_expression(cmd->data.unary.n, *scope);
        break;

    case NOREAD:
    {
        Node *id = cmd->data.unary.n;
        if (!id || id->species != NOIDENTIFICADOR)
        {
            helper_error_message(cmd->row, "Comando 'leia' exige um identificador.");
            break;
        }

        SymbolEntry *s = table_search_above(*scope, id->data.leaf.lexeme);
        if (!s)
        {
            helper_error_message(id->row, "Variavel '%s' nao declarada.", id->data.leaf.lexeme);
            break;
        }

        if (helper_convert_type(s->type) != TYINT)
            helper_error_message(id->row, "'leia' aceita apenas inteiros.");
        break;
    }

    default:
        break;
    }
}

Types semantic_expression(Node *ex, SymbolTable *scope)
{
    if (!ex)
        return TYVOID;

    switch (ex->species)
    {
    case NOINT_CONST:
        return TYINT;

    case NOCAR_CONST:
        return TYCAR;

    case NOIDENTIFICADOR:
    {
        SymbolEntry *s = table_search_above(scope, ex->data.leaf.lexeme);
        if (!s)
        {
            helper_error_message(ex->row, "Identificador '%s' nao declarado.", ex->data.leaf.lexeme);
            exit(1);
        }
        return helper_convert_type(s->type);
    }

    case NOATRIBUICAO:
        return helper_analyze_atribuition(ex, scope);

    case NOSOMA:
    case NOSUBTRACAO:
    case NOMULTIPLICACAO:
    case NODIVISAO:
        return helper_check_binary_int(ex, scope, "Operacoes aritmeticas exigem inteiros.");

    case NOOR:
    case NOAND:
        return helper_check_binary_int(ex, scope, "Operacoes logicas exigem inteiros.");

    case NOIGUAL:
    case NODIFERENTE:
    case NOMENOR:
    case NOMENOR_IGUAL:
    case NOMAIOR:
    case NOMAIOR_IGUAL:
        return helper_check_binary_same(ex, scope, "Comparacao entre tiposition diferentes.");

    case NOCHAMADA_FUNCAO:
        return semantic_func_call(ex, scope);

    default:
        return TYVOID;
    }
}

Types semantic_func_call(Node *call, SymbolTable *scope)
{
    Node *name_node = call->data.nnary.first;

    if (!name_node || name_node->species != NOIDENTIFICADOR)
    {
        helper_error_message(call->row, "Chamada de funcao mal formada.");
        return TYVOID;
    }

    char *name = name_node->data.leaf.lexeme;
    SymbolEntry *s = table_search_above(scope, name);

    if (!s)
    {
        helper_error_message(call->row, "Funcao '%s' nao declarada.", name);
        return TYVOID;
    }

    if (s->entry != FUN_ENTRY)
    {
        helper_error_message(call->row, "'%s' nao e funcao.", name);
        return TYVOID;
    }

    Types ret = helper_convert_type(s->data.fun_data.type);

    Node *arg = name_node->next;
    int real = 0;
    for (Node *x = arg; x; x = x->next)
        real++;

    int expected = s->data.fun_data.count_params;
    if (real != expected)
    {
        helper_error_message(call->row, "Funcao '%s' recebeu %d argumentos, esperava %d.", name, real, expected);
    }

    DataType *formal = s->data.fun_data.param_types;

    int i = 0;
    for (Node *p = arg; p && i < expected; p = p->next, i++)
    {
        Types got = semantic_expression(p, scope);
        Types want = helper_convert_type(formal[i]);

        if (got != want)
            helper_error_message(call->row, "Tipo do argumento %d de '%s' nao confere.", i + 1, name);
    }

    return ret;
}
