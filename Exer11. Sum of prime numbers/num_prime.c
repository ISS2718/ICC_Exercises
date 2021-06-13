#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int itsPrimeNumber (const int n);

int main (int argc, char *arcgv[]) {
    int n;// number
    scanf ("%d", &n);

    int verify = itsPrimeNumber (n);
    
    if (verify) {
        printf("%d it's a Prime Number", n);
    } else {
        printf("%d it isn't a Prime Number", n);
    }
    
    return 1;
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