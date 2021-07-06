#include<stdio.h>
#include<stdlib.h>
/*

1º bit: furo(1) ou sem furo(0) - menos significativo
2º bit: quadrado(1) ou circular(0)
3º bit: pequeno(1) ou grande(0)
4ª bit: preto(1) ou branco(0)

*/
int checkColumn(int *boardInt, int *pointerWinnerFeature){
    int allFeature = 0B1111;
    int bitColumn;
    int winnerFeature;
    for (int column = 0; column < 4; column++){
        bitColumn = boardInt[column] & boardInt[column + 4] & boardInt[column + 8] & boardInt[column + 12];
        winnerFeature = allFeature & bitColumn;
        if (winnerFeature != 0B0000){ 
            *pointerWinnerFeature = winnerFeature;
        }     
    } 
}

int checkLine(int *boardInt, int *pointerWinnerFeature) {
    int allFeature = 0B1111;
    int bitColumn;
    int winnerFeature;
    for (int column = 0; column <= 12; column + 4){
        bitColumn = boardInt[column] & boardInt[column + 1] & boardInt[column + 2] & boardInt[column + 3];
        winnerFeature = allFeature & bitColumn;
        if (winnerFeature != 0B0000){ 
            *pointerWinnerFeature = winnerFeature;
        }     
    } 
}
int gameOver(int *boardInt){
    int *pointerWinnerFeature;
    int winnerFeature;
    *pointerWinnerFeature = &winnerFeature;
    checkColumn(boardInt, pointerWinnerFeature);
    checkLine(boardInt, pointerWinnerFeature);
    checkPrincipalDiagonal();
    checkSecundaryDiagonal();
}
void makeGameBoard(int *boardInt, char **boardString){
    int piece;
    int positionBoard;
    for (int i = 0; i < 16; i++){
        scanf("%x", &piece);
        scanf("%x", &positionBoard);
        boardInt[positionBoard] = piece;
        boardString[positionBoard] = piece + '0';
        if(gameOver(boardInt)){
            break;
        } 
    } 
}
void makeEmptyBoard(int *boardInt, char **boardString){ 
    for (int i = 0; i < 16; i++){
        boardInt[i] = -1;
    }
    for (int i = 0; i < 16; i++){
        printf("%d", boardInt[i]);
    }   
}
int main(void){
    char boardString[16];
    char *pointerBoardString = boardString;
    int boardInt[16];
    int *pointerBoardInt = boardInt;
    makeEmptyBoard(boardInt, boardString);
    makeGameBoard(boardInt, boardString); 

}
/*
    0   1   2   3
    4   5   6   7
    8   9   10  11
    12  13  14  15
*/