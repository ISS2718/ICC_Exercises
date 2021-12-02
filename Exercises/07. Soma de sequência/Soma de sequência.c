#include <stdio.h>

int main (int argc, char *argv[]) {
    int N, M;
    scanf("%d%d", &N, &M);
    int sum = 0;
    for (int i = N; i <= M; i++) {
        sum += i;
    }
    printf("%d", sum);
    return 0;
}