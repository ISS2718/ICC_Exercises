#include <stdio.h>

int main (int argc, char *argv[]) {
    int quant_num;
    scanf("%d", &quant_num);

    int greater_num = 0, smalller_num = 0, sum = 0;
    for (int i = 0; i < quant_num; i++) {
        int num = 0;
        scanf("%d", &num);
        if(i == 0) {
            greater_num = num;
            smalller_num = num;
        } 
        else if (num > greater_num) {
            greater_num = num;
        } 
        else if (num < smalller_num) {
            smalller_num = num;
        }
        sum += num;
    }
    printf("%d\n%d\n%d\n", greater_num, smalller_num, sum);
}