#include <stdio.h>

#define BoardSize 4

int main (void) {
    int num;
    scanf("%d", &num);

    int colum = num % BoardSize;
    int line = (num - colum)/ BoardSize;

    printf("%d, %d", line, colum);
}
/*
0  1  2  3
4  5  6  7
8  9  10 11
12 13 14 15

0 % BoardSize = 0
(0 - 0) / BoardSize  = 0

1 % BoardSize = 1
(1 - 1) / BoardSize  = 0

8 % BoardSize = 0
(8 - 0) / BoardSize  = 0

15 % BoardSize = 1
(15 - 1) / BoardSize  = 3
*/