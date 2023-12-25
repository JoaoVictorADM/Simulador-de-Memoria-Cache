# Simulador de Memória Cache em C

Este é um simulador de memória cache implementado em linguagem C, capaz de operar com mapeamento direto e associativo. O programa lê um arquivo de instruções (`instrucoes.txt`) que contém os endereços das palavras na memória principal e simula o comportamento da memória cache em resposta a essas instruções.

## Ambiente de Desenvolvimento
Este projeto foi desenvolvido e compilado utilizando exclusivamente o ambiente de desenvolvimento Dev-C++ versão 5.11. Para executar o programa, siga os passos abaixo:

1. Abra o arquivo "ProjetoORG.dev" no Dev-C++.
2. Compile e execute o arquivo "mainProjeto.c" pressionando a tecla "F11".
3. Certifique-se de que os arquivos de texto (`instrucoes.txt` e `memPrincipal.txt`) estão na mesma pasta que o arquivo `.c`.

## Especificações das Memórias

### Memória Principal
- Tamanho total: 256 bytes (linhas do arquivo de texto usado como entrada).
- Palavra: 1 byte (uma palavra por linha).
- Largura do barramento de endereço: 1 byte (busca uma palavra por vez).

### Memória Cache
- Tamanho de cada linha: 4 bytes.
- Total de linhas: 4 (16 bytes de tamanho total).
- Largura do barramento de endereço: 1 byte (o processador requisita uma única palavra da cache).

### Mapeamento Direto
- TAG (R - S): 4 bits.
- Linha (R): 2 bits.
- Palavra (W): 2 bits.
- Quantidade de TAGs: 16.
- Quantidade de blocos: 64.
- Total de endereços que podem ser mapeados para a cache: 256.

### Mapeamento Associativo
- TAG (S): 6 bits.
- Palavra (W): 2 bits.
- Quantidade de blocos: 64.
- Total de endereços que podem ser mapeados para a cache: 256.

## Entrada de Dados

### Arquivos de Entrada
- `instrucoes.txt`: Contém os endereços das palavras na memória principal.
- `memPrincipal.txt`: Representa a memória principal, com cada linha representando uma palavra de 1 byte.

## Execução do Programa

O simulador exibirá em tela as etapas do mapeamento selecionado pelo usuário, mostrando o estado da cache após o fim de cada ciclo de instrução, indicando se ocorreu um cache hit ou miss.

## Saída

O programa também contabiliza a quantidade de hits e misses de cache obtidos para cada função de mapeamento, levando em consideração os algoritmos de substituição no caso do mapeamento associativo.

## Observações

- **Escolha do Mapeamento:**
  O usuário pode escolher entre dois tipos de mapeamento:
  - Mapeamento Direto
  - Mapeamento Associativo

- **Mapeamento Associativo:**
  No caso do mapeamento associativo, o usuário deve indicar qual algoritmo de substituição deseja utilizar:
  - FIFO (First In First Out)
  - LFU (Least Frequently Used)
  - LRU (Least Recently Used)
