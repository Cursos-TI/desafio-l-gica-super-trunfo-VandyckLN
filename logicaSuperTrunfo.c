#include <stdio.h>
#include <string.h>
// Desafio Super Trunfo - Países
// Tema 2 - Comparação das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de comparação de cartas de cidades. 
// Siga os comentários para implementar cada parte do desafio.

/**
 * Projeto: Sistema de Territórios para Jogo de War
 * Descrição: Este programa permite o cadastro e visualização de 5 territórios,
 *            armazenando informações como nome, cor do exército e quantidade de tropas.
 * Data: 13/08/2025
 */




/**
 * Definição da estrutura Territorio que armazena:
 * - nome: nome do território (até 29 caracteres + '\0')
 * - cor: cor do exército que ocupa o território (até 9 caracteres + '\0')
 * - tropas: quantidade de tropas no território
 */
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int principal()
{
    // Declaração do vetor de estruturas para armazenar 5 territórios
    Territorio territorios[5];

    printf("===== CADASTRO DE TERRITORIOS =====\n\n");

    // Laço para entrada de dados dos territórios
    for (int i = 0; i < 5; i++)
    {
        printf("Cadastro do territorio %d:\n", i + 1);

        // Leitura do nome do território
        printf("Nome do territorio: ");
        scanf("%29s", territorios[i].nome);

        // Limpar o buffer de entrada
        fflush(stdin);

        // Leitura da cor do exército
        printf("Cor do exercito: ");
        scanf("%9s", territorios[i].cor);

        // Leitura da quantidade de tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados dos territórios cadastrados
    printf("\n===== TERRITORIOS CADASTRADOS =====\n\n");

    for (int i = 0; i < 5; i++)
    {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do exercito: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("\n");
    }

    printf("===== FIM DO PROGRAMA =====\n");

    return 0;
}
