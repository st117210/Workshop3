#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>
#include<vector>
#include <fstream>

int main()
{
	std::vector<double> ro = { 0.7, 1.18, 2.79, 7.9, 8.5, 11.34 };
	std::vector<double> mass(6, 0);

	for (int i = 0; i < mass.size(); i++)
	{
		mass[i] = (4.0 / 3.0) * M_PI * 0.5 * 0.5 * 0.5 * ro[i];
	}

	std::ofstream outputFile("Mass.csv");
	for (const double m : mass)
	{
		outputFile << m << std::endl;
	}
	outputFile.close();

	return 0;
}