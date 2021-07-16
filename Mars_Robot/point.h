#ifndef __POINT__
#define __POINT__

#include "structs.h"

void SetPoint(Point* P, const unsigned int x, const unsigned int y);
Point MakePoint(const unsigned int x, const unsigned int y);
int AreEqual(Point* P1, Point* P2);

#endif