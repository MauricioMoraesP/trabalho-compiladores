%{
#include "../syntax/header.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Flex global variables
extern char *yytext;
extern int yylineno;
int lin_ini_com;

extern YYSTYPE yylval;
%}

%option noyywrap yylineno 

DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          ([a-zA-Z]|_)[a-zA-Z0-9_]*

%x comment

%%
"programa"       { return TPROGRAM; }
"car"            { return TCAR; }
"int"            { return TINT; }
"retorne"        { return TRETURN; }
"leia"           { return TREAD; }
"escreva"        { return TWRITE; }
"novalinha"      { return TNEWLINE; }
"se"             { return TIF; }
"entao"          { return TTHEN; }
"senao"          { return TELSE; }
"enquanto"       { return TWHILE; }
"execute"        { return TEXECUTE; }
"e"              { return TAND; }
"ou"             { return TOR; }
"!"              { return TNEG; }
"+"              { return TPLUS; }
"-"              { return TMINUS; }
"*"              { return TTIMES; }
"/"              { return TDIVIDE; }
"="              { return TASSIGN; }
"=="             { return TEQ; }
"!="             { return TNEQ; }
"<"              { return TLT; }
"<="             { return TLEQ; }
">"              { return TGT; }
">="             { return TGEQ; }
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

{DIGIT}+ {
    yylval.ival = atoi(yytext);
    return TINT_CONST;
}

\'([^\'\\\n]|\\.)\' {
    yylval.cval = yytext[1];
    return TCHAR_CONST;
}

\"([^"\\\n]|\\.)*\" {
    yylval.str = strdup(yytext);
    return TSTRING_LITERAL;
}

\"([^"\\\n]|\\.)* {
    fprintf(stderr, "ERRO: CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA %d\n", yylineno);
    return -1;
}

"/*" {
    BEGIN(comment);
    lin_ini_com = yylineno;
}

<comment>"*/"    { BEGIN(INITIAL); }

<comment>\n      { yylineno++; }

<comment>.       {}

<comment><<EOF>> {
    fprintf(stderr, "ERRO: COMENTARIO NAO FINALIZADO %d\n", lin_ini_com);
    return -1;
}

[ \t\r]+        { /* Ignores spaces, tabs, and carriage returns */ }

\n              {}

. {
    fprintf(stderr, "ERRO: CARACTERE INVALIDO '%s' %d\n", yytext, yylineno);
    return -1;
}

%%

