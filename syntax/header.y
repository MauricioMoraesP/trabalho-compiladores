%{
#include "types.h"
#include "ast.h"
#include "syntax/header.tab.h"
#include "../semantic/semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Flex global functions and variables
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
extern int yydebug;

// Lexical analyzer function declaration
int yylex();

// Error handling function declaration
void yyerror(const char *s);
Node* root = NULL;
int lex_error = 0;
SymbolTable *global=NULL;
SymbolTable *current=NULL;
int declaration_position = 0;
int sem_error = 0;
%}

%union {
    int ival;
    char cval;
    char *str;
    Node *n;
    Types type;
}

%type <n> Bloco ListaDeclVar ListaComando Comando Expr OrExpr AndExpr EqExpr DesignExpr
%type <n> Programa DeclFuncVar DeclProg DeclVar DeclFunc ListaParametros ListaParametrosCont
%type <n> AddExpr MulExpr UnExpr PrimExpr ListExpr 
%type <type> Tipo

%token <str> TID_TOKEN TSTRING_LITERAL
%token <ival> TINT_CONST
%token <cval> TCHAR_CONST

%token TPROGRAM TCAR TINT TRETURN TREAD TWRITE TNEWLINE TIF TTHEN TELSE TWHILE TEXECUTE TAND
%token TPLUS TMINUS TTIMES TDIVIDE TASSIGN TEQ TNEQ TLT TLEQ TGT TGEQ TSEMICOLON TLPAREN TRPAREN TLBRACE TRBRACE TLBRACKET TRBRACKET TCOMMA TOR TNEG

%nonassoc TTHEN
%nonassoc TELSE
%nonassoc TNEG
%left TTIMES TDIVIDE
%left TPLUS TMINUS
%nonassoc TLT TLEQ TGT TGEQ
%left TEQ TNEQ
%left TAND
%left TOR
%right TASSIGN
%left TCOMMA

%start Programa

%%

Programa:
    DeclFuncVar DeclProg {
        Node *program = create_nnary_node(NOPROGRAMA, yylineno, TYVOID);
        nnary_merge_children(program, $1);
        if ($2)
            nnary_add_child(program, $2);
        $$ = program;
        root = program;
    }
;

DeclFuncVar:
    Tipo TID_TOKEN DeclVar TSEMICOLON DeclFuncVar {
        Node *decl = create_nnary_node(NODECL_VAR, yylineno, $1);
        Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, $1, $2, 0, 0);
        nnary_add_child(decl, id);
        insert_variable(current, $2, $1, declaration_position);
        nnary_merge_children(decl, $3);
        Node *list = ($5 ? $5 : create_nnary_node(NOLISTA_DECL, yylineno, TYVOID));
        nnary_add_child(list, decl);
        $$ = list;
    }
       | Tipo TID_TOKEN DeclFunc DeclFuncVar {
        Node *func = create_nnary_node(NODECL_FUNCAO, yylineno, $1);
        Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, $1, $2, 0, 0);
        nnary_add_child(func, id);

        Node *params_node = ($3 && $3->data.nnary.first) ? $3->data.nnary.first : NULL;
        int num_params = 0;
        DataType *param_types = NULL;
        if (params_node && params_node->data.nnary.first) {
            Node *p = params_node->data.nnary.first;
            while (p) { num_params++; p = p->next; }
            param_types = malloc(sizeof(DataType) * num_params);
            int i = 0;
            p = params_node->data.nnary.first;
            while (p) {
                param_types[i++] = (p->type == TYINT ? INT_TYPE : CAR_TYPE);
                p = p->next;
            }
        }
        if (global) insert_function(global, $2, ($1 == TYINT ? INT_TYPE : CAR_TYPE),num_params, param_types);
        else  insert_function(current ? current : global, $2, ($1 == TYINT ? INT_TYPE : CAR_TYPE), num_params, param_types);
    
        nnary_merge_children(func, $3);
        Node *list = $4 ? $4 : create_nnary_node(NOLISTA_DECL, yylineno, TYVOID);
        nnary_add_child(list, func);
        $$ = list;
    }
     | /* epsilon */ { $$ = NULL; }

;


DeclProg:
    TPROGRAM Bloco { $$ = $2; }
;


DeclVar:
    TCOMMA TID_TOKEN DeclVar {
        Node *id_node = create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, $2, 0, 0);
        Node *list = create_nnary_node(NOLISTA_DECL, yylineno, TYVOID);
        nnary_add_child(list, id_node);
        nnary_merge_children(list, $3);
        $$ = list;
    }
    | /* epsilon */ { $$ = NULL; }
;


DeclFunc:
    TLPAREN { create_new_scope(&current); declaration_position = 0; }
    ListaParametros TRPAREN Bloco 
    { 
        Node *wrap = create_nnary_node(NOFUNC_COMPONENTS, yylineno, TYVOID);
        Node *params = $3; 
        if (!params) params = create_nnary_node(NOLISTA_PARAMS, yylineno, TYVOID);
        nnary_add_child(wrap, params);
        nnary_add_child(wrap, $5);  
        remove_current_scope(&current);
        $$ = wrap;
    }
