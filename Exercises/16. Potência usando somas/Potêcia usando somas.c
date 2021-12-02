#include <stdio.h>

int multiply (int A, int B);

int main (int argc, char *argv[]) {
    int A, B;
    scanf("%d%d", &A, &B);

    int sumPower = 1;
    for (int i = 0; i < B; i++) {
        sumPower = multiply(sumPower, A);
    }
    printf("%d", sumPower);
    
    return 0;
}

int multiply (int A, int B) {
    int sumMultiply = 0;
    for (int i = 0; i < B; i++) {
        sumMultiply += A;
    }
    return sumMultiply;
}