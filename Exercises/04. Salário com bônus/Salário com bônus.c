#include <stdio.h>


int main (int argc, char *argv[]) {
    float salary, sales;
    scanf("%f%f", &salary, &sales);

    float final_salary = salary + (0.18 * sales);
    printf("%.2f", final_salary);
    return 0;
}