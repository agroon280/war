#include <stdio.h>


typedef struct {
    int ano;
    char marca[20];
}carro;

int main() {
carro* p = (carro*)malloc(sizeof(carro));

strcpy(p->marca, "ford");
p->ano = 1999;

printf("o carro e do ano%d", p->ano);
printf("o modelo do carro e %s",p->marca);
    
return 0;
};