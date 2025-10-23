%{
#include "types.h" 
#include "ast.h"
#include "syntax/header.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern int yylineno;
extern char *yytext;
extern FILE *yyin;

int yylex();
void yyerror(const char *s);

int error = 0;
PNode root = NULL;
%}

%union {
    PNode TEspecies;
    int ival;
    char cval;
    char *str;
}

%token <str> TID_TOKEN TSTRING_LITERAL
%token <ival> TINT_CONST
%token <cval> TCHAR_CONST

%type<TEspecies> Programa DeclFuncVar DeclProg DeclVar DeclFunc ListaParametros ListaParametrosCont Bloco ListaDeclVar ListaComando Comando Expr UnExpr PrimExpr LValueExpr ListExpr ListExprCont Tipo

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
        { $$ = (PNode)cNodeAST(NODE_PROGRAMA, yylineno, (PNode)$1, (PNode)$2, NULL, NULL);
          root = $$; }
;

DeclFuncVar:
      Tipo TID_TOKEN DeclVar TSEMICOLON DeclFuncVar
        {
          PNode decl = (PNode)cNodeAST(NODE_DECL_VAR, yylineno, (PNode)$1, cNodeIdentifier(yylineno, $2), (PNode)$3, NULL);
          $$ = (PNode)cNodeAST(NODE_DECL_VAR, yylineno, decl, (PNode)$5, NULL, NULL);
        }
    | Tipo TID_TOKEN DeclFunc DeclFuncVar
        {
          PNode declFunc = (PNode)cNodeAST(NODE_DECL_FUNCAO, yylineno, (PNode)$1, cNodeIdentifier(yylineno, $2), (PNode)$3, NULL);
          $$ = (PNode)cNodeAST(NODE_DECL_FUNCAO, yylineno, declFunc, (PNode)$4, NULL, NULL);
        }
    | /* epsilon */
        { $$ = NULL; }
;

DeclProg:
      TPROGRAM Bloco
        { $$ = (PNode)$2; }
;

DeclVar:
      /* epsilon */
        { $$ = NULL; }
    | TCOMMA TID_TOKEN DeclVar
        { $$ = (PNode)cNodeAST(NODE_DECL_VAR, yylineno, cNodeIdentifier(yylineno, $2), (PNode)$3, NULL, NULL); }
;

DeclFunc:
      TLPAREN ListaParametros TRPAREN Bloco
        { $$ = (PNode)cNodeAST(NODE_DECL_FUNCAO, yylineno, (PNode)$2, (PNode)$4, NULL, NULL); }
;

ListaParametros:
      Tipo TID_TOKEN ListaParametrosCont
        { $$ = (PNode)cNodeAST(NODE_DECL_VAR, yylineno, (PNode)$1, cNodeIdentifier(yylineno, $2), (PNode)$3, NULL); }
    | /* epsilon */
        { $$ = NULL; }
;

ListaParametrosCont:
      TCOMMA Tipo TID_TOKEN ListaParametrosCont
        { $$ = (PNode)cNodeAST(NODE_DECL_VAR, yylineno, (PNode)$2, cNodeIdentifier(yylineno, $3), (PNode)$4, NULL); }
    | /* epsilon */
        { $$ = NULL; }
;

Bloco:
      TLBRACE ListaDeclVar ListaComando TRBRACE
        { $$ = (PNode)cNodeAST(NODE_BLOCO, yylineno, (PNode)$2, (PNode)$3, NULL, NULL); }
    | TLBRACE ListaDeclVar TRBRACE
        { $$ = (PNode)cNodeAST(NODE_BLOCO, yylineno, (PNode)$2, NULL, NULL, NULL); }
;

ListaDeclVar:
      Tipo TID_TOKEN DeclVar TSEMICOLON ListaDeclVar
        {
          PNode decl = (PNode)cNodeAST(NODE_DECL_VAR, yylineno, (PNode)$1, cNodeIdentifier(yylineno, $2), (PNode)$3, NULL);
          $$ = (PNode)cNodeAST(NODE_DECL_VAR, yylineno, decl, (PNode)$5, NULL, NULL);
        }
    | /* epsilon */
        { $$ = NULL; }
;

ListaComando:
      Comando ListaComando
        { $$ = (PNode)cNodeAST(NODE_LISTA_COMANDOS, yylineno, (PNode)$1, (PNode)$2, NULL, NULL); }
    | /* epsilon */
        { $$ = NULL; }
;

