#include <stdio.h>

int main (int argc, char *argv[]) {
    int a;
    scanf("%d", &a);

    if(a > 15 && a < 18) {
        printf("FACULTATIVO");
    } else if (a > 17 && a < 70) {
        printf("OBRIGATORIO");
    } else {
        printf("DISPENSADO");
    }
    
    return 0;
}