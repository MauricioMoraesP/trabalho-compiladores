#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "utils/helpers.h"
#include "../syntax/ast.h"
#include "../symbol_table/structure.h"
#include "semantic.h"
#include "../syntax/utils/dictionary/dictionary.h"

extern int sem_error;

Types current_function_type = TYVOID;

static SymbolTable *root_global_scope = NULL;

void analyze_program(Node *ast, SymbolTable *global_scope)
{
    if (!ast)
        return;

    if (ast->species != NOPROGRAMA)
    {
        error_message(ast->row, "AST inválida: raiz não é NOPROGRAMA.");
        sem_error = 1;
        return;
    }

    root_global_scope = global_scope;

    Node *child = ast->data.unary.n;
    while (child)
    {
        if (child->species == NODECL_FUNCAO)
        {
            analyze_function(child, global_scope);
        }
        else if (child->species == NOBLOCO)
        {
            create_new_scope(&global_scope);
            analyze_command(child, &global_scope, TYVOID);
            remove_current_scope(&global_scope);
        }
        else
        {
            if (child->species == NODECL_VAR)
            {
                Node *decl_id = child->data.nnary.first;
                while (decl_id)
                {
                    if (decl_id->species == NOIDENTIFICADOR)
                    {
                        char *name = decl_id->data.leaf.lexeme;
                        Types tdecl = child->type;

                        if (!table_search_name_in_CURRENT_scope(global_scope, name))
                        {
                            insert_variable(global_scope, name, convert_type(tdecl), 0);
                        }
                    }
                    decl_id = decl_id->next;
                }
            }

            analyze_command(child, &global_scope, TYVOID);
        }
        child = child->next;
    }
}

void analyze_function(Node *func_node, SymbolTable *global_scope)
{
    if (!func_node)
        return;

    Types old_type = current_function_type;

    current_function_type = func_node->type;

    create_new_scope(&global_scope);
    SymbolTable *function_scope = global_scope;

    Node *name_node = func_node->data.nnary.first;
    Node *params_node = name_node ? name_node->next : NULL;
    Node *body_node = params_node ? params_node->next : NULL;

    if (params_node &&
        (params_node->species == NOLISTA_DECL ||
         params_node->species == NOLISTA_PARAMS))
    {
        Node *p = params_node->data.nnary.first;
        int pos = 0;

        while (p)
        {
            if (p->species == NOIDENTIFICADOR)
            {
                char *name = p->data.leaf.lexeme;
                Types tparam = p->type;

                if (table_search_name_in_CURRENT_scope(function_scope, name))
                {
                    error_message(p->row, "Parâmetro '%s' redeclarado.", name);
                    sem_error = 1;
                }
                else
                {
                    insert_parameter(function_scope, name, convert_type(tparam), pos);
                }
                pos++;
            }
            p = p->next;
        }
    }

    if (body_node && body_node->species == NOBLOCO)
    {
        analyze_command(body_node, &function_scope, current_function_type);
    }
    else
    {
        analyze_command(body_node, &function_scope, current_function_type);
    }

    current_function_type = old_type;

    remove_current_scope(&global_scope);
}

