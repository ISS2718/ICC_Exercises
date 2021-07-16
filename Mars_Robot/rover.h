#ifndef __ROVER__
#define __ROVER__
#include <stdio.h>
#include "structs.h"
#include "point.h"
#include "matrix.h"

void ConstructRover(Rover* R, const Point InitialPosition, const Point Destiny, const Point MapSize) ;
void DestroyRover(Rover* R);
int NorthCost(const Rover* R);
int EastCost(const Rover* R);
int CanMoveNorth(const Rover* R);
int CanMoveEast(const Rover* R);
void MoveNorth(Rover* R);
void MoveEast(Rover* R);
int IsMoving(Rover* R);
void TakeInput(Rover* R);

#endif