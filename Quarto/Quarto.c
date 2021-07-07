#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define BoardSize 4
#define NumberOfProperties 4
#define BinaryMask 15

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
	if (C->IsEmpity) {
		printf("-");
	}
	else {
		printf("%X", C->Piece);
	}
}

typedef struct Board {
	Cell Cells[BoardSize][BoardSize];
	int RemainingPieces[BoardSize * BoardSize];
	char WinningLine;
	int WinningIndex;
	const char* Dictionary[2][BoardSize];
	int WinningPropState;
	int WinningProp;
}Board;

void InitializeBoard(Board* B) {
	B->Dictionary[0][0] = "solida\0";
	B->Dictionary[0][1] = "circular\0";
	B->Dictionary[0][2] = "grande\0";
	B->Dictionary[0][3] = "branca\0";
	B->Dictionary[1][0] = "oca\0";
	B->Dictionary[1][1] = "quadrada\0";
	B->Dictionary[1][2] = "pequena\0";
	B->Dictionary[1][3] = "escura\0";
	B->WinningLine = '\0';
	B->WinningIndex = -1;
	B->WinningPropState = -1;
	B->WinningProp = -1;
	for (int i = 0; i < BoardSize; i++) {
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
	int Column;
}Position;

void PlacePieceOnBoard(Board* B, int Piece, Position Pair) {
	PlacePieceOnCell(&(B->Cells[Pair.Row][Pair.Column]), Piece);
	B->RemainingPieces[Piece] = -1;
}

void PrintBoard(Board* B) {
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			PrintCell(&(B->Cells[i][j]));
		}
		printf("\n");
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

void WinningCondition(Board* B, int C1, int C0) {
	if (C1) {
		B->WinningProp = (int)log2(C1);
		B->WinningPropState = 1;
	}
	else if (C0) {
		B->WinningProp = (int)log2(C0);
		B->WinningPropState = 0;
	}
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
		int CompletedWith0 = ~(B->Cells[Row][0].Piece)&(BinaryMask);
		for (int i = 1; i < BoardSize; i++) {
			CompletedWith1 &= B->Cells[Row][i].Piece;
			CompletedWith0 &= ~(B->Cells[Row][i].Piece)&(BinaryMask);
		}
		WinningCondition(B, CompletedWith1, CompletedWith0);
		return (CompletedWith1 | CompletedWith0);
	}
	return 0;
}

int ColumnIsComplete(Board* B, int Column) {
	for (int i = 0; i < BoardSize; i++) {
		if (B->Cells[i][Column].IsEmpity) {
			return 0;
		}
	}
	return 1;
}

int CheckColumnForWinner(Board* B, int Column) {
	if (ColumnIsComplete(B, Column)) {
		int CompletedWith1 = B->Cells[0][Column].Piece;
		int CompletedWith0 = ~(B->Cells[0][Column].Piece)&(BinaryMask);
		for (int i = 1; i < BoardSize; i++) {
			CompletedWith1 &= B->Cells[i][Column].Piece;
			CompletedWith0 &= ~(B->Cells[i][Column].Piece)&(BinaryMask);
		}
		WinningCondition(B, CompletedWith1, CompletedWith0);
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
		int CompletedWith0 = ~(B->Cells[0][0].Piece)&(BinaryMask);
		for (int i = 1; i < BoardSize; i++) {
			CompletedWith1 &= B->Cells[i][i].Piece;
			CompletedWith0 &= ~(B->Cells[i][i].Piece)&(BinaryMask);
		}
		WinningCondition(B, CompletedWith1, CompletedWith0);
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
		int CompletedWith0 = ~(B->Cells[0][BoardSize - 1].Piece)&(BinaryMask);
		for (int i = 1; i < BoardSize; i++) {
			CompletedWith1 &= B->Cells[i][BoardSize - 1 - i].Piece;
			CompletedWith0 &= ~(B->Cells[i][BoardSize - 1 - i].Piece)&(BinaryMask);
		}
		WinningCondition(B, CompletedWith1, CompletedWith0);
		return (CompletedWith1 | CompletedWith0);
	}
	return 0;
}

