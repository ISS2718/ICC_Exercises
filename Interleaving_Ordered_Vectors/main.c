#include <stdio.h>
#include <stdlib.h>

void VectorOrganization (int A[], int m, int B[], int n, int C[]);

int main (int argc, char *argv[]) {
    int m;
    scanf("%d", &m);
    int A[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &A[i]);
    }

    int n;
    scanf("%d", &n);
    int B[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }
    
    int C[m + n];
    VectorOrganization(A, m, B, n, C);
    

    for (int i = 0; i < m + n; i++) {
        printf("%d ", C[i]);
    }
}

void VectorOrganization (int A[], int m, int B[], int n, int C[]) {
    int count_m = 0;
    int count_n = 0;
    int count_c = 0;
    while (count_c != m + n) {
        if (count_m < m && count_n < n){
            if(A[count_m] < B[count_n]) {
                C[count_c] = A[count_m];
                if(count_c < (m + n)) {
                    count_c++;
                }
                count_m++;
            } else {
                C[count_c] = B[count_n];
                if(count_c < (m + n)) {
                    count_c++;
                }
                count_n++;
            }
        } else if (count_m == m) {
            while (count_n < n) {
                C[count_c] = B[count_n];
                count_c++;
                count_n++;
            }
        } else if (count_n == n) {
            while (count_m < m) {
                C[count_c] = A[count_m];
                count_c++;
                count_m++;
            }
        }
    }
}