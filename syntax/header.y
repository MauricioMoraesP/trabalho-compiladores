%{
#include "../symbol_table/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Flex global functions and variables
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

// Lexical analyzer function declaration
int yylex();

// Error handling function declaration
void yyerror(const char *s);

int erroEncontrado = 0; // Flag para indicar erro
%}

%union {
    int ival;
    char cval;
    char *str;
}

%token <str> ID_TOKEN TSTRING_LITERAL
%token <ival> INT_CONST
%token <cval> TCHAR_CONST

%token TPROGRAM TCAR TINT TRETURN TREAD TWRITE TNEWLINE TIF TTHEN TELSE TWHILE TEXECUTE TAND
%token TPLUS TMINUS TTIMES TDIVIDE TASSIGN TEQ TNEQ TLT TLEQ TGT TGEQ TSEMICOLON TLPAREN TRPAREN TLBRACE TRBRACE TLBRACKET TRBRACKET TCOMMA
%token TOR
%token TNEG

%right TASSIGN
%left TPLUS TMINUS
%left TTIMES TDIVIDE
%right TEQ TNEQ
%right TLT TLEQ TGT TGEQ
%left TOR
%left TAND

%nonassoc TTHEN
%nonassoc TELSE

%start Programa

%%

Programa: DeclFuncVar DeclProg
;

DeclFuncVar: Tipo ID_TOKEN DeclVar TSEMICOLON DeclFuncVar
           | Tipo ID_TOKEN DeclFunc DeclFuncVar
           | /* epsilon */
;

DeclProg: TPROGRAM Bloco
;

DeclVar: /* epsilon */
       | TCOMMA ID_TOKEN DeclVar
;

DeclFunc: TLPAREN ListaParametros TRPAREN Bloco
;

ListaParametros: Tipo ID_TOKEN ListaParametrosCont
               | /* epsilon */
;

ListaParametrosCont: TCOMMA Tipo ID_TOKEN ListaParametrosCont
                   | /* epsilon */
;

Bloco: TLBRACE ListaDeclVar ListaComando TRBRACE
     | TLBRACE ListaDeclVar TRBRACE
;

ListaDeclVar: Tipo ID_TOKEN DeclVar TSEMICOLON ListaDeclVar
            | /* epsilon */
;

ListaComando: Comando ListaComando
            | /* epsilon */
;

Comando: TSEMICOLON
       | Expr TSEMICOLON
       | TRETURN Expr TSEMICOLON
       | TREAD LValueExpr TSEMICOLON
       | TWRITE Expr TSEMICOLON
       | TWRITE TSTRING_LITERAL TSEMICOLON
       | TNEWLINE TSEMICOLON
       | TIF TLPAREN Expr TRPAREN TTHEN Comando TELSE Comando
       | TIF TLPAREN Expr TRPAREN TTHEN Comando
       | TWHILE TLPAREN Expr TRPAREN TEXECUTE Comando
       | Bloco
       | LValueExpr TASSIGN Expr TSEMICOLON
;

Expr: OrExpr
;

OrExpr: OrExpr TOR AndExpr
      | AndExpr
;

AndExpr: AndExpr TAND EqExpr
       | EqExpr
;

EqExpr: EqExpr TEQ DesigExpr
      | EqExpr TNEQ DesigExpr
      | DesigExpr
;

DesigExpr: DesigExpr TLT AddExpr
         | DesigExpr TGT AddExpr
         | DesigExpr TLEQ AddExpr
         | DesigExpr TGEQ AddExpr
         | AddExpr
;

AddExpr: AddExpr TPLUS MulExpr
       | AddExpr TMINUS MulExpr
       | MulExpr
;

MulExpr: MulExpr TTIMES UnExpr
       | MulExpr TDIVIDE UnExpr
       | UnExpr
;

UnExpr: TMINUS PrimExpr
      | TNEG PrimExpr
      | PrimExpr
;

LValueExpr: ID_TOKEN
;

PrimExpr: INT_CONST
        | TCHAR_CONST
        | TSTRING_LITERAL
        | TLPAREN Expr TRPAREN
        | ID_TOKEN TLPAREN ListExpr TRPAREN
        | ID_TOKEN TLPAREN TRPAREN
        | ID_TOKEN
;

ListExpr: Expr ListExprCont
        | /* epsilon */
;

ListExprCont: TCOMMA Expr ListExprCont
            | /* epsilon */
;

Tipo: TCAR
    | TINT
;

%%

/* User C Code */

// Error handling function
void yyerror(const char *s) {
    erroEncontrado = 1;
    fprintf(stderr, "ERRO: Erro sintático na linha %d, próximo a '%s'\n", yylineno, yytext);
}

// Main function to start the analyzer
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso correto: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }
    
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "Não foi possível abrir o arquivo: %s\n", argv[1]);
        return 1;
    }
    
    yyin = f;
    yyparse();
    fclose(yyin);

    if (!erroEncontrado) {
        printf("Analise sintatica concluida com sucesso!\n");
    }

    return 0;
}
