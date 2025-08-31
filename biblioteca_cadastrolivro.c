#include <stdio.h>

typedef struct{
 char nome[20];
 char autor[20];
 char editora[20];
 int ediçao;
}cadastro;

int main(){
 cadastro c1 = {"Asa branca", "flavia fontinele", "casabranca", 2018};
 printf("nome do livro: %s \n",c1.nome);
 printf("autor(a): %s \n", c1.autor);
    
return 0;
}