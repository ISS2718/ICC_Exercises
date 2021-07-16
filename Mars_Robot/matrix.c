#include "matrix.h"

void ConstructMatrix(Matrix* M, const Point Size) {
	M->NumOfRows = Size.Row;
	M->NumOfColumns = Size.Column;
	M->Values = (int**)calloc(Size.Row, sizeof(int*));
	if (M->Values == NULL) {
		printf("Error: Failure to allocate memory for Matrix object");
		return;
	}
	for (unsigned int i = 0; i < Size.Row; i++) {
		M->Values[i] = (int*)calloc(Size.Column, sizeof(int));
		if (M->Values[i] == NULL) {
			printf("Error: Failure to allocate memory for Matrix object");
			return;
		}
		for (unsigned int j = 0; j < Size.Column; j++) {
			M->Values[i][j] = DefaultCost;
		}
	}
	M->Values[Size.Row - 1][0] = 0;
	M->Values[0][Size.Column - 1] = 0;
}

void DestroyMatrix(Matrix* M) {
	for (unsigned int i = 0; i < M->NumOfRows; i++) {
		free(M->Values[i]);
	}
	free(M->Values);
}

void SetValue(Matrix* M, const Point P, const int Value) {
	if (P.Row < M->NumOfRows && P.Column < M->NumOfColumns) {
		M->Values[P.Row][P.Column] = Value;
	}
}

int GetValue(const Matrix* M, const Point P) {
	if (P.Row < M->NumOfRows && P.Column < M->NumOfColumns) {
		return M->Values[P.Row][P.Column];
	}
	printf("Error: Trying to access out of range index in Matrix object");
	return -1;
}
