#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]){
    int N;
    scanf("%d", &N);
    float dY;
    scanf("%f", &dY);
    float m_x = 0;
    scanf("%f", &m_x);

    float soma = 0;
    for(int i = 0; i < N; i++){
        float x;
        scanf("%f", &x);
        float soma_p_2 = x - m_x;
        soma += soma_p_2 * soma_p_2;
    }

    double nota_final = sqrt((double) dY / soma);
    printf("%lf", nota_final);
}
