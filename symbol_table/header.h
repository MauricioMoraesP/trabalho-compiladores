#ifndef HEADER_H
#define HEADER_H

#define SCOPE 200
#define NAME_IDENTIFIER 25
/*
Data types in Goianinha
*/
typedef enum DataType
{
    INT_TYPE = 0,
    CAR_TYPE = 1
} DataType;

// Possibles entrys in Goianinha
typedef enum EntryType
{
    VAR_ENTRY = 0,
    FUN_ENTRY = 1,
    PARAM_ENTRY = 2,
} EntryType;

// Escope position
typedef struct
{
    int scope_level;
    int declaration_position;
} VarData;

// Parameter Node in function
typedef struct ParameterNode
{
    DataType type;
    char name[NAME_IDENTIFIER];
    int declaration_position;
    struct ParameterNode *next;
} ParameterNode;

// Function-specific data
typedef struct FunData
{
    int num_params;
    DataType return_type;
    ParameterNode *params_list;
} FunData;

// A union para lidar com dados específicos de cada tipo de entrada
typedef union EntryData
{
    FunData fun_data;
    VarData var_data;
    DataType *params_types;
} EntryData;

// Identifier
typedef struct Lexeme
{
    char lex[NAME_IDENTIFIER];
} Lexeme;

typedef struct SymbolEntry
{
    Lexeme lexeme;   // Identifier
    DataType type;   // Type for identifier
    EntryType entry; // Entry for identifier
    EntryData data;  // A union for specific data
} SymbolEntry;

// A single scope or symbol table, count is used to count the number of symbols
typedef struct SymbolTable
{
    SymbolEntry *entries;
    int count;
} SymbolTable;

// A stack of symbol tables
typedef struct SymbolTableStack
{
    SymbolTable *tables[SCOPE];
    int top;
} SymbolTableStack;

// Protytpes Functions Symbol Table
void initializeSymbolTableStack(SymbolTableStack **stack);
void createNewScope(SymbolTableStack *stack);
SymbolEntry *tableSearchName(SymbolTableStack *stack, char *name);
void removeCurrentScope(SymbolTableStack *stack);
void insertFunction(SymbolTableStack *stack, char *name, int num_params, DataType return_type, ParameterNode *params_list);
void insertVariable(SymbolTableStack *stack, char *name, DataType type);
void insertParameter(SymbolTableStack *stack, char *name, DataType type);
void destroySymbolTableStack(SymbolTableStack *stack);

#endif