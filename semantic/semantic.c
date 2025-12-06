#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "semantic.h"
#include "../syntax/ast.h"
#include "../symbol_table/structure.h"
#include "utils/helpers.h"
#include "../syntax/utils/dictionary/dictionary.h"

static Types current_return_type = TYVOID;   // guarda o tipo de retorno que a função atual deve produzir
static SymbolTable *global_scope_ref = NULL; // referência do escopo global para distinguir vars globais e locais

Types analyze_semantic_program(Node *node, SymbolTable **scope, Types expected_return)
{
    if (!node)
        return TYVOID;

    switch (node->species)
    {
    case NOCAR_CONST: // retorna o tipo caractere para constantes de caractere
        return TYCAR;

    case NOWRITE: // comando write apenas avalia a expressão e não retorna tipo relevante
        analyze_semantic_program(node->data.unary.n, scope, expected_return);
        return TYVOID;

    case NOAND:
    case NOOR: // operadores lógicos aceitam apenas inteiros (0 ou 1)
        return helper_check_binary_int(node, *scope, "Operacoes logicas exigem inteiros.");

    case NODECL_VAR: // declaração de variável insere no escopo correto (global/local)
        if (*scope == global_scope_ref)
            helper_insert_global_variables(node, scope);
        else
            helper_insert_local_variables(node, scope);
        return TYVOID;

    case NOIF: // condição do IF precisa ser inteira e depois analisa o bloco then
        helper_type_is_int(node->data.binary.left, *scope, "Condicao do IF deve ser inteira.");
        analyze_semantic_program(node->data.ifelse.then_node, scope, expected_return);
        return TYVOID;

    case NOMULTIPLICACAO:
    case NODIVISAO:
    case NOSOMA:
    case NOSUBTRACAO: // operações aritméticas exigem dois operandos inteiros
        return helper_check_binary_int(node, *scope, "Operacoes aritmeticas exigem inteiros.");

    case NOMAIOR:
    case NOMENOR:
    case NOMAIOR_IGUAL:
    case NOMENOR_IGUAL:
    case NOIGUAL:
    case NODIFERENTE: // comparações exigem tipos equivalentes nos dois lados
        return helper_check_binary_same(node, *scope, "Comparacao entre tipos diferentes.");

    case NOINT_CONST: // constante inteira retorna tipo int
        return TYINT;

    case NOREAD: // comando read exige que o destino seja variável int válida
    {
        Node *id = node->data.unary.n;

        if (!id || id->species != NOIDENTIFICADOR)
        {
            helper_error_message(node->row, "Comando 'leia' espera identificador.");
            return TYVOID;
        }

        SymbolEntry *s = table_search_above(*scope, id->data.leaf.lexeme);

        if (!s)
        {
            helper_error_message(id->row, "Variavel '%s' nao foi declarada.", id->data.leaf.lexeme);
            return TYVOID;
        }

        if (helper_convert_type(s->type) != TYINT)
            helper_error_message(id->row, "'leia' aceita apenas inteiros.");

        return TYINT;
    }

    case NOWHILE: // condição do WHILE precisa ser inteira e depois analisa corpo
        helper_type_is_int(node->data.binary.left, *scope, "Condicao do WHILE deve ser inteira.");
        analyze_semantic_program(node->data.binary.right, scope, expected_return);
        return TYVOID;

    case NOIDENTIFICADOR: // uso de variável consulta tabela de símbolos
    {
        SymbolEntry *s = table_search_above(*scope, node->data.leaf.lexeme);

        if (!s)
        {
            helper_error_message(node->row, "Identificador '%s' nao declarado.", node->data.leaf.lexeme);
            exit(1);
            return TYVOID;
        }

        return helper_convert_type(s->type);
    }

    case NORETURN: // return verifica compatibilidade com o tipo da função
    {
        Node *exp = node->data.unary.n;
        Types t = analyze_semantic_program(exp, scope, expected_return);

        if (t != TYVOID && t != expected_return)
            helper_error_message(node->row, "Tipo retornado nao corresponde ao tipo da funcao.");

        return t;
    }

    case NOATRIBUICAO: // atribuição precisa compatibilizar o tipo da variável com o da expressão
        return helper_analyze_atribuition(node, *scope);

    case NOBLOCO: // bloco abre novo escopo e analisa comandos internos
        create_new_scope(scope);
        for (Node *c = node->data.nnary.first; c; c = c->next)
            analyze_semantic_program(c, scope, expected_return);
        remove_current_scope(scope);
        return TYVOID;

    case NOIF_ELSE: // if-else exige cond int e analisa dois blocos
        helper_type_is_int(node->data.binary.left, *scope, "Condicao do IF-ELSE deve ser inteira.");
        analyze_semantic_program(node->data.ifelse.then_node, scope, expected_return);
        analyze_semantic_program(node->data.ifelse.else_node, scope, expected_return);
        return TYVOID;

    case NOCHAMADA_FUNCAO: // chamada de função valida existência, tipos e contagem de args
    {
        Node *name = node->data.nnary.first;

        if (!name || name->species != NOIDENTIFICADOR)
        {
            helper_error_message(node->row, "Chamada de funcao mal formada.");
            return TYVOID;
        }

        char *lex = name->data.leaf.lexeme;
        SymbolEntry *s = table_search_above(*scope, lex);

        if (!s)
        {
            helper_error_message(node->row, "Funcao '%s' nao existe.", lex);
            return TYVOID;
        }

        if (s->entry != FUN_ENTRY)
        {
            helper_error_message(node->row, "'%s' nao e funcao.", lex);
            return TYVOID;
        }

        Types ret = helper_convert_type(s->data.fun_data.type);

        Node *arg = name->next;
        int count_real = 0;
        for (Node *x = arg; x; x = x->next)
            count_real++;

        if (count_real != s->data.fun_data.count_params)
            helper_error_message(node->row, "Funcao '%s' recebeu %d argumentos, esperava %d.",
                                 lex, count_real, s->data.fun_data.count_params);

        DataType *formal = s->data.fun_data.param_types;

        int i = 0;
        for (Node *p = arg; p && i < s->data.fun_data.count_params; p = p->next, i++)
        {
            Types got = analyze_semantic_program(p, scope, expected_return);
            Types want = helper_convert_type(formal[i]);

            if (got != want)
                helper_error_message(node->row,
                                     "Tipo do argumento %d invalido em '%s'.", i + 1, lex);
        }

        return ret;
    }

    case NODECL_FUNCAO: // declaração de função cria escopo, insere params e analisa corpo
    {
        Types old = current_return_type;
        current_return_type = node->type;

        create_new_scope(scope);
        SymbolTable *local = *scope;

        Node *params = node->data.nnary.first->next;
        Node *body = params ? params->next : NULL;

        int pos = 0;
        if (params && (params->species == NOLISTA_DECL || params->species == NOLISTA_PARAMS))
        {
            for (Node *p = params->data.nnary.first; p; p = p->next)
            {
                if (p->species != NOIDENTIFICADOR)
                    continue;

                char *name = p->data.leaf.lexeme;
                Types t = p->type;

                if (table_search_name(local, name))
                    helper_error_message(p->row, "Parametro '%s' duplicado.", name);
                else
                    insert_parameter(local, name, helper_convert_type(t), pos++);
            }
        }

        if (body)
            analyze_semantic_program(body, &local, current_return_type);

        current_return_type = old;
        remove_current_scope(scope);
        return TYVOID;
    }

    case NOPROGRAMA: // programa raiz inicializa escopo global e analisa declarações do topo
        global_scope_ref = *scope;
        for (Node *n = node->data.unary.n; n; n = n->next)
            analyze_semantic_program(n, scope, TYVOID);
        return TYVOID;

    default: // qualquer caso não tratado explicitamente retorna vazio
        return TYVOID;
    }
}
