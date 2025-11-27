#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utils/helpers.h"

/*
  IMPLEMENTATION.C - tabela de simbolos simplificada (pilha)

  Mudancas principais:
  - Removida a logica de "next_scope" (lista de filhos/irmaos) na criacao de escopos.
    Isso evita tentativas de acessar um escopo ja liberado através desse encadeamento.
  - Mantida a pilha via `before_scope` (ponteiro para o pai).
  - remove_current_scope() atualiza o ponteiro passado (SymbolTable **) ANTES de liberar
    o escopo removido.
  - destroy_symbol_table() foi tornado robusto: procura o topo (se next_scope existir)
    para permanecer compatível com versões antigas; em seguida libera escopos subindo
    pela cadeia before_scope (top -> parent -> ... -> NULL).
  - print_symbol_table: imprime escopos a partir do ESCOP0 for passado. Para imprimir toda
    a pilha chame print_symbol_table(current) (topo).
*/

/* Inicializacao da tabela de simbolos. */
void initialize_symbol_table(SymbolTable **table)
{
    *table = NULL;
    create_new_scope(table); // cria escopo 0 automaticamente
}

/* Criacao de um novo escopo na tabela. Simplificado: usa apenas before_scope. */
void create_new_scope(SymbolTable **scope)
{
    SymbolTable *parent = *scope; /* guarda o pai atual (pode ser NULL) */
    SymbolTable *new_scope = helper_malloc(sizeof(SymbolTable), "criacao de escopo");

    /* Inicializa entradas */
    new_scope->first_entry = NULL;
    new_scope->last_entry = NULL;
    new_scope->entries = NULL;

    /* Encadeamento de pilha: apenas before_scope */
    new_scope->before_scope = parent;

    /* Mantemos o campo next_scope presente (compatibilidade de struct),
       mas NÃO o usamos para encadear filhos. Sempre deixamos NULL.
       Isso evita acessar nós liberados por esse caminho. */
    new_scope->next_scope = NULL;

    if (parent != NULL)
    {
        new_scope->level = parent->level + 1;
        /* OBS: removida a logica que alterava parent->next_scope ou
           percorria filhos. Isso simplifica a estrutura para uma pilha. */
    }
    else
    {
        new_scope->level = 0;
    }

    /* novo topo da pilha de escopos */
    *scope = new_scope;
}

/* Remove o escopo atual. Atualiza o ponteiro passado ANTES de liberar. */
void remove_current_scope(SymbolTable **scope_ptr)
{
    if (scope_ptr == NULL || *scope_ptr == NULL)
    {
        return; // nada a remover
    }

    SymbolTable *scope_to_remove = *scope_ptr;
    SymbolTable *previous_scope = scope_to_remove->before_scope;

    /* Atualiza o ponteiro do chamador para apontar para o escopo anterior
       ANTES de liberar o escopo que será removido. Isso é crítico para evitar
       use-after-free quando outro código tentar usar o ponteiro 'current'. */
    *scope_ptr = previous_scope;

    /* Libera entradas da tabela (SymbolEntry) */
    SymbolEntry *entry = scope_to_remove->first_entry;
    while (entry != NULL)
    {
        SymbolEntry *next = entry->next_symbol;

        if (entry->lexeme.lex)
        {
            free(entry->lexeme.lex);
            entry->lexeme.lex = NULL;
        }

        if (entry->entry == FUN_ENTRY && entry->data.fun_data.param_types)
        {
            free(entry->data.fun_data.param_types);
            entry->data.fun_data.param_types = NULL;
        }

        free(entry);
        entry = next;
    }

    /* Finalmente libera o próprio escopo */
    free(scope_to_remove);
}

/*
  Destroy: libera toda a tabela de simbolos "da pilha".
  Estratégia:
  - Se existir next_scope (por compatibilidade com versões antigas), localiza o
    topo seguindo next_scope até o fim; caso contrário, assume que o ponteiro
    fornecido já é o topo possível.
  - A partir do topo, caminha para cima usando before_scope e vai liberando cada escopo.
*/
void destroy_symbol_table(SymbolTable *table)
{
    if (!table)
        return;

    /* 1) Encontrar o topo (o escopo mais profundo) caso next_scope tenha sido usado */
    SymbolTable *top = table;
    while (top->next_scope)
    {
        top = top->next_scope;
    }

    /* 2) Liberar do topo até o root usando before_scope */
    while (top)
    {
        SymbolEntry *curr = top->first_entry;
        while (curr)
        {
            SymbolEntry *next = curr->next_symbol;
            if (curr->lexeme.lex)
                free(curr->lexeme.lex);

            if (curr->entry == FUN_ENTRY && curr->data.fun_data.param_types)
            {
                free(curr->data.fun_data.param_types);
                curr->data.fun_data.param_types = NULL;
            }

            free(curr);
            curr = next;
        }

        SymbolTable *prev = top->before_scope;
        free(top);
        top = prev;
    }
}

