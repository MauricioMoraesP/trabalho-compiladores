%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../syntax/types.h"
#include "../syntax/ast.h"
#include "../syntax/header.tab.h"

int row_count;
extern char *yytext;
extern int yylineno;
extern YYSTYPE yylval;
%}

%option noyywrap yylineno 

INT       [0-9]
CAR      [a-zA-Z]
ID       {CAR}({CAR}|{INT}|_)*

%x comment

%%
"programa"       { return TPROGRAM; }
"car"            { return TCAR; }
"leia"           { return TREAD; }
"escreva"        { return TWRITE; }
"retorne"        { return TRETURN; }
"novalinha"      { return TNEWLINE; }
"se"             { return TIF; }
"senao"          { return TELSE; }
"int"            { return TINT; }
"entao"          { return TTHEN; }
"execute"        { return TEXECUTE; }
"e"              { return TAND; }
"enquanto"       { return TWHILE; }
"ou"             { return TOR; }

"!"              { return TNEG; }
"+"              { return TPLUS; }
"-"              { return TMINUS; }
"*"              { return TTIMES; }
"/"              { return TDIVIDE; }
"=="             { return TEQ; }
"!="             { return TNEQ; }
"<="             { return TLEQ; }
">="             { return TGEQ; }
"="              { return TASSIGN; }
"<"              { return TLT; }
">"              { return TGT; }
";"              { return TSEMICOLON; }
"("              { return TLPAREN; }
")"              { return TRPAREN; }
"{"              { return TLBRACE; }
"}"              { return TRBRACE; }
"["              { return TLBRACKET; }
"]"              { return TRBRACKET; }
","              { return TCOMMA; }

{ID} {

    yylval.str = strdup(yytext);
    return TID_TOKEN;
}

{INT}+ {
    yylval.ival = atoi(yytext);
    return TINT_CONST;
}

\"([^"\\\n]|\\.)*\" {
    yylval.str = strdup(yytext);
    return TSTRING_LITERAL;
}


\"([^"\\\n]|\\.)*$ {
    fprintf(stderr, "[ERRO]: String nao foi finalizada de forma certa em %d\n", yylineno);
    exit(1);
}

\'([^\'\\\n]|\\.)\' {
    yylval.cval = yytext[1];
    return TCHAR_CONST;
}


"/*" {
    BEGIN(comment);
    row_count = yylineno;
}

<comment>"*/"    { BEGIN(INITIAL); }

<comment>\n      { yylineno++; }

<comment>.       {}

<comment><<EOF>> {
    fprintf(stderr, "[ERRO]: Comentario nao foi finalizado, na linha %d\n", row_count);
    exit(1);
}

[ \t\n]+       ;

. {
    fprintf(stderr, "[ERRO]: Caractere invalido '%s', na linha %d\n", yytext, yylineno);
   exit(1);
}

%%
