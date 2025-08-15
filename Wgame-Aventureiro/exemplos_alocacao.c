#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Exemplo didático: Diferenças entre malloc e calloc
 *
 * Este programa demonstra as diferenças práticas entre
 * malloc, calloc e realloc na alocação de memória.
 */

void demonstrarMalloc()
{
    printf("\n===== DEMONSTRANDO MALLOC =====\n");

    // Aloca array de 5 inteiros com malloc
    int *numeros = (int *)malloc(5 * sizeof(int));

    if (numeros == NULL)
    {
        printf("Erro na alocação com malloc!\n");
        return;
    }

    // Exibe os valores iniciais (contém "lixo" de memória)
    printf("Valores após malloc (sem inicialização):\n");
    for (int i = 0; i < 5; i++)
    {
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }

    // Inicializa manualmente
    printf("\nInicializando manualmente com zeros...\n");
    memset(numeros, 0, 5 * sizeof(int));

    // Exibe após inicialização manual
    printf("Valores após inicialização manual:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }

    free(numeros);
    printf("\nMemória liberada com free()\n");
}

void demonstrarCalloc()
{
    printf("\n===== DEMONSTRANDO CALLOC =====\n");

    // Aloca array de 5 inteiros com calloc
    int *numeros = (int *)calloc(5, sizeof(int));

    if (numeros == NULL)
    {
        printf("Erro na alocação com calloc!\n");
        return;
    }

    // Exibe os valores iniciais (já inicializados com zero)
    printf("Valores após calloc (já inicializados com zero):\n");
    for (int i = 0; i < 5; i++)
    {
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }

    free(numeros);
    printf("\nMemória liberada com free()\n");
}

void demonstrarRealloc()
{
    printf("\n===== DEMONSTRANDO REALLOC =====\n");

    // Aloca array inicial de 3 inteiros
    int *numeros = (int *)malloc(3 * sizeof(int));

    if (numeros == NULL)
    {
        printf("Erro na alocação inicial!\n");
        return;
    }

    // Preenche com valores
    printf("Preenchendo array inicial...\n");
    for (int i = 0; i < 3; i++)
    {
        numeros[i] = (i + 1) * 10;
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }

    // Expande para 5 elementos com realloc
    printf("\nExpandindo para 5 elementos com realloc...\n");
    int *novoArray = (int *)realloc(numeros, 5 * sizeof(int));

    if (novoArray == NULL)
    {
        printf("Erro na realocação!\n");
        free(numeros); // Importante: liberar o array original se realloc falhar
        return;
    }

    numeros = novoArray;

    // Adiciona novos valores
    numeros[3] = 40;
    numeros[4] = 50;

    // Exibe todos os valores após realocação
    printf("Valores após realloc (valores originais preservados):\n");
    for (int i = 0; i < 5; i++)
    {
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }

    free(numeros);
    printf("\nMemória liberada com free()\n");
}

int main()
{
    printf("===================================\n");
    printf("  ALOCAÇÃO DINÂMICA: DEMONSTRAÇÃO \n");
    printf("===================================\n");

    demonstrarMalloc();
    demonstrarCalloc();
    demonstrarRealloc();

    printf("\n===== PROGRAMA FINALIZADO =====\n");
    return 0;
}
