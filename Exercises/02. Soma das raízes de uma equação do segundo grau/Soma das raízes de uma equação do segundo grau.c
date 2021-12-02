#include <stdio.h>
#include <math.h>

int main (int argc, char *argv[]) {
    float a, b, c;
    scanf("%f%f%f", &a, &b, &c);

    float delta = (b * b) - (4 * a * c); 
    
    float root1, root2;
    if (delta == 0) {
        root1 = (-1 * b + sqrt(delta)) / (2 * a);
        root2 = root1;
    } else if (delta > 0) {
        root1 = (-1 * b + sqrt(delta)) / (2 * a);
        root2 = (-1 * b - sqrt(delta)) / (2 * a);
    } else {
        printf("nan");
        return 0;
    }
    printf("%.2f", root1 + root2);
    return 0;
}