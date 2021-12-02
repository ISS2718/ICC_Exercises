#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int itsPrimeNumber (const int n); 

int main (int argc, char *argv[]) {
    int a, b;
    scanf("%d%d", &a, &b);
    
    int maxloop;
    if (a > b) {
        maxloop = a;
    } else {
        maxloop = b;
    }

    int mdc = 1;
    int i = 0;
    while (i < maxloop) {
        if (itsPrimeNumber(i)) {
            while (!(a % i) && !(b % i)) {
                mdc *= i;
                a /= i;
                b /= i;
            }
        }
        i++;
    }
    printf("%d", mdc);
    return 0;
}

int itsPrimeNumber (const int n) {
    if (n == 2 || n == 3) {
        return TRUE;
    }
    if (n <= 1 || n % 2 == 0 || n % 3 == 0) {
        return FALSE;
    }
    int sqrt_n = sqrt(n);
    for (int i = 5; i <= sqrt_n; i++)
    {
        if (n % i == 0){
            return FALSE;
        }    
    }
    return TRUE;
}