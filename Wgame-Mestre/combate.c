/**
 * combate.c - Implementação das funções para combate entre territórios
 * Parte do Sistema de Territórios para Jogo de War
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "combate.h"
#include "territorio.h"

/**
 * Função para lançar dois dados e retornar o resultado
 * Implementa passagem por referência usando ponteiro
 */
void lancarDados(ResultadoDados *resultado)
{
    resultado->dado1 = rand() % 6 + 1;
    resultado->dado2 = rand() % 6 + 1;
    resultado->soma = resultado->dado1 + resultado->dado2;
}

/**
 * Função para simular um ataque entre territórios
 * Implementa passagem por referência usando ponteiros
 */
ResultadoAtaque atacar(Territorio *atacante, Territorio *defensor)
{
    ResultadoDados dadosAtacante, dadosDefensor;
    ResultadoAtaque resultado;

    // Simula a rolagem de dois dados de 1 a 6 para cada lado
    lancarDados(&dadosAtacante);
    lancarDados(&dadosDefensor);

    printf("\n===================================\n");
    printf("        SIMULACAO DE ATAQUE       \n");
    printf("===================================\n");
    printf("Atacante: %s (%s)\n", atacante->nome, atacante->cor);
    printf("  Dados: %d e %d (Total: %d)\n", dadosAtacante.dado1, dadosAtacante.dado2, dadosAtacante.soma);
    printf("Defensor: %s (%s)\n", defensor->nome, defensor->cor);
    printf("  Dados: %d e %d (Total: %d)\n", dadosDefensor.dado1, dadosDefensor.dado2, dadosDefensor.soma);

    // Determina o resultado do ataque
    if (dadosAtacante.soma > dadosDefensor.soma)
    {
        resultado = VITORIA_ATACANTE;
    }
    else if (dadosAtacante.soma < dadosDefensor.soma)
    {
        resultado = VITORIA_DEFENSOR;
    }
    else
    {
        resultado = EMPATE;
    }

    // Processa o resultado do ataque
    processarResultadoAtaque(atacante, defensor, resultado, &dadosAtacante, &dadosDefensor);

    return resultado;
}

/**
 * Função para processar o resultado de um ataque
 * Implementa passagem por referência usando ponteiros
 */
void processarResultadoAtaque(
    Territorio *atacante,
    Territorio *defensor,
    ResultadoAtaque resultadoAtaque,
    const ResultadoDados *dadosAtacante,
    const ResultadoDados *dadosDefensor)
{
    int tropasPerdidas;

    switch (resultadoAtaque)
    {
    case VITORIA_ATACANTE:
        printf("\nResultado: %s venceu o ataque!\n", atacante->nome);

        // Defensor perde 15% das tropas e possivelmente muda de cor
        tropasPerdidas = conquistarTerritorio(defensor, atacante->cor, 15.0);

        // Verifica se a cor do território mudou (ou seja, se as tropas chegaram a zero)
        if (strcmp(defensor->cor, atacante->cor) == 0)
        {
            printf("O territorio %s foi conquistado e agora pertence ao exercito %s\n", defensor->nome, defensor->cor);
        }
        else
        {
            printf("O territorio %s sofreu danos mas manteve sua cor %s\n", defensor->nome, defensor->cor);
        }
        printf("O defensor perdeu %d tropas (15%% do total)\n", tropasPerdidas);
        break;

    case VITORIA_DEFENSOR:
        printf("\nResultado: %s defendeu com sucesso!\n", defensor->nome);

        // Atacante perde 15% das tropas
        tropasPerdidas = reduzirTropas(atacante, 15.0);

        printf("%s perdeu %d tropas no ataque (15%% do total)!\n", atacante->nome, tropasPerdidas);
        break;

    case EMPATE:
        printf("\nResultado: Empate! Ambos os lados mantêm suas posições.\n");

        // Em caso de empate, ambos perdem 5% das tropas
        int tropasPerdidas1 = reduzirTropas(atacante, 5.0);
        int tropasPerdidas2 = reduzirTropas(defensor, 5.0);

        printf("Ambos os lados sofreram baixas!\n");
        printf("%s perdeu %d tropas (5%% do total)\n", atacante->nome, tropasPerdidas1);
        printf("%s perdeu %d tropas (5%% do total)\n", defensor->nome, tropasPerdidas2);
        break;
    }

    printf("===================================\n\n");
}
