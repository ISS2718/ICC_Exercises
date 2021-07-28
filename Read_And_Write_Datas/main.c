#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int main (int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    Data datas[n];

    for (int i = 0; i < n; i++) {
        char *data_input = malloc(sizeof(char) * 11);
        scanf("%s", data_input);
        datas[i] = constructorData(data_input);
        free(data_input);
        printData(&datas[i]);
    }
}
