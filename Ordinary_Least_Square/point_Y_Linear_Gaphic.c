#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main () {
    int N;
    double a, b;
    scanf("%d", &N);
    scanf("%lf", &a);
    scanf("%lf", &b);
    double *y = malloc(sizeof(double) * N);
    if(y == NULL ) {
        printf("Error: could not allocate y array");
        return -1;
    } 
    for (int i = 0; i < N; i++) {
        double x;
        scanf("%lf", &x);
        y[i] = (a * x) + b;
    }
    for (int i = 0; i < N; i++) {
        printf("y%d: %lf\n", i, y[i]);
        free(&y[i]);
    }
    return 1;
}    