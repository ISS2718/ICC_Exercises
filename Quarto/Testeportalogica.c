#include <stdio.h>

typedef char bool;
void checkbitabit (const int piece1, const int piece2, const int piece3, const int piece4, int *result[]) {

    for(int i = 0; i < 4; i++) {
        bool bit_piece1 = 0b00000001 & piece1 >> i;
        bool bit_piece2 = 0b00000001 & piece2 >> i;
        bool bit_piece3 = 0b00000001 & piece3 >> i;
        bool bit_piece4 = 0b00000001 & piece4 >> i;

        result[i] = ( (!bit_piece1 & !bit_piece2 & !bit_piece3 & !bit_piece4)| 
        (bit_piece1 & bit_piece2 & bit_piece3 & bit_piece4) );
    }
     
}

int main (char *argc, int* argv[]) {
    int a;
    scanf("%d", &a);
    int b;
    scanf("%d", &b);
    int c;
    scanf("%d", &c);
    int d;
    scanf("%d", &d);
    
    int result[4];
    checkbitabit(a, b, c, d, &result);
    printf("-------------------\n");

    for (int i = 3; i > -1; i--) {
        printf("%d \n", result[i]);
    }

  
    /*
    int result = (( (~a) & (~b) & (~c) & (~d) ) | (a & b & c & d));
    printf("%d", result);
   */
   return 1;
}

// 1 0 1 0 = 10
// 0 0 1 1 = 3
// 0 0 1 0 = 2
// 0 0 0 1 = 1


