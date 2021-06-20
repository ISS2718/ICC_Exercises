#include <stdio.h>

#define nonebonus 0
#define spare 1
#define strike 3

void print_Score_Table(int a, int b, int c, int n);
void print_score(int n);

int main () {
    int score[21];
    for (int i = 0; i < 21; i++) {
        score[i] = 0;
    }

    for (int i = 0; i < 21; i++) {
        scanf("%d", &score[i]);
        if(i == 19) {
            if ((score[18] + score[19]) < 10) {
                break;
            }
        } else if (i < 18) {
            if(score[i] == 10){
                i++;
            }
        }
    }

    for (int i = 0; i < 19; i+= 2) {
        int a = score[i];
        int b = score[i + 1];
        if(i < 18) {
            print_Score_Table(a, b, 0, i);
        } else {
            int c = score[i + 2];
            print_Score_Table(a, b, c, i);
        }
    }

    int n_score = 0;
    int flag_spare_strike = 0;
    for (int i = 0; i < 19; i++) {
        n_score += score[i];

        if (i % 2 && score[i] < 10) {
            if (score[i] + score[i + 1] == 10) {
                flag_spare_strike = spare;
            } else {
                flag_spare_strike = nonebonus;
            }
        } else if (i % 2) {
            flag_spare_strike = strike;
        }

        if (flag_spare_strike == 1) {
            if(score[i] != 10) {
                n_score += score[i + 1];
            } else {
                n_score += score[i + 2];
            }
            flag_spare_strike = nonebonus;
        } else if (flag_spare_strike == 2) {
            if(score[i] != 10) {
                n_score += score[i + 1];
                if(score[i + 1] != 10) {
                    n_score += score[i + 2];
                }    
            } else {
                n_score += score[i + 3];
            }
        }
    }

    printf("\n%d", n_score);    
}

void print_Score_Table(int a, int b, int c, int n) {
    char _a = '\0';
    char _b = '\0';
    char _c = '\0';

    if(n < 18) {
        if(a == 10) {
            _a = 'X';
            _b = '_';
        } else if ((a + b) == 10) {
            _a = a + '0';
            _b = '/';
        } else {
            _a = a + '0';
            _b = b + '0';
        }
        printf("%c %c | ", _a, _b);
    } else {
        if (a != 10) {
            _a = a + '0';
            if ((a + b) != 10) {
                _b = b + '0';
                printf("%c %c", _a, _b);
                return;
            } else {
                _b = '/';
                if(c != 10) {
                    _c = c + '0';
                } else {
                    _c = 'X';
                }
            }
        } else {
            _a = 'X';
            if (b != 10) {
                _b = b + '0';
                if ((b + c) == 10) {
                    _c = '/';
                } else {
                    _c = c + '0';
                } 
            } else {
                _b = 'X';
                if(c != 10) {
                    _c = c + '0';
                } else {
                    _c = 'X';
                }
                
            }  
        }
        printf ("%c %c %c", _a, _b, _c);
    }
    return;
}