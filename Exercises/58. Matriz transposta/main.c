#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    int row, column;
    scanf("%d%d", &row, &column);

    int matrix[row][column];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            scanf("%d", &matrix[i][j]);
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            printf("%d ", matrix[j][i]); 
        }
        printf("\n");
    } 
}