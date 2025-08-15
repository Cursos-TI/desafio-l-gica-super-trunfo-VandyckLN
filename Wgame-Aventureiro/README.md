# Sistema de Territórios para Jogo de War (Versão Aventureiro Otimizada)

Este projeto implementa um sistema de gerenciamento de territórios para um jogo estilo War, demonstrando diferentes técnicas de alocação dinâmica de memória em C.

## Sobre o Projeto

O sistema permite:

- Cadastrar territórios com nome, cor e quantidade de tropas
- Simular batalhas entre territórios com dados aleatórios
- Adicionar novos territórios dinamicamente durante a execução
- Selecionar automaticamente o método de alocação mais eficiente

## Funções de Alocação Dinâmica no Código

### malloc()

```c
mapa = (Territorio *)malloc(quantidade * sizeof(Territorio));
```

- **O que faz**: Aloca memória sem inicializar
- **Onde é usado**: Para grandes quantidades de territórios (>50)
- **Vantagem**: Mais rápido por não inicializar a memória
- **Desvantagem**: Exige inicialização manual com `memset`

### calloc()

```c
mapa = (Territorio *)calloc(quantidade, sizeof(Territorio));
```

- **O que faz**: Aloca E inicializa memória com zeros
- **Onde é usado**: Para pequenas quantidades de territórios (≤50)
- **Vantagem**: Memória já inicializada, evitando bugs
- **Desvantagem**: Ligeiramente mais lento para grandes alocações

### realloc()

```c
novoMapa = (Territorio *)realloc(mapa, novoTotal * sizeof(Territorio));
```

- **O que faz**: Redimensiona um bloco de memória existente
- **Onde é usado**: Na opção "Adicionar mais territórios" do menu
- **Vantagem**: Preserva os dados dos territórios já cadastrados
- **Desvantagem**: Pode falhar em sistemas com memória fragmentada

### free()

```c
free(mapa);
```

- **O que faz**: Libera memória alocada para reutilização pelo sistema
- **Onde é usado**: Na função `liberarMemoria()` ao finalizar o programa
- **Importância**: Fundamental para evitar vazamentos de memória (memory leaks)

## Seleção Automática Inteligente

O projeto implementa um algoritmo que escolhe automaticamente entre `malloc` e `calloc` baseado em critérios de eficiência:

```c
TipoAlocacao escolherTipoAlocacao(int quantidade, size_t tamanhoElemento) {
    if (quantidade > 50 || tamanhoElemento > 100 || quantidade * tamanhoElemento > 5000) {
        return USAR_MALLOC;  // Para grandes alocações
    } else {
        return USAR_CALLOC;  // Para pequenas alocações
    }
}
```

Esta escolha é baseada em três critérios:

1. **Quantidade de elementos** (>50 favorece malloc)
2. **Tamanho de cada elemento** (>100 bytes favorece malloc)
3. **Tamanho total da alocação** (>5000 bytes favorece malloc)

## Comparativo: malloc vs. calloc no Projeto

| Característica  | malloc()                                  | calloc()                                 |
| --------------- | ----------------------------------------- | ---------------------------------------- |
| Inicialização   | Não inicializa (contém lixo)              | Inicializa todos os bytes com 0          |
| Parâmetros      | `malloc(quantidade * sizeof(Territorio))` | `calloc(quantidade, sizeof(Territorio))` |
| Performance     | Mais rápido para muitos territórios       | Mais lento (inicializa memória)          |
| Segurança       | Exige inicialização manual com memset     | Inicialização automática                 |
| Uso no projeto  | Para >50 territórios                      | Para ≤50 territórios                     |
| Quando realocar | Reavaliado para o novo tamanho total      | Reavaliado para o novo tamanho total     |

## Boas Práticas Demonstradas no Código

1. **Verificação após alocação**:

   ```c
   if (mapa == NULL) {
       printf("Erro na alocacao de memoria! O programa sera encerrado.\n");
       return 1;
   }
   ```

2. **Inicialização adequada após malloc**:

   ```c
   for (int i = 0; i < quantidade; i++) {
       memset(&mapa[i], 0, sizeof(Territorio));
   }
   ```

3. **Verificação após realloc**:

   ```c
   if (novoMapa == NULL) {
       printf("Erro na realocacao de memoria!\n");
       break;
   }
   ```

4. **Liberação de memória ao finalizar**:
   ```c
   liberarMemoria(mapa, tipoAlocacao);
   ```

## Fluxo de Alocação no Projeto

```c
// 1. Declaração do ponteiro
Territorio *mapa = NULL;

// 2. Escolha automática do método de alocação
tipoAlocacao = escolherTipoAlocacao(quantidade, sizeof(Territorio));

// 3. Alocação de memória conforme método escolhido
if (tipoAlocacao == USAR_MALLOC) {
    mapa = (Territorio *)malloc(quantidade * sizeof(Territorio));
    // Inicialização manual necessária
    for (int i = 0; i < quantidade; i++) {
        memset(&mapa[i], 0, sizeof(Territorio));
    }
} else {
    mapa = (Territorio *)calloc(quantidade, sizeof(Territorio));
    // Já inicializado automaticamente
}

// 4. Verificação de sucesso da alocação
if (mapa == NULL) {
    printf("Erro na alocacao de memoria! O programa sera encerrado.\n");
    return 1;
}

// 5. Realocação (quando necessário)
novoMapa = (Territorio *)realloc(mapa, novoTotal * sizeof(Territorio));
if (novoMapa == NULL) {
    printf("Erro na realocacao de memoria!\n");
    break;
}
mapa = novoMapa;

// 6. Liberação ao finalizar
liberarMemoria(mapa, tipoAlocacao);
```

## Executando o Projeto

1. Compile com GCC:

   ```
   gcc -o war_game_aventureiro war_game_aventureiro.c
   ```

2. Execute o programa:
   ```
   ./war_game_aventureiro
   ```

---

_Projeto desenvolvido para estudos de Estruturas de Dados e Alocação Dinâmica de Memória - 15/08/2025_
