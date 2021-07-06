#include<stdio.h>
#include<stdlib.h>

#define BoardSize 4
#define NumberOfProperties 4

void PrintInBinary(int Decimal) {
	int Current = Decimal;
	for (int i = 0; i < NumberOfProperties; i++) {
		printf("%d", Current % 2);
		Current /= 2;
	}
}

typedef struct Cell {
	int IsEmpity;
	int Piece;
}Cell;

void InitializeCell(Cell* C) {
	C->IsEmpity = 1;
	C->Piece = -1;
}

void PlacePieceOnCell(Cell* C, int Piece) {
	C->Piece = Piece;
	C->IsEmpity = 0;
}

void PrintCell(Cell* C) {
	PrintInBinary(C->Piece);
	printf(" | ");
}

typedef struct Board {
	Cell Cells[BoardSize][BoardSize];
	int RemainingPieces[BoardSize * BoardSize];
}Board;

void InitializeBoard(Board* B) {
	for (int i = 0; i < BoardSize; i++){
		for (int j = 0; j < BoardSize; j++) {
			InitializeCell(&(B->Cells[i][j]));
		}
	}
	for (int i = 0; i < BoardSize * BoardSize; i++) {
		B->RemainingPieces[i] = i;
	}
}

typedef struct Position {
	int Row;
	int Collum;
}Position;

void PlacePieceOnBoard(Board* B, int Piece, Position Pair) {
	PlacePieceOnCell(&(B->Cells[Pair.Row][Pair.Collum]), Piece);
	B->RemainingPieces[Piece] = -1;
}

void PrintBoard(Board* B) {
	printf("\nBoard:\n");
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			PrintCell(&(B->Cells[i][j]));
		}
		printf("\n\n");
	}
}

void PrintRemainingPieces(Board* B) {
	printf("Remaining Pieces: ");
	for (int i = 0; i < BoardSize * BoardSize; i++) {
		if (B->RemainingPieces[i] >= 0) {
			PrintInBinary(i);
			printf("=%d ", i);
		}
	}
	printf("\n\n");
}

int RowIsComplete(Board* B, int Row) {
	for (int i = 0; i < BoardSize; i++) {
		if (B->Cells[Row][i].IsEmpity) {
			return 0;
		}
	}
	return 1;
}

int CheckRowForWinner(Board* B, int Row) {
	if (RowIsComplete(B, Row)) {
		int CompletedWith1 = B->Cells[Row][0].Piece;
		int CompletedWith0 = ~(B->Cells[Row][0].Piece);
		for (int i = 1; i < BoardSize; i++) {
			CompletedWith1 &= B->Cells[Row][i].Piece;
			CompletedWith0 &= ~(B->Cells[Row][i].Piece);
		}
		return (CompletedWith1 | CompletedWith0);
	}
	return 0;
}

int CollumIsComplete(Board* B, int Collum) {
	for (int i = 0; i < BoardSize; i++) {
		if (B->Cells[i][Collum].IsEmpity) {
			return 0;
		}
	}
	return 1;
}

int CheckCollumForWinner(Board* B, int Collum) {
	if (CollumIsComplete(B, Collum)) {
		int CompletedWith1 = B->Cells[0][Collum].Piece;
		int CompletedWith0 = ~(B->Cells[0][Collum].Piece);
		for (int i = 1; i < BoardSize; i++) {
			CompletedWith1 &= B->Cells[i][Collum].Piece;
			CompletedWith0 &= ~(B->Cells[i][Collum]).Piece;
		}
		return (CompletedWith1 | CompletedWith0);
	}
	return 0;
}

int MainDiagonalIsComplete(Board* B) {
	for (int i = 0; i < BoardSize; i++) {
		if (B->Cells[i][i].IsEmpity) {
			return 0;
		}
	}
	return 1;
}

int CheckMainDiagonalForWinner(Board* B) {
	if (MainDiagonalIsComplete(B)) {
		int CompletedWith1 = B->Cells[0][0].Piece;
		int CompletedWith0 = ~(B->Cells[0][0].Piece);
		for (int i = 1; i < BoardSize; i++) {
			CompletedWith1 &= B->Cells[i][i].Piece;
			CompletedWith0 &= ~(B->Cells[i][i].Piece);
		}
		return (CompletedWith1 | CompletedWith0);
	}
	return 0;
}

int SecondaryDiagonalIsComplete(Board* B) {
	for (int i = 0; i < BoardSize; i++) {
		if (B->Cells[i][BoardSize - 1 - i].IsEmpity) {
			return 0;
		}
	}
	return 1;
}

int CheckSecondaryDiagonalForWinner(Board* B) {
	if (SecondaryDiagonalIsComplete(B)) {
		int CompletedWith1 = B->Cells[0][BoardSize - 1].Piece;
		int CompletedWith0 = ~(B->Cells[0][BoardSize - 1].Piece);
		for (int i = 1; i < BoardSize; i++) {
			CompletedWith1 &= B->Cells[i][BoardSize - 1 - i].Piece;
			CompletedWith0 &= ~(B->Cells[i][BoardSize - 1 - i].Piece);
		}
		return (CompletedWith1 | CompletedWith0);
	}
	return 0;
}

int GetPiece(Board* B) {
	int Entry;
	scanf("%d", &Entry);
	if (B->RemainingPieces[Entry] >= 0 && Entry < BoardSize * BoardSize) {
		return Entry;
	}
	else {
		return GetPiece(B);
	}
}
/*
Position GetCell(Board* B, int PlayerNumber) {
	printf("Player %d, please enter a valid row, collum pair: ", PlayerNumber);
	Position Pair;
	scanf("%d%d", &Pair.Row, &Pair.Collum);
	if (B->Cells[Pair.Row][Pair.Collum].IsEmpity && Pair.Row < BoardSize && Pair.Collum < BoardSize) {
		return Pair;
	}
	else {
		return GetCell(B, PlayerNumber);
	}
}
*/
Position arrayToMatrix (int num) {
	Position result; 

    result.Collum = num % BoardSize;
    result.Row = (num - result.Collum )/ BoardSize;

	return result;
}

Position GetCell (Board *B){
	int n;
	scanf("%d", &n);
	Position position = arrayToMatrix (n);
	if(n > 0 && n < BoardSize * BoardSize && 
	B->Cells[position.Row][position.Collum].IsEmpity) {
		return position;
	} else {
		return GetCell (B);
	}
}

int main(int Argument01, char** Argument02) {
	Board B;
	InitializeBoard(&B);
	int NumberOfTurns = 0;
	int ThereIsAWinner = 0;
	int CurrentPlayer = 0;
	while (!ThereIsAWinner && NumberOfTurns < BoardSize * BoardSize) {
		PrintBoard(&B);
		PrintRemainingPieces(&B);
		int ChosenPiece = GetPiece(&B);
		int OtherPlayer = (CurrentPlayer + 1) % 2;
		Position ChosenCell = GetCell(&B);
		PlacePieceOnBoard(&B, ChosenPiece, ChosenCell);
		ThereIsAWinner = (CheckMainDiagonalForWinner(&B) | CheckSecondaryDiagonalForWinner(&B));
		for (int i = 0; i < BoardSize; i++) {
			ThereIsAWinner |= (CheckRowForWinner(&B, i) | CheckCollumForWinner(&B, i));
		}
		NumberOfTurns++;
		CurrentPlayer = OtherPlayer;
	}
	PrintBoard(&B);
	if (ThereIsAWinner) {
		printf("Player %d is the winner!!!\n", CurrentPlayer);
	}
	else {
		printf("It's a draw.\n");
	}

	system("cls"); 
}