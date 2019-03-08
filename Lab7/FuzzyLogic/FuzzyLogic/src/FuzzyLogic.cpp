#include "..\inc\FuzzyLogic.h"
#include <algorithm>
double FuzzyLogic::fuzzyGrade(double value, double x0, double x1)
{
	double result = 0;
	double x = value;

	if (x <= x0)
		result = 0;
	else if (x > x1)
		result = 1;
	else
		result = ((x - x0) / (x1 - x0));

	return result;
}

double FuzzyLogic::fuzzyTriangle(double value, double x0, double x1, double x2)
{
	double result = 0;
	double x = value;

	if ((x <= x0) || (x >= x2))
		result = 0;
	else if (x == x1)
		result = 1;
	else if ((x > x0) && (x < x1))
		result = ((x - x0) / (x1 - x0));
	else
		result = ((x2 - x) / (x2 - x1));

	return result;
}

double FuzzyLogic::fuzzyTrapezoid(double value, double x0, double x1, double x2, double x3)
{
	double result = 0;
	double x = value;

	if ((x <= x0) || (x >= x3))
		result = 0;
	else if ((x >= x1) && (x <= x2))
		result = 1;
	else if ((x > x0) && (x < x1))
		result = ((x - x0) / (x1 - x0));
	else
		result = ((x3 - x) / (x3 - x2));
	
	return result;
}

double FuzzyLogic::fuzzyAND(double a, double b)
{
	return std::min(a, b);
}

double FuzzyLogic::fuzzyOR(double a, double b)
{
	return std::max(a, b);
}

double FuzzyLogic::fuzzyNOT(double a)
{
	return 1.0 - a;
}