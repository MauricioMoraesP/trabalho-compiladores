#ifndef STRUCTURE_H
#define STRUCTURE_H

// Dados basicos da linguagem
typedef enum DataType
{
    INT_TYPE = 0, // Tipo inteiro
    CAR_TYPE = 1  // Tipo caractere
} DataType;

// Tipo de entrada na tabela de simbolos
typedef enum EntryType
{
    VAR_ENTRY = 0,  // Variavel
    FUN_ENTRY = 1,  // Funcao
    PARAM_ENTRY = 2 // Parametro
} EntryType;

// Lexema
typedef struct Lexeme
{
    char *lex; // Nome ou valor do lexema
} Lexeme;

// Informacoes sobre parametro ou variavel
typedef struct DataInfo
{
    int scope_level;          // Nivel do escopo em que foi declarado
    int declaration_position; // Ordem de declaracao
} DataInfo;

// Informacoes de dados para simbolos do tipo funcao
typedef struct FunData
{
    int count_params;      // Numero de parametros
    DataType type;         // Tipo de retorno (INT_TYPE ou CAR_TYPE)
    DataType *param_types; // Tipos dos parametros da funcao
} FunData;

// Uniao das diferentes entradas que podem existir na tabela de simbolos
typedef union EntryData
{
    FunData fun_data;  // Usado para simbolos que representam funcoes
    DataInfo var_info; // Usado para simbolos que representam variaveis ou parametros
} EntryData;

// Estrutura que representa um simbolo na tabela de simbolos
typedef struct SymbolEntry
{
    Lexeme lexeme;                     // Lexema do simbolo (nome)
    DataType type;                     // Tipo do simbolo (INT_TYPE ou CAR_TYPE)
    EntryType entry;                   // Tipo de entrada (VAR_ENTRY, FUN_ENTRY, PARAM_ENTRY)
    EntryData data;                    // Informacoes especificas do tipo de entrada
    struct SymbolEntry *next_symbol;   // Ponteiro para o proximo simbolo
    struct SymbolEntry *before_symbol; // Ponteiro para o simbolo anterior
} SymbolEntry;

// Estrutura da tabela de simbolos (cada tabela representa um escopo)
typedef struct SymbolTable
{
    SymbolEntry *entries;             // Ponteiro para todas as entradas de simbolos
    SymbolEntry *first_entry;         // Primeiro simbolo inserido
    SymbolEntry *last_entry;          // Ultimo simbolo inserido
    struct SymbolTable *next_scope;   // Ponteiro para o proximo escopo
    struct SymbolTable *before_scope; // Ponteiro para o escopo anterior
    int level;                        // Nivel do escopo
} SymbolTable;

// Funcoes base para manipulacao da tabela de simbolos
void initialize_symbol_table(SymbolTable **table);
void create_new_scope(SymbolTable **scope);
void remove_current_scope(SymbolTable **scope);
void destroy_symbol_table(SymbolTable *table);
SymbolEntry *table_search_name_in_scope(SymbolTable *scope, char *name);
int insert_symbol(SymbolTable *scope, char *name, EntryType entry_type, DataType data_type, int num_params, DataType *param_types, int declaration_position);
int insert_function(SymbolTable *scope, char *name, DataType type, int num_params, DataType *param_types);
int insert_variable(SymbolTable *scope, char *name, DataType type, int declaration_position);
int insert_parameter(SymbolTable *scope, char *name, DataType type, int position);
void print_symbol_entry(SymbolEntry *entry);
void print_symbol_table(SymbolTable *table);
SymbolEntry *table_search_name_in_CURRENT_scope(SymbolTable *scope, char *name);
SymbolEntry *table_search_upwards(SymbolTable *scope, char *name);
#endif
