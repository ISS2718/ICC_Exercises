#include <stdio.h>

int verifyLeapYear (int year);

int main (int argc, char *argv[]) {
    int year;
    scanf("%d", &year);
    if (year > 0) {
        printf("%d", verifyLeapYear(year));
    } else {
        printf("-1");
    }
    return 0;
}

int verifyLeapYear (int year) {
    if ((year % 400) == 0) {
        return 1;
    } else if(year % 4 == 0 && year % 100 != 0) {
        return 1;
    } else {
        return 0;
    }
}