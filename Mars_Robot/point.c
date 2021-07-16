#include "point.h"

void SetPoint(Point* P, const unsigned int x, const unsigned int y) {
	P->Row = x;
	P->Column = y;
}

Point MakePoint(const unsigned int x, const unsigned int y) {
	Point P = { x, y };
	return P;
}

int AreEqual(Point* P1, Point* P2) {
	return (P1->Row == P2->Row && P1->Column == P2->Column);
}