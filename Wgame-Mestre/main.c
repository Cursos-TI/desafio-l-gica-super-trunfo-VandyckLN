/**
 * main.c - Função principal do Sistema de Territórios para Jogo de War
 *
 * Descrição: Este programa permite o cadastro, visualização e simulação de batalhas entre territórios,
 *            armazenando informações como nome, cor do exército e quantidade de tropas.
 *            Esta versão utiliza alocação dinâmica de memória com seleção automática inteligente
 *            entre malloc e calloc com base na quantidade de territórios e tamanho das estruturas,
 *            otimizando o desempenho do jogo. Também implementa realocação dinâmica (realloc).
 *
 * Implementação: Versão modularizada com uso de ponteiros e passagem por referência
 * Data: 15/08/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "territorio.h"
#include "alocacao.h"
#include "combate.h"

int main()
{
    int quantidade = 0;
    Territorio *mapa = NULL;
    int opcao = 0;
    int idAtacante, idDefensor;
    TipoAlocacao tipoAlocacao;

    // Inicializa a semente para números aleatórios
    srand(time(NULL));

    printf("===================================\n");
    printf("  SISTEMA DE TERRITORIOS PARA WAR  \n");
    printf("===================================\n\n");

    // Solicita a quantidade de territórios a serem cadastrados
    printf("Informe a quantidade de territorios: ");
    scanf("%d", &quantidade);
    limparBuffer();

    if (quantidade <= 0)
    {
        printf("Quantidade invalida! O programa sera encerrado.\n");
        return 1;
    }

    // Aloca memória para os territórios usando a função modularizada
    mapa = alocarTerritorios(quantidade, &tipoAlocacao);

    // Verificação de falha na alocação
    if (mapa == NULL)
    {
        printf("Erro na alocacao de memoria! O programa sera encerrado.\n");
        return 1;
    }

    // Laço para entrada de dados dos territórios
    for (int i = 0; i < quantidade; i++)
    {
        cadastrarTerritorio(&mapa[i], i, quantidade);
    }

    // Exibe os territórios cadastrados
    listarTerritorios(mapa, quantidade);

    // Menu de opções para simulação de ataques
    do
    {
        printf("===================================\n");
        printf("             MENU                 \n");
        printf("===================================\n");
        printf("1 - Listar territorios\n");
        printf("2 - Realizar ataque\n");
        printf("3 - Adicionar mais territorios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            listarTerritorios(mapa, quantidade);
            break;

        case 2:
            // Solicita os territórios para o ataque
            listarTerritorios(mapa, quantidade);

            printf("Escolha o territorio atacante (1 a %d): ", quantidade);
            scanf("%d", &idAtacante);
            limparBuffer();

            printf("Escolha o territorio defensor (1 a %d): ", quantidade);
            scanf("%d", &idDefensor);
            limparBuffer();

            // Valida as escolhas
            if (idAtacante < 1 || idAtacante > quantidade ||
                idDefensor < 1 || idDefensor > quantidade ||
                idAtacante == idDefensor)
            {
                printf("\nEscolha invalida! Tente novamente.\n\n");
                break;
            }

            // Ajusta os índices (interface usa 1-N, array usa 0-(N-1))
            idAtacante--;
            idDefensor--;

            // Verifica se os territórios pertencem ao mesmo jogador
            if (strcmp(mapa[idAtacante].cor, mapa[idDefensor].cor) == 0)
            {
                printf("\nVoce nao pode atacar um territorio da sua propria cor!\n\n");
                break;
            }

            // Realiza o ataque usando a função modularizada
            atacar(&mapa[idAtacante], &mapa[idDefensor]);

            // Exibe os territórios atualizados
            printf("Estado atual dos territorios envolvidos:\n");
            exibirTerritorio(&mapa[idAtacante], idAtacante);
            exibirTerritorio(&mapa[idDefensor], idDefensor);
            break;

        case 3:
            // Adicionar mais territórios usando realloc
            {
                int novos;
                printf("Quantos novos territorios deseja adicionar? ");
                scanf("%d", &novos);
                limparBuffer();

                if (novos <= 0)
                {
                    printf("Quantidade invalida!\n");
                    break;
                }

                int novoTotal = quantidade + novos;

                // Realoca memória usando a função modularizada
                Territorio *novoMapa = realocarTerritorios(mapa, quantidade, novoTotal, &tipoAlocacao);

                if (novoMapa == NULL)
                {
                    printf("Erro na realocacao de memoria!\n");
                    break;
                }

                mapa = novoMapa;

                // Cadastra os novos territórios
                for (int i = quantidade; i < novoTotal; i++)
                {
                    cadastrarTerritorio(&mapa[i], i, novoTotal);
                }

                quantidade = novoTotal;
                printf("Territorios adicionados com sucesso!\n");
            }
            break;

        case 0:
            printf("\n===== PROGRAMA FINALIZADO =====\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n\n");
            break;
        }

    } while (opcao != 0);

    // Libera a memória alocada
    liberarMemoria(mapa);

    printf("Pressione ENTER para sair...");
    getchar();

    return 0;
}
