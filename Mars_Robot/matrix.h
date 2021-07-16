#ifndef __MATRIX__
#define __MATRIX__

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "point.h"

#define DefaultCost 1
#define Abyss 99

void ConstructMatrix(Matrix* M, const Point Size);
void DestroyMatrix(Matrix* M);
void SetValue(Matrix* M, const Point P, const int Value);
int GetValue(const Matrix* M, const Point P);

#endif