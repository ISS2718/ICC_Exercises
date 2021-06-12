#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]){
    int N;
    scanf("%d", &N);

    float soma = 0;
    for(int i = 0; i < N; i++){
        float x;
        scanf("%f", &x);
        soma += x;
    }

    float nota_final = soma / N;
    printf("%f", nota_final);
}
