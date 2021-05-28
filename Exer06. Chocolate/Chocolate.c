#include <stdio.h>

int main () {
    int n; // Money
    scanf("%d", &n);
    int c; // Price
    scanf("%d", &c);
    int m;// Packages for exchange
    scanf("%d", &m);

    if(m < 0) {
        m = 1;
    }

    printf("Money: %d, Price of Chocolate: %d, Packaging for exchange: %d \n", n, c, m);

    int purchased_choc = n / c;
    int eaten_choc = 0;
    int package_choc = 0;
    
    for (purchased_choc; purchased_choc > 0; purchased_choc--) {
        eaten_choc++;
        package_choc++;
        if (package_choc >= m) {
            package_choc = package_choc - m; 
            purchased_choc++;
        }
    }
    
    printf("Osmar eaten: %d chocolates", eaten_choc);

    return 1;
}