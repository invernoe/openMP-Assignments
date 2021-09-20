#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

int main(int argc, char* argv[])
{
	const int POINTS = 5000000;
	int inner = 0;
	int i;

#pragma omp parallel for reduction(+:inner)
		for (i = 0; i < POINTS; i++)
		{
			float x = (float) rand() / RAND_MAX;
			float y = (float) rand() / RAND_MAX;
			if (sqrt(pow(x - 0.5, 2) + pow(y - 0.5, 2)) <= 0.5)
				inner++;
		}

	float result = 4 * ((float)inner) / POINTS;
	printf("PI = %f\n", result);

	return 0;
}