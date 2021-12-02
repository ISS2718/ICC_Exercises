#include <stdio.h>

int main (int argc, char *argv[]) {
    int L, V;
    double M, A;
    scanf("%d%lf%lf%d", &L, &M, &A, &V);

    double value = 0.0;
    if (V > L) {
        value = M;
        value += A * (V - L);
    }
    printf("%.2lf", value);
    return 0;
}