#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "utils/helpers.h"
#include "../syntax/ast.h"
#include "../symbol_table/structure.h"
#include "semantic.h"
#include "../syntax/utils/dictionary/dictionary.h"

Types global_fun_type = TYVOID;
SymbolTable *root_gl_scope = NULL;

/* Faz a análise semântica geral do programa. Começa do NOPROGRAMA e vai varrendo tudo. */
void analyze_semantic_program(Node *ast, SymbolTable *global)
{
    helper_validation_null_table(global);

    if (ast == NULL)
        return;

    /* O nó raiz obrigatoriamente tem que ser um NOPROGRAMA */
    if (ast->species != NOPROGRAMA)
    {
        helper_error_message(ast->row, "A raiz do programa não e um NOPROGRAMA, reescreva o código.");
        return;
    }

    /* Guardamos onde está o escopo global real */
    root_gl_scope = global;

    Node *child = ast->data.unary.n;
    while (child)
    {
        /* Análise das funções declaradas antes do programa */
        if (child->species == NODECL_FUNCAO)
        {
            semantic_function(child, global);
        }
        /* Analisa o bloco principal do programa (dentro de 'programa { }') */
        else if (child->species == NOBLOCO)
        {
            create_new_scope(&global);
            semantic_command(child, &global, TYVOID);
            remove_current_scope(&global);
        }
        else
        {
            /* Tratamento das declarações globais antes do bloco principal */
            if (child->species == NODECL_VAR)
            {
                Node *declaration_id = child->data.nnary.first;
                while (declaration_id)
                {
                    if (declaration_id->species == NOIDENTIFICADOR)
                    {
                        char *name = declaration_id->data.leaf.lexeme;
                        Types tdeclaration = child->type;

                        /* Variável global só entra se ainda não existir. Se já existe no global, é redeclaração. */
                        if (!table_search_name(global, name))
                        {
                            insert_variable(global, name, helper_convert_type(tdeclaration), 0);
                        }
                    }
                    declaration_id = declaration_id->next;
                }
            }

            /* Para qualquer outro comando global, aplica as regras semânticas */
            semantic_command(child, &global, TYVOID);
        }
        child = child->next;
    }
}

/* Análise semântica da função: parâmetros, corpo e tipo de retorno */
void semantic_function(Node *func, SymbolTable *global)
{
    if (func == NULL)
        return;

    /* Guarda o tipo de retorno anterior (caso esteja processando outra função antes) */
    Types type = global_fun_type;

    /* Define o tipo de retorno que a função atual promete retornar */
    global_fun_type = func->type;

    /* Toda função abre seu próprio escopo local */
    create_new_scope(&global);
    SymbolTable *function_scope = global;

    /* Pega a lista de parâmetros e o bloco da função */
    Node *first_node = func->data.nnary.first;
    Node *params = first_node ? first_node->next : NULL;
    Node *components = params ? params->next : NULL;

    /* Insere os parâmetros formais na tabela da função */
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

                /* Parâmetro não pode repetir nome dentro do escopo da função */
                if (table_search_name(function_scope, name))
                {
                    helper_error_message(p->row, "Problema de redeclarationaração de parametro: '%s'.", name);
                }
                else
                    insert_parameter(function_scope, name, helper_convert_type(type_params), cont);

                cont++;
            }
            p = p->next;
        }
    }

    /* Analisa o bloco da função, validando retornos e comandos */
    if (components && components->species == NOBLOCO)
        semantic_command(components, &function_scope, global_fun_type);
    else
        semantic_command(components, &function_scope, global_fun_type);

    /* Volta o tipo antigo porque terminou a função atual */
    global_fun_type = type;
    remove_current_scope(&global);
}

