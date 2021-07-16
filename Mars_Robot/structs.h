#ifndef __STRUCTS__
#define __STRUCTS__

typedef struct Point {
	unsigned int Row;
	unsigned int Column;
}Point;

typedef struct Matrix {
	int** Values;
	unsigned int NumOfRows;
	unsigned int NumOfColumns;
}Matrix;

typedef struct Rover {
	Matrix Map;
	Point Position;
	Point Destination;
	int Cost;
}Rover;

#endif