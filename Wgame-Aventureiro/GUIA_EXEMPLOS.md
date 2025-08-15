# Guia: Alocação Dinâmica de Memória em C

Este repositório contém:

1. **war_game_aventureiro.c**: Um jogo estilo War que demonstra técnicas avançadas de alocação de memória
2. **exemplos_alocacao.c**: Um programa didático simples que ilustra as diferenças entre malloc, calloc e realloc
3. **README.md**: Documentação detalhada sobre o projeto principal

## Como usar o exemplo didático

O arquivo `exemplos_alocacao.c` foi criado para demonstrar de forma clara as diferenças entre as funções de alocação. Para executá-lo:

```bash
gcc -o exemplos_alocacao exemplos_alocacao.c
./exemplos_alocacao
```

O programa irá mostrar:

1. **malloc**: Como a memória não é inicializada e contém "lixo"
2. **calloc**: Como a memória já é inicializada com zeros
3. **realloc**: Como a memória pode ser redimensionada preservando os dados

## Diferenças-chave ilustradas no exemplo

- **malloc** não inicializa a memória, mostrando valores aleatórios
- **calloc** inicializa automaticamente a memória com zeros
- **realloc** preserva os dados existentes ao redimensionar

## Aplicação no projeto principal

O jogo `war_game_aventureiro.c` aplica estes conceitos em um cenário real, escolhendo automaticamente entre malloc e calloc com base no tamanho da alocação para otimizar o desempenho.

## Compile e execute o projeto principal

```bash
gcc -o war_game_aventureiro war_game_aventureiro.c
./war_game_aventureiro
```

---

Para mais detalhes sobre como a alocação de memória é implementada no projeto principal, consulte o README.md.
