#include <fstream>
#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{
	ifstream file;
	file.open("points.dat");

	double num;
	vector<double> vec;

	while (file >> num) {
		vec.push_back(num);
	}

	double x_avg = 0.0;
	double y_avg = 0.0;
	double z_avg = 0.0;
#pragma omp parallel for reduction(+:x_avg,y_avg,z_avg)
	for (int i = 0; i < vec.size(); i++)
	{
		switch (i % 3) {
		case 0:
			x_avg += vec[i];
			break;
		case 1:
			y_avg += vec[i];
			break;
		case 2:
			z_avg += vec[i];
			break;
		}
	}

	int pointSize = vec.size() / 3;
	printf("vec size = %d\npoint size = %d\n", vec.size(), pointSize);
	printf("loop version:\n");
	printf("x_avg = %f\ny_avg = %f\nz_avg = %f\n", x_avg / pointSize, y_avg / pointSize, z_avg / pointSize);

	double x_avg_section = 0.0;
	double y_avg_section = 0.0;
	double z_avg_section = 0.0;
#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp section
			{
				for (int i = 0; i < vec.size(); i += 3) {
					x_avg_section += vec[i];
				}
				x_avg_section = x_avg_section / pointSize;
			}
#pragma omp section
			{
				for (int i = 1; i < vec.size(); i += 3) {

					y_avg_section += vec[i];
				}
				y_avg_section = y_avg_section / pointSize;
			}
#pragma omp section
			{
				for (int i = 2; i < vec.size(); i += 3) {

					z_avg_section += vec[i];
				}
				z_avg_section = z_avg_section / pointSize;
			}

		}
	}

	printf("section version:\n");
	printf("x_avg = %f\ny_avg = %f\nz_avg = %f\n", x_avg_section, y_avg_section, z_avg_section);

	return 0;
}