;




ListaParametros:
     /* epsilon */ {
         $$ = create_nnary_node(NOLISTA_PARAMS, yylineno, TYVOID);
     }
    |
     ListaParametrosCont {
         $$ = $1;
     }
;

ListaParametrosCont:
     Tipo TID_TOKEN {
         Node *list = create_nnary_node(NOLISTA_PARAMS, yylineno, TYVOID);
         Node *param = create_leaf_node(NOIDENTIFICADOR, yylineno, $1, $2, 0, 0);
         nnary_add_child(list, param);
         if (current)  insert_parameter(current, $2,($1 == TYINT ? INT_TYPE : CAR_TYPE), declaration_position++);
         $$ = list;
     }
    | Tipo TID_TOKEN TCOMMA ListaParametrosCont {

         Node *list = $4;
         Node *param = create_leaf_node(NOIDENTIFICADOR, yylineno, $1, $2, 0, 0);
         nnary_add_child(list, param);
         if (current) insert_parameter(current, $2,($1 == TYINT ? INT_TYPE : CAR_TYPE),declaration_position++);
         $$ = list;
     }
;

Bloco:
    TLBRACE 
    {
        create_new_scope(&current);
        declaration_position = 0;
    }
    ListaDeclVar
    ListaComando
    TRBRACE
    {
        remove_current_scope(&current);
        Node *bloco = create_nnary_node(NOBLOCO, yylineno, TYVOID);
        nnary_merge_children(bloco, $3);
        nnary_merge_children(bloco, $4);
        $$ = bloco;
    }
;

ListaDeclVar:
    /* epsilon */ {
        $$ = create_nnary_node(NOLISTA_DECL, yylineno, TYVOID);
    }
    |
    Tipo TID_TOKEN DeclVar TSEMICOLON ListaDeclVar 
    {
        Node *decl = create_nnary_node(NODECL_VAR, yylineno, $1);
        Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, $1, $2, 0, 0);
        nnary_add_child(decl, id);
        if (current) insert_variable(current,$2, ($1 == TYINT ? INT_TYPE : CAR_TYPE),declaration_position++);
        if ($3 && $3->data.nnary.first) {
            Node *child = $3->data.nnary.first;
            while (child) {
                Node *next = child->next;
                child->type = $1;
                if (current && child->data.leaf.lexeme) {
                    insert_variable(
                        current,
                        child->data.leaf.lexeme,
                        ($1 == TYINT ? INT_TYPE : CAR_TYPE),
                        declaration_position++
                    );
                }
                nnary_add_child(decl, child);
                child = next;
            }
        }
        Node *acc = $5 ? $5 : create_nnary_node(NOLISTA_DECL, yylineno, TYVOID);
        nnary_add_child(acc, decl);
        $$ = acc;
    }
;



Tipo:
    TINT { $$ = TYINT; }
    | TCAR { $$ = TYCAR; }
;

ListaComando:
    ListaComando Comando {
        if ($2 == NULL) { $$ = $1; } 
        else if ($1 != NULL) { nnary_add_child($1, $2); $$ = $1; } 
        else { 
            Node *l = create_nnary_node(NOLISTA_COMANDOS, yylineno, TYVOID); 
            nnary_add_child(l, $2); 
            $$ = l; 
        }
    }
    | Comando {
        if ($1 != NULL) { 
            Node *l = create_nnary_node(NOLISTA_COMANDOS, yylineno, TYVOID); 
            nnary_add_child(l, $1); 
            $$ = l; 
        }
        else $$ = NULL;

        
    }
;


Comando:
    TSEMICOLON
        { $$ = NULL; }

    | Expr TSEMICOLON
        { $$ = $1; }

    | TRETURN Expr TSEMICOLON
        { $$ = create_unary_node(NORETURN, yylineno, TYVOID, $2); }

    | TREAD TID_TOKEN TSEMICOLON
        {
            Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, $2, 0, 0);            
            $$ = create_unary_node(NOREAD, yylineno, TYVOID, id);
        }

    | TWRITE Expr TSEMICOLON
        { $$ = create_unary_node(NOWRITE, yylineno, TYVOID, $2); }

    | TWRITE TSTRING_LITERAL TSEMICOLON
        {
            Node *str = create_leaf_node(NOSTRING_LITERAL, yylineno, TYVOID, $2, 0, 0);            
            $$ = create_unary_node(NOWRITE_LITERAL, yylineno, TYVOID, str);
        }

    | TNEWLINE TSEMICOLON
        { $$ = create_nnary_node(NONEWLINE, yylineno, TYVOID); }

    | TIF TLPAREN Expr TRPAREN TTHEN Comando
        { $$ = create_binary_node(NOIF, yylineno, TYVOID, $3, $6); }

    | TIF TLPAREN Expr TRPAREN TTHEN Comando TELSE Comando
        { $$ = create_if_else_node(NOIF_ELSE, yylineno, TYVOID, $3, $6, $8); }

    |TWHILE TLPAREN Expr TRPAREN TEXECUTE Comando
{
        Node *body;
        if ($6->species == NOBLOCO) {
            body = $6;
        } else {
            body = create_nnary_node(NOBLOCO, yylineno, TYVOID);
            nnary_add_child(body, $6);
        }

        $$ = create_binary_node(NOWHILE, yylineno, TYVOID, $3, body);
    }


    | Bloco
        { $$ = $1; }
