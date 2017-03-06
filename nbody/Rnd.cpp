#pragma once
#include "Rnd.h"

double rnd(double rangemin, double rangemax)			// random float within supplied range...
{
	double f = (double)rand() / RAND_MAX;
	return f * (rangemax - rangemin) + rangemin;
}