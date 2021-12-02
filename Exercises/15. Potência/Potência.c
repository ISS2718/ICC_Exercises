#include <stdio.h>

int main (int argc, char *argv[]) {
    int A, B;
    scanf("%d%d", &A, &B);

    int power = 1;
    for (int i = 0; i < B; i++) {
        power *= A;
    }
    printf("%d", power);
    
    return 0;
}