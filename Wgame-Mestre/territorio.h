/**
 * territorio.h - Definições e protótipos para manipulação de territórios
 * Parte do Sistema de Territórios para Jogo de War
 */

#ifndef TERRITORIO_H
#define TERRITORIO_H

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
void limparBuffer();

/**
 * Função para ler uma string com espaços usando fgets e remover o '\n' final
 * @param destino Ponteiro para o destino onde a string será armazenada
 * @param tamanho Tamanho máximo da string (incluindo '\0')
 * @param mensagem Mensagem de prompt a ser exibida ao usuário
 */
void lerString(char *destino, int tamanho, const char *mensagem);

/**
 * Função para cadastrar um território no vetor dinâmico
 * @param territorio Ponteiro para o território a ser preenchido
 * @param indice Índice do território no vetor
 * @param total Total de territórios a serem cadastrados
 */
void cadastrarTerritorio(Territorio *territorio, int indice, int total);

/**
 * Função para exibir os dados de um território específico
 * @param territorio Ponteiro para o território a ser exibido
 * @param indice Índice do território no vetor
 */
void exibirTerritorio(const Territorio *territorio, int indice);

/**
 * Função para listar todos os territórios cadastrados
 * @param mapa Ponteiro para o vetor de territórios
 * @param quantidade Quantidade total de territórios
 */
void listarTerritorios(const Territorio *mapa, int quantidade);

/**
 * Função para transferir o controle de um território para outro exército
 * @param territorio Ponteiro para o território a ser conquistado
 * @param novaCor String contendo a cor do novo exército controlador
 * @param percentualPerda Percentual de tropas que serão perdidas (0-100)
 * @return Quantidade de tropas perdidas
 */
int conquistarTerritorio(Territorio *territorio, const char *novaCor, float percentualPerda);

/**
 * Função para reduzir tropas de um território após uma derrota
 * @param territorio Ponteiro para o território que perderá tropas
 * @param percentualPerda Percentual de tropas que serão perdidas (0-100)
 * @return Quantidade de tropas perdidas
 */
int reduzirTropas(Territorio *territorio, float percentualPerda);

#endif /* TERRITORIO_H */
