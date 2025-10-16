#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo as constantes
#define tamnh_strg 100
#define max_livr 50
#define max_emprestimo 100

// Definindo a struct livro
struct livro {
    char nome[tamnh_strg];
    char autor[tamnh_strg];
    char editora[tamnh_strg];
    int edicao;
    int disponivel; // 0 para não disponível, 1 para disponível
};

// Função para limpar o buffer do teclado
void limparbuff() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

struct Emprestimo {
    char nome_usuario[tamnh_strg];
    int indice_livro;
};

int main() {
    struct livro *biblioteca;
    struct Emprestimo *emprestimos;

    biblioteca = (struct livro*)calloc(max_livr, sizeof(struct livro));
    emprestimos = (struct Emprestimo*)malloc(max_emprestimo * sizeof(struct Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("erro ao alocar memoria");
        return 1;
    }

    int total_livros = 0;
    int total_emprestimos = 0;
    int opcao;

    // Inicializa a disponibilidade de todos os livros como 1 (disponível)
    for (int i = 0; i < max_livr; i++) {
        biblioteca[i].disponivel = 1;
    }

    do {
        // Exibindo o menu de opções
        printf("\n========== BIBLIOTECA ==========\n");
        printf("1 - CADASTRAR UM NOVO LIVRO\n");
        printf("2 - VER LIVROS CADASTRADOS\n");
        printf("3 - REALIZAR EMPRESTIMOS\n");
        printf("4 - LISTAR EMPRESTIMOS\n");
        printf("0 - SAIR DA BIBLIOTECA\n");
        printf("==================================\n");
        printf("ESCOLHA UMA OPCAO: ");
        scanf("%d", &opcao);
        limparbuff();
        
        switch(opcao) {
            case 1:
                printf("\n--- CADASTRAR LIVRO ---\n");

                if (total_livros < max_livr) {
                    printf("NOME DO LIVRO: ");
                    fgets(biblioteca[total_livros].nome, tamnh_strg, stdin);
                    biblioteca[total_livros].nome[strcspn(biblioteca[total_livros].nome, "\n")] = 0;

                    printf("AUTOR: ");
                    fgets(biblioteca[total_livros].autor, tamnh_strg, stdin);
                    biblioteca[total_livros].autor[strcspn(biblioteca[total_livros].autor, "\n")] = 0;
                
                    printf("EDITORA: ");
                    fgets(biblioteca[total_livros].editora, tamnh_strg, stdin);
                    biblioteca[total_livros].editora[strcspn(biblioteca[total_livros].editora, "\n")] = 0;

                    printf("EDICAO: ");
                    scanf("%d", &biblioteca[total_livros].edicao);
                    limparbuff();
                    
                    total_livros++;
                    printf("Livro cadastrado com sucesso!\n");
                } else {
                    printf(" Nao ha espaco para cadastrar novos livros.\n ");
                }

                printf("pressione enter para continuar");
                getchar();
                break;
            
            case 2:
                printf("LISTA DE LIVROS CADASTRADOS\n");
                if (total_livros == 0) {
                   printf("nao existe nenhum livro cadastrado\n");
                } else {
                    for(int i = 0; i < total_livros; i++) {
                        printf("LIVRO: %d\n", i + 1);
                        printf("NOME: %s\n", biblioteca[i].nome);
                        printf("AUTOR: %s\n", biblioteca[i].autor);
                        printf("EDITORA: %s\n", biblioteca[i].editora);
                        printf("EDIÇAO: %d\n\n", biblioteca[i].edicao);
                    }
                    printf("-------------------------------------\n");
                }

                printf("\npressione enter para continuar");
                getchar();
                break;
            
            case 3:
                printf("REALIZAR EMPRESTIMO\n");
                if (total_emprestimos >= max_emprestimo) {
                    printf("LIMITE DE EMPRESTIMOS ATINGIDO\n");
                } else {
                    printf("livros Disponiveis\n");
                    int disponiveis = 0;//serve como contador
                    
                    for (int i = 0; i < total_livros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }
                    
                    if (disponiveis == 0) {
                        printf("NENHUM LIVRO DISPONIVEL\n");
                    } else {
                        printf("digite o numero do livro que deseja emprestar: ");
                        int num_livro;
                        scanf("%d", &num_livro);
                        limparbuff();

                        int indice = num_livro - 1;

                        if (indice >= 0 && indice < total_livros && biblioteca[indice].disponivel) {
                            printf("digite o nome do usuario que esta pegando o livro: ");
                            fgets(emprestimos[total_emprestimos].nome_usuario, tamnh_strg, stdin);
                            emprestimos[total_emprestimos].nome_usuario[strcspn(emprestimos[total_emprestimos].nome_usuario, "\n")] = 0;

                            emprestimos[total_emprestimos].indice_livro = indice;
                            biblioteca[indice].disponivel = 0;
                            total_emprestimos++;
                            printf("emprestimo realizado com sucesso\n");
                        } else {
                            printf("numero de livro invalido ou indisponivel no momento\n");
                        }
                    }
                }
                printf("pressione enter para continuar");
                getchar();
                break;
            
            case 4:
                printf("LISTA DE EMPRESTIMOS\n");
                if (total_emprestimos == 0) {
                    printf("nenhum emprestimo realizado\n");
                } else {
                    for(int i = 0; i < total_emprestimos; i++) {
                        int indice_livro_emprestado = emprestimos[i].indice_livro; // Correção
                        printf("Emprestimo: %d\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indice_livro_emprestado].nome);
                        printf("Usuario: %s\n", emprestimos[i].nome_usuario); // Correção
                        printf("-------------------------------------\n");
                    }
                }
                printf("pressione enter para continuar");
                getchar();
                break;

            case 0:
                printf("SAINDO DO APLICATIVO DA BIBLIOTECA\n");
                break;
            
            default:
                printf("opcao invalida\n");
                printf("pressione enter para continuar");
                getchar();
                break;
        } // Fim do switch
    } while (opcao != 0);

    // Mover a liberação de memória para antes do return
    free(biblioteca);
    free(emprestimos);
    printf("memoria liberada com sucesso!\n");
    
    return 0;
}
