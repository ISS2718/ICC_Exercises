#include <stdio.h>

int main (int argc, char *argv[]) {
    int n = 1;
    int sumPar = 0;
    int sumOdd = 0;
    int sum = 0; 
    while (n != 0) {
        scanf("%d", &n);
        sum += n;
        if (n % 2) {
            sumOdd += n;
        } else {
            sumPar += n;
        }
    }
    printf("%d\n%d\n%d", sumPar, sumOdd, sum);
    return 0;
}