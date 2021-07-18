#include <stdio.h>
#include <math.h>

int main () {
    int N;
    double a, b;
    scanf("%d", &N);
    scanf("%lf", &a);
    scanf("%lf", &b);
    double sum = 0;
    for(int i = 0; i < N; i++) {
        double x;
        double y;
        scanf("%lf", &x);
        scanf("%lf", &y);
        double sum_sqr = (a * x + b - y);
        sum += sum_sqr * sum_sqr;
    }

    double result = sqrt(sum / (N - 2));
    printf("dY: %lf", result);
    return 1;
}
