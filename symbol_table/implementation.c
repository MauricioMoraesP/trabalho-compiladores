#include <stdlib.h>
#include <stdio.h>
#include "header.h"
#include "utils/validations.h"
#include <string.h>

// Initialize TableStack
void initializeSymbolTableStack(SymbolTableStack **stack)
{
    *stack = (SymbolTableStack *)malloc(sizeof(SymbolTableStack));
    verifyStackIsNull(*stack, "Nao foi INICIALIZAR a pilha de escopos.\n");
    (*stack)->top = -1;
    printf("Sucesso: Pilha de tabelas de simbolos INICIALIZADA!\n");
}

// Create a new scope in TableStack
void createNewScope(SymbolTableStack *stack)
{
    verifyStackIsNull(stack, "A pilha de escopo não foi INICIALIZADA, portanto, não é possível CRIAR um novo escopo.\n");
    verifyBurstStack(stack, "Houve um estouro de pilha de ESCOPOS. Nao e possivel CRIAR um novo escopo\n");
    stack->top++;
    stack->tables[stack->top] = (SymbolTable *)malloc(sizeof(SymbolTable));
    if (stack->tables[stack->top] == NULL)
    {
        printf("Erro: Falha na alocação de memória para a tabela de símbolos\n");
        exit(EXIT_FAILURE);
    }
    stack->tables[stack->top]->entries = NULL;
    stack->tables[stack->top]->count = 0;
    printf("Sucesso: Escopo CRIADO.\n");
}

// Search for a symbol by name in the stack (from top scope down)
SymbolEntry *tableSearchName(SymbolTableStack *stack, char *name)
{
    if (verifyStackIsNullSucess(stack, "A tabela de símbolos está VAZIA, logo não tem conteúdo nela."))
        return NULL;

    for (int i = stack->top; i >= 0; i--)
    {
        SymbolTable *currentTable = stack->tables[i];
        if (currentTable == NULL || currentTable->entries == NULL)
            continue;

        for (int j = 0; j < currentTable->count; j++)
        {
            if (strcmp(currentTable->entries[j].lexeme.lex, name) == 0)
            {
                return &currentTable->entries[j];
            }
        }
    }

    return NULL;
}

// Remove the current (top) scope from the stack
void removeCurrentScope(SymbolTableStack *stack)
{
    verifyStackUnderflow(stack, "Não é possível REMOVER um ESCOPO. A pilha já está vazia.\n");
    free(stack->tables[stack->top]);
    stack->tables[stack->top] = NULL;
    stack->top--;
    printf("Sucesso: Escopo REMOVIDO.\n");
}

// Insert a function into the current scope
void insertFunction(SymbolTableStack *stack, char *name, int num_params, DataType return_type, ParameterNode *params_list)
{
    verifyStackUnderflow(stack, "Não há escopo ativo para inserir a função.");

    SymbolTable *currentTable = stack->tables[stack->top];
    ensureSpaceForEntry(currentTable,
                        "Falha ao alocar memória para a primeira FUNÇÃO.",
                        "Falha ao realocar memória para FUNÇÕES.");

    SymbolEntry newEntry;
    strncpy(newEntry.lexeme.lex, name, NAME_IDENTIFIER - 1);
    newEntry.lexeme.lex[NAME_IDENTIFIER - 1] = '\0';

    newEntry.entry = FUN_ENTRY;
    newEntry.type = return_type;

    newEntry.data.fun_data.num_params = num_params;
    newEntry.data.fun_data.return_type = return_type;
    newEntry.data.fun_data.params_list = params_list;
    currentTable->entries[currentTable->count++] = newEntry;

    printf("Função '%s' inserida com sucesso no escopo atual.\n", name);
}

// Insert a variable into the current scope
void insertVariable(SymbolTableStack *stack, char *name, DataType type)
{
    verifyStackUnderflow(stack, "Não há escopo ativo para inserir a VARIÁVEL.");

    SymbolTable *currentTable = stack->tables[stack->top];
    ensureSpaceForEntry(currentTable,
                        "Falha ao alocar memória para a primeira VARIÁVEL.",
                        "Falha ao realocar memória para VARIÁVEIS.");
    SymbolEntry newEntry;
    strncpy(newEntry.lexeme.lex, name, NAME_IDENTIFIER - 1);
    newEntry.lexeme.lex[NAME_IDENTIFIER - 1] = '\0';

    newEntry.entry = VAR_ENTRY;
    newEntry.type = type;
    newEntry.data.var_data.scope_level = stack->top;

    currentTable->entries[currentTable->count] = newEntry;
    currentTable->count++;

    printf("Variável '%s' INSERIDA com sucesso no escopo atual.\n", name);
}

// Insert a parameter into the current scope
void insertParameter(SymbolTableStack *stack, char *name, DataType type)
{
    verifyStackUnderflow(stack, "Não há escopo ativo para inserir o PARÂMETRO.");

    SymbolTable *currentTable = stack->tables[stack->top];
    ensureSpaceForEntry(currentTable,
                        "Falha ao alocar memória para o primeiro PARÂMETRO.",
                        "Falha ao realocar memória para PARÂMETROS.");
    SymbolEntry newEntry;
    strncpy(newEntry.lexeme.lex, name, NAME_IDENTIFIER - 1);
    newEntry.lexeme.lex[NAME_IDENTIFIER - 1] = '\0';

    newEntry.entry = PARAM_ENTRY;
    newEntry.type = type;
    newEntry.data.var_data.scope_level = stack->top;

    currentTable->entries[currentTable->count] = newEntry;
    currentTable->count++;

    printf("Parâmetro '%s' inserido com sucesso no escopo atual.\n", name);
}

// Destroy the entire symbol table stack and free all memory
void destroySymbolTableStack(SymbolTableStack *stack)
{
    if (verifyStackIsNullSucess(stack, "A tabela de símbolos já está VAZIA, logo não tem conteúdo nela."))
        return;

    for (int i = stack->top; i >= 0; i--)
    {
        if (stack->tables[i] != NULL)
        {
            if (stack->tables[i]->entries != NULL)
            {
                for (int j = 0; j < stack->tables[i]->count; j++)
                {
                    SymbolEntry *entry = &stack->tables[i]->entries[j];

                    if (entry->entry == FUN_ENTRY && entry->data.fun_data.params_list != NULL)
                    {
                        ParameterNode *current = entry->data.fun_data.params_list;
                        while (current != NULL)
                        {
                            ParameterNode *next = current->next;
                            free(current);
                            current = next;
                        }

                        entry->data.fun_data.params_list = NULL;
                    }
                }

                free(stack->tables[i]->entries);
                stack->tables[i]->entries = NULL;
            }

            free(stack->tables[i]);
            stack->tables[i] = NULL;
        }
    }

    free(stack);
    printf("Sucesso: Pilha de tabelas de símbolos DESTRUIDA.\n");
}
