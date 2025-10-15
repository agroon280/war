#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho_max 50
#define max_jog 10

//decidindo os arrays
struct territ{
    char pais[tamanho_max];
    char cor[tamanho_max];
    int tropas_hibri;
    int tropas_terrest;
    int tropas_aerea;
};

 void limparbuff(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
};

int main() {
   struct territ p1[max_jog];
   int opçao;
   int total_territ = 0;

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
           if (total_territ < max_jog){
               printf("DIGITE O NOME DO PAIS: ");
               fgets(p1[total_territ].pais, tamanho_max, stdin);
               p1[total_territ].pais[strcspn(p1[total_territ].pais, "\n")] = 0;

               printf("DIGITE A COR: ");
               fgets(p1[total_territ].cor, tamanho_max, stdin);
               p1[total_territ].cor[strcspn(p1[total_territ].cor, "\n")] = 0;

               printf("DIGITE QUANTIDADE DE TROPAS HIBRIDAS: ");
               scanf("%d", &p1[total_territ].tropas_hibri);
               limparbuff();

               printf("DIGITE O TOTAL DE TROPAS AEREAS: ");
               scanf("%d", &p1[total_territ].tropas_aerea);
               limparbuff();

               printf("DIGITE O TOTAL DE TROPAS TERRESTRES: ");
               scanf("%d", &p1[total_territ].tropas_terrest);
               limparbuff();

        } else{
               printf("TERRITORIOS DOMINADOS COMPLETAMENTE\n");
        }
          total_territ++;

          break;

    case 2:
          printf("INFORMAÇOES DE ESPIOES SOBRE TERRITORIOS\n\n");
          if(total_territ == 0) {
             printf("NAO EXISTE TERRITORIO OCUPADO\n");
        } 
          else {
              for(int i = 0; i < total_territ; i++){
                     printf("\nTERRITORIO ATIVO: %d\n", i +1);
                     printf("PAIS: %s\n", p1[i].pais);
                     printf("COR: %s\n", p1[i].cor);
                     printf("TROPAS HIBRIDAS: %d\n", p1[i].tropas_hibri);
                     printf("TROPAS AEREAS:%d\n", p1[i].tropas_aerea);
                     printf("TROPAS TERRESTRES: %d\n", p1[i].tropas_terrest);
        }
                     printf("PRESSIONE ENTER PARA CONTINUAR A JOGAR.....");
                     getchar();
                     break;
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