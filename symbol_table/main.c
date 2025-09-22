#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Helper function to print a symbol table entry
void printSymbolEntry(SymbolEntry *entry)
{
    if (entry == NULL)
    {
        printf("Entrada nula\n");
        return;
    }

    printf("  Lexema: %s\n", entry->lexeme.lex);
    printf("  Tipo: %s\n", entry->type == INT_TYPE ? "int" : "car");
    printf("  Entrada: ");
    switch (entry->entry)
    {
    case VAR_ENTRY:
        printf("Variável\n");
        printf("  Nível de escopo: %d\n", entry->data.var_data.scope_level);
        printf("  Posição de declaração: %d\n", entry->data.var_data.declaration_position);
        break;
    case FUN_ENTRY:
        printf("Função\n");
        printf("  Número de parâmetros: %d\n", entry->data.fun_data.num_params);
        printf("  Tipo de retorno: %s\n", entry->data.fun_data.return_type == INT_TYPE ? "int" : "car");
        break;
    case PARAM_ENTRY:
        printf("Parâmetro\n");
        printf("  Nível de escopo: %d\n", entry->data.var_data.scope_level);
        printf("  Posição de declaração: %d\n", entry->data.var_data.declaration_position);
        break;
    default:
        printf("Desconhecido\n");
    }
    printf("------------------------\n");
}

int main()
{
    SymbolTableStack *stack = NULL;
    SymbolEntry *foundEntry;

    // Initialize the stack
    printf("--- Teste 1: Inicialização da Pilha ---\n");
    initializeSymbolTableStack(&stack);
    printf("\n");

    // Create a new scope
    printf("--- Teste 2: Criação de Escopo Global ---\n");
    createNewScope(stack);
    printf("\n");

    // Insert variables into the global scope
    printf("--- Teste 3: Inserção de Variáveis ---\n");
    insertVariable(stack, "global_var_a", INT_TYPE);
    insertVariable(stack, "global_var_b", CAR_TYPE);
    printf("\n");

    // Insert a function
    printf("--- Teste 4: Inserção de Função e Parâmetros ---\n");
    ParameterNode *param1 = (ParameterNode *)malloc(sizeof(ParameterNode));
    param1->type = INT_TYPE;
    strcpy(param1->name, "p_a");
    param1->next = NULL;

    insertFunction(stack, "minha_funcao", 1, INT_TYPE, param1);
    printf("\n");

    // Create a new scope for the function
    printf("--- Teste 5: Criação de Escopo para a Função ---\n");
    createNewScope(stack);
    insertParameter(stack, "p_a", INT_TYPE);
    insertVariable(stack, "local_var_x", INT_TYPE);
    printf("\n");

    // Search by identifiers
    printf("--- Teste 6: Pesquisa de Identificadores ---\n");
    printf("Pesquisando por 'local_var_x' (deve ser encontrado no escopo atual):\n");
    foundEntry = tableSearchName(stack, "local_var_x");
    printSymbolEntry(foundEntry);

    printf("Pesquisando por 'global_var_a' (deve ser encontrado em um escopo externo):\n");
    foundEntry = tableSearchName(stack, "global_var_a");
    printSymbolEntry(foundEntry);

    printf("Pesquisando por 'p_a' (deve ser encontrado no escopo atual):\n");
    foundEntry = tableSearchName(stack, "p_a");
    printSymbolEntry(foundEntry);

    printf("Pesquisando por 'variavel_nao_existente' (deve ser nulo):\n");
    foundEntry = tableSearchName(stack, "variavel_nao_existente");
    printSymbolEntry(foundEntry);
    printf("\n");

    // Remove the current scope
    printf("--- Teste 7: Remoção do Escopo Atual ---\n");
    removeCurrentScope(stack);
    printf("\n");

    // Search again for 'local_var_x' (it should no longer be found)
    printf("--- Teste 8: Verificação após a Remoção do Escopo ---\n");
    printf("Pesquisando por 'local_var_x' (agora deve ser nulo):\n");
    foundEntry = tableSearchName(stack, "local_var_x");
    printSymbolEntry(foundEntry);
    printf("\n");

    // Destroy the stack
    printf("--- Teste 9: Destruição da Pilha ---\n");
    destroySymbolTableStack(stack);
    printf("\n");

    return 0;
}