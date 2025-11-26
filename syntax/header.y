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
int error = 0;
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
        Node *program = createNnaryNode(NOPROGRAMA, yylineno, TYVOID);
        if ($1 && $1->data.nnary.first) {
            Node *child = $1->data.nnary.first;
            while (child) {
                Node *next = child->next;
                nnaryAddChild(program, child);
                child = next;
            }
        }
        if ($1) free($1);

        if ($2)
            nnaryAddChild(program, $2);
        $$ = program;
        root = program;
    }
;

DeclFuncVar:
    Tipo TID_TOKEN DeclVar TSEMICOLON DeclFuncVar {
        Node *decl = createNnaryNode(NODECL_VAR, yylineno, $1);
        Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, $1, $2, 0, 0);
        nnaryAddChild(decl, id);

        /* se houver lista de identificadores vindos de DeclVar, movê-los com segurança */
        if ($3 && $3->data.nnary.first) {
            Node *child = $3->data.nnary.first;
            while (child) {
                Node *next = child->next; 
                nnaryAddChild(decl, child);
                child = next;
            }
        }
        /* CORREÇÃO 1: Libera o nó container $3 (DeclVar) */
        if ($3) free($3);
        /* CORREÇÃO 4: Libera o lexema $2 */
        free($2);

        Node *list = ($5 ? $5 : createNnaryNode(NOLISTA_DECL, yylineno, TYVOID));
        nnaryAddChild(list, decl);
        $$ = list;
    }
    | Tipo TID_TOKEN DeclFunc DeclFuncVar {
        Node *func = createNnaryNode(NODECL_FUNCAO, yylineno, $1);
        Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, $1, $2, 0, 0);

        nnaryAddChild(func, id);
        
        /* CORREÇÃO 4: Libera o lexema $2 */
        free($2);

        Node *child = $3->data.nnary.first;
        while (child) {
            Node *next = child->next;
            nnaryAddChild(func, child);
            child = next;
        }

        /* CORREÇÃO 2: Libera o nó container $3 (DeclFunc/NOFUNC_COMPONENTS) */
        if ($3) free($3);

        Node *list = $4 ? $4 : createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
        nnaryAddChild(list, func);
        $$ = list;
    }
    | %empty { $$ = NULL; }
;


DeclProg:
    TPROGRAM Bloco { $$ = $2; }
;


DeclVar:
    TCOMMA TID_TOKEN DeclVar {
        Node *id_node = createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, $2, 0, 0);
        /* CORREÇÃO 4: Libera o lexema $2 */
        free($2);

        /* criar nova lista com o id atual em primeiro */
        Node *list = createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
        nnaryAddChild(list, id_node);

        /* anexar (mover) os filhos de $3, se existirem, após o id atual */
        if ($3 && $3->data.nnary.first) {
            Node *child = $3->data.nnary.first;
            while (child) {
                Node *next = child->next;
                /* desconectar antes de anexar */
                child->next = NULL;
                nnaryAddChild(list, child);
                child = next;
            }
        }

        /* liberar o container antigo para evitar vazamento */
        if ($3)
            free($3);

        $$ = list;
    }
    | %empty { $$ = NULL; }
;


DeclFunc:
    TLPAREN ListaParametros TRPAREN Bloco { 
        Node *wrap = createNnaryNode(NOFUNC_COMPONENTS, yylineno, TYVOID);
        
        Node *params = $2; 
        if (!params) {
             params = createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
        }
        
        nnaryAddChild(wrap, params);
        nnaryAddChild(wrap, $4);
        $$ = wrap;
    }
;


ListaParametros:
     %empty {
         $$ = createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
     }
    |
     ListaParametrosCont {
         $$ = $1;
     }
;


ListaParametrosCont:
     Tipo TID_TOKEN {
         Node *list = createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
         Node *param = createLeafNode(NOIDENTIFICADOR, yylineno, $1, $2, 0, 0);
         nnaryAddChild(list, param);
         /* CORREÇÃO 4: Libera o lexema $2 */
         free($2);
         $$ = list;
     }
    | Tipo TID_TOKEN TCOMMA ListaParametrosCont {
         Node *list = $4 ? $4 : createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
         Node *param = createLeafNode(NOIDENTIFICADOR, yylineno, $1, $2, 0, 0);
         nnaryAddChild(list, param);
         /* CORREÇÃO 4: Libera o lexema $2 */
         free($2);
         $$ = list;
     }
;

Bloco:
    TLBRACE ListaDeclVar ListaComando TRBRACE {
        Node *bloco = createNnaryNode(NOBLOCO, yylineno, TYVOID);
        /* ------ Mover declarações ($2) ------ */
        if ($2) {
            Node *child = $2->data.nnary.first;
            while (child) {
                Node *next = child->next;
                child->next = NULL;
                nnaryAddChild(bloco, child);
                child = next;
            }
            free($2);   /* libera o contêiner */
            $2 = NULL;
        }

        /* ------ Mover comandos ($3) ------ */
        if ($3) {
            Node *child = $3->data.nnary.first;
            while (child) {
                Node *next = child->next;
                child->next = NULL;
                nnaryAddChild(bloco, child);
                child = next;
            }
            free($3);  
            $3 = NULL;
        }
        $$ = bloco;
    }
;



ListaDeclVar:
    %empty {
        $$ = createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
    }
    |
    Tipo TID_TOKEN DeclVar TSEMICOLON ListaDeclVar {

        /* Declaração individual */
        Node *decl = createNnaryNode(NODECL_VAR, yylineno, $1);
        Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, $1, $2, 0, 0);
        nnaryAddChild(decl, id);
        
        /* CORREÇÃO 4: Libera o lexema $2 */
        free($2);

        /* Adiciona ids separados por vírgula */
        if ($3 && $3->data.nnary.first) {
            Node *child = $3->data.nnary.first;
            while (child) {
                Node *next = child->next;
                nnaryAddChild(decl, child);
                child = next;
            }
        }
        /* Libera o container de IDs DeclVar ($3) se ele existe */
        if ($3) free($3);


        /* $5 é a ListaDeclVar recursiva (à direita) */
        Node *acc = $5 ? $5 : createNnaryNode(NOLISTA_DECL, yylineno, TYVOID);
        nnaryAddChild(acc, decl);

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
        else if ($1 != NULL) { nnaryAddChild($1, $2); $$ = $1; } 
        else { 
            Node *l = createNnaryNode(NOLISTA_COMANDOS, yylineno, TYVOID); 
            nnaryAddChild(l, $2); 
            $$ = l; 
        }
    }
    | Comando {
        if ($1 != NULL) { 
            Node *l = createNnaryNode(NOLISTA_COMANDOS, yylineno, TYVOID); 
            nnaryAddChild(l, $1); 
            $$ = l; 
        }
        else { $$ = NULL; } // Comando nulo, retorna NULL. OK.
    }
;


Comando:
    TSEMICOLON
        { $$ = NULL; }

    | Expr TSEMICOLON
        { $$ = $1; }

    | TRETURN Expr TSEMICOLON
        { $$ = createUnaryNode(NORETURN, yylineno, TYVOID, $2); }

    | TREAD TID_TOKEN TSEMICOLON
        {
            Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, $2, 0, 0);
            /* CORREÇÃO 4: Libera o lexema $2 */
            free($2);
            $$ = createUnaryNode(NOREAD, yylineno, TYVOID, id);
        }

    | TWRITE Expr TSEMICOLON
        { $$ = createUnaryNode(NOWRITE, yylineno, TYVOID, $2); }

    | TWRITE TSTRING_LITERAL TSEMICOLON
        {
            Node *str = createLeafNode(NOSTRING_LITERAL, yylineno, TYVOID, $2, 0, 0);
            /* CORREÇÃO 4: Libera o lexema $2 */
            free($2);
            $$ = createUnaryNode(NOWRITE_LITERAL, yylineno, TYVOID, str);
        }

    | TNEWLINE TSEMICOLON
        { $$ = createNnaryNode(NONEWLINE, yylineno, TYVOID); }

    | TIF TLPAREN Expr TRPAREN TTHEN Comando
        { $$ = createBinaryNode(NOIF, yylineno, TYVOID, $3, $6); }

    | TIF TLPAREN Expr TRPAREN TTHEN Comando TELSE Comando
        { $$ = createIfElseNode(NOIF_ELSE, yylineno, TYVOID, $3, $6, $8); }

    |TWHILE TLPAREN Expr TRPAREN TEXECUTE Comando
{
        Node *body;

        if ($6->species == NOBLOCO) {
            body = $6;
        } else {
            body = createNnaryNode(NOBLOCO, yylineno, TYVOID);
            nnaryAddChild(body, $6);
        }

        $$ = createBinaryNode(NOWHILE, yylineno, TYVOID, $3, body);
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
            $$ = createBinaryNode(NOATRIBUICAO, yylineno, TYVOID,
                                     createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, $1, 0, 0),
                                     $3);
            /* CORREÇÃO 4: Libera o lexema $1 */
            free($1);
        }
;


OrExpr:
    OrExpr TOR AndExpr { $$ = createBinaryNode(NOOR, yylineno, TYINT, $1, $3); }
    | AndExpr { $$ = $1; }
;

AndExpr:
    AndExpr TAND EqExpr { $$ = createBinaryNode(NOAND, yylineno, TYINT, $1, $3); }
    | EqExpr { $$ = $1; }
;

EqExpr:
    EqExpr TEQ DesignExpr { $$ = createBinaryNode(NOIGUAL, yylineno, TYINT, $1, $3); }
    | EqExpr TNEQ DesignExpr { $$ = createBinaryNode(NODIFERENTE, yylineno, TYINT, $1, $3); }
    | DesignExpr { $$ = $1; }
;

DesignExpr:
    DesignExpr TLT AddExpr { $$ = createBinaryNode(NOMENOR, yylineno, TYINT, $1, $3); }
    | DesignExpr TGT AddExpr { $$ = createBinaryNode(NOMAIOR, yylineno, TYINT, $1, $3); }
    | DesignExpr TGEQ AddExpr { $$ = createBinaryNode(NOMAIOR_IGUAL, yylineno, TYINT, $1, $3); }
    | DesignExpr TLEQ AddExpr { $$ = createBinaryNode(NOMENOR_IGUAL, yylineno, TYINT, $1, $3); }
    | AddExpr { $$ = $1; }
;

AddExpr:
    AddExpr TPLUS MulExpr { $$ = createBinaryNode(NOSOMA, yylineno, TYINT, $1, $3); }
    | AddExpr TMINUS MulExpr { $$ = createBinaryNode(NOSUBTRACAO, yylineno, TYINT, $1, $3); }
    | MulExpr { $$ = $1; }
;

MulExpr:
    MulExpr TTIMES UnExpr { $$ = createBinaryNode(NOMULTIPLICACAO, yylineno, TYINT, $1, $3); }
    | MulExpr TDIVIDE UnExpr { $$ = createBinaryNode(NODIVISAO, yylineno, TYINT, $1, $3); }
    | UnExpr { $$ = $1; }
;

UnExpr:
    TMINUS PrimExpr { $$ = createUnaryNode(NOMENOS_UNARIO, yylineno, TYINT, $2); }
    | TNEG PrimExpr { $$ = createUnaryNode(NONEGACAO, yylineno, TYINT, $2); }
    | PrimExpr { $$ = $1; }
;


PrimExpr:
    TID_TOKEN TLPAREN ListExpr TRPAREN {
    Node *call = createNnaryNode(NOCHAMADA_FUNCAO, yylineno, TYVOID);
    Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, $1, 0, 0);
    nnaryAddChild(call, id);
    /* CORREÇÃO 4: Libera o lexema $1 */
    free($1);
    
    if ($3 && $3->data.nnary.first) {
        Node *child = $3->data.nnary.first;
        while (child) {
            Node *next = child->next;
            nnaryAddChild(call, child);
            child = next;
        }
    }

    /* free do container ListExpr: já movemos os filhos */
    if ($3) free($3);

    $$ = call;
}

    | TID_TOKEN TLPAREN TRPAREN {
        Node *call = createNnaryNode(NOCHAMADA_FUNCAO, yylineno, TYVOID);
        Node *id = createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, $1, 0, 0);
        nnaryAddChild(call, id);
        
        /* CORREÇÃO 4: Libera o lexema $1 */
        free($1);

        $$ = call;
      }
    | TID_TOKEN {
        $$ = createLeafNode(NOIDENTIFICADOR, yylineno, TYVOID, $1, 0, 0);
        /* CORREÇÃO 4: Libera o lexema $1 */
        free($1);
      }
    | TCHAR_CONST {
        $$ = createLeafNode(NOCAR_CONST, yylineno, TYCAR, NULL, 0, $1);
      }
    | TINT_CONST {
        $$ = createLeafNode(NOINT_CONST, yylineno, TYINT, NULL, $1, 0);
      }
    | TLPAREN Expr TRPAREN { $$ = $2; }
;

ListExpr:
    Expr {
        Node *l = createNnaryNode(NOLISTA_EXPR, yylineno, TYVOID);
        nnaryAddChild(l, $1);
        $$ = l;
      }
    | ListExpr TCOMMA Expr {
        nnaryAddChild($1, $3);
        $$ = $1;
      }
;


%%

/* User C Code */

// Error handling function
void yyerror(const char *s) {
    error = 1;
    fprintf(stderr, "Erro: Erro sintático na linha %d, próximo a '%s'\n", yylineno, yytext);
}

// Main function to start the analyzer
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

    /* preparar tabela de símbolos */
    //SymbolTable *table = NULL;
   // initialize_symbol_table(&table);
    
    // 💡 Salva o ponteiro para o escopo RAIZ (Nível 0).
   // SymbolTable *table_root = table; 
    
    // 'table' passa a apontar para o escopo interno/atual (Nível 1)
   // create_new_scope(&table); 

    /* PARSE */
    // Assumindo que 'root' é uma variável global que recebe o nó raiz da AST
    yyparse(); 
    printAST(root, 0);
    fclose(yyin);

    /* Se houve erro sintático, liberar tudo e encerrar */
    if (error) {
        if (root) {
            freeAST(root);
            root = NULL;
        }
        // 🛑 Usa a raiz para destruir todos os escopos.
       /* if (table_root) { 
            destroy_symbol_table(table_root);
            table_root = NULL;
        }*/
        fprintf(stderr, "Falha: foram encontrados erros sintáticos.\n");
        return 1;
    }

    /* Sem erros sintáticos → executar análise semântica */
    // Note: analyze_semantic deve usar e restaurar os escopos corretamente.
    //analyze_semantic(root, table); 

    /* Liberar recursos SEMPRE */
    // 🌳 Libera a Árvore Sintática Abstrata
    if (root) {
        freeAST(root);
        root = NULL;
    }

    // 📚 Libera a Tabela de Símbolos, usando o ponteiro RAIZ.
   /* if (table_root) {
        destroy_symbol_table(table_root);
        table_root = NULL;
    }*/

    /* Resultado final */
    if (error) {
        fprintf(stderr,
                "Sucesso: análise foi concluída, mas foram encontrados erros semânticos.\n");
        return 1;
    }

    printf("Sucesso: análise concluída com sucesso.\n");
    return 0;
}