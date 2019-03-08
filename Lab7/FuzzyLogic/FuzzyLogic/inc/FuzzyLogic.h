#pragma once
class FuzzyLogic
{
public:
	static double fuzzyGrade(double value, double x0, double x1);
	static double fuzzyTriangle(double value, double x0, double x1, double x2);
	static double fuzzyTrapezoid(double value, double x0, double x1, double x2, double x3);

	static double fuzzyAND(double a, double b);
	static double fuzzyOR(double a, double b);
	static double fuzzyNOT(double a);
private:

};