/* Análise semântica de qualquer comando da linguagem */
void semantic_command(Node *cmmd, SymbolTable **scope, Types return_prev)
{
    if (cmmd == NULL || scope == NULL)
        return;

    switch (cmmd->species)
    {
    case NOBLOCO:
    {
        /* Cada bloco novo abre um novo escopo */
        create_new_scope(scope);

        Node *c = cmmd->data.nnary.first;
        while (c)
        {
            semantic_command(c, scope, return_prev);
            c = c->next;
        }

        /* Remove o escopo ao sair do bloco */
        remove_current_scope(scope);
        break;
    }

    case NODECL_VAR:
    {
        /* Variáveis globais já foram tratadas antes, então ignoramos aqui */
        if (*scope == root_gl_scope)
            break;

        Node *declaration = cmmd->data.nnary.first;
        while (declaration)
        {
            if (declaration->species == NOIDENTIFICADOR)
            {
                char *name = declaration->data.leaf.lexeme;
                Types tdeclaration = cmmd->type;

                /* Redeclaração de variável no mesmo escopo não pode */
                if (table_search_name(*scope, name))
                {
                    helper_error_message(declaration->row, "Variavel '%s' foi redeclaracao de variavel no mesmo escopo, corrija seu codigo.", name);
                }
                else
                {
                    SymbolEntry *found = NULL;

                    /* Checa se conflita com nome de parâmetro da função */
                    if ((*scope)->before_scope)
                        found = table_search_above((*scope)->before_scope, name);

                    if (found && found->entry == PARAM_ENTRY)
                        helper_error_message(declaration->row, "Varivel tem o mesmo nome do parametro:'%s' .", name);

                    /* Nome válido → insere a variável no escopo atual */
                    if (found == NULL)
                        insert_variable(*scope, name, helper_convert_type(tdeclaration), 0);
                }
            }
            declaration = declaration->next;
        }
        break;
    }

    case NOATRIBUICAO:
        /* Checa se o tipo da expressão bate com o tipo da variável */
        helper_analyze_atribuition(cmmd, *scope);
        break;

    case NOIF:
        /* A condição do 'se' precisa obrigatoriamente ser int */
        helper_type_is_int(cmmd->data.binary.left, *scope, "Condicao do 'se' deve ser int valida.");
        semantic_command(cmmd->data.ifelse.then_node, scope, return_prev);
        break;

    case NOIF_ELSE:
        /* A condição do 'se então' precisa ser int */
        helper_type_is_int(cmmd->data.binary.left, *scope, "Condicao do 'se então' deve ser int valida.");
        semantic_command(cmmd->data.ifelse.then_node, scope, return_prev);
        semantic_command(cmmd->data.ifelse.else_node, scope, return_prev);
        break;

    case NOWHILE:
        /* Condição do enquanto também precisa ser int */
        helper_type_is_int(cmmd->data.binary.left, *scope, "Condicao do enquanto deve ser int valido.");
        semantic_command(cmmd->data.binary.right, scope, return_prev);
        break;

    case NORETURN:
    {
        /* Verifica se o tipo retornado bate com o tipo da função */
        Node *expression = cmmd->data.unary.n;
        Types type = semantic_expression(expression, *scope);
        if (type != TYVOID && type != return_prev)
            helper_error_message(cmmd->row, "Tipo da expressao retornada é diferente do tipo da funçao.");
        break;
    }

    /* Chamada de função é avaliada como expressão para validar tipos */
    case NOCHAMADA_FUNCAO:
        semantic_expression(cmmd, *scope);
        break;

    case NOWRITE:
        /* write expr → precisa só analisar a expressão que está sendo escrita */
        semantic_expression(cmmd->data.unary.n, *scope);
        break;

    case NOWRITE_LITERAL:
    case NONEWLINE:
        break;

    case NOREAD:
    {
        /* 'leia' só pode receber identificadores válidos (e precisam ser int) */
        Node *id = cmmd->data.unary.n;

        if (!id || id->species != NOIDENTIFICADOR)
        {
            helper_error_message(cmmd->row, "Comando 'leia' com argumento invalido.");
            break;
        }

        /* Variável precisa existir */
        SymbolEntry *s = table_search_above(*scope, id->data.leaf.lexeme);
        if (!s)
        {
            helper_error_message(id->row, "Variavel '%s' nao foi declarationarada.", id->data.leaf.lexeme);
            break;
        }

        /* 'leia' aceita somente variáveis inteiras */
        if (helper_convert_type(s->type) != TYINT)
            helper_error_message(id->row, "Comando 'leia' só aceita variaveis inteiras.");

        break;
    }

    default:
        break;
    }
}

