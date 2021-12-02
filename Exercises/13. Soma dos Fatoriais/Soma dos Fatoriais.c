#include <stdio.h>

int fatorial (int num); 

int main (int argc, char *argv[]) {
    int n;
    scanf("%d", &n);

    int sumFatorial = 0;
    for (int i = 0; i <= n; i++) {
        sumFatorial += fatorial(i);
    }
    
    printf("%d", sumFatorial);
    return 0;
}

int fatorial (const int num) {
    int fatorial = 1;
    for (int i = num; i > 0; i--) {
        fatorial *= i;
    }
    return fatorial;
}