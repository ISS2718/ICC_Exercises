#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]){
    int N;
    scanf("%d", &N);
    float a;
    scanf("%f", &a);
    float b;
    scanf("%f", &b);

    float soma = 0;

    for(int i = 0; i < N; i++){
        float x;
        float y;
        scanf("%f", &x);
        scanf("%f", &y);
        float soma_p_2 = (a * x + b - y);
        soma += soma_p_2 * soma_p_2;
    }
    double nota_final = sqrt((double) soma / (N - 2));
    printf("%lf", nota_final);
}
