#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Melhoria: Nomes de constantes em MAIÚSCULAS
#define TAM_STRING 100
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100

// Definindo a struct livro
struct livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 0 para não disponível, 1 para disponível
};

struct Emprestimo {
    char nome_usuario[TAM_STRING];
    int indice_livro;
};

// Protótipos das Funções Corrigidos:
// Passando total_livros/total_emprestimos por PONTEIRO para que a mudança persista no main
void limparbuff();
void exibir_menu();
void cadastrar_livro(struct livro *biblioteca, int *total_livros);
void listar_livros(const struct livro *biblioteca, int total_livros);
void realizar_emprestimo(struct livro *biblioteca, int total_livros, struct Emprestimo *emprestimos, int *total_emprestimos);
void listar_emprestimo(const struct livro *biblioteca, int total_livros, const struct Emprestimo *emprestimos, int total_emprestimos);
void liberar_memoria(struct livro *biblioteca, struct Emprestimo *emprestimos);

int main() {
    struct livro *biblioteca;
    struct Emprestimo *emprestimos;

    // Alocação de memória (Correta)
    biblioteca = (struct livro*)calloc(MAX_LIVROS, sizeof(struct livro));
    emprestimos = (struct Emprestimo*)malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memoria.\n");
        // É importante liberar o que foi alocado antes de sair
        free(biblioteca);
        free(emprestimos);
        return 1;
    }

    int total_livros = 0;
    int total_emprestimos = 0;
    int opcao;

    // Inicializa a disponibilidade (Correto)
    for (int i = 0; i < MAX_LIVROS; i++) {
        biblioteca[i].disponivel = 1;
    }

    do {
        exibir_menu();
        // 1. CORREÇÃO: Usar &opcao para ler o valor no scanf
        if (scanf("%d", &opcao) != 1) {
            opcao = -1; // Garante que caia no default em caso de erro de leitura
        }
        limparbuff(); // Limpa o buffer após o scanf

        switch(opcao) {
            case 1:
                // 2. CORREÇÃO: Nome da função e passagem do endereço de total_livros
                cadastrar_livro(biblioteca, &total_livros);
                break;
            
            case 2:
                listar_livros(biblioteca, total_livros);
                break;
                
            case 3:
                printf("REALIZAR EMPRESTIMO\n");
                // 3. CORREÇÃO: Passar total_emprestimos por endereço
                realizar_emprestimo(biblioteca, total_livros, emprestimos, &total_emprestimos);
                break;
            
            case 4:
                printf("LISTA DE EMPRESTIMOS\n");
                // 4. CORREÇÃO: Nome da função e passagem de todos os argumentos
                listar_emprestimo(biblioteca, total_livros, emprestimos, total_emprestimos);
                break;

            case 0:
                printf("SAINDO DO APLICATIVO DA BIBLIOTECA\n");
                break;
            
            default:
                printf("Opcao invalida.\n");
                printf("Pressione Enter para continuar.\n");
                // O limparbuff() acima já "consumiu" a quebra de linha, 
                // mas a função getchar() abaixo vai esperar um novo Enter.
                getchar();
                break;
        } // Fim do switch
    } while (opcao != 0);

    liberar_memoria(biblioteca, emprestimos);
    printf("Memoria liberada com sucesso!\n");
    
    return 0;
}

// Funções Auxiliares:
void exibir_menu() {
    printf("\n========== BIBLIOTECA ==========\n");
    printf("1 - CADASTRAR UM NOVO LIVRO\n");
    printf("2 - VER LIVROS CADASTRADOS\n");
    printf("3 - REALIZAR EMPRESTIMOS\n");
    printf("4 - LISTAR EMPRESTIMOS\n");
    printf("0 - SAIR DA BIBLIOTECA\n");
    printf("==================================\n");
    printf("ESCOLHA UMA OPCAO: ");
}

void limparbuff() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 5. CORREÇÃO na assinatura: Recebe o total por PONTEIRO
void cadastrar_livro(struct livro *biblioteca, int *total_livros) {
    printf("\n--- CADASTRAR LIVRO ---\n");
    // 6. CORREÇÃO: Usa MAX_LIVROS
    if (*total_livros < MAX_LIVROS) {
        // Usa *total_livros para acessar a posição correta
        printf("NOME DO LIVRO: ");
        fgets(biblioteca[*total_livros].nome, TAM_STRING, stdin);
        biblioteca[*total_livros].nome[strcspn(biblioteca[*total_livros].nome, "\n")] = 0;

        printf("AUTOR: ");
        fgets(biblioteca[*total_livros].autor, TAM_STRING, stdin);
        biblioteca[*total_livros].autor[strcspn(biblioteca[*total_livros].autor, "\n")] = 0;
    
        printf("EDITORA: ");
        fgets(biblioteca[*total_livros].editora, TAM_STRING, stdin);
        biblioteca[*total_livros].editora[strcspn(biblioteca[*total_livros].editora, "\n")] = 0;

        printf("EDICAO: ");
        scanf("%d", &biblioteca[*total_livros].edicao);
        limparbuff();
        
        // 7. CORREÇÃO: Incrementa o valor apontado
        (*total_livros)++; 
        printf("Livro cadastrado com sucesso!\n");
    } else {
        printf("Nao ha espaco para cadastrar novos livros.\n");
    }

    printf("Pressione Enter para continuar.\n");
    getchar();
}

void listar_livros (const struct livro *biblioteca, int total_livros) {
    printf("LISTA DE LIVROS CADASTRADOS\n");
    if (total_livros == 0) {
        printf("Nao existe nenhum livro cadastrado.\n");
    } else {
        for(int i = 0; i < total_livros; i++) {
            printf("LIVRO: %d\n", i + 1);
            printf("NOME: %s\n", biblioteca[i].nome);
            printf("AUTOR: %s\n", biblioteca[i].autor);
            printf("EDITORA: %s\n", biblioteca[i].editora);
            printf("EDIÇÃO: %d\n", biblioteca[i].edicao);
            printf("DISPONIBILIDADE: %s\n\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
        }
        printf("-------------------------------------\n");
    }

    printf("\nPressione Enter para continuar.\n");
    getchar();
}

// 8. CORREÇÃO na assinatura: Recebe total_livros por valor e total_emprestimos por PONTEIRO
void realizar_emprestimo (struct livro *biblioteca, int total_livros, struct Emprestimo *emprestimos, int *total_emprestimos) {
    // 9. CORREÇÃO: Usar MAX_EMPRESTIMOS
    if (*total_emprestimos >= MAX_EMPRESTIMOS) {
        printf("LIMITE DE EMPRESTIMOS ATINGIDO.\n");
    } else {
        printf("Livros Disponiveis:\n");
        int disponiveis = 0; // Serve como contador de livros disponíveis
        
        for (int i = 0; i < total_livros; i++) {
            if (biblioteca[i].disponivel) {
                printf("%d - %s\n", i + 1, biblioteca[i].nome);
                disponiveis++;
            }
        }
        
        if (disponiveis == 0) {
            printf("NENHUM LIVRO DISPONIVEL.\n");
        } else {
            printf("Digite o numero do livro que deseja emprestar: ");
            int num_livro;
            scanf("%d", &num_livro);
            limparbuff(); // Limpar buffer após a leitura

            int indice = num_livro - 1;

            if (indice >= 0 && indice < total_livros && biblioteca[indice].disponivel) {
                printf("Digite o nome do usuario que esta pegando o livro: ");
                // Usa *total_emprestimos para a posição correta
                fgets(emprestimos[*total_emprestimos].nome_usuario, TAM_STRING, stdin);
                emprestimos[*total_emprestimos].nome_usuario[strcspn(emprestimos[*total_emprestimos].nome_usuario, "\n")] = 0;

                emprestimos[*total_emprestimos].indice_livro = indice;
                biblioteca[indice].disponivel = 0;
                // 10. CORREÇÃO: Incremento correto do valor apontado
                (*total_emprestimos)++;
                printf("Emprestimo realizado com sucesso.\n");
            } else {
                printf("Numero de livro invalido ou indisponivel no momento.\n");
            }
        }
    }
    printf("Pressione Enter para continuar.\n");
    getchar();
}

// 11. CORREÇÃO na assinatura: Conforme chamada no main
void listar_emprestimo (const struct livro *biblioteca, int total_livros, const struct Emprestimo *emprestimos, int total_emprestimos) {
    if (total_emprestimos == 0) {
        printf("Nenhum emprestimo realizado.\n");
    } else {
        for(int i = 0; i < total_emprestimos; i++) {
            int indice_livro_emprestado = emprestimos[i].indice_livro;
            
            // Verifica se o índice do livro emprestado é válido (segurança)
            if (indice_livro_emprestado >= 0 && indice_livro_emprestado < total_livros) {
                printf("Emprestimo: %d\n", i + 1);
                printf("Livro: %s\n", biblioteca[indice_livro_emprestado].nome);
                printf("Usuario: %s\n", emprestimos[i].nome_usuario);
                printf("-------------------------------------\n");
            } else {
                printf("Emprestimo %d: Livro com indice invalido (%d).\n", i + 1, indice_livro_emprestado);
                printf("-------------------------------------\n");
            }
        }
    }
    printf("Pressione Enter para continuar.\n");
    getchar();
}

void liberar_memoria(struct livro *biblioteca, struct Emprestimo *emprestimos) {
    // 12. CORREÇÃO/BOA PRÁTICA: Uso da função free
    free(biblioteca);
    free(emprestimos);
}