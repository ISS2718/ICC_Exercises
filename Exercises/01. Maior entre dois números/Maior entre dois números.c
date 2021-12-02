#include <stdio.h>

int main (int argc, char *argv[]) {
    int a, b;
    scanf("%d%d", &a, &b);

    if(a > b) {
        printf("%d", a);
    } else {
        printf("%d", b);
    }

    return 0;
}