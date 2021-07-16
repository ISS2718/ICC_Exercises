#include<stdio.h>
#include<stdlib.h>
#include "structs.h"
#include "point.h"
#include "matrix.h"
#include "rover.h"

int main(int Argument01, char** Argument02) {
	Rover Car;
	TakeInput(&Car);
	while (IsMoving(&Car)) {
	};
	printf("%d\n%d\n", Car.Cost, AreEqual(&Car.Position, &Car.Destination));
	DestroyRover(&Car);
}