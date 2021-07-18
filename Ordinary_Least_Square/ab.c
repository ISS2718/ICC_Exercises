#include <stdio.h>
#include <math.h>

int main () {
    int N;
    double m_X, m_Y;
    scanf("%d", &N);
    scanf("%lf", &m_X);
    scanf("%lf", &m_Y);

    double x_deviation = 0;
    double x_deviation_y = 0;
    for (int i = 0; i < N; i++) {
        double x;
        double y;
        scanf("%lf", &x);
        scanf("%lf", &y);
        x_deviation += (x - m_X);
        x_deviation_y += (x - m_X) * y;
    }
    double a;
    if((int) x_deviation != 0) {
        a =  (x_deviation_y / (x_deviation * x_deviation));
    } else {
        a =  x_deviation_y;
    }
    double b = (m_Y - a * m_X);
    printf("a: %lf\nb: %lf", a, b);
    return 1;
} 
 /*

 */