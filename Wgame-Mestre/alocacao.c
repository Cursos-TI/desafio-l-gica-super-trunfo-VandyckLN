/**
 * alocacao.c - Implementação das funções para alocação de memória
 * Parte do Sistema de Territórios para Jogo de War
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alocacao.h"
#include "territorio.h"

/**
 * Função auxiliar para determinar o melhor tipo de alocação com base na quantidade e tamanho
 */
TipoAlocacao escolherTipoAlocacao(int quantidade, size_t tamanhoElemento)
{
    // Para grandes alocações, malloc é geralmente mais eficiente
    if (quantidade > 50 || tamanhoElemento > 100 || quantidade * tamanhoElemento > 5000)
    {
        return USAR_MALLOC;
    }
    // Para pequenas alocações, calloc é mais seguro e o overhead de inicialização é aceitável
    else
    {
        return USAR_CALLOC;
    }
}

/**
 * Função para alocar memória para territórios
 * Implementa passagem por referência para o tipo de alocação
 */
Territorio *alocarTerritorios(int quantidade, TipoAlocacao *tipoAlocacao)
{
    Territorio *mapa = NULL;

    // Escolhe o tipo de alocação mais adequado
    *tipoAlocacao = escolherTipoAlocacao(quantidade, sizeof(Territorio));

    // Aloca a memória de acordo com o tipo escolhido
    if (*tipoAlocacao == USAR_MALLOC)
    {
        // Aloca memória sem inicializar (mais rápido para grandes blocos)
        mapa = (Territorio *)malloc(quantidade * sizeof(Territorio));

        // Inicialização manual necessária após malloc
        if (mapa != NULL)
        {
            for (int i = 0; i < quantidade; i++)
            {
                memset(&mapa[i], 0, sizeof(Territorio));
            }
        }
    }
    else
    {
        // Aloca E inicializa memória com zeros (mais seguro, ligeiramente mais lento)
        mapa = (Territorio *)calloc(quantidade, sizeof(Territorio));
    }

    return mapa;
}

/**
 * Função para realocar memória para territórios
 * Implementa passagem por referência para o tipo de alocação
 */
Territorio *realocarTerritorios(Territorio *mapa, int quantidadeAtual, int novaQuantidade, TipoAlocacao *tipoAlocacao)
{
    Territorio *novoMapa;

    // Reavalia o método de alocação ideal para o novo tamanho total
    TipoAlocacao novoTipoAlocacao = escolherTipoAlocacao(novaQuantidade, sizeof(Territorio));
    *tipoAlocacao = novoTipoAlocacao; // Atualiza o tipo para futuras realocações

    // Realoca o bloco para o novo tamanho
    novoMapa = (Territorio *)realloc(mapa, novaQuantidade * sizeof(Territorio));

    // Inicializa os novos territórios se necessário e se a realocação foi bem-sucedida
    if (novoMapa != NULL && *tipoAlocacao == USAR_MALLOC)
    {
        for (int i = quantidadeAtual; i < novaQuantidade; i++)
        {
            memset(&novoMapa[i], 0, sizeof(Territorio));
        }
    }

    return novoMapa;
}

/**
 * Função para liberar a memória alocada para o vetor de territórios
 */
void liberarMemoria(Territorio *mapa)
{
    free(mapa);
}
