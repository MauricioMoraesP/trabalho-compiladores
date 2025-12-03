#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utils/helpers.h"

/* Inicializa a tabela criando o escopo global */
void initialize_symbol_table(SymbolTable **table)
{
    *table = NULL;
    create_new_scope(table);
}

/* Cria um novo escopo e o empilha sobre o atual */
void create_new_scope(SymbolTable **scope)
{

    SymbolTable *parent = *scope;
    SymbolTable *new_scope = helper_malloc(sizeof(SymbolTable), "criacao de escopo");
    new_scope->first_entry = NULL;
    new_scope->last_entry = NULL;
    new_scope->entries = NULL;
    new_scope->before_scope = parent;

    if (parent != NULL)
        new_scope->level = parent->level + 1;
    else
        new_scope->level = 0;

    *scope = new_scope;
}

/* Remove o escopo atual e libera seus símbolos */
void remove_current_scope(SymbolTable **scope)
{

    if (scope == NULL || *scope == NULL)
        return;

    SymbolTable *scope_to_remove = *scope;
    SymbolTable *previous_scope = scope_to_remove->before_scope;
    *scope = previous_scope;

    SymbolEntry *entry = scope_to_remove->first_entry;
    free_scope_entries(scope_to_remove->first_entry);
    free(scope_to_remove);
}

/* Destroi toda a tabela, liberando todos os escopos e símbolos */
void destroy_symbol_table(SymbolTable *table)
{
    if (table == NULL)
        return;

    SymbolTable *top = table;

    while (top)
    {
        SymbolTable *prev = top->before_scope;
        free_scope_entries(top->first_entry);
        free(top);
        top = prev;
    }
}

/* Inserção genérica de símbolo no escopo corrente */
int insert_symbol(SymbolTable *scope, char *name, EntryType entry_type, DataType data_type, int num_params, DataType *param_types, int declaration_position)
{
    helper_not_null(scope, "inserir um novo simbolo");

    SymbolEntry *entry = table_search_name_in_scope(scope, name);
    if (entry != NULL)
    {
        return -1;
    }

    SymbolEntry *new_entry = helper_malloc(sizeof(SymbolEntry), "insercao de simbolo");
    new_entry->lexeme.lex = strdup(name);
    new_entry->type = data_type;
    new_entry->entry = entry_type;
    new_entry->next_symbol = NULL;
    new_entry->before_symbol = scope->last_entry;

    if (entry_type == FUN_ENTRY)
    {
        new_entry->data.fun_data.count_params = num_params;
        new_entry->data.fun_data.param_types = param_types;
        new_entry->data.fun_data.type = data_type;
    }
    else if (entry_type == VAR_ENTRY || entry_type == PARAM_ENTRY)
    {
        new_entry->data.var_info.scope_level = scope->level;
        new_entry->data.var_info.declaration_position = declaration_position;
    }

    if (scope->first_entry == NULL)
    {
        scope->first_entry = new_entry;
        scope->entries = new_entry;
    }
    else
        scope->last_entry->next_symbol = new_entry;

    scope->last_entry = new_entry;
    return 0;
}

/* Insere função */
int insert_function(SymbolTable *scope, char *name, DataType type, int num_params, DataType *param_types)
{
    return insert_symbol(scope, name, FUN_ENTRY, type, num_params, param_types, 0);
}

/* Insere variável */
int insert_variable(SymbolTable *scope, char *name, DataType type, int declaration_position)
{

    return insert_symbol(scope, name, VAR_ENTRY, type, 0, NULL, declaration_position);
}

/* Insere parâmetro */
int insert_parameter(SymbolTable *scope, char *name, DataType type, int position)
{
    return insert_symbol(scope, name, PARAM_ENTRY, type, 0, NULL, position);
}

/* Busca símbolo apenas no escopo atual */
SymbolEntry *table_search_name_in_scope(SymbolTable *scope, char *name)
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

/* Busca símbolo subindo a pilha de escopos */
SymbolEntry *table_search_up(SymbolTable *scope, char *name)
{
    SymbolTable *currentent = scope;
    while (currentent != NULL)
    {
        SymbolEntry *found = table_search_name_in_scope(currentent, name);
        if (found)
            return found;
        currentent = currentent->before_scope;
    }
    return NULL;
}