Comando:
      TSEMICOLON
        { $$ = NULL; }
    | Expr TSEMICOLON
        { $$ = (PNode)$1; }
    | TRETURN Expr TSEMICOLON
        { $$ = (PNode)cNodeAST(NODE_RETURN, yylineno, (PNode)$2, NULL, NULL, NULL); }
    | TREAD LValueExpr TSEMICOLON
        { $$ = (PNode)cNodeAST(NODE_LEIA, yylineno, (PNode)$2, NULL, NULL, NULL); }
    | TWRITE Expr TSEMICOLON
        { $$ = (PNode)cNodeAST(NODE_ESCREVA, yylineno, (PNode)$2, NULL, NULL, NULL); }
    | TWRITE TSTRING_LITERAL TSEMICOLON
        { $$ = (PNode)cNodeAST(NODE_ESCREVA_LITERAL, yylineno, NULL, NULL, NULL, $2); }
    | TNEWLINE TSEMICOLON
        { $$ = (PNode)cNodeAST(NODE_NOVALINHA, yylineno, NULL, NULL, NULL, NULL); }
    | TIF TLPAREN Expr TRPAREN TTHEN Comando TELSE Comando
        { $$ = (PNode)cNodeAST(NODE_IF_ELSE, yylineno, (PNode)$3, (PNode)$6, (PNode)$8, NULL); }
    | TIF TLPAREN Expr TRPAREN TTHEN Comando
        { $$ = (PNode)cNodeAST(NODE_IF, yylineno, (PNode)$3, (PNode)$6, NULL, NULL); }
    | TWHILE TLPAREN Expr TRPAREN TEXECUTE Comando
        { $$ = (PNode)cNodeAST(NODE_WHILE, yylineno, (PNode)$3, (PNode)$6, NULL, NULL); }
    | Bloco
        { $$ = (PNode)$1; }
    | LValueExpr TASSIGN Expr TSEMICOLON
        { $$ = (PNode)cNodeAST(NODE_ATRIBUICAO, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
;

Expr:
      PrimExpr
        { $$ = (PNode)$1; }
    | UnExpr
        { $$ = (PNode)$1; }
    | Expr TPLUS Expr        { $$ = (PNode)cNodeAST(NODE_SOMA, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TMINUS Expr       { $$ = (PNode)cNodeAST(NODE_SUBTRACAO, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TTIMES Expr       { $$ = (PNode)cNodeAST(NODE_MULTIPLICACAO, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TDIVIDE Expr      { $$ = (PNode)cNodeAST(NODE_DIVISAO, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TOR Expr          { $$ = (PNode)cNodeAST(NODE_OR, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TAND Expr         { $$ = (PNode)cNodeAST(NODE_AND, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TEQ Expr          { $$ = (PNode)cNodeAST(NODE_IGUAL, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TNEQ Expr         { $$ = (PNode)cNodeAST(NODE_DIFERENTE, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TLT Expr          { $$ = (PNode)cNodeAST(NODE_MENOR, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TLEQ Expr         { $$ = (PNode)cNodeAST(NODE_MENOR_IGUAL, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TGT Expr          { $$ = (PNode)cNodeAST(NODE_MAIOR, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | Expr TGEQ Expr         { $$ = (PNode)cNodeAST(NODE_MAIOR_IGUAL, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
    | LValueExpr TASSIGN Expr
        { $$ = (PNode)cNodeAST(NODE_ATRIBUICAO, yylineno, (PNode)$1, (PNode)$3, NULL, NULL); }
;

UnExpr:
      TMINUS PrimExpr
        { $$ = (PNode)cNodeAST(NODE_MENOS_UNARIO, yylineno, (PNode)$2, NULL, NULL, NULL); }
    | TNEG PrimExpr
        { $$ = (PNode)cNodeAST(NODE_NEGACAO, yylineno, (PNode)$2, NULL, NULL, NULL); }
    | PrimExpr
        { $$ = (PNode)$1; }
;

LValueExpr:
      TID_TOKEN
        { $$ = cNodeIdentifier(yylineno, $1); }
;

PrimExpr:
      TINT_CONST              { $$ = cNodeConstInt(yylineno, $1); }
    | TCHAR_CONST             { $$ = cNodeConstChar(yylineno, $1); }
    | TSTRING_LITERAL         { $$ = (PNode)cNodeAST(NODE_STRING_LITERAL, yylineno, NULL, NULL, NULL, $1); }
    | TLPAREN Expr TRPAREN    { $$ = (PNode)$2; }
    | TID_TOKEN TLPAREN ListExpr TRPAREN
                              { $$ = (PNode)cNodeAST(NODE_CHAMADA_FUNCAO, yylineno, cNodeIdentifier(yylineno, $1), (PNode)$3, NULL, NULL); }
    | TID_TOKEN TLPAREN TRPAREN
                              { $$ = (PNode)cNodeAST(NODE_CHAMADA_FUNCAO, yylineno, cNodeIdentifier(yylineno, $1), NULL, NULL, NULL); }
    | TID_TOKEN               { $$ = cNodeIdentifier(yylineno, $1); }
;

ListExpr:
      Expr ListExprCont
        { $$ = (PNode)cNodeAST(NODE_LISTA_EXPRESSOES, yylineno, (PNode)$1, (PNode)$2, NULL, NULL); }
    | /* epsilon */
        { $$ = NULL; }
;

ListExprCont:
      TCOMMA Expr ListExprCont
        { $$ = (PNode)cNodeAST(NODE_LISTA_EXPRESSOES, yylineno, (PNode)$2, (PNode)$3, NULL, NULL); }
    | /* epsilon */
        { $$ = NULL; }
;

Tipo:
      TCAR
        { $$ = (PNode)cNodeAST(NODE_TIPO_CAR, yylineno, NULL, NULL, NULL, "car"); }
    | TINT
        { $$ = (PNode)cNodeAST(NODE_TIPO_INT, yylineno, NULL, NULL, NULL, "int"); }
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
