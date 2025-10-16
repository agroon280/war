#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//estrutura para um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// CADASTRO DE TERRITÓRIOS
// Aloca dinamicamente e preenche os dados iniciais
Territorio* cadastrarTerritorios(int numTerritorios) {
    Territorio* mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    printf("\n--- Cadastro de Territorios ---\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("  Nome: ");
        scanf(" %29[^\n]", mapa[i].nome); // Lê a linha inteira, evitando o problema de buffer
        limparBuffer();
        
        printf("  Cor (ex: Vermelho, Azul): ");
        scanf(" %9s", mapa[i].cor);
        limparBuffer();
        
        printf("  Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
    }
    return mapa;
}

//---
// EXIBIÇÃO DE TERRITÓRIOS
// Exibe os dados de todos os territórios
void exibirTerritorios(Territorio* mapa, int numTerritorios) {
    printf("\n--- Estado Atual dos Territorios ---\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("  [%d] Nome: %s, Dono: %s, Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

//---
// FUNÇÃO DE ATAQUE
// Simula um ataque de um território para outro
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- Simulação de Ataque ---\n");
    printf("%s (%s) ataca %s (%s)!\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Simula o lançamento de dados
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("  Dado do Atacante: %d\n", dadoAtacante);
    printf("  Dado do Defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("  O ataque foi bem-sucedido! %s conquistou %s.\n", atacante->nome, defensor->nome);

        // Transfere a cor do atacante
        strcpy(defensor->cor, atacante->cor);

        // Calcula tropas a transferir garantindo que defensor tenha >=1
        int tropasTransferidas = atacante->tropas / 2;      // regra original
        if (tropasTransferidas < 1) tropasTransferidas = 1; // pelo menos 1 para o conquistador

        // Garante que o atacante permaneça com pelo menos 1 tropa
        if (atacante->tropas - tropasTransferidas < 1) {
            tropasTransferidas = atacante->tropas - 1;
            if (tropasTransferidas < 1) {
                // caso extremo (não deveria ocorrer porque o atacante precisa ter >=2 para atacar)
                tropasTransferidas = 1;
            }
        }

        // Aplica transferência
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

        // Segurança extra: não permitir valores negativos
        if (atacante->tropas < 1) atacante->tropas = 1;
        if (defensor->tropas < 1) defensor->tropas = 1;

    } else {
        printf("  O ataque falhou. %s se defendeu com sucesso.\n", defensor->nome);

        // Atacante perde uma tropa, se tiver mais de uma
        if (atacante->tropas > 1) {
            atacante->tropas--;
        } else {
            atacante->tropas = 1; // garante que não chegue a 0
        }
    }
}

//---
// LIBERAÇÃO DE MEMÓRIA
// Libera a memória alocada para os territórios
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemoria liberada com sucesso.\n");
    }
}

//---
// FUNÇÃO PRINCIPAL (MAIN)
int main() {
    srand(time(NULL));
    Territorio* mapa = NULL;
    int numTerritorios = 0;
    int opcao;

    printf("Bem-vindo a simulacao de batalha de territorios!\n");

    do {
        printf("\n----------ESCOLHA UMA DAS OPCOES A SEGUIR----------\n");
        printf("1 - CADASTRO DE TERRITORIOS\n");
        printf("2 - MOSTRAR TERRITORIOS\n");
        printf("3 - ATACAR\n");
        printf("0 - SAIR DO JOGO\n");
        printf("DIGITE UMA OPCAO: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                if (mapa != NULL) {
                    printf("\nTerritorios ja foram cadastrados. Reinicie o jogo para cadastrar novamente.\n");
                } else {
                    printf("Quantos territorios voce deseja criar? ");
                    scanf("%d", &numTerritorios);
                    limparBuffer();
                    mapa = cadastrarTerritorios(numTerritorios);
                }
                break;

            case 2:
                if (mapa == NULL) {
                    printf("\nNao existe territorio ocupado. Cadastre-os primeiro.\n");
                } else {
                    exibirTerritorios(mapa, numTerritorios);
                }
                break;
                
            case 3:
                if (mapa == NULL || numTerritorios < 2) {
                    printf("\nE necessario cadastrar no minimo 2 territorios para atacar.\n");
                } else {
                    int atacante_idx, defensor_idx;
                    exibirTerritorios(mapa, numTerritorios);
                    
                    printf("\nEscolha o territorio atacante (0 a %d): ", numTerritorios - 1);
                    scanf("%d", &atacante_idx);
                    
                    printf("Escolha o territorio defensor (0 a %d): ", numTerritorios - 1);
                    scanf("%d", &defensor_idx);
                    limparBuffer();

                    // Validação de entrada
                    if (atacante_idx < 0 || atacante_idx >= numTerritorios || defensor_idx < 0 || defensor_idx >= numTerritorios) {
                        printf("Escolha invalida. Tente novamente.\n");
                        continue;
                    }

                    // Validação da lógica do jogo
                    if (strcmp(mapa[atacante_idx].cor, mapa[defensor_idx].cor) == 0) {
                        printf("Erro! Nao e possivel atacar um territorio da mesma cor. Tente novamente.\n");
                    } else if (mapa[atacante_idx].tropas < 2) {
                        printf("Erro! O territorio atacante deve ter pelo menos 2 tropas.\n");
                    } else {
                        // Passando ponteiros para as structs atacante e defensor
                        atacar(&mapa[atacante_idx], &mapa[defensor_idx]);
                    }
                }
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}