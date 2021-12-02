#include <stdio.h>

int main (int argc, char *argv[]) {
    int N;
    scanf("%d", &N);

    double sum = 0;
    for (int i = 1; i <= N; i++) {
        sum += 1 / (double)(i);
    }
    
    printf("%.4lf", sum);
    return 0;
}