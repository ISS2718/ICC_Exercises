#include <stdio.h>
#include "sum.h"

int main (int argc, char *argv[]) {
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    int result = sum (a, b);
    printf("%d", result);
}
