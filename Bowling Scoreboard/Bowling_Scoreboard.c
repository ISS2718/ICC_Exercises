#include <stdio.h>

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
            int itsPair = !(i % 2);
            if(score[i] == 10 && itsPair){
                i++;
            }
        }
    }

    //ScoreBoard print
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
    //-----

    //Number Score Calculus and print
    int n_score = 0;
    for (int i = 0; i < 21; i++) {
        n_score += score[i];
        
        if (i < 18) { 
            int itsodd = i % 2;
            if (!itsodd && score[i] == 10) {
                i++;
                n_score += score[i + 1];
            
                if(score[i + 1] != 10 || i == 17) {
                    n_score += score[i + 2];
                } else if (i != 17){
                    n_score += score[i + 3];
                }
            } else if (itsodd) {
                if (score[i - 1] + score[i] == 10) {
                    n_score += score[i + 1];
                }
            }
        }
    }
    printf("\n%d", n_score);
    //-----    
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
                if ((b + c) != 10) {
                    _c = c + '0';
                } else {
                    _c = '/';
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