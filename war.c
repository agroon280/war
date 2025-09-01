#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho_max 50
#define max_livr 10

//decidindo os arrays
struct territ{
   char pais[tamanho_max];
   char cor[tamanho_max];
   int tropashibri;
   int tropasterrest;
   int tropasaerea;
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
printf("\n----------ESCOLHA UMA DAS OPÇOES A SEGUIR----------\n");
printf("1 - CADASTRO DA TERRITORIO\n");
printf("2 - MOSTRA OS TERRITORIOS\n");
printf("0 -  SAIR DO JOGO\n");
printf("DIGITE UMA OPÇAO: ");

scanf("%d", &opçao);
limparbuff();

switch (opçao) {
    case 1:
         printf("\n-----------CADASTRO DE CARTA----------\n\n");
           if (total < max_livr){
               printf("DIGITE O NOME DO PAIS: ");
               fgets(p1[total].pais, tamanho_max, stdin);
               p1[total].pais[strcspn(p1[total].pais, "\n")] = 0;
           
               printf("DIGITE A COR: ");
               fgets(p1[total].cor, tamanho_max, stdin);
               p1[total].cor[strcspn(p1[total].cor, "\n")] = 0;

               printf("DIGITE QUANTIDADE DE TROPAS HIBRIDAS: ");
               scanf("%d", &p1[total].tropashibri);
               limparbuff();

               printf("DIGITE O TOTAL DE TROPAS AEREAS: ");
               scanf("%d", &p1[total].tropasaerea);
               limparbuff();

               printf("DIGITE O TOTAL DE TROPAS TERRESTRES: ");
               scanf("%d", &p1[total].tropasterrest);
               limparbuff();

        }     else{
                 printf("TERRITORIOS DOMINADOS COMPLETAMENTE\n");
        }
          total++;

          break;
    case 2:
          printf("INFORMAÇOES DE ESPIOES SOBRE TERRITORIOS\n\n");
          if(total == 0) {
             printf("NAO EXISTE TERRITORIO OCUPADO\n");
        } 
          else {
              for(int i = 0; i < total; i++){
                     printf("\nTERRITORIO ATIVO: %d\n", i +1);
                     printf("PAIS: %s\n", p1[i].pais);
                     printf("COR: %s\n", p1[i].cor);
                     printf("TROPAS HIBRIDAS: %d\n", p1[i].tropashibri);
                     printf("TROPAS AEREAS:%d\n", p1[i].tropasaerea);
                     printf("TROPAS TERRESTRES: %d\n", p1[i].tropasterrest);
        }
                     printf("Pressione Enter.....");
                     getchar();
    }
    case 0:
         printf("SAINDO DO JOGO");
         break; 

    default:
        printf("escolha invalida");
        break;
}

}while (opçao != 0);
return 0;
}