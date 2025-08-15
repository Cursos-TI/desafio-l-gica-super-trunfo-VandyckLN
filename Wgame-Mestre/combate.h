/**
 * combate.h - Definições e protótipos para funções de combate
 * Parte do Sistema de Territórios para Jogo de War
 */

#ifndef COMBATE_H
#define COMBATE_H

#include "territorio.h"

/**
 * Estrutura para armazenar os resultados dos dados
 */
typedef struct
{
    int dado1;
    int dado2;
    int soma;
} ResultadoDados;

/**
 * Enum para representar o resultado de um ataque
 */
typedef enum
{
    VITORIA_ATACANTE,
    VITORIA_DEFENSOR,
    EMPATE
} ResultadoAtaque;

/**
 * Função para lançar dois dados e retornar o resultado
 * @param resultado Ponteiro para estrutura onde o resultado será armazenado
 */
void lancarDados(ResultadoDados *resultado);

/**
 * Função para simular um ataque entre territórios
 * @param atacante Ponteiro para o território atacante
 * @param defensor Ponteiro para o território defensor
 * @return Resultado do ataque (VITORIA_ATACANTE, VITORIA_DEFENSOR ou EMPATE)
 */
ResultadoAtaque atacar(Territorio *atacante, Territorio *defensor);

/**
 * Função para processar o resultado de um ataque
 * @param atacante Ponteiro para o território atacante
 * @param defensor Ponteiro para o território defensor
 * @param resultadoAtaque Resultado do ataque
 * @param dadosAtacante Resultado dos dados do atacante
 * @param dadosDefensor Resultado dos dados do defensor
 */
void processarResultadoAtaque(
    Territorio *atacante,
    Territorio *defensor,
    ResultadoAtaque resultadoAtaque,
    const ResultadoDados *dadosAtacante,
    const ResultadoDados *dadosDefensor);

#endif /* COMBATE_H */