int GetPiece(Board* B) {
	int Entry;
	scanf_s("%X", &Entry);
	if (B->RemainingPieces[Entry] >= 0 && Entry < BoardSize * BoardSize) {
		return Entry;
	}
	else {
		return GetPiece(B);
	}
}

Position ArrayToMatrix(int num) {
	Position result;
	result.Column = num % BoardSize;
	result.Row = (num - result.Column) / BoardSize;
	return result;
}

Position GetCell(Board* B) {
	int n;
	scanf_s("%X", &n);
	Position position = ArrayToMatrix(n);
	if (n >= 0 && n < BoardSize * BoardSize && B->Cells[position.Row][position.Column].IsEmpity) {
		return position;
	}
	else {
		return GetCell(B);
	}
}

void PrintWinningRow(Board* B) {
	for (int i = 0; i < BoardSize; i++) {
		printf("%X", BoardSize * (B->WinningIndex) + i);
	}
}

void PrintWinningColumn(Board* B) {
	for (int i = 0; i < BoardSize; i++) {
		printf("%X", B->WinningIndex + i * BoardSize);
	}
}

void PrintMainDiagonal(Board* B) {
	for (int i = 0; i < BoardSize; i++) {
		printf("%X", i + i * BoardSize);
	}
}

void PrintSecondaryDiagonal(Board* B) {
	for (int i = 0; i < BoardSize; i++) {
		printf("%X", i * BoardSize + BoardSize - i - 1);
	}
}

int CheckForWinner(Board* B, int player) {
	for (int i = 0; i < BoardSize; i++) {
		if (CheckRowForWinner(B, i)) {
			B->WinningLine = 'R';
			B->WinningIndex = i;
			return 1;
		}
	}
	for (int i = 0; i < BoardSize; i++) {
		if (CheckColumnForWinner(B, i)) {
			B->WinningLine = 'C';
			B->WinningIndex = i;
			return 1;
		}
	}

	if (CheckMainDiagonalForWinner(B)) {
		B->WinningLine = 'P';
		return 1;
	}

	if (CheckSecondaryDiagonalForWinner(B)) {
		B->WinningLine = 'S';
		return 1;
	}
	return 0;
}

void PrintVictory(Board* B, int player) {
	PrintBoard(B);
	printf("%d\n", (player + 1));
	switch (B->WinningLine) {
	case 'R':
		PrintWinningRow(B);
		break;
	case 'C':
		PrintWinningColumn(B);
		break;
	case 'P':
		PrintMainDiagonal(B);
		break;
	case 'S':
		PrintSecondaryDiagonal(B);
		break;
	}
	int Row = B->WinningPropState;
	int Column = B->WinningProp;
	printf("\n%s", B->Dictionary[Row][Column]);
}


int main(int Argument01, char** Argument02) {
	Board B;
	InitializeBoard(&B);
	int NumberOfTurns = 0;
	int ThereIsAWinner = 0;
	int CurrentPlayer = 0;
	while (!ThereIsAWinner && NumberOfTurns < BoardSize * BoardSize) {
		int ChosenPiece = GetPiece(&B);
		int OtherPlayer = (CurrentPlayer + 1) % 2;
		Position ChosenCell = GetCell(&B);
		PlacePieceOnBoard(&B, ChosenPiece, ChosenCell);
		ThereIsAWinner = CheckForWinner(&B, CurrentPlayer);
		NumberOfTurns++;
		CurrentPlayer = OtherPlayer;
	}

	if (ThereIsAWinner) {
		PrintVictory(&B, CurrentPlayer);
	}
	else {
		PrintBoard(&B);
		printf("0");
	}
}