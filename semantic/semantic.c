#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "semantic.h"
#include "../syntax/ast.h"
#include "../symbol_table/structure.h"
#include "utils/helpers.h"
#include "../syntax/utils/dictionary/dictionary.h"

// Variaveis auxiliadoras
// Depois de codar a metade do semântico percebi que não ia dar certo se eu não salvasse essas referências em variáveis auxiliadoras.
static Types aux_current_type = TYVOID;      // guarda o tipo de retorno que a função atual deve produzir
static SymbolTable *aux_global_scope = NULL; // referência do escopo global para distinguir vars globais e locais

// O semântico foi feito de forma simples, em uma única função recursiva.
Types analyze_semantic_program(Node *ast, SymbolTable **scope, Types expected_return)
{
    if (!ast)
        return TYVOID;

    switch (ast->species)
    {
    case NOCAR_CONST: // retorna o tipo caractere para constantes de caractere
        return TYCAR;

    case NOWRITE: // comando 'escreva' apenas avalia a expressão e não retorna tipo relevante
        analyze_semantic_program(ast->data.unary.n, scope, expected_return);
        return TYVOID;

    case NOAND:
    case NOOR: // operadores lógicos aceitam apenas inteiros (0 ou 1)
        return helper_check_binary_int(ast, *scope, "Operacoes logicas exigem inteiros.");

    case NODECL_VAR: // declaração de variável insere no escopo correto (global/local)
        if (*scope == aux_global_scope)
            helper_insert_global_variables(ast, scope);
        else
            helper_insert_local_variables(ast, scope);
        return TYVOID;

    case NOIF: // condição 'se' deve ser inteiro
        helper_type_is_int(ast->data.binary.left, *scope, "Condicao do IF deve ser inteira.");
        analyze_semantic_program(ast->data.ifelse.then_node, scope, expected_return);
        return TYVOID;

    case NOMULTIPLICACAO:
    case NODIVISAO:
    case NOSOMA:
    case NOSUBTRACAO: // operações aritméticas exigem dois operandos inteiros
        return helper_check_binary_int(ast, *scope, "Operacoes aritmeticas exigem inteiros.");

    case NOMAIOR:
    case NOMENOR:
    case NOMAIOR_IGUAL:
    case NOMENOR_IGUAL:
    case NOIGUAL:
    case NODIFERENTE: // comparações exigem tipos equivalentes nos dois lados
        return helper_check_binary_same(ast, *scope, "Comparacao entre tipos diferentes.");

    case NOINT_CONST: // constante inteira retorna tipo int
        return TYINT;

    case NOREAD: // comando 'leia' exige que o destino seja variável válida
    {
        Node *id = ast->data.unary.n;

        if (!id || id->species != NOIDENTIFICADOR)
        {
            helper_error_message(ast->row, "Comando 'leia' espera identificador.");
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

    case NOWHILE: // condição do 'enquanto' precisa ser inteiro valido
        helper_type_is_int(ast->data.binary.left, *scope, "Condicao do WHILE deve ser inteira.");
        analyze_semantic_program(ast->data.binary.right, scope, expected_return);
        return TYVOID;

    case NOIDENTIFICADOR: // uso de variável consultando a tabela de símbolos
    {
        SymbolEntry *s = table_search_above(*scope, ast->data.leaf.lexeme);

        if (!s)
        {
            helper_error_message(ast->row, "Identificador '%s' nao declarado.", ast->data.leaf.lexeme);
            exit(1);
            return TYVOID;
        }

        return helper_convert_type(s->type);
    }

    case NORETURN: // 'return' verifica compatibilidade com o tipo da função
    {
        Node *exp = ast->data.unary.n;
        Types t = analyze_semantic_program(exp, scope, expected_return);

        if (t != TYVOID && t != expected_return)
            helper_error_message(ast->row, "Tipo retornado nao corresponde ao tipo da funcao.");

        return t;
    }

    case NOATRIBUICAO: // atribuição precisa analisar o tipo da variável com o da expressão
        return helper_analyze_atribuition(ast, *scope);

    case NOBLOCO: // analise do bloco e do seu escopo.
        create_new_scope(scope);
        for (Node *c = ast->data.nnary.first; c; c = c->next)
            analyze_semantic_program(c, scope, expected_return);
        remove_current_scope(scope);
        return TYVOID;

    case NOIF_ELSE: // 'se' com 'então' exige condição int e analisa dois blocos
        helper_type_is_int(ast->data.binary.left, *scope, "Condicao do IF-ELSE deve ser inteira.");
        analyze_semantic_program(ast->data.ifelse.then_node, scope, expected_return);
        analyze_semantic_program(ast->data.ifelse.else_node, scope, expected_return);
        return TYVOID;

    case NOCHAMADA_FUNCAO: // validação de existência da função, tipos e contagem de argumentos
    {
        Node *name = ast->data.nnary.first;

        if (!name || name->species != NOIDENTIFICADOR)
        {
            helper_error_message(ast->row, "Chamada de funcao mal formada.");
            return TYVOID;
        }

        char *lex = name->data.leaf.lexeme;
        SymbolEntry *search_above = table_search_above(*scope, lex);

        if (!search_above)
        {
            helper_error_message(ast->row, "Funcao '%s' nao existe.", lex);
            return TYVOID;
        }

        if (search_above->entry != FUN_ENTRY)
        {
            helper_error_message(ast->row, "'%s' nao e funcao.", lex);
            return TYVOID;
        }

        Types ret = helper_convert_type(search_above->data.fun_data.type);

        Node *arg = name->next;
        int count_real = 0;
        for (Node *a = arg; a; a = a->next)
            count_real++;

        if (count_real != search_above->data.fun_data.count_params)
            helper_error_message(ast->row, "Funcao '%s' recebeu %d argumentos, esperava %d argumentos.", lex, count_real, search_above->data.fun_data.count_params);

        DataType *formal = search_above->data.fun_data.param_types;

        int i = 0;
        for (Node *p = arg; p && i < search_above->data.fun_data.count_params; p = p->next, i++)
        {
            Types got = analyze_semantic_program(p, scope, expected_return);
            Types want = helper_convert_type(formal[i]);

            if (got != want)
                helper_error_message(ast->row, "Tipo do argumento %d invalido em '%s'.", i + 1, lex);
        }

        return ret;
    }

    case NODECL_FUNCAO: // declaração de função, inseração de parametros e analise do corpo e sua semâtica
    {
        Types before_type = aux_current_type;
        aux_current_type = ast->type;

        create_new_scope(scope);
        SymbolTable *local = *scope;

        Node *params = ast->data.nnary.first->next;
        Node *others = params ? params->next : NULL;

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

        if (others)
            analyze_semantic_program(others, &local, aux_current_type);

        aux_current_type = before_type;
        remove_current_scope(scope);
        return TYVOID;
    }

    case NOPROGRAMA: // nó raiz
        aux_global_scope = *scope;
        for (Node *n = ast->data.unary.n; n; n = n->next)
            analyze_semantic_program(n, scope, TYVOID);
        return TYVOID;

    default:
        return TYVOID;
    }
}
