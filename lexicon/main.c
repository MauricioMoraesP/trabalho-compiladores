#include <stdio.h>

extern FILE *yyin;
extern int yylineno;
extern char *yytext;
extern int yylex();

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Uso: %s arquivo_entrada\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin)
    {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    int token;
    while ((token = yylex()) != 0 && token != -1 && token != EOF)
    {
        printf("Encontrado o lexema %s pertencente ao token de codigo %d linha %d\n", yytext, token, yylineno);
    }

    fclose(yyin);
    return 0;
}
