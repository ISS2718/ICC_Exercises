#include <stdio.h>
#include <math.h>

int main () {
    int N;
    scanf("%d", &N);
    double soma = 0;
    for (int i = 0; i < N; i++){
        double x;
        scanf("%lf", &x);
        soma += x;
    }
    double result = (soma / N);
    printf("%lf", result);
    return 1;
}
