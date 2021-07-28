#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

Data constructorData (char *string) {
    Data d;
    char *data_str = strtok(string, "/");

    d.day = stringToNum(data_str);

    data_str = strtok(NULL, "/");
    d.num_month = stringToNum(data_str);
    convertMonth(d.num_month, &d);

    data_str = strtok(NULL, "/");
    d.year = stringToNum(data_str);
    return d;
}

int stringToNum (char *string) {
    int num = 0;
    int size_str = strlen(string);
    for (int i = 0; i < size_str; i++) {
        int num_str = string[i] - '0';
        int power = 1;
        for (int j = 0; j < (size_str - i - 1); j++) {
            power *= 10;
        }
        num += num_str * power;
    }
    return num;
}

void convertMonth(int month, Data *data) {
    switch (month) {
        case 1:
            strcpy (data->str_month, "janeiro");
            data->str_month[strlen(data->str_month)] = '\0';
            return;

        case 2:
            strcpy (data->str_month, "fevereiro");
            data->str_month[strlen(data->str_month)] = '\0';
            return;

        case 3:
            strcpy (data->str_month, "marco");
            data->str_month[strlen(data->str_month)] = '\0';
            return;
        
        case 4:
            strcpy (data->str_month, "abril");
            data->str_month[strlen(data->str_month)] = '\0';
            return;

        case 5:
            strcpy (data->str_month, "maio");
            data->str_month[strlen(data->str_month)] = '\0';
            return;

        case 6:
            strcpy (data->str_month, "junho");
            data->str_month[strlen(data->str_month)] = '\0';
            return;

        case 7:
            strcpy (data->str_month, "julho");
            data->str_month[strlen(data->str_month)] = '\0';
            return;

        case 8:
            strcpy (data->str_month, "agosto");
            data->str_month[strlen(data->str_month)] = '\0';
            return;

        case 9:
            strcpy (data->str_month, "setembro");
            data->str_month[strlen(data->str_month)] = '\0';
            return;

        case 10:
            strcpy (data->str_month, "outubro");
            data->str_month[strlen(data->str_month)] = '\0';
            return;

        case 11:
            strcpy (data->str_month, "novembro");
            data->str_month[strlen(data->str_month)] = '\0';
            return;

        case 12:
            strcpy (data->str_month, "dezembro");
            data->str_month[strlen(data->str_month)] = '\0';
            return;
    }
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

int verifyData(Data *d) {
    if (d->day != 0 && d->num_month != 0 && d->year != 0){
        if (d->num_month <= 12) {
            int month_Par_Odd = d->num_month % 2;
            if ((d->num_month <= 7 && month_Par_Odd == 1) || (d->num_month >= 8 && month_Par_Odd == 0)) {
                if (d->day <= 31) {
                    return 1;
                }
            }else {
                if (d->num_month == 2) {
                    if (verifyLeapYear(d->year)){
                        if (d->day <= 29) {
                            return 1;
                        }
                    } else if (d->day <= 28) {
                        return 1;
                    }
                } else if (d->day <= 30) {
                    return 1;
                }
            }
        } 
    }  
    return 0;
}

void printData(Data *d) {
    if (verifyData(d)) {
        if (d->day < 10) {
          printf("0%d", d->day);  
        } else {
            printf("%d", d->day);
        }
        printf(" de %s de ", d->str_month);

        if (d->year < 10) {
            printf("000%d\n", d->year);
        } else if (d->year < 100) {
            printf("00%d\n", d->year);
        } else if (d->year < 1000){
            printf("0%d\n", d->year);
        } else {
            printf("%d\n", d->year);
        }
    } else {
        printf("DATA INVALIDA\n");
    }
}