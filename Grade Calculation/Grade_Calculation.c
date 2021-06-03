#include <stdio.h>

int main(int argc, char *argv[]){
    int k;
    scanf("%d", &k);
    float a;
    scanf("%f", &a);

    float soma_pesos = 0;
    float soma_dir_cima = 0;

    for(int i = 0; i < k; i++){
        float peso;
        float nota;
        scanf("%f", &peso);
        scanf("%f", &nota);
        soma_dir_cima += peso/(nota + a);
        soma_pesos += peso;
    }
    float nota_final = (soma_pesos/soma_dir_cima) - a;
    printf("%.1f", nota_final);
}
