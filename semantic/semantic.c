#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "utils/helpers.h"
#include "../syntax/ast.h"
#include "../symbol_table/structure.h"
#include "semantic.h"
#include "../syntax/utils/dictionary/dictionary.h"

Types current_function_type = TYVOID;
SymbolTable *root_gl_scope = NULL;

void analyze_program(Node *ast, SymbolTable *global_scope)
{
    if (!ast)
        return;

    if (ast->species != NOPROGRAMA)
    {
        error_message(ast->row, "AST invalida: raiz nao e NOPROGRAMA.");
        sem_error = 1;
        return;
    }

    root_gl_scope = global_scope;

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

                        if (!table_search_name_in_scope(global_scope, name))
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

void analyze_function(Node *func, SymbolTable *global_scope)
{
    if (!func)
        return;

    Types type = current_function_type;

    current_function_type = func->type;

    create_new_scope(&global_scope);
    SymbolTable *function_scope = global_scope;

    Node *name_node = func->data.nnary.first;
    Node *params_node = name_node ? name_node->next : NULL;
    Node *body_node = params_node ? params_node->next : NULL;

    if (params_node &&
        (params_node->species == NOLISTA_DECL ||
         params_node->species == NOLISTA_PARAMS))
    {
        Node *p = params_node->data.nnary.first;
        int cont = 0;

        while (p)
        {
            if (p->species == NOIDENTIFICADOR)
            {
                char *name = p->data.leaf.lexeme;
                Types tparam = p->type;

                if (table_search_name_in_scope(function_scope, name))
                {
                    error_message(p->row, "Parametro '%s' redeclarado.", name);
                    sem_error = 1;
                }
                else
                {
                    insert_parameter(function_scope, name, convert_type(tparam), cont);
                }
                cont++;
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

    current_function_type = type;

    remove_current_scope(&global_scope);
}

void analyze_command(Node *cmd, SymbolTable **scope, Types return_prev)
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
            analyze_command(c, scope, return_prev);
            c = c->next;
        }

        remove_current_scope(scope);
        break;
    }

    case NODECL_VAR:
    {
        if (*scope == root_gl_scope)
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

                if (table_search_name_in_scope(*scope, name))
                {
                    error_message(decl->row, "Variavel '%s' redeclarada no mesmo escopo.", name);
                    sem_error = 1;
                }
                else
                {
                    SymbolEntry *found = NULL;

                    if ((*scope)->before_scope)
                    {
                        found = table_search_up((*scope)->before_scope, name);
                    }

                    if (found && found->entry == PARAM_ENTRY)
                    {
                        error_message(decl->row, "Variavel '%s' conflita com parametro da funcao.", name);
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
        analyze_assignment(cmd, *scope);
        break;
    }

    case NOIF:
    {
        require_int(cmd->data.binary.left, *scope, "Condicao do 'se' deve ser int.");
        analyze_command(cmd->data.ifelse.then_node, scope, return_prev);
        break;
    }

    case NOIF_ELSE:
    {
        require_int(cmd->data.binary.left, *scope, "Condicao do 'se então' deve ser int.");
        analyze_command(cmd->data.ifelse.then_node, scope, return_prev);
        analyze_command(cmd->data.ifelse.else_node, scope, return_prev);
        break;
    }

    case NOWHILE:
    {
        require_int(cmd->data.binary.left, *scope, "Condicao do 'enquanto' deve ser int.");
        analyze_command(cmd->data.binary.right, scope, return_prev);
        break;
    }

    case NORETURN:
    {
        Node *expression = cmd->data.unary.n;
        Types tret = analyze_expression(expression, *scope);
        if (tret != return_prev)
        {
            error_message(cmd->row, "Tipo da expressionessão retornada difere do tipo da função.");
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
            error_message(cmd->row, "Comando 'leia' com argumento invalido.");
            sem_error = 1;
            break;
        }
        SymbolEntry *s = table_search_up(*scope, id->data.leaf.lexeme);
        if (!s)
        {
            error_message(id->row, "Variavel '%s' nao declarada.", id->data.leaf.lexeme);
            sem_error = 1;
            break;
        }
        if (convert_type(s->type) != TYINT)
        {
            error_message(id->row, "Comando 'leia' só aceita variaveis inteiras.");
            sem_error = 1;
        }
        break;
    }

    default:
        break;
    }
}

Types analyze_expression(Node *expression, SymbolTable *scope)
{
    if (!expression)
        return TYVOID;

    switch (expression->species)
    {
    case NOINT_CONST:
        return TYINT;

    case NOCAR_CONST:
        return TYCAR;

    case NOIDENTIFICADOR:
    {
        SymbolEntry *symbol = table_search_up(scope, expression->data.leaf.lexeme);
        if (!symbol)
        {
            error_message(expression->row, "Identificador '%s' nao declarado.", expression->data.leaf.lexeme);
            sem_error = 1;
            return TYVOID;
        }
        return convert_type(symbol->type);
    }

    case NOATRIBUICAO:
    {
        return analyze_assignment(expression, scope);
    }

    case NOSOMA:
    case NOSUBTRACAO:
    case NOMULTIPLICACAO:
    case NODIVISAO:
        return check_binary_int(expression, scope, "Operacao aritmeticas exigem inteiros.");
    case NOOR:
    case NOAND:
        return check_binary_int(expression, scope, "Operacao logicas exigem inteiros.");
    case NOIGUAL:
    case NODIFERENTE:
    case NOMENOR:
    case NOMENOR_IGUAL:
    case NOMAIOR:
    case NOMAIOR_IGUAL:
        return check_binary_same(expression, scope, "Comparacao entre tipos diferentes.");
    case NOCHAMADA_FUNCAO:
        return analyze_func_call(expression, scope);

    default:
        return TYVOID;
    }
}

Types analyze_func_call(Node *func, SymbolTable *scope)
{
    Node *name_node = func->data.nnary.first;
    if (!name_node || name_node->species != NOIDENTIFICADOR)
    {
        error_message(func->row, "Chamada de funcao invalida.");
        sem_error = 1;
        return TYVOID;
    }

    char *func_name = name_node->data.leaf.lexeme;
    SymbolEntry *symbol = table_search_up(scope, func_name);
    if (!symbol)
    {
        error_message(func->row, "Funcao '%s' não declarada.", func_name);
        sem_error = 1;
        return TYVOID;
    }
    if (symbol->entry != FUN_ENTRY)
    {
        error_message(func->row, "'%s' nao e uma funcao.", func_name);
        sem_error = 1;
        return TYVOID;
    }

    Types type = convert_type(symbol->data.fun_data.type);
    Node *args = name_node->next;
    int expected = symbol->data.fun_data.count_params;
    int actual = 0;
    Node *p = args;
    while (p)
    {
        actual++;
        p = p->next;
    }
    if (actual != expected)
    {
        error_message(func->row, "Funcao '%s' chamada com %d argumentos, mas espera %d.", func_name, actual, expected);
        sem_error = 1;
    }

    DataType *formal = symbol->data.fun_data.param_types;
    p = args;
    int i = 0;
    while (p && i < expected)
    {
        Types arg_t = analyze_expression(p, scope);
        Types formal_t = convert_type(formal[i]);
        if (arg_t != formal_t)
        {
            error_message(func->row, "Tipo do argumento %d da funcao '%s' incompativel.", i + 1, func_name);
            sem_error = 1;
        }
        i++;
        p = p->next;
    }

    return type;
}