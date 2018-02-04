#include "stdafx.h"
#include "POINToperators.h"

bool operator<(POINT a, POINT b) { return a.x < b.x ? true : a.y < b.y; }
bool operator>(POINT a, POINT b) { return a.x > b.x ? true : a.y > b.y; }
bool operator==(POINT a, POINT b) { return a.x == b.x ? true : a.y == b.y; }
bool operator!=(POINT a, POINT b) { return a.x != b.x ? true : a.y != b.y; }