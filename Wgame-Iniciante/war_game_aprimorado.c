/**
 * Projeto: Sistema de Territórios para Jogo de War (Versão Aprimorada)
 * Descrição: Este programa permite o cadastro e visualização de 5 territórios,
 *            armazenando informações como nome, cor do exército e quantidade de tropas.
 *            Esta versão possui tratamento melhorado para entrada de strings.
 * Data: 13/08/2025
 */

#include <stdio.h>
#include <string.h>

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

int main()
{
    // Declaração do vetor de estruturas para armazenar 5 territórios
    Territorio territorios[5];

    printf("===================================\n");
    printf("  SISTEMA DE TERRITORIOS PARA WAR  \n");
    printf("===================================\n\n");

    // Laço para entrada de dados dos territórios
    for (int i = 0; i < 5; i++)
    {
        printf("Cadastro do territorio %d de 5:\n", i + 1);
        printf("----------------------------------\n");

        // Leitura do nome do território com espaços
        lerString(territorios[i].nome, 30, "Nome do territorio: ");

        // Leitura da cor do exército com espaços
        lerString(territorios[i].cor, 10, "Cor do exercito: ");

        // Leitura da quantidade de tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBuffer(); // Limpa o buffer após o scanf

        printf("----------------------------------\n\n");
    }

    // Exibição dos dados dos territórios cadastrados
    printf("\n===================================\n");
    printf("     TERRITORIOS CADASTRADOS      \n");
    printf("===================================\n\n");

    for (int i = 0; i < 5; i++)
    {
        printf("Territorio %d: %s\n", i + 1, territorios[i].nome);
        printf("  Cor do exercito: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("----------------------------------\n\n");
    }

    printf("===== PROGRAMA FINALIZADO =====\n");
    printf("Pressione ENTER para sair...");
    getchar();

    return 0;
}