/* Insercao generica de simbolos: verifica duplicata na pilha inteira (comportamento atual) */
int insert_symbol(SymbolTable *scope, char *name, EntryType entry_type, DataType data_type,
                  int num_params, DataType *param_types, int declaration_position)
{
    helper_not_null(scope, "inserir um novo simbolo");

    //
    // ✔️ Correção principal: procurar SÓ no escopo atual
    //
    SymbolEntry *existing_entry = table_search_name_in_CURRENT_scope(scope, name);
    if (existing_entry != NULL)
    {
        // Já existe algo com esse nome NO MESMO ESCOPO
        return -1;
    }

    // Criar nova entrada
    SymbolEntry *new_entry = helper_malloc(sizeof(SymbolEntry), "insercao de simbolo");
    new_entry->lexeme.lex = strdup(name);
    new_entry->type = data_type;
    new_entry->entry = entry_type;
    new_entry->next_symbol = NULL;
    new_entry->before_symbol = scope->last_entry;

    // Inserir na lista de entradas do escopo
    if (!scope->first_entry)
    {
        scope->first_entry = new_entry;
        scope->entries = new_entry;
    }
    else
    {
        scope->last_entry->next_symbol = new_entry;
    }

    scope->last_entry = new_entry;

    // Configuração adicional para funções
    if (entry_type == FUN_ENTRY)
    {
        new_entry->data.fun_data.count_params = num_params;
        new_entry->data.fun_data.type = data_type;
        new_entry->data.fun_data.param_types = param_types;
    }
    else // Variáveis e parâmetros
    {
        new_entry->data.var_info.scope_level = scope->level;
        new_entry->data.var_info.declaration_position = declaration_position;
    }

    return 0;
}

int insert_function(SymbolTable *scope, char *name, DataType type, int num_params, DataType *param_types)
{
    printf(">> INSERINDO '%s' NO ESCOPO %d\n", name, scope->level);
    return insert_symbol(scope, name, FUN_ENTRY, type, num_params, param_types, 0);
}

int insert_variable(SymbolTable *scope, char *name, DataType type, int declaration_position)
{
    printf(">> INSERINDO '%s' NO ESCOPO %d\n", name, scope->level);

    printf("[INSERT VAR] name=%s tipo=%d nivel=%d pos=%d\n",
           name, type, scope->level, declaration_position);
    return insert_symbol(scope, name, VAR_ENTRY, type, 0, NULL, declaration_position);
}

int insert_parameter(SymbolTable *scope, char *name, DataType type, int position)
{
    return insert_symbol(scope, name, PARAM_ENTRY, type, 0, NULL, position);
}

/* Impressao de uma entrada */
void print_symbol_entry(SymbolEntry *entry)
{
    if (entry == NULL)
    {
        printf("Ponteiro nulo!\n");
        return;
    }

    if (entry->entry == VAR_ENTRY || entry->entry == PARAM_ENTRY)
    {
        printf("Tipo de entrada: %s\nLexema: %s\nTipo de dado: %s\nScope lvl: %d \n Posicao: %d\n",
               (entry->entry == VAR_ENTRY) ? "Var" : "Param",
               entry->lexeme.lex,
               entry->type == CAR_TYPE ? "CHAR" : "INT",
               entry->data.var_info.scope_level,
               entry->data.var_info.declaration_position);
    }
    else if (entry->entry == FUN_ENTRY)
    {
        printf("Tipo de entrada: Funcao\nLexema: %s\nTipo de retorno: %s\nNumero de parametros: %d \n Tipos: ",
               entry->lexeme.lex,
               entry->data.fun_data.type == INT_TYPE ? "INT" : "CHAR",
               entry->data.fun_data.count_params);

        for (int i = 0; i < entry->data.fun_data.count_params; i++)
        {
            printf("%s", entry->data.fun_data.param_types[i] == CAR_TYPE ? "CHAR" : "INT");
            if (i < entry->data.fun_data.count_params - 1)
                printf(" | ");
        }
        printf("\n\n");
    }
    else
    {
        printf("Tipo de entrada desconhecido.\n");
        return;
    }
}

/*
  Impressao de todos os simbolos a partir DO ESCOPO passado.
  Observacao: com o modelo de pilha (sem next_scope), para imprimir a pilha inteira
  chame print_symbol_table(current) onde `current` é o topo da pilha.
*/
void print_symbol_table(SymbolTable *table)
{
    helper_not_null(table, "A tabela esta vazia.");

    printf("Inicializacao da impressao da tabela de simbolos.\n");
    printf("Level da tabela de simbolos: %d\n", table->level);

    SymbolEntry *ent = table->first_entry;
    while (ent != NULL)
    {
        print_symbol_entry(ent);
        ent = ent->next_symbol;
    }

    /* Se por acaso next_scope estiver presente (compatibilidade), mostra também.
       Normalmente, com a simplificação, next_scope será NULL. */
    if (table->next_scope)
    {
        print_symbol_table(table->next_scope);
    }
}

SymbolEntry *table_search_name_in_CURRENT_scope(SymbolTable *scope, char *name)
{
    SymbolEntry *entry = scope->first_entry;
    while (entry != NULL)
    {
        if (entry->lexeme.lex && name && strcmp(entry->lexeme.lex, name) == 0)
            return entry;

        entry = entry->next_symbol;
    }
    return NULL;
}