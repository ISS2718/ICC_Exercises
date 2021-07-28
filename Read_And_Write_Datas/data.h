#ifndef __DATA__
#define __DATA__

typedef struct {
    int day;
    int num_month;
    char str_month[12];
    int year;

} Data;

Data constructorData (char *string);
int stringToNum (char *string);
void convertMonth(int month, Data* data);
int verifyData(Data *d);
int verifyLeapYear (int year);
void printData(Data *d);
#endif