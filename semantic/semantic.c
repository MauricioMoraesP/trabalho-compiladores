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
    if (ast == NULL)
        return;

    if (ast->species != NOPROGRAMA)
    {
        error_message(ast->row, "A raiz do programa não e um NOPROGRAMA, reescreva o código.");
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

                        if (!table_search_name(global_scope, name))
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
    if (func == NULL)
        return;

    Types type = current_function_type;

    current_function_type = func->type;

    create_new_scope(&global_scope);
    SymbolTable *function_scope = global_scope;

    Node *first_node = func->data.nnary.first;
    Node *params = first_node ? first_node->next : NULL;
    Node *body = params ? params->next : NULL;

    if (params && (params->species == NOLISTA_DECL || params->species == NOLISTA_PARAMS))
    {
        Node *p = params->data.nnary.first;
        int cont = 0;

        while (p)
        {
            if (p->species == NOIDENTIFICADOR)
            {
                char *name = p->data.leaf.lexeme;
                Types type_params = p->type;

                if (table_search_name(function_scope, name))
                {
                    error_message(p->row, "Problema de redeclaração de parametro: '%s'.", name);
                }
                else
                    insert_parameter(function_scope, name, convert_type(type_params), cont);

                cont++;
            }
            p = p->next;
        }
    }

    if (body && body->species == NOBLOCO)
        analyze_command(body, &function_scope, current_function_type);
    else
        analyze_command(body, &function_scope, current_function_type);

    current_function_type = type;
    remove_current_scope(&global_scope);
}

void analyze_command(Node *cmd, SymbolTable **scope, Types return_prev)
{
    if (cmd == NULL || scope == NULL)
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
            break;

        Node *decl = cmd->data.nnary.first;
        while (decl)
        {
            if (decl->species == NOIDENTIFICADOR)
            {
                char *name = decl->data.leaf.lexeme;
                Types tdecl = cmd->type;

                if (table_search_name(*scope, name))
                {
                    error_message(decl->row, "Variavel '%s' foi redeclarada no mesmo escopo, corrija seu codigo.", name);
                }
                else
                {
                    SymbolEntry *found = NULL;

                    if ((*scope)->before_scope)
                        found = table_search_above((*scope)->before_scope, name);

                    if (found && found->entry == PARAM_ENTRY)
                        error_message(decl->row, "Varivel tem o mesmo nome do parametro:'%s' .", name);

                    if (found == NULL)
                        insert_variable(*scope, name, convert_type(tdecl), 0);
                }
            }
            decl = decl->next;
        }
        break;
    }

    case NOATRIBUICAO:
    {
        analyze_atribuition(cmd, *scope);
        break;
    }

    case NOIF:
    {
        type_is_int(cmd->data.binary.left, *scope, "Condicao do 'se' deve ser int valida.");
        analyze_command(cmd->data.ifelse.then_node, scope, return_prev);
        break;
    }

    case NOIF_ELSE:
    {
        type_is_int(cmd->data.binary.left, *scope, "Condicao do 'se então' deve ser int valida.");
        analyze_command(cmd->data.ifelse.then_node, scope, return_prev);
        analyze_command(cmd->data.ifelse.else_node, scope, return_prev);
        break;
    }

    case NOWHILE:
    {
        type_is_int(cmd->data.binary.left, *scope, "Condicao do enquanto deve ser int valido.");
        analyze_command(cmd->data.binary.right, scope, return_prev);
        break;
    }
    case NORETURN:
    {
        Node *expression = cmd->data.unary.n;
        Types type = analyze_expression(expression, *scope);
        if (type != TYVOID && type != return_prev)
            error_message(cmd->row, "Tipo da expressao retornada é diferente do tipo da funçao.");

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
            break;
        }
        SymbolEntry *s = table_search_above(*scope, id->data.leaf.lexeme);
        if (!s)
        {
            error_message(id->row, "Variavel '%s' nao foi declarada.", id->data.leaf.lexeme);
            break;
        }
        if (convert_type(s->type) != TYINT)
            error_message(id->row, "Comando 'leia' não aceita aceita variaveis  não inteiras.");

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
        SymbolEntry *symbol = table_search_above(scope, expression->data.leaf.lexeme);
        if (!symbol)
        {
            error_message(expression->row, "Identificador '%s' nao foi declaro.", expression->data.leaf.lexeme);
            exit(1);
            return TYVOID;
        }
        return convert_type(symbol->type);
    }

    case NOATRIBUICAO:
    {
        return analyze_atribuition(expression, scope);
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
    Node *first_node = func->data.nnary.first;
    if (!first_node || first_node->species != NOIDENTIFICADOR)
    {
        error_message(func->row, "Chamada de funcao invalida.");
        return TYVOID;
    }

    char *func_name = first_node->data.leaf.lexeme;
    SymbolEntry *symbol = table_search_above(scope, func_name);
    if (!symbol)
    {
        error_message(func->row, "Funcao '%s' não declarada.", func_name);
        return TYVOID;
    }
    if (symbol->entry != FUN_ENTRY)
    {
        error_message(func->row, "'%s' nao e uma funcao valida no programa.", func_name);
        return TYVOID;
    }

    Types type = convert_type(symbol->data.fun_data.type);
    Node *args = first_node->next;
    int expected = symbol->data.fun_data.count_params;
    int real = 0;
    Node *p = args;
    while (p)
    {
        real++;
        p = p->next;
    }
    if (real != expected)
        error_message(func->row, "Funcao '%s' usa %d argumentos, porem espera %d.", func_name, real, expected);

    DataType *formal = symbol->data.fun_data.param_types;
    p = args;
    int i = 0;
    while (p && i < expected)
    {
        Types arg_type = analyze_expression(p, scope);
        Types real_type = convert_type(formal[i]);
        if (arg_type != real_type)
            error_message(func->row, "Tipo do argumento %d da funcao '%s' e incompativel.", i + 1, func_name);
        i++;
        p = p->next;
    }

    return type;
}