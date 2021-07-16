#include "rover.h"

void ConstructRover(Rover* R, const Point InitialPosition, const Point Destiny, const Point MapSize) {
	ConstructMatrix(&(R->Map), MapSize);
	R->Position = InitialPosition;
	R->Destination = Destiny;
	R->Cost = 0;
}

void DestroyRover(Rover* R) {
	DestroyMatrix(&(R->Map));
}

int NorthCost(const Rover* R) {
	return R->Map.Values[R->Position.Row - 1][R->Position.Column];
}

int EastCost(const Rover* R) {
	return R->Map.Values[R->Position.Row][R->Position.Column + 1];
}

int CanMoveNorth(const Rover* R) {
	return (R->Position.Row > 0 && NorthCost(R) < Abyss);
}

int CanMoveEast(const Rover* R) {
	return (R->Position.Column < R->Map.NumOfColumns - 1 && EastCost(R) < Abyss);
}

void MoveNorth(Rover* R) {
	R->Position.Row -= 1;
}

void MoveEast(Rover* R) {
	R->Position.Column += 1;
}

int IsMoving(Rover* R) {
	R->Cost += GetValue(&(R->Map), R->Position);
	if (CanMoveEast(R)) {
		if (CanMoveNorth(R) && NorthCost(R) < EastCost(R)) {
			MoveNorth(R);
			return 1;
		}
		else {
			MoveEast(R);
			return 1;
		}
	}
	else {
		if (CanMoveNorth(R)) {
			MoveNorth(R);
			return 1;
		}
		else {
			return 0;
		}
	}
}

void TakeInput(Rover* R) {
	Point MapSize;
	scanf("%u%u", &MapSize.Row, &MapSize.Column);
	ConstructRover(R, MakePoint(MapSize.Row - 1, 0), MakePoint(0, MapSize.Column - 1), MapSize);
	Point EnteredPoint;
	int EnteredValue;
	while (scanf("%u%u%d", &EnteredPoint.Row, &EnteredPoint.Column, &EnteredValue) != EOF) {
		SetValue(&(R->Map), EnteredPoint, EnteredValue);
	}
}