;

Expr:
    OrExpr
        {
            $$ = $1;
        }
    | TID_TOKEN TASSIGN Expr
        {
            $$ = create_binary_node(NOATRIBUICAO, yylineno, TYVOID, create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, $1, 0, 0), $3);            
        }
;


OrExpr:
    OrExpr TOR AndExpr { $$ = create_binary_node(NOOR, yylineno, TYINT, $1, $3); }
    | AndExpr { $$ = $1; }
;

AndExpr:
    AndExpr TAND EqExpr { $$ = create_binary_node(NOAND, yylineno, TYINT, $1, $3); }
    | EqExpr { $$ = $1; }
;

EqExpr:
    EqExpr TEQ DesignExpr { $$ = create_binary_node(NOIGUAL, yylineno, TYINT, $1, $3); }
    | EqExpr TNEQ DesignExpr { $$ = create_binary_node(NODIFERENTE, yylineno, TYINT, $1, $3); }
    | DesignExpr { $$ = $1; }
;

DesignExpr:
    DesignExpr TLT AddExpr { $$ = create_binary_node(NOMENOR, yylineno, TYINT, $1, $3); }
    | DesignExpr TGT AddExpr { $$ = create_binary_node(NOMAIOR, yylineno, TYINT, $1, $3); }
    | DesignExpr TGEQ AddExpr { $$ = create_binary_node(NOMAIOR_IGUAL, yylineno, TYINT, $1, $3); }
    | DesignExpr TLEQ AddExpr { $$ = create_binary_node(NOMENOR_IGUAL, yylineno, TYINT, $1, $3); }
    | AddExpr { $$ = $1; }
;

AddExpr:
    AddExpr TPLUS MulExpr { $$ = create_binary_node(NOSOMA, yylineno, TYINT, $1, $3); }
    | AddExpr TMINUS MulExpr { $$ = create_binary_node(NOSUBTRACAO, yylineno, TYINT, $1, $3); }
    | MulExpr { $$ = $1; }
;

MulExpr:
    MulExpr TTIMES UnExpr { $$ = create_binary_node(NOMULTIPLICACAO, yylineno, TYINT, $1, $3); }
    | MulExpr TDIVIDE UnExpr { $$ = create_binary_node(NODIVISAO, yylineno, TYINT, $1, $3); }
    | UnExpr { $$ = $1; }
;

UnExpr:
    TMINUS PrimExpr { $$ = create_unary_node(NOMENOS_UNARIO, yylineno, TYINT, $2); }
    | TNEG PrimExpr { $$ = create_unary_node(NONEGACAO, yylineno, TYINT, $2); }
    | PrimExpr { $$ = $1; }
;


PrimExpr:
    TID_TOKEN TLPAREN ListExpr TRPAREN {
    Node *call = create_nnary_node(NOCHAMADA_FUNCAO, yylineno, TYVOID);
    Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, $1, 0, 0);
    nnary_add_child(call, id);    
    nnary_merge_children(call, $3);
    $$ = call;
}

    | TID_TOKEN TLPAREN TRPAREN {
        Node *call = create_nnary_node(NOCHAMADA_FUNCAO, yylineno, TYVOID);
        Node *id = create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, $1, 0, 0);
        nnary_add_child(call, id);
        $$ = call;
      }
    | TID_TOKEN {
        $$ = create_leaf_node(NOIDENTIFICADOR, yylineno, TYVOID, $1, 0, 0);        
      }
    | TCHAR_CONST {
        $$ = create_leaf_node(NOCAR_CONST, yylineno, TYCAR, NULL, 0, $1);
      }
    | TINT_CONST {
        $$ = create_leaf_node(NOINT_CONST, yylineno, TYINT, NULL, $1, 0);
      }
    | TLPAREN Expr TRPAREN { $$ = $2; }
;

ListExpr:
    Expr {
        Node *l = create_nnary_node(NOLISTA_EXPR, yylineno, TYVOID);
        nnary_add_child(l, $1);
        $$ = l;
      }
    | ListExpr TCOMMA Expr {
        nnary_add_child($1, $3);
        $$ = $1;
      }
;


%%

void yyerror(const char *s) {
    lex_error = 1;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Erro: argumento ausente.\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s'.\n", argv[1]);
        return 1;
    }

    initialize_symbol_table(&global);
    current = global;
    declaration_position = 0;

    yyparse(); 
    fclose(yyin);
    analyze_program(root, global);

    if (lex_error) {
        if (root) {
            free_ast(root);
            root = NULL;
        }
        return 1;
    }

   
    if (sem_error) {
        fprintf(stderr, "Sucesso: analise foi concluida, mas foram encontrados erros SEMANTICOS.\n");
        return 1;
    }

    printf("Sucesso: análise concluída com sucesso, livre de erros semanticos e de erros sintaticos.\n");
    return 0;
}