#include <stdio.h>
#include <stdlib.h>
//definindo a struct e colocando os dados
//usando typedef para codigo mais limpo

typedef struct{
 char nome[20];
 char autor[20];
 char editora[20];
 int ediçao;
}cadastro;//cadastro passa a ser o nome que puxa toda a estrutura 
//com uso do typedef

int main(){
//dando valor as variaveis dentro da estrutura de acordo com as variaveis.
 cadastro c1 = {"Asa branca", "flavia fontinele", "casabranca", 2018};
  printf("nome do livro: %s \n",c1.nome);
  printf("Autor(a): %s \n", c1.autor);
    
return 0;
}