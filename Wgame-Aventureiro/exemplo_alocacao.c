/**
 * Exemplo: Demonstração de alocação dinâmica em C
 *
 * Este programa demonstra o uso de malloc, calloc e free
 * com exemplos práticos e visualização da memória.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para visualizar conteúdo da memória
void visualizarMemoria(const void *ptr, size_t tamanho, const char *descricao)
{
    const unsigned char *bytes = (const unsigned char *)ptr;

    printf("\n=== %s ===\n", descricao);
    printf("Endereço: %p\n", ptr);
    printf("Conteúdo (primeiros 20 bytes ou menos):\n");

    for (size_t i = 0; i < (tamanho < 20 ? tamanho : 20); i++)
    {
        printf("%02X ", bytes[i]);
        if ((i + 1) % 8 == 0)
            printf("\n");
    }
    printf("\n");
}

int main()
{
    int tamanho = 10;
    int *array_malloc = NULL;
    int *array_calloc = NULL;
    int *array_realloc = NULL;

    // === Demonstração de malloc ===
    printf("\n== DEMONSTRAÇÃO DE malloc() ==\n");
    array_malloc = (int *)malloc(tamanho * sizeof(int));

    if (array_malloc == NULL)
    {
        printf("Erro: Falha na alocação com malloc\n");
        return 1;
    }

    // Memória não é inicializada (mostra lixo)
    printf("Após malloc (antes de inicializar):\n");
    visualizarMemoria(array_malloc, tamanho * sizeof(int), "MALLOC - Memória não inicializada");

    // Inicialização manual após malloc
    for (int i = 0; i < tamanho; i++)
    {
        array_malloc[i] = i * 10;
    }

    printf("\nApós inicialização manual:\n");
    visualizarMemoria(array_malloc, tamanho * sizeof(int), "MALLOC - Memória inicializada manualmente");

    // === Demonstração de calloc ===
    printf("\n== DEMONSTRAÇÃO DE calloc() ==\n");
    array_calloc = (int *)calloc(tamanho, sizeof(int));

    if (array_calloc == NULL)
    {
        printf("Erro: Falha na alocação com calloc\n");
        free(array_malloc);
        return 1;
    }

    // Calloc já inicializa com zeros
    printf("Após calloc (já inicializado com zeros):\n");
    visualizarMemoria(array_calloc, tamanho * sizeof(int), "CALLOC - Memória inicializada automaticamente");

    // Preenchendo o array calloc
    for (int i = 0; i < tamanho; i++)
    {
        array_calloc[i] = i * 5;
    }

    printf("\nApós preencher os valores:\n");
    visualizarMemoria(array_calloc, tamanho * sizeof(int), "CALLOC - Após preenchimento");

    // === Demonstração de realloc ===
    printf("\n== DEMONSTRAÇÃO DE realloc() ==\n");

    // Expandindo o array malloc usando realloc
    int novo_tamanho = tamanho * 2;
    array_realloc = (int *)realloc(array_malloc, novo_tamanho * sizeof(int));

    if (array_realloc == NULL)
    {
        printf("Erro: Falha na realocação com realloc\n");
        free(array_malloc);
        free(array_calloc);
        return 1;
    }

    // array_malloc é substituído por array_realloc (apontam para o mesmo bloco)
    array_malloc = array_realloc;

    printf("Após realloc (tamanho dobrado):\n");
    printf("Note que os valores originais são preservados!\n");
    visualizarMemoria(array_malloc, novo_tamanho * sizeof(int), "REALLOC - Memória expandida");

    // Inicializa a nova parte do array
    for (int i = tamanho; i < novo_tamanho; i++)
    {
        array_malloc[i] = i * 10;
    }

    printf("\nApós preencher a nova parte do array:\n");
    visualizarMemoria(array_malloc, novo_tamanho * sizeof(int), "REALLOC - Após preenchimento");

    // === Demonstração de free ===
    printf("\n== DEMONSTRAÇÃO DE free() ==\n");
    printf("Liberando memória...\n");

    // Libera memória alocada
    free(array_malloc);
    free(array_calloc);

    printf("Memória liberada com sucesso!\n");
    printf("IMPORTANTE: Depois de free(), os ponteiros ainda existem,\n");
    printf("mas apontam para endereços inválidos (dangling pointers).\n");

    // Boa prática: atribuir NULL após liberar
    array_malloc = NULL;
    array_calloc = NULL;

    printf("\nBoa prática: após free(), atribuímos NULL aos ponteiros.\n");
    printf("array_malloc = %p\n", array_malloc);
    printf("array_calloc = %p\n", array_calloc);

    return 0;
}
