#include "stdafx.h"
#include "POINToperators.h"

bool operator<(POINT a, POINT b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
bool operator>(POINT a, POINT b) { return a.x == b.x ? a.y > b.y : a.x > b.x; }
bool operator==(POINT a, POINT b) { return a.x == b.x && a.y == b.y; }
bool operator!=(POINT a, POINT b) { return a.x != b.x || a.y != b.y; }