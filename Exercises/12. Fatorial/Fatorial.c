#include <stdio.h>

int main (int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    int fatorial = 1;
    for (int i = n; i > 0; i--) {
        fatorial *= i;
    }
    printf("%d", fatorial);
    return 0;
}