void analyze_command(Node *cmd, SymbolTable **scope, Types expected_return)
{
    if (!cmd || !scope)
        return;

    switch (cmd->species)
    {
    case NOBLOCO:
    {
        create_new_scope(scope);

        Node *c = cmd->data.nnary.first;
        while (c)
        {
            analyze_command(c, scope, expected_return);
            c = c->next;
        }

        remove_current_scope(scope);
        break;
    }

    case NODECL_VAR:
    {
        if (*scope == root_global_scope)
        {
            break;
        }

        Node *decl = cmd->data.nnary.first;
        while (decl)
        {
            if (decl->species == NOIDENTIFICADOR)
            {
                char *name = decl->data.leaf.lexeme;
                Types tdecl = cmd->type;

                if (table_search_name_in_CURRENT_scope(*scope, name))
                {
                    error_message(decl->row, "Variável '%s' redeclarada no mesmo escopo.", name);
                    sem_error = 1;
                }
                else
                {
                    SymbolEntry *found = NULL;

                    if ((*scope)->before_scope)
                    {
                        found = table_search_upwards((*scope)->before_scope, name);
                    }

                    if (found && found->entry == PARAM_ENTRY)
                    {
                        error_message(decl->row, "Variável '%s' conflita com parâmetro da função.", name);
                        sem_error = 1;
                    }

                    if (!sem_error)
                    {
                        insert_variable(*scope, name, convert_type(tdecl), 0);
                    }
                }
            }
            decl = decl->next;
        }
        break;
    }

    case NOATRIBUICAO:
    {
        Node *left = cmd->data.binary.left;
        Node *right = cmd->data.binary.right;

        if (!left || left->species != NOIDENTIFICADOR)
        {
            error_message(cmd->row, "Atribuição inválida: lado esquerdo não é identificador.");
            sem_error = 1;
            break;
        }

        SymbolEntry *sym = table_search_upwards(*scope, left->data.leaf.lexeme);
        if (!sym)
        {
            error_message(cmd->row, "Variável '%s' não declarada.", left->data.leaf.lexeme);
            sem_error = 1;
            break;
        }

        Types rt = analyze_expression(right, *scope);
        Types lt = convert_type(sym->type);

        if (rt != lt)
        {
            error_message(cmd->row, "Atribuição com tipo incompatível para '%s'.", left->data.leaf.lexeme);
            sem_error = 1;
        }
        break;
    }

    case NOIF:
    {
        Types cond_t = analyze_expression(cmd->data.ifelse.condition_node, *scope);
        if (cond_t != TYINT)
        {
            error_message(cmd->row, "Condição do 'se' deve ser int.");
            sem_error = 1;
        }
        analyze_command(cmd->data.ifelse.then_node, scope, expected_return);
        break;
    }

    case NOIF_ELSE:
    {
        Types cond_t = analyze_expression(cmd->data.ifelse.condition_node, *scope);
        if (cond_t != TYINT)
        {
            error_message(cmd->row, "Condição do 'se' deve ser int.");
            sem_error = 1;
        }
        analyze_command(cmd->data.ifelse.then_node, scope, expected_return);
        analyze_command(cmd->data.ifelse.else_node, scope, expected_return);
        break;
    }

    case NOWHILE:
    {
        Types cond_t = analyze_expression(cmd->data.binary.left, *scope);
        if (cond_t != TYINT)
        {
            error_message(cmd->row, "Condição do 'enquanto' deve ser int.");
            sem_error = 1;
        }
        analyze_command(cmd->data.binary.right, scope, expected_return);
        break;
    }

    case NORETURN:
    {
        Node *expr = cmd->data.unary.n;
        Types tret = analyze_expression(expr, *scope);
        if (tret != expected_return)
        {
            error_message(cmd->row, "Tipo da expressão retornada difere do tipo da função.");
            sem_error = 1;
        }
        break;
    }

    case NOCHAMADA_FUNCAO:
        analyze_expression(cmd, *scope);
        break;

    case NOWRITE:
        analyze_expression(cmd->data.unary.n, *scope);
        break;

    case NOWRITE_LITERAL:
    case NONEWLINE:
        break;

    case NOREAD:
    {
        Node *id = cmd->data.unary.n;
        if (!id || id->species != NOIDENTIFICADOR)
        {
            error_message(cmd->row, "Comando 'leia' com argumento inválido.");
            sem_error = 1;
            break;
        }
        SymbolEntry *s = table_search_upwards(*scope, id->data.leaf.lexeme);
        if (!s)
        {
            error_message(id->row, "Variável '%s' não declarada.", id->data.leaf.lexeme);
            sem_error = 1;
            break;
        }
        if (convert_type(s->type) != TYINT)
        {
            error_message(id->row, "Comando 'leia' só aceita variáveis inteiras.");
            sem_error = 1;
        }
        break;
    }

    default:
        break;
    }
}

Types analyze_expression(Node *expr, SymbolTable *scope)
{
    if (!expr)
        return TYVOID;

    switch (expr->species)
    {
    case NOINT_CONST:
        return TYINT;

    case NOCAR_CONST:
        return TYCAR;

    case NOIDENTIFICADOR:
    {
        SymbolEntry *sym = table_search_upwards(scope, expr->data.leaf.lexeme);
        if (!sym)
        {
            error_message(expr->row, "Identificador '%s' não declarado.", expr->data.leaf.lexeme);
            sem_error = 1;
            return TYVOID;
        }
        return convert_type(sym->type);
    }

    case NOATRIBUICAO:
    {
        Node *left = expr->data.binary.left;
        Node *right = expr->data.binary.right;

        if (!left || left->species != NOIDENTIFICADOR)
        {
            error_message(expr->row, "Atribuição inválida: lado esquerdo não é identificador.");
            sem_error = 1;
            return TYVOID;
        }

        SymbolEntry *sym = table_search_upwards(scope, left->data.leaf.lexeme);
        if (!sym)
        {
            error_message(expr->row, "Variável '%s' não declarada.", left->data.leaf.lexeme);
            sem_error = 1;
            return TYVOID;
        }

        Types rt = analyze_expression(right, scope);
        Types lt = convert_type(sym->type);

        if (rt != lt)
        {
            error_message(expr->row, "Atribuição com tipo incompatível para '%s'.", left->data.leaf.lexeme);
            sem_error = 1;
        }
        return lt;
    }

    case NOSOMA:
    case NOSUBTRACAO:
    case NOMULTIPLICACAO:
    case NODIVISAO:
    {
        Types l = analyze_expression(expr->data.binary.left, scope);
        Types r = analyze_expression(expr->data.binary.right, scope);
        if (l != TYINT || r != TYINT)
        {
            error_message(expr->row, "Operações aritméticas exigem inteiros.");
            sem_error = 1;
        }
        return TYINT;
    }

    case NOOR:
    case NOAND:
    {
        Types l = analyze_expression(expr->data.binary.left, scope);
        Types r = analyze_expression(expr->data.binary.right, scope);
        if (l != TYINT || r != TYINT)
        {
            error_message(expr->row, "Operações lógicas exigem inteiros.");
            sem_error = 1;
        }
        return TYINT;
    }

    case NOIGUAL:
    case NODIFERENTE:
    case NOMENOR:
    case NOMENOR_IGUAL:
    case NOMAIOR:
    case NOMAIOR_IGUAL:
    {
        Types l = analyze_expression(expr->data.binary.left, scope);
        Types r = analyze_expression(expr->data.binary.right, scope);
        if (l != r)
        {
            error_message(expr->row, "Comparação entre tipos diferentes.");
            sem_error = 1;
        }
        return TYINT;
    }

    case NOCHAMADA_FUNCAO:
        return analyze_func_call(expr, scope);

    default:
        return TYVOID;
    }
}

Types analyze_func_call(Node *call, SymbolTable *scope)
{
    Node *name_node = call->data.nnary.first;
    if (!name_node || name_node->species != NOIDENTIFICADOR)
    {
        error_message(call->row, "Chamada de função inválida (nome ausente).");
        sem_error = 1;
        return TYVOID;
    }

    char *func_name = name_node->data.leaf.lexeme;
    SymbolEntry *sym = table_search_upwards(scope, func_name);
    if (!sym)
    {
        error_message(call->row, "Função '%s' não declarada.", func_name);
        sem_error = 1;
        return TYVOID;
    }
    if (sym->entry != FUN_ENTRY)
    {
        error_message(call->row, "'%s' não é uma função.", func_name);
        sem_error = 1;
        return TYVOID;
    }

    Types ret = convert_type(sym->data.fun_data.type);
    Node *arg_list = name_node->next;
    int expected = sym->data.fun_data.count_params;
    int actual = 0;
    Node *p = arg_list;
    while (p)
    {
        actual++;
        p = p->next;
    }
    if (actual != expected)
    {
        error_message(call->row, "Função '%s' chamada com %d argumentos, mas espera %d.",
                      func_name, actual, expected);
        sem_error = 1;
    }

    DataType *formal = sym->data.fun_data.param_types;
    p = arg_list;
    int idx = 0;
    while (p && idx < expected)
    {
        Types arg_t = analyze_expression(p, scope);
        Types formal_t = convert_type(formal[idx]);
        if (arg_t != formal_t)
        {
            error_message(call->row, "Tipo do argumento %d da função '%s' incompatível.", idx + 1, func_name);
            sem_error = 1;
        }
        idx++;
        p = p->next;
    }

    return ret;
}