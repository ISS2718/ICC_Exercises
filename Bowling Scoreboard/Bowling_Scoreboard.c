#include <stdio.h>

void print_Score_Table(int a, int b, int c, int n);
void print_score(int n);

int main () {
    int score[21];
    for (int i = 0; i < 21; i++) {
        score[i] = 0;
    }
    //Input of values
    int i = 0;
    while (i < 21) {
        scanf("%d", &score[i]);

        int strike_flag = 0;
        if(i == 19) {
            if ((score[18] + score[19]) < 10) {
                break;
            }
        } else if (i < 18) {
            int itsPair = !(i % 2);
            if(score[i] == 10 && itsPair){
                strike_flag = 1;
            }
        }

        if(strike_flag == 1) {
            i += 2;
            strike_flag = 0;
        } else {
            i++;
        }
    }
    //----

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
    //----

    //Number Score Calculus and print
    i = 0;
    int n_score = 0;
    while (i < 21) {
        n_score += score[i];
        
        int strike_flag = 0;
        if (i < 18) { 
            int itsodd = i % 2;
            if (!itsodd && score[i] == 10) {
                strike_flag = 1;
                n_score += score[i + 2];
            
                if(score[i + 2] != 10 || i == 17) {
                    n_score += score[i + 3];
                } else if (i != 17){
                    n_score += score[i + 4];
                }
            } else if (itsodd) {
                if (score[i - 1] + score[i] == 10) {
                    n_score += score[i + 1];
                }
            }
        }

        if(strike_flag == 1) {
            i += 2;
            strike_flag = 0;
        } else {
            i++;
        }
    }
    printf("\n%d", n_score);
    //----  
}

void print_Score_Table(int a, int b, int c, int n) {
    char _a = '\0';
    char _b = '\0';
    char _c = '\0';
    int p_exception = 0;

    if (a != 10) {
        _a = a + '0';
        if ((a + b) != 10 && n == 18) {
            _b = b + '0';
            p_exception = 1;
        } else if ((a + b) != 10) {
            _b = b + '0';
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
            if(n < 18) {
                _b = '_';
            }else {
               _b = b + '0';  
            }
            
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
    if (p_exception) {
        printf("%c %c", _a, _b);
    } else if (n < 18) {
        printf("%c %c | ", _a, _b);
    } else {
        printf ("%c %c %c", _a, _b, _c);
    }
    return;
}