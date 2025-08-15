/**
 * Projeto: Sistema de Territórios para Jogo de War (Versão Aventureiro Otimizada)
 * Descrição: Este programa permite o cadastro, visualização e simulação de batalhas entre territórios,
 *            armazenando informações como nome, cor do exército e quantidade de tropas.
 *            Esta versão utiliza alocação dinâmica de memória com seleção automática inteligente
 *            entre malloc e calloc com base na quantidade de territórios e tamanho das estruturas,
 *            otimizando o desempenho do jogo. Também implementa realocação dinâmica (realloc).
 * Data: 15/08/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
 * - malloc():
 *   - Aloca memória sem inicializar
 *   - Apenas reserva o espaço solicitado
 *   - Mais rápido para grandes alocações
 *   - Prototype: void* malloc(size_t size)
 *
 * - calloc():
 *   - Aloca E inicializa a memória com zeros
 *   - Mais seguro para pequenas alocações
 *   - Evita problemas com lixo de memória
 *   - Prototype: void* calloc(size_t nmemb, size_t size)
 *
 * A escolha se baseia em três critérios:
 * 1. Quantidade de elementos (>50 favorece malloc)
 * 2. Tamanho de cada elemento (>100 bytes favorece malloc)
 * 3. Tamanho total da alocação (>5000 bytes favorece malloc)
 *
 * @param quantidade Quantidade de elementos a serem alocados
 * @param tamanhoElemento Tamanho em bytes de cada elemento
 * @return Tipo de alocação recomendado (USAR_MALLOC ou USAR_CALLOC)
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

/**
 * param e mensagem a ser exibida
 * Função para cadastrar um território no vetor dinâmico
 * @param territorio Ponteiro para o território a ser preenchido
 * @param indice Índice do território no vetor
 * @param total Total de territórios a serem cadastrados
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
 * @param territorio Ponteiro para o território a ser exibido
 * @param indice Índice do território no vetor
 */
void exibirTerritorio(Territorio *territorio, int indice)
{
    printf("Territorio %d: %s\n", indice + 1, territorio->nome);
    printf("  Cor do exercito: %s\n", territorio->cor);
    printf("  Tropas: %d\n", territorio->tropas);
    printf("----------------------------------\n\n");
}

/**
 * Função para listar todos os territórios cadastrados
 * @param mapa Ponteiro para o vetor de territórios
 * @param quantidade Quantidade total de territórios
 */
void listarTerritorios(Territorio *mapa, int quantidade)
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
 * Função para simular um ataque entre territórios
 * @param atacante Ponteiro para o território atacante
 * @param defensor Ponteiro para o território defensor
 */
void atacar(Territorio *atacante, Territorio *defensor)
{
    // Simula a rolagem de dois dados de 1 a 6 para cada lado
    int dadoAtacante1 = rand() % 6 + 1;
    int dadoAtacante2 = rand() % 6 + 1;
    int somaAtacante = dadoAtacante1 + dadoAtacante2;

    int dadoDefensor1 = rand() % 6 + 1;
    int dadoDefensor2 = rand() % 6 + 1;
    int somaDefensor = dadoDefensor1 + dadoDefensor2;

    printf("\n===================================\n");
    printf("        SIMULACAO DE ATAQUE       \n");
    printf("===================================\n");
    printf("Atacante: %s (%s)\n", atacante->nome, atacante->cor);
    printf("  Dados: %d e %d (Total: %d)\n", dadoAtacante1, dadoAtacante2, somaAtacante);
    printf("Defensor: %s (%s)\n", defensor->nome, defensor->cor);
    printf("  Dados: %d e %d (Total: %d)\n", dadoDefensor1, dadoDefensor2, somaDefensor);

    // Determina o vencedor e atualiza os dados dos territórios
    if (somaAtacante > somaDefensor)
    {
        printf("\nResultado: %s venceu o ataque!\n", atacante->nome);

        // Defensor perde 15% das tropas
        int tropasPerdidas = (int)(defensor->tropas * 0.15);
        if (tropasPerdidas < 1)
            tropasPerdidas = 1; // Garante perda mínima de 1 tropa

        // Transfere a cor do exército atacante para o território conquistado
        strcpy(defensor->cor, atacante->cor);

        // Ajusta a quantidade de tropas do defensor após a perda
        defensor->tropas -= tropasPerdidas;
        if (defensor->tropas <= 0)
            defensor->tropas = 1; // Garantir pelo menos 1 tropa

        printf("O territorio %s agora pertence ao exercito %s\n", defensor->nome, defensor->cor);
        printf("O defensor perdeu %d tropas (15%% do total)\n", tropasPerdidas);
    }
    else if (somaAtacante < somaDefensor)
    {
        printf("\nResultado: %s defendeu com sucesso!\n", defensor->nome);

        // Atacante perde 15% das tropas
        int tropasPerdidas = (int)(atacante->tropas * 0.15);
        if (tropasPerdidas < 1)
            tropasPerdidas = 1; // Garante perda mínima de 1 tropa

        atacante->tropas -= tropasPerdidas;
        if (atacante->tropas <= 0)
            atacante->tropas = 1; // Garantir pelo menos 1 tropa

        printf("%s perdeu %d tropas no ataque (15%% do total)!\n", atacante->nome, tropasPerdidas);
    }
    else // Empate
    {
        printf("\nResultado: Empate! Ambos os lados mantêm suas posições.\n");

        // Em caso de empate, ambos perdem 5% das tropas
        int tropasPerdidas1 = (int)(atacante->tropas * 0.05);
        int tropasPerdidas2 = (int)(defensor->tropas * 0.05);

        if (tropasPerdidas1 < 1)
            tropasPerdidas1 = 1;
        if (tropasPerdidas2 < 1)
            tropasPerdidas2 = 1;

        atacante->tropas -= tropasPerdidas1;
        defensor->tropas -= tropasPerdidas2;

        if (atacante->tropas <= 0)
            atacante->tropas = 1;
        if (defensor->tropas <= 0)
            defensor->tropas = 1;

        printf("Ambos os lados sofreram baixas!\n");
        printf("%s perdeu %d tropas (5%% do total)\n", atacante->nome, tropasPerdidas1);
        printf("%s perdeu %d tropas (5%% do total)\n", defensor->nome, tropasPerdidas2);
    }

    printf("===================================\n\n");
}

/**
 * Função para liberar a memória alocada para o vetor de territórios
 * @param mapa Ponteiro para o vetor de territórios
 * @param tipoAlocacao Tipo de alocação utilizada (apenas para referência interna)
 */
void liberarMemoria(Territorio *mapa, TipoAlocacao tipoAlocacao)
{
    /*
     * A função free() libera a memória alocada independentemente do método
     * utilizado na alocação (malloc, calloc ou realloc).
     *
     * O sistema operacional gerencia o pool de memória, e toda memória
     * alocada dinamicamente DEVE ser liberada para evitar memory leaks.
     *
     * Após free(mapa), o ponteiro mapa ainda existe, mas a memória para
     * a qual ele aponta não é mais válida para uso (dangling pointer).
     */
    free(mapa);

    // Nota: não usamos mais o parâmetro tipoAlocacao, mas mantemos por compatibilidade
}

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

    /*
     * Escolha automática do método de alocação de memória
     *
     * O sistema decide automaticamente entre:
     * - malloc: Para grandes quantidades (>50) ou estruturas grandes (>100 bytes)
     *   Vantagem: Mais rápido por não inicializar a memória
     *   Desvantagem: Requer inicialização manual para evitar lixo de memória
     *
     * - calloc: Para pequenas quantidades de dados
     *   Vantagem: Inicializa automaticamente toda a memória com zeros
     *   Desvantagem: Ligeiramente mais lento para grandes alocações
     */
    tipoAlocacao = escolherTipoAlocacao(quantidade, sizeof(Territorio));

    /*
     * Alocação de memória para os territórios
     * --------------------------------------
     * Tamanho de cada território: sizeof(Territorio) bytes
     * Total de memória necessária: quantidade * sizeof(Territorio) bytes
     *
     * Processo de alocação:
     * 1. Se usando malloc: Aloca memória bruta sem inicialização
     * 2. Se usando malloc: É necessário zerar manualmente a memória com memset
     * 3. Se usando calloc: A memória já é alocada e inicializada automaticamente
     */
    if (tipoAlocacao == USAR_MALLOC)
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

    // Verificação de falha na alocação
    if (mapa == NULL)
    {
        printf("Erro na alocacao de memoria! O programa sera encerrado.\n");
        return 1;
    }

    /* Neste ponto, a memória foi alocada com sucesso e:
     * - Se malloc foi usado: A memória foi manualmente zerada com memset
     * - Se calloc foi usado: A memória foi automaticamente zerada
     * Em ambos os casos, a estrutura está pronta para receber os dados
     */

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

            // Realiza o ataque
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
                Territorio *novoMapa;

                /*
                 * Processo de realocação de memória:
                 * 1. Reavaliamos o método de alocação ideal para o novo tamanho total
                 * 2. Usamos realloc para redimensionar o bloco de memória
                 *    - realloc preserva o conteúdo original
                 *    - realloc pode mover o bloco para um novo endereço se necessário
                 *    - realloc retorna NULL se falhar, mantendo o bloco original intacto
                 */
                TipoAlocacao novoTipoAlocacao = escolherTipoAlocacao(novoTotal, sizeof(Territorio));
                tipoAlocacao = novoTipoAlocacao; // Atualiza o tipo para futuras realocações

                // Realoca o bloco para o novo tamanho
                novoMapa = (Territorio *)realloc(mapa, novoTotal * sizeof(Territorio));

                if (novoMapa == NULL)
                {
                    printf("Erro na realocacao de memoria!\n");
                    break;
                }

                mapa = novoMapa;

                // Inicializa os novos territórios se necessário
                if (tipoAlocacao == USAR_MALLOC)
                {
                    for (int i = quantidade; i < novoTotal; i++)
                    {
                        memset(&mapa[i], 0, sizeof(Territorio));
                    }
                }

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
    liberarMemoria(mapa, tipoAlocacao);

    printf("Pressione ENTER para sair...");
    getchar();

    return 0;
}
