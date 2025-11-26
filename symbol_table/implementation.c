#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utils/helpers.h"

// Inicializacao da tabela de simbolos.
void initialize_symbol_table(SymbolTable **table)
{
    *table = helper_malloc(sizeof(SymbolTable), "inicializacao da tabela de simbolos");
    (*table)->entries = NULL;
    (*table)->first_entry = NULL;
    (*table)->last_entry = NULL;
    (*table)->next_scope = NULL;
    (*table)->before_scope = NULL;
    (*table)->level = 0;
}
// Criacao de um novo escopo na tabela.
void create_new_scope(SymbolTable **scope)
{
    SymbolTable *new_scope = helper_malloc(sizeof(SymbolTable), "criacao de escopo");
    new_scope->entries = NULL;
    new_scope->first_entry = NULL;
    new_scope->last_entry = NULL;
    new_scope->before_scope = *scope;
    new_scope->level = (*scope) ? ((*scope)->level + 1) : 0;
    new_scope->next_scope = NULL;
    if (*scope)
        (*scope)->next_scope = new_scope;
    *scope = new_scope;
}

// Remove o escopo atual.
void remove_current_scope(SymbolTable **scope)
{
    helper_not_null(scope, "remover o escopo atual.");
    SymbolTable *current = *scope;
    SymbolEntry *entry = current->last_entry;

    *scope = current->before_scope;
    if (*scope != NULL)
        (*scope)->next_scope = NULL;

    while (entry != NULL)
    {
        SymbolEntry *prev = entry->before_symbol;
        if (entry->lexeme.lex)
            free(entry->lexeme.lex);

        if (entry->entry == FUN_ENTRY && entry->data.fun_data.param_types)
        {
            free(entry->data.fun_data.param_types);
            entry->data.fun_data.param_types = NULL;
        }

        free(entry);
        entry = prev;
    }
    free(current);
}

void destroy_symbol_table(SymbolTable *table)
{
    if (!table)
        return;

    destroy_symbol_table(table->next_scope);

    SymbolEntry *curr = table->first_entry;
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

    free(table);
}

// Procura um lexema no escopo.
SymbolEntry *table_search_name_in_scope(SymbolTable *scope, char *name)
{
    SymbolTable *current = scope;
    while (current != NULL)
    {
        SymbolEntry *entry = current->first_entry;
        while (entry != NULL)
        {
            if (entry->lexeme.lex && name && strcmp(entry->lexeme.lex, name) == 0)
                return entry;

            entry = entry->next_symbol;
        }
        current = current->before_scope;
    }
    return NULL;
}

// Funcao generica para insercao de simbolos.
void insert_symbol(SymbolTable *scope, char *name, EntryType entry_type, DataType data_type, int num_params, DataType *param_types, int declaration_position)
{
    helper_not_null(scope, "inserir um novo simbolo");

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

    if (entry_type == FUN_ENTRY)
    {
        new_entry->data.fun_data.count_params = num_params;
        new_entry->data.fun_data.type = data_type;
        new_entry->data.fun_data.param_types = param_types;
    }
    else
    {
        new_entry->data.var_info.scope_level = scope->level;
        new_entry->data.var_info.declaration_position = declaration_position;
    }
}

void insert_function(SymbolTable *scope, char *name, DataType type, int num_params, DataType *param_types)
{
    insert_symbol(scope, name, FUN_ENTRY, type, num_params, param_types, 0);
}

void insert_variable(SymbolTable *scope, char *name, DataType type, int declaration_position)
{
    insert_symbol(scope, name, VAR_ENTRY, type, 0, NULL, declaration_position);
}

void insert_parameter(SymbolTable *scope, char *name, DataType type, int position)
{
    insert_symbol(scope, name, PARAM_ENTRY, type, 0, NULL, position);
}
// Impressao dos simbolos por escopo.
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
    else if (entry->entry != VAR_ENTRY && entry->entry != PARAM_ENTRY && entry->entry != FUN_ENTRY)
    {
        printf("Tipo de entrada desconhecido.\n");
        return;
    }
}
// Impressao de todos os simbolos
void print_symbol_table(SymbolTable *table)
{
    helper_not_null(table, "A tabela esta vazia.");

    printf("Inicializacao da impressao da tabela de simbolos.\n");
    printf("Level da tabela de simbolos e de : %d\n", table->level);

    SymbolEntry *current = table->first_entry;
    while (current != NULL)
    {
        print_symbol_entry(current);
        current = current->next_symbol;
    }
    if (table->next_scope)
    {
        print_symbol_table(table->next_scope);
    }
}
