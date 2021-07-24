#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    char str [200] = "Olah \n meu \n nome eh \n Isaac";
    char *new_str;
    new_str = strtok(str, "\n");
    strcpy(str, new_str);
    while (new_str != NULL) { 
        new_str = strtok(NULL, "\n");
        if(new_str != NULL) {
            str[strlen(str)-1] = '\0';
            strcat(str, new_str);
        }
    }
    printf("%s", str);
}
