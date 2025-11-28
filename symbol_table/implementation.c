#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utils/helpers.h"

void initialize_symbol_table(SymbolTable **table)
{
    *table = NULL;
    create_new_scope(table);
}

void create_new_scope(SymbolTable **scope)
{

    SymbolTable *parent = *scope;
    SymbolTable *new_scope = helper_malloc(sizeof(SymbolTable), "criacao de escopo");
    new_scope->first_entry = NULL;
    new_scope->last_entry = NULL;
    new_scope->entries = NULL;
    new_scope->before_scope = parent;
    new_scope->next_scope = NULL;

    if (parent != NULL)
    {
        new_scope->level = parent->level + 1;
    }
    else
    {
        new_scope->level = 0;
    }

    *scope = new_scope;
}

void remove_current_scope(SymbolTable **scope_ptr)
{

    if (scope_ptr == NULL || *scope_ptr == NULL)
        return;

    SymbolTable *scope_to_remove = *scope_ptr;
    SymbolTable *previous_scope = scope_to_remove->before_scope;
    *scope_ptr = previous_scope;

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

    free(scope_to_remove);
}

void destroy_symbol_table(SymbolTable *table)
{
    if (!table)
        return;

    SymbolTable *top = table;
    while (top->next_scope)
    {
        top = top->next_scope;
    }

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

    SymbolEntry *existing_entry = table_search_name_in_CURRENT_scope(scope, name);
    if (existing_entry != NULL)
    {

        return -1;
    }

    SymbolEntry *new_entry = helper_malloc(sizeof(SymbolEntry), "insercao de simbolo");
    new_entry->lexeme.lex = strdup(name);
    new_entry->type = data_type;
    new_entry->entry = entry_type;
    new_entry->next_symbol = NULL;
    new_entry->before_symbol = scope->last_entry;

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
    return 0;
}

int insert_function(SymbolTable *scope, char *name, DataType type, int num_params, DataType *param_types)
{
    return insert_symbol(scope, name, FUN_ENTRY, type, num_params, param_types, 0);
}

int insert_variable(SymbolTable *scope, char *name, DataType type, int declaration_position)
{

    return insert_symbol(scope, name, VAR_ENTRY, type, 0, NULL, declaration_position);
}

int insert_parameter(SymbolTable *scope, char *name, DataType type, int position)
{
    return insert_symbol(scope, name, PARAM_ENTRY, type, 0, NULL, position);
}

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

SymbolEntry *table_search_upwards(SymbolTable *scope, char *name)
{
    SymbolTable *curr = scope;
    while (curr != NULL)
    {
        SymbolEntry *found = table_search_name_in_CURRENT_scope(curr, name);
        if (found)
            return found;
        curr = curr->before_scope;
    }
    return NULL;
}
