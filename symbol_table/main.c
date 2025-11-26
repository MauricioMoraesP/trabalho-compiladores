#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "utils/helpers.h"

int main()
{

    SymbolTable *table;
    initialize_symbol_table(&table);
    table->level = 0;

    insert_variable(table, "x", CAR_TYPE, 1);
    insert_variable(table, "y", INT_TYPE, 2);
    insert_variable(table, "z", CAR_TYPE, 3);

    DataType fun_params1[3] = {CAR_TYPE, INT_TYPE, CAR_TYPE};
    insert_function(table, "concatFunc", CAR_TYPE, 3, fun_params1);

    create_new_scope(&table->next_scope);
    table->next_scope->level = 1;
    insert_variable(table->next_scope, "tempVar", INT_TYPE, 1);

    print_symbol_table(table);

    insert_variable(table, "a", CAR_TYPE, 4);
    insert_variable(table, "b", INT_TYPE, 5);
    insert_variable(table, "c", CAR_TYPE, 6);

    insert_variable(table, "m", INT_TYPE, 7);
    insert_variable(table, "n", INT_TYPE, 8);

    DataType fun_params2[2] = {INT_TYPE, INT_TYPE};
    insert_function(table, "multiplica", INT_TYPE, 2, fun_params2);

    create_new_scope(&table->next_scope);
    table->next_scope->level = 2;
    insert_variable(table->next_scope, "tempMult", INT_TYPE, 1);

    print_symbol_table(table);

    destroy_symbol_table(table);

    return 0;
}
