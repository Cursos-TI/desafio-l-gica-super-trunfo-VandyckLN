/**
 * alocacao.h - Definições e protótipos para funções de alocação de memória
 * Parte do Sistema de Territórios para Jogo de War
 */

#ifndef ALOCACAO_H
#define ALOCACAO_H

#include "territorio.h"

// Definição do tipo de alocação
typedef enum
{
    USAR_MALLOC,
    USAR_CALLOC
} TipoAlocacao;

/**
 * Função auxiliar para determinar o melhor tipo de alocação com base na quantidade e tamanho
 *
 * Esta função implementa uma heurística para escolher o método de alocação mais eficiente:
 *
 * - malloc(): Aloca memória sem inicializar, mais rápido para grandes alocações
 * - calloc(): Aloca E inicializa a memória com zeros, mais seguro para pequenas alocações
 *
 * @param quantidade Quantidade de elementos a serem alocados
 * @param tamanhoElemento Tamanho em bytes de cada elemento
 * @return Tipo de alocação recomendado (USAR_MALLOC ou USAR_CALLOC)
 */
TipoAlocacao escolherTipoAlocacao(int quantidade, size_t tamanhoElemento);

/**
 * Função para alocar memória para territórios
 * @param quantidade Quantidade de territórios a alocar
 * @param tipoAlocacao Ponteiro para receber o tipo de alocação escolhido
 * @return Ponteiro para o vetor de territórios alocado ou NULL em caso de falha
 */
Territorio *alocarTerritorios(int quantidade, TipoAlocacao *tipoAlocacao);

/**
 * Função para realocar memória para territórios
 * @param mapa Ponteiro atual para o vetor de territórios
 * @param quantidadeAtual Quantidade atual de territórios
 * @param novaQuantidade Nova quantidade de territórios
 * @param tipoAlocacao Ponteiro para o tipo de alocação (será atualizado se necessário)
 * @return Ponteiro para o novo vetor de territórios realocado ou NULL em caso de falha
 */
Territorio *realocarTerritorios(Territorio *mapa, int quantidadeAtual, int novaQuantidade, TipoAlocacao *tipoAlocacao);

/**
 * Função para liberar a memória alocada para o vetor de territórios
 * @param mapa Ponteiro para o vetor de territórios
 */
void liberarMemoria(Territorio *mapa);

#endif /* ALOCACAO_H */
