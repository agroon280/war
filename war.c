#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho_max 50
#define max_livr 10

//decidindo os arrays
struct territ{
char pais[tamanho_max];
char cor[tamanho_max];
char tropashibri[tamanho_max];
char tropasterrest[tamanho_max];
char tropasaerea[tamanho_max];
};

void limparbuff(){
int c;
while((c = getchar()) != '\n' && c != EOF);
};

int main() {
struct territ p1[max_livr];
int opçao;
int total = 0;

do{
printf("----------ESCOLHA UMA DAS OPÇOES A SEGUIR----------\n");
printf("1 - CADASTRO DA CARTA\n");
printf("2 - MOSTRA OS TERRITORIOS\n");
printf("0 -  SAIR DO JOGO\n");
printf("DIGITE A OPÇAO:");

scanf("%d", &opçao);
limparbuff();

switch (opçao) {
    case 1:
         printf("-----------CADASTRO DE CARTA----------\n\n");
           if (total < max_livr){
           printf("DIGITE O NOME DO PAIS: ");
           fgets(p1[total].pais, tamanho_max, stdin);
           p1[total].pais[strcspn(p1[total].pais, "\n")] = 0;
           
           printf("DIGITE A COR: ");
           fgets(p1[total].cor, tamanho_max, stdin);
           p1[total].cor[strcspn(p1[total].cor, "\n")] = 0;
}
printf("\npressione enter");
getchar();
    break;

default:
    break;
}


}while (opçao != 0);
return 0;
}