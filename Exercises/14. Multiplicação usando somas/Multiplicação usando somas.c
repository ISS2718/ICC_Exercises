#include <stdio.h>

int main (int argc, char *argv[]) {
    int A, B;
    scanf("%d%d", &A, &B);

    int sumMultiply = 0;
    for (int i = 0; i < B; i++) {
        sumMultiply += A;
    }
    printf("%d", sumMultiply);
    
    return 0;
}