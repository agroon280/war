#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo as constantes
#define tamnh_strg 100
#define max_livr 25

// Definindo a struct livro
struct livro {
    char nome[tamnh_strg];
    char autor[tamnh_strg];
    char editora[tamnh_strg];
    int edicao;
};

// Função para limpar o buffer do teclado
void limparbuff() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Declaração do array de structs e da variável de controle
    struct livro biblioteca[max_livr];
    int totalivros = 0;
    int opcao;

    do {
        // Exibindo o menu de opções
        printf("\n========== BIBLIOTECA ==========\n");
        printf("1 - CADASTRAR UM NOVO LIVRO\n");
        printf("2 - VER LIVROS CADASTRADOS\n");
        printf("3 - SAIR DA BIBLIOTECA\n");
        printf("==================================\n");
        printf("ESCOLHA UMA OPCAO: ");
        
        // Lendo a opção do usuário
        scanf("%d", &opcao);
        limparbuff();

        switch (opcao) {
            case 1:
                printf("\n--- CADASTRO DE LIVRO ---\n");
                if (totalivros < max_livr) {
              
                    printf("Nome do livro: ");
                    fgets(biblioteca[totalivros].nome, tamnh_strg, stdin);
                    biblioteca[totalivros].nome[strcspn(biblioteca[totalivros].nome, "\n")] = 0;
                    
                    // Pede e lê o nome do autor
                    printf("Autor: ");
                    fgets(biblioteca[totalivros].autor, tamnh_strg, stdin);
                    biblioteca[totalivros].autor[strcspn(biblioteca[totalivros].autor, "\n")] = 0;
                 
                    // Pede e lê a editora
                    printf("Editora: ");
                    fgets(biblioteca[totalivros].editora, tamnh_strg, stdin);//lê o que digita no teclado
                    biblioteca[totalivros].editora[strcspn(biblioteca[totalivros].editora, "\n")] = 0;
                    //essa funçao vai ler o fgets e trocar o \ n por \ 0 apenas.
                    //A função strcspn(biblioteca[totalivros].editora, "\n") 
                    //olha para a caixa e conta quantos passos ela dá até encontrar a letra \n.
                    
                    // Pede e lê a edição
                    printf("Edicao: ");
                    scanf("%d", &biblioteca[totalivros].edicao);
                    limparbuff();

                    // Incrementa o contador de livros
                    totalivros++;
                    printf("Livro cadastrado com sucesso!\n");
                } else {
                    printf("Nao ha mais espaco para cadastrar novos livros.\n");
                }
                break;
            
            case 2:
                // Esta parte será implementada futuramente
                printf("Opcao em desenvolvimento...\n");
                break;
            
            case 3:
                printf("Saindo da biblioteca. Ate mais!\n");
                break;
            
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 3); // O loop continua até que o usuário escolha a opção 3

    return 0;
}