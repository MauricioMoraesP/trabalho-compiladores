# Instruções.

Este projeto implementa um compilador didático para a linguagem Goianinha. O trabalho abrange a criação da Tabela de Símbolos, do Analisador Léxico, o Analisador Sintático e o Analisador Semântico.



### Estrutura de Pastas.

/lexicon - Contém os arquivos para o analisador léxico.

/symbol_table - Contém os arquivos para a tabela de símbolos.

/symbol_table/utils - Contém as funções de validação da tabela de símbolos.

/syntax -  Contém os arquivos para o analisador sintático.

/syntax/utils/dicitionary -  Contém os arquivos do dicionário de dados que foi criado para a AST.

/semantic - Contém os arquivos do semântico.

/semantic/utils - Contém as funções de apoio do semântico.

/tests - Possui os testes do analisador semântico e do léxico dado pelo professor.


### Compilando o código e todos exemplos de teste

No prompt:
```
make

make test
```


