# Instruções.

Este projeto implementa um compilador didático para a linguagem Goianinha. O trabalho abrange a criação da Tabela de Símbolos, do Analisador Léxico e do Analisador Sintático.



### Estrutura de Pastas.

/lexicon - Contém os arquivos para o analisador léxico.

/symbol_table - Contém os arquivos para o analisador sintático.

/symbol_table/utils - Contém os arquivos para a tabela de símbolos.

/syntax - Contém as funções de validação.

### Teste das funções da tabela de síombolos.

No prompt:

```
gcc -o test_symbol_table main.c implementation.c utils/*.c

./test_symbol_table 

```



### Compilando o código

No prompt:
```
make

./parser <nome_do_arquivo>.goianinha
```

### Exemplo de Uso

Para demonstrar o funcionamento do compilador, utilize o seguinte código de exemplo:


**`meu_programa.goianinha`**
```goianinha
programa {
    int a, b, c;

    car d;

    a = 1;
    b = 2;
    c = a + b;

    se (a == b) entao {
        escreva a;
    } senao {
        escreva b;
    }

    enquanto (c > 0) execute {
        c = c - 1;
    }
}

```