/* Analisa expressões e retorna o tipo que ela produz */
Types semantic_expression(Node *expression, SymbolTable *scope)
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
        /* Identificador precisa existir em algum escopo acima */
        SymbolEntry *symbol = table_search_above(scope, expression->data.leaf.lexeme);
        if (!symbol)
        {
            helper_error_message(expression->row, "Identificador '%s' nao foi declarationaro.", expression->data.leaf.lexeme);
            exit(1);
            return TYVOID;
        }
        return helper_convert_type(symbol->type);
    }

    case NOATRIBUICAO:
        return helper_analyze_atribuition(expression, scope);

    /* Operações aritméticas só funcionam com inteiros */
    case NOSOMA:
    case NOSUBTRACAO:
    case NOMULTIPLICACAO:
    case NODIVISAO:
        return helper_check_binary_int(expression, scope, "Operacao aritmeticas exigem inteiros.");

    /* Operações lógicas também exigem inteiros */
    case NOOR:
    case NOAND:
        return helper_check_binary_int(expression, scope, "Operacao logicas exigem inteiros.");

    /* Operações relacionais exigem que os dois lados tenham o mesmo tipo */
    case NOIGUAL:
    case NODIFERENTE:
    case NOMENOR:
    case NOMENOR_IGUAL:
    case NOMAIOR:
    case NOMAIOR_IGUAL:
        return helper_check_binary_same(expression, scope, "Comparacao entre tipos diferentes.");

    case NOCHAMADA_FUNCAO:
        return semantic_func_call(expression, scope);

    default:
        return TYVOID;
    }
}

/* Valida uma chamada de função: nome, número de argumentos e tipos */
Types semantic_func_call(Node *func, SymbolTable *scope)
{
    Node *first_node = func->data.nnary.first;
    if (!first_node || first_node->species != NOIDENTIFICADOR)
    {
        helper_error_message(func->row, "Chamada de funcao invalida.");
        return TYVOID;
    }

    char *func_name = first_node->data.leaf.lexeme;
    SymbolEntry *symbol = table_search_above(scope, func_name);

    /* A função precisa existir no escopo */
    if (!symbol)
    {
        helper_error_message(func->row, "Funcao '%s' não declarationarada.", func_name);
        return TYVOID;
    }

    /* E o identificador realmente deve ser uma função */
    if (symbol->entry != FUN_ENTRY)
    {
        helper_error_message(func->row, "'%s' nao e uma funcao valida.", func_name);
        return TYVOID;
    }

    Types type = helper_convert_type(symbol->data.fun_data.type);

    /* Conta quantos argumentos reais foram passados */
    Node *args = first_node->next;
    int expected = symbol->data.fun_data.count_params;
    int real = 0;
    Node *p = args;

    while (p)
    {
        real++;
        p = p->next;
    }

    /* Número de parâmetros da função tem que bater com o número passado na chamada */
    if (real != expected)
        helper_error_message(func->row, "Funcao '%s' usa %d argumentos, porem espera %d.", func_name, real, expected);

    /* Cada argumento precisa ter exatamente o mesmo tipo do parâmetro formal */
    DataType *formal = symbol->data.fun_data.param_types;
    p = args;
    int i = 0;

    while (p && i < expected)
    {
        Types arg_type = semantic_expression(p, scope);
        Types real_type = helper_convert_type(formal[i]);

        if (arg_type != real_type)
            helper_error_message(func->row, "Tipo do argumento %d da funcao '%s' e incompativel.", i + 1, func_name);

        i++;
        p = p->next;
    }

    return type;
}
