#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes para o Sistema de Missões
#define MAX_JOGADORES 2
#define TAM_MISSAO 100

// Vetor de Missões
const char *MISSOES[] = {
    "Conquistar o territorio 'Ilha Deserta'.",
    "Ter 5 ou mais territorios sob seu controle.",
    "Eliminar todas as tropas da cor 'Vermelho'.",
    "Ter 10 tropas em um unico territorio."
};
const int TOTAL_MISSOES = 4;

// Estrutura para um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções de Missão
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes);
int verificarMissao(const char* missao, const Territorio* mapa, int tamanho, const char* corJogador);
void exibirMissao(const char* missao);

// Função para limpar o buffer do teclado
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// CADASTRO DE TERRITÓRIOS (Mantida)
Territorio* cadastrarTerritorios(int numTerritorios) {
    Territorio* mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    
    char buffer[100]; 

    printf("\n--- Cadastro de Territorios ---\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        
        printf("  Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("  Cor (ex: Vermelho, Azul): ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;
        
        printf("  Tropas: ");
        if (fgets(buffer, 100, stdin) == NULL || sscanf(buffer, "%d", &mapa[i].tropas) != 1) {
            mapa[i].tropas = 1; 
            printf("AVISO: Entrada invalida. Tropas definidas para 1.\n");
        }
        if (mapa[i].tropas < 1) mapa[i].tropas = 1;
    }
    return mapa;
}

//---
// EXIBIÇÃO DE TERRITÓRIOS (Mantida)
void exibirTerritorios(Territorio* mapa, int numTerritorios) {
    printf("\n--- Estado Atual dos Territorios ---\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("  [%d] Nome: %s, Dono: %s, Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

//---
// FUNÇÃO DE ATAQUE (ATUALIZADA)
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- Simulação de Ataque ---\n");
    printf("%s (%s) com %d tropas ataca %s (%s) com %d tropas!\n", 
           atacante->nome, atacante->cor, atacante->tropas, defensor->nome, defensor->cor, defensor->tropas);

    // Simula o lançamento de dados
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("  Dado do Atacante: %d\n", dadoAtacante);
    printf("  Dado do Defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("  VITORIA! O ataque foi bem-sucedido! %s conquistou %s.\n", atacante->nome, defensor->nome);

        // 1. Transfere a cor do atacante
        strcpy(defensor->cor, atacante->cor);

        // 2. Lógica de Transferência: Transfere exatamente 1 tropa.
        int tropasMovidas = 1;
        
        // A validação no main garante que atacante.tropas >= 2
        
        // 3. Aplica Transferência
        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;
        
        // Segurança extra (embora a validação do main previna):
        if (atacante->tropas < 1) atacante->tropas = 1; 
        if (defensor->tropas < 1) defensor->tropas = 1; 

    } else {
        printf("  DERROTA. O ataque falhou. %s se defendeu com sucesso.\n", defensor->nome);

        // Perde exatamente 1 tropa, mas nunca menos de 1
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("  %s perdeu 1 tropa.\n", atacante->nome);
        } else {
            printf("  %s tem apenas 1 tropa e se manteve na defesa.\n", atacante->nome);
        }
    }
}

//---
// IMPLEMENTAÇÃO DAS FUNÇÕES DE MISSÃO (Mantidas)
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

void exibirMissao(const char* missao) {
    if (missao) {
        printf("=> MISSAO SECRETA: %s\n", missao);
    } else {
        printf("Nenhuma missao atribuida.\n");
    }
}

int verificarMissao(const char* missao, const Territorio* mapa, int tamanho, const char* corJogador) {
    // 1. Missão: Conquistar o territorio 'Ilha Deserta'.
    if (strstr(missao, "Ilha Deserta") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strstr(mapa[i].nome, "Ilha Deserta") != NULL) {
                if (strcmp(mapa[i].cor, corJogador) == 0) {
                    return 1;
                }
            }
        }
    }

    // 2. Missão: Ter 5 ou mais territorios sob seu controle.
    if (strstr(missao, "5 ou mais territorios") != NULL) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                count++;
            }
        }
        if (count >= 5) {
            return 1;
        }
    }

    // 3. Missão: Eliminar todas as tropas da cor 'Vermelho'.
    if (strstr(missao, "Eliminar todas as tropas da cor 'Vermelho'") != NULL) {
        if (strcmp(corJogador, "Azul") == 0) {
            int inimigo_existe = 0;
            for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i].cor, "Vermelho") == 0) {
                    inimigo_existe = 1;
                    break;
                }
            }
            if (!inimigo_existe) {
                return 1;
            }
        }
    }

    // 4. Missão: Ter 10 tropas em um unico territorio.
    if (strstr(missao, "10 tropas em um unico territorio") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 10) {
                return 1;
            }
        }
    }
    
    return 0;
}


//---
// LIBERAÇÃO DE MEMÓRIA (Mantida)
void liberarMemoria(Territorio* mapa, char** missoesJogadores) {
    if (mapa != NULL) {
        free(mapa);
    }
    
    if (missoesJogadores != NULL) {
        for (int i = 0; i < MAX_JOGADORES; i++) {
            if (missoesJogadores[i] != NULL) {
                free(missoesJogadores[i]);
            }
        }
        free(missoesJogadores);
    }

    printf("\nMemoria liberada com sucesso.\n");
}

//---
// FUNÇÃO PRINCIPAL (MAIN) (Mantida)
int main() {
    srand(time(NULL));
    Territorio* mapa = NULL;
    int numTerritorios = 0;
    int opcao;
    
    char** missoesJogadores = (char**)calloc(MAX_JOGADORES, sizeof(char*));
    char* corJogadorPrincipal = "Azul";
    
    if (missoesJogadores == NULL) {
        printf("Erro ao alocar memoria para as missoes.\n");
        return 1;
    }
    
    for (int i = 0; i < MAX_JOGADORES; i++) {
        missoesJogadores[i] = (char*)malloc(TAM_MISSAO * sizeof(char));
        if (missoesJogadores[i] == NULL) {
            printf("Erro ao alocar memoria para a missao do jogador %d.\n", i);
            for (int j = 0; j < i; j++) free(missoesJogadores[j]);
            free(missoesJogadores);
            return 1;
        }
    }

    printf("Bem-vindo a simulacao de batalha de territorios!\n");

    do {
        // --- Verifica Vencedor antes de prosseguir (Exibição Condicional) ---
        if (mapa != NULL) {
            if (verificarMissao(missoesJogadores[0], mapa, numTerritorios, corJogadorPrincipal)) {
                printf("\n=========================================================\n");
                printf("!!! JOGADOR %s VENCEU! MISSAO CUMPRIDA: %s !!!\n", corJogadorPrincipal, missoesJogadores[0]);
                printf("=========================================================\n");
                opcao = 0;
                continue;
            }
        }
        // -------------------------------------------------------------------

        printf("\n----------ESCOLHA UMA DAS OPCOES A SEGUIR----------\n");
        printf("1 - CADASTRO DE TERRITORIOS\n");
        printf("2 - MOSTRAR TERRITORIOS\n");
        printf("3 - ATACAR\n");
        printf("4 - MOSTRAR MISSAO SECRETA (%s)\n", corJogadorPrincipal);
        printf("0 - SAIR DO JOGO\n");
        printf("DIGITE UMA OPCAO: ");

        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                if (mapa != NULL) {
                    printf("\nTerritorios ja foram cadastrados. Reinicie o jogo para cadastrar novamente.\n");
                } else {
                    printf("Quantos territorios voce deseja criar? ");
                    if (scanf("%d", &numTerritorios) != 1 || numTerritorios < 2) {
                        printf("Entrada invalida ou numero de territorios menor que 2. Abortando.\n");
                        numTerritorios = 0;
                    }
                    limpar_buffer();
                    if (numTerritorios >= 2) {
                        mapa = cadastrarTerritorios(numTerritorios);
                        atribuirMissao(missoesJogadores[0], MISSOES, TOTAL_MISSOES);
                        printf("\nMISSAO SECRETA ATRIBUIDA AO JOGADOR %s!\n", corJogadorPrincipal);
                    }
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
                    limpar_buffer();

                    if (atacante_idx < 0 || atacante_idx >= numTerritorios || defensor_idx < 0 || defensor_idx >= numTerritorios) {
                        printf("Escolha invalida. Tente novamente.\n");
                        continue;
                    }

                    if (atacante_idx == defensor_idx) {
                        printf("Erro! Nao e possivel atacar o proprio territorio. Tente novamente.\n");
                    } else if (strcmp(mapa[atacante_idx].cor, mapa[defensor_idx].cor) == 0) {
                        printf("Erro! Nao e possivel atacar um territorio da mesma cor. Tente novamente.\n");
                    } else if (mapa[atacante_idx].tropas < 2) {
                        printf("Erro! O territorio atacante deve ter pelo menos 2 tropas.\n");
                    } else {
                        atacar(&mapa[atacante_idx], &mapa[defensor_idx]);
                    }
                }
                break;
            
            case 4:
                if (missoesJogadores[0] != NULL) {
                    printf("\n--- MISSAO SECRETA DO JOGADOR %s ---\n", corJogadorPrincipal);
                    exibirMissao(missoesJogadores[0]);
                    printf("--------------------------------------\n");
                } else {
                    printf("Cadastre os territorios para que a missao seja atribuida.\n");
                }
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarMemoria(mapa, missoesJogadores);
    return 0;
}