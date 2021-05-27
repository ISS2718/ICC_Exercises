#include <stdio.h>

int main () {
    int n; // Money
    scanf("%d", &n);
    int c; // Price
    scanf("%d", &c);
    int m;// Packages
    scanf("%d", &m);

    if(m < 0) {
        m = 1;
    }

    printf("Money: %d, Price of Chocolate: %d, Packaging for exchange: %d \n", n, c, m);

    int purchased_choc = n / c;
    int pakecge_changing = purchased_choc / m;
 
    int eaten_choc = purchased_choc + pakecge_changing;
    printf("Osmar eaten: %d chocolates", eaten_choc);

    return 1;
}