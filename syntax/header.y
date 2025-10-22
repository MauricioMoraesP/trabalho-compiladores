%{
#include "../symbol_table/header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

int yylex();
void yyerror(const char *s);

int error = 0;
PNode root = NULL;
%}

%union {
    int ival;
    char cval;
    char *str;
    PNode Tespecies;
}

%token <str> TID_TOKEN TSTRING_LITERAL
%token <ival> TINT_CONST
%token <cval> TCHAR_CONST

%type<Tespecies> Programa DeclFuncVar DeclProg DeclVar DeclFunc ListaParametros ListaParametrosCont Bloco ListaDeclVar ListaComando Comando Expr UnExpr PrimExpr LValueExpr ListExpr ListExprCont Tipo

%token TPROGRAM TCAR TINT TRETURN TREAD TWRITE TNEWLINE TIF TTHEN TELSE TWHILE TEXECUTE TAND
%token TPLUS TMINUS TTIMES TDIVIDE TASSIGN TEQ TNEQ TLT TLEQ TGT TGEQ TSEMICOLON TLPAREN TRPAREN TLBRACE TRBRACE TLBRACKET TRBRACKET TCOMMA
%token TOR
%token TNEG

%left TASSIGN
%left TPLUS TMINUS
%left TTIMES TDIVIDE
%left TEQ TNEQ
%left TLT TLEQ TGT TGEQ
%left TOR
%left TAND

%nonassoc TTHEN
%nonassoc TELSE

%start Programa

%%

Programa:
      DeclFuncVar DeclProg
        { $$ = cNodeAST(NODE_PROGRAMA, yylineno, $1, $2, NULL, NULL);
          root = $$; }
;

DeclFuncVar:
      Tipo TID_TOKEN DeclVar TSEMICOLON DeclFuncVar
        {
          PNode decl = cNodeAST(NODE_DECL_VAR, yylineno, $1, cNodeIdentifier(yylineno, $2), $3, NULL);
          $$ = cNodeAST(NODE_DECL_VAR, yylineno, decl, $5, NULL, NULL);
        }
    | Tipo TID_TOKEN DeclFunc DeclFuncVar
        {
          PNode declFunc = cNodeAST(NODE_DECL_FUNCAO, yylineno, $1, cNodeIdentifier(yylineno, $2), $3, NULL);
          $$ = cNodeAST(NODE_DECL_FUNCAO, yylineno, declFunc, $4, NULL, NULL);
        }
    | /* epsilon */
        { $$ = NULL; }
;

DeclProg:
      TPROGRAM Bloco
        { $$ = $2; }
;

DeclVar:
      /* epsilon */
        { $$ = NULL; }
    | TCOMMA TID_TOKEN DeclVar
        { $$ = cNodeAST(NODE_DECL_VAR, yylineno, cNodeIdentifier(yylineno, $2), $3, NULL, NULL); }
;

DeclFunc:
      TLPAREN ListaParametros TRPAREN Bloco
        { $$ = cNodeAST(NODE_DECL_FUNCAO, yylineno, $2, $4, NULL, NULL); }
;

ListaParametros:
      Tipo TID_TOKEN ListaParametrosCont
        { $$ = cNodeAST(NODE_DECL_VAR, yylineno, $1, cNodeIdentifier(yylineno, $2), $3, NULL); }
    | /* epsilon */
        { $$ = NULL; }
;

ListaParametrosCont:
      TCOMMA Tipo TID_TOKEN ListaParametrosCont
        { $$ = cNodeAST(NODE_DECL_VAR, yylineno, $2, cNodeIdentifier(yylineno, $3), $4, NULL); }
    | /* epsilon */
        { $$ = NULL; }
;

Bloco:
      TLBRACE ListaDeclVar ListaComando TRBRACE
        { $$ = cNodeAST(NODE_BLOCO, yylineno, $2, $3, NULL, NULL); }
    | TLBRACE ListaDeclVar TRBRACE
        { $$ = cNodeAST(NODE_BLOCO, yylineno, $2, NULL, NULL, NULL); }
;

ListaDeclVar:
      Tipo TID_TOKEN DeclVar TSEMICOLON ListaDeclVar
        {
          PNode decl = cNodeAST(NODE_DECL_VAR, yylineno, $1, cNodeIdentifier(yylineno, $2), $3, NULL);
          $$ = cNodeAST(NODE_DECL_VAR, yylineno, decl, $5, NULL, NULL);
        }
    | /* epsilon */
        { $$ = NULL; }
;

ListaComando:
      Comando ListaComando
        { $$ = cNodeAST(NODE_LISTA_COMANDOS, yylineno, $1, $2, NULL, NULL); }
    | /* epsilon */
        { $$ = NULL; }
;

Comando:
      TSEMICOLON
        { $$ = NULL; }
    | Expr TSEMICOLON
        { $$ = $1; }
    | TRETURN Expr TSEMICOLON
        { $$ = cNodeAST(NODE_RETURN, yylineno, $2, NULL, NULL, NULL); }
    | TREAD LValueExpr TSEMICOLON
        { $$ = cNodeAST(NODE_LEIA, yylineno, $2, NULL, NULL, NULL); }
    | TWRITE Expr TSEMICOLON
        { $$ = cNodeAST(NODE_ESCREVA, yylineno, $2, NULL, NULL, NULL); }
    | TWRITE TSTRING_LITERAL TSEMICOLON
        { $$ = cNodeAST(NODE_ESCREVA_LITERAL, yylineno, NULL, NULL, NULL, $2); }
    | TNEWLINE TSEMICOLON
        { $$ = cNodeAST(NODE_NOVALINHA, yylineno, NULL, NULL, NULL, NULL); }
    | TIF TLPAREN Expr TRPAREN TTHEN Comando TELSE Comando
        { $$ = cNodeAST(NODE_IF_ELSE, yylineno, $3, $6, $8, NULL); }
    | TIF TLPAREN Expr TRPAREN TTHEN Comando
        { $$ = cNodeAST(NODE_IF, yylineno, $3, $6, NULL, NULL); }
    | TWHILE TLPAREN Expr TRPAREN TEXECUTE Comando
        { $$ = cNodeAST(NODE_WHILE, yylineno, $3, $6, NULL, NULL); }
    | Bloco
        { $$ = $1; }
    | LValueExpr TASSIGN Expr TSEMICOLON
        { $$ = cNodeAST(NODE_ATRIBUICAO, yylineno, $1, $3, NULL, NULL); }
;

Expr:
      PrimExpr
        { $$ = $1; }
    | UnExpr
        { $$ = $1; }
    | Expr TPLUS Expr        { $$ = cNodeAST(NODE_SOMA, yylineno, $1, $3, NULL, NULL); }
    | Expr TMINUS Expr       { $$ = cNodeAST(NODE_SUBTRACAO, yylineno, $1, $3, NULL, NULL); }
    | Expr TTIMES Expr       { $$ = cNodeAST(NODE_MULTIPLICACAO, yylineno, $1, $3, NULL, NULL); }
    | Expr TDIVIDE Expr      { $$ = cNodeAST(NODE_DIVISAO, yylineno, $1, $3, NULL, NULL); }
    | Expr TOR Expr          { $$ = cNodeAST(NODE_OR, yylineno, $1, $3, NULL, NULL); }
    | Expr TAND Expr         { $$ = cNodeAST(NODE_AND, yylineno, $1, $3, NULL, NULL); }
    | Expr TEQ Expr          { $$ = cNodeAST(NODE_IGUAL, yylineno, $1, $3, NULL, NULL); }
    | Expr TNEQ Expr         { $$ = cNodeAST(NODE_DIFERENTE, yylineno, $1, $3, NULL, NULL); }
    | Expr TLT Expr          { $$ = cNodeAST(NODE_MENOR, yylineno, $1, $3, NULL, NULL); }
    | Expr TLEQ Expr         { $$ = cNodeAST(NODE_MENOR_IGUAL, yylineno, $1, $3, NULL, NULL); }
    | Expr TGT Expr          { $$ = cNodeAST(NODE_MAIOR, yylineno, $1, $3, NULL, NULL); }
    | Expr TGEQ Expr         { $$ = cNodeAST(NODE_MAIOR_IGUAL, yylineno, $1, $3, NULL, NULL); }
    | LValueExpr TASSIGN Expr
        { $$ = cNodeAST(NODE_ATRIBUICAO, yylineno, $1, $3, NULL, NULL); }
;

UnExpr:
      TMINUS PrimExpr
        { $$ = cNodeAST(NODE_MENOS_UNARIO, yylineno, $2, NULL, NULL, NULL); }
    | TNEG PrimExpr
        { $$ = cNodeAST(NODE_NEGACAO, yylineno, $2, NULL, NULL, NULL); }
    | PrimExpr
        { $$ = $1; }
;

LValueExpr:
      TID_TOKEN
        { $$ = cNodeIdentifier(yylineno, $1); }
;

PrimExpr:
      TINT_CONST              { $$ = cNodeConstInt(yylineno, $1); }
    | TCHAR_CONST             { $$ = cNodeConstChar(yylineno, $1); }
    | TSTRING_LITERAL         { $$ = cNodeAST(NODE_STRING_LITERAL, yylineno, NULL, NULL, NULL, $1); }
    | TLPAREN Expr TRPAREN    { $$ = $2; }
    | TID_TOKEN TLPAREN ListExpr TRPAREN
                              { $$ = cNodeAST(NODE_CHAMADA_FUNCAO, yylineno, cNodeIdentifier(yylineno, $1), $3, NULL, NULL); }
    | TID_TOKEN TLPAREN TRPAREN
                              { $$ = cNodeAST(NODE_CHAMADA_FUNCAO, yylineno, cNodeIdentifier(yylineno, $1), NULL, NULL, NULL); }
    | TID_TOKEN               { $$ = cNodeIdentifier(yylineno, $1); }
;

ListExpr:
      Expr ListExprCont
        { $$ = cNodeAST(NODE_LISTA_EXPRESSOES, yylineno, $1, $2, NULL, NULL); }
    | /* epsilon */
        { $$ = NULL; }
;

ListExprCont:
      TCOMMA Expr ListExprCont
        { $$ = cNodeAST(NODE_LISTA_EXPRESSOES, yylineno, $2, $3, NULL, NULL); }
    | /* epsilon */
        { $$ = NULL; }
;

Tipo:
      TCAR
        { $$ = cNodeAST(NODE_TIPO_CAR, yylineno, NULL, NULL, NULL, "car"); }
    | TINT
        { $$ = cNodeAST(NODE_TIPO_INT, yylineno, NULL, NULL, NULL, "int"); }
;

%%

void yyerror(const char *s) {
    error = 1;
    fprintf(stderr, "ERRO: Erro sintático na linha %d, próximo a '%s'\n", yylineno, yytext);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "Erro ao abrir arquivo '%s'\n", argv[1]);
        return 1;
    }

    yyin = f;
    printf("Iniciando análise sintática para '%s'...\n", argv[1]);
    yyparse();
    fclose(f);

    if (!error) {
        printf("Análise concluída com sucesso!\n\n--- AST ---\n");
        printAST(root, 0);
    } else {
        printf("Análise encerrada com erros.\n");
    }
    return 0;
}
