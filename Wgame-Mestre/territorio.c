/**
 * territorio.c - Implementação das funções para manipulação de territórios
 * Parte do Sistema de Territórios para Jogo de War
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "territorio.h"

/**
 * Função para limpar o buffer de entrada após leituras com scanf
 */
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * Função para ler uma string com espaços usando fgets e remover o '\n' final
 */
void lerString(char *destino, int tamanho, const char *mensagem)
{
    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);

    // Remove o '\n' do final, se existir
    int len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n')
    {
        destino[len - 1] = '\0';
    }
}

/**
 * Função para cadastrar um território no vetor dinâmico
 */
void cadastrarTerritorio(Territorio *territorio, int indice, int total)
{
    printf("Cadastro do territorio %d de %d:\n", indice + 1, total);
    printf("----------------------------------\n");

    // Leitura do nome do território com espaços
    lerString(territorio->nome, 30, "Nome do territorio: ");

    // Leitura da cor do exército com espaços
    lerString(territorio->cor, 10, "Cor do exercito: ");

    // Leitura da quantidade de tropas
    printf("Quantidade de tropas: ");
    scanf("%d", &territorio->tropas);
    limparBuffer(); // Limpa o buffer após o scanf

    printf("----------------------------------\n\n");
}

/**
 * Função para exibir os dados de um território específico
 */
void exibirTerritorio(const Territorio *territorio, int indice)
{
    printf("Territorio %d: %s\n", indice + 1, territorio->nome);
    printf("  Cor do exercito: %s\n", territorio->cor);
    printf("  Tropas: %d\n", territorio->tropas);
    printf("----------------------------------\n\n");
}

/**
 * Função para listar todos os territórios cadastrados
 */
void listarTerritorios(const Territorio *mapa, int quantidade)
{
    printf("\n===================================\n");
    printf("     TERRITORIOS CADASTRADOS      \n");
    printf("===================================\n\n");

    for (int i = 0; i < quantidade; i++)
    {
        exibirTerritorio(&mapa[i], i);
    }
}

/**
 * Função para transferir o controle de um território para outro exército
 * Implementa passagem por referência usando ponteiro
 */
int conquistarTerritorio(Territorio *territorio, const char *novaCor, float percentualPerda)
{
    int tropasPerdidas = (int)(territorio->tropas * percentualPerda / 100.0);

    // Garante perda mínima de 1 tropa
    if (tropasPerdidas < 1)
    {
        tropasPerdidas = 1;
    }

    // Ajusta a quantidade de tropas do defensor após a perda
    territorio->tropas -= tropasPerdidas;

    // Se as tropas ficaram menores ou iguais a zero, transfere a cor do exército atacante
    if (territorio->tropas <= 0)
    {
        // Transfere a cor do exército atacante para o território conquistado
        strcpy(territorio->cor, novaCor);
        // Garantir pelo menos 1 tropa
        territorio->tropas = 1;
    }

    return tropasPerdidas;
}

/**
 * Função para reduzir tropas de um território após uma derrota
 * Implementa passagem por referência usando ponteiro
 */
int reduzirTropas(Territorio *territorio, float percentualPerda)
{
    int tropasPerdidas = (int)(territorio->tropas * percentualPerda / 100.0);

    // Garante perda mínima de 1 tropa
    if (tropasPerdidas < 1)
    {
        tropasPerdidas = 1;
    }

    // Reduz tropas
    territorio->tropas -= tropasPerdidas;

    // Garantir pelo menos 1 tropa
    if (territorio->tropas <= 0)
    {
        territorio->tropas = 1;
    }

    return tropasPerdidas;
}
