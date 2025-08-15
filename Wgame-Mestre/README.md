# Sistema de Territórios para Jogo de War - Versão Modularizada

## Sobre o Projeto

Este projeto implementa um sistema de gerenciamento de territórios para um jogo inspirado no War, permitindo o cadastro de territórios, simulação de batalhas e gerenciamento dinâmico de tropas. A versão atual foi completamente modularizada e utiliza conceitos avançados de ponteiros e passagem por referência para uma implementação eficiente e organizada.

## Estrutura do Projeto

O projeto foi dividido em módulos, cada um com responsabilidades específicas:

```
Wgame-Desafiante/
│
├── main.c             - Programa principal e menu interativo
├── territorio.h       - Definições de estruturas e funções para territórios
├── territorio.c       - Implementação das funções de territórios
├── alocacao.h         - Definições para funções de alocação dinâmica
├── alocacao.c         - Implementação das funções de alocação
├── combate.h          - Definições para funções de combate
├── combate.c          - Implementação das funções de combate
├── teste.c            - Programa de teste para verificar funções
└── Makefile           - Arquivo para automatizar compilação
```

## Benefícios da Modularização

### 1. Organização do Código

A modularização divide o código em arquivos menores e mais gerenciáveis, cada um com uma responsabilidade específica:

- O módulo `territorio` gerencia a estrutura e manipulação dos territórios
- O módulo `alocacao` cuida da alocação dinâmica de memória
- O módulo `combate` implementa a lógica de batalhas entre territórios

Esta separação torna o código mais organizado e fácil de navegar.

### 2. Reusabilidade

Funções específicas podem ser reutilizadas em diferentes partes do programa sem duplicação de código. Por exemplo, a função `conquistarTerritorio` pode ser chamada em qualquer lugar que precise dessa funcionalidade.

### 3. Manutenção

Modificar uma parte específica do código não afeta outras áreas. Por exemplo, alterar a lógica de combate no módulo `combate.c` não requer modificações em outros módulos.

### 4. Desenvolvimento em Equipe

Múltiplos desenvolvedores podem trabalhar em diferentes módulos simultaneamente sem conflitos.

### 5. Encapsulamento

Cada módulo expõe apenas as funções e estruturas necessárias, escondendo detalhes de implementação.

## Uso de Ponteiros e Endereços

### Passagem por Referência

Uma das principais melhorias na implementação foi o uso de ponteiros para passagem por referência, permitindo que funções modifiquem diretamente os dados originais ao invés de trabalhar com cópias.

#### Exemplos de Passagem por Referência:

1. **Modificação de Territórios Conquistados**

```c
int conquistarTerritorio(Territorio *territorio, const char *novaCor, float percentualPerda) {
    // Modifica diretamente o território através do ponteiro
    strcpy(territorio->cor, novaCor);

    // Calcula e reduz tropas
    int tropasPerdidas = (int)(territorio->tropas * percentualPerda / 100.0);
    if (tropasPerdidas < 1) tropasPerdidas = 1;

    territorio->tropas -= tropasPerdidas;
    if (territorio->tropas <= 0) territorio->tropas = 1;

    return tropasPerdidas;
}
```

Neste exemplo, a função recebe um ponteiro para um `Territorio` e modifica diretamente seus atributos (cor e tropas). Isso é mais eficiente do que receber uma cópia da estrutura e retorná-la modificada, especialmente se a estrutura for grande.

2. **Resultados de Dados para Combate**

```c
void lancarDados(ResultadoDados *resultado) {
    resultado->dado1 = rand() % 6 + 1;
    resultado->dado2 = rand() % 6 + 1;
    resultado->soma = resultado->dado1 + resultado->dado2;
}
```

A função preenche uma estrutura `ResultadoDados` através de um ponteiro, evitando a necessidade de retornar a estrutura completa.

3. **Escolha do Método de Alocação**

```c
Territorio* alocarTerritorios(int quantidade, TipoAlocacao *tipoAlocacao) {
    // Escolhe e armazena o tipo de alocação através do ponteiro
    *tipoAlocacao = escolherTipoAlocacao(quantidade, sizeof(Territorio));
    // ...
}
```

A função retorna um ponteiro para o vetor alocado, mas também atualiza o tipo de alocação escolhido através do ponteiro `tipoAlocacao`.

### Vantagens do Uso de Ponteiros

1. **Eficiência de Memória**: Evita cópias desnecessárias de estruturas grandes.
2. **Múltiplos Valores de Retorno**: Permite que uma função retorne múltiplas informações.
3. **Modificação Direta**: Permite modificar diretamente estruturas de dados complexas.
4. **Controle de Tempo de Vida**: Melhor gerenciamento da vida útil dos objetos.

## Alocação Dinâmica de Memória

O sistema implementa uma estratégia inteligente para escolher entre `malloc` e `calloc` com base no tamanho e quantidade de elementos a serem alocados:

```c
Territorio* alocarTerritorios(int quantidade, TipoAlocacao *tipoAlocacao) {
    *tipoAlocacao = escolherTipoAlocacao(quantidade, sizeof(Territorio));

    if (*tipoAlocacao == USAR_MALLOC) {
        // Aloca com malloc e inicializa manualmente
        // ...
    } else {
        // Aloca e inicializa automaticamente com calloc
        // ...
    }
}
```

## Como Compilar e Executar

1. Para compilar o programa:

   ```
   gcc -Wall -Wextra -std=c99 -o war_game_desafiante main.c territorio.c alocacao.c combate.c
   ```

2. Para executar:

   ```
   .\war_game_desafiante
   ```

3. Para compilar usando o Makefile:

   ```
   make
   ```

4. Para executar o programa de teste:
   ```
   gcc -Wall -Wextra -std=c99 -o teste teste.c territorio.c alocacao.c combate.c
   .\teste
   ```

## Conclusão

A modularização e o uso de ponteiros para passagem por referência transformaram este projeto em uma solução mais robusta, eficiente e fácil de manter. Estas técnicas são fundamentais na programação em C, permitindo um melhor controle sobre o uso de memória e a organização do código.

A aplicação destes conceitos não apenas melhorou a estrutura do código, mas também proporcionou uma implementação que demonstra boas práticas de programação, resultando em um sistema mais confiável e escalável.
