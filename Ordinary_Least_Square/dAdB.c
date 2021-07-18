#include <stdio.h>
#include <math.h>

int main () {
    int N;
    double m_X, dY;
    scanf("%d", &N);
    scanf("%lf", &m_X);
    scanf("%lf", &dY);    

    double sum = 0;
    double x_sqr_sum = 0;
    double x_sqr_deviation = 0;
    for (int i = 0; i < N; i++) {
        double x;
        scanf("%lf", &x);
        double sum_p_2 = x - m_X;
        sum += sum_p_2 * sum_p_2;
        x_sqr_sum += x * x;
        x_sqr_deviation += (x - m_X) * (x - m_X);
    }
    double  result_dA, result_dB;
    if ((int) sum != 0) {
         result_dA = (dY / sqrt(sum));
    } else {
        result_dA = dY;
    }

    if ((int) x_sqr_deviation != 0) {
        result_dB = (sqrt(x_sqr_sum / (N * x_sqr_deviation)) * dY);
    } else {
        result_dB = sqrt(x_sqr_sum/ N) * dY;
    }
       
    printf("dA: %lf, dB: %lf", result_dA, result_dB);
    return 1;
}
