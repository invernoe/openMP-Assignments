#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#define ImageWidthSize 10
#define ImageHeightSize 10 
#define HistogramSize 256

int main(int argc, char* argv[])
{
	int ImagePixelsData[ImageWidthSize][ImageHeightSize];
	int* HistogramResult = new int[HistogramSize];

	for (int j = 0; j < ImageWidthSize; j++)
	{
		for (int k = 0; k < ImageHeightSize; k++) {
			ImagePixelsData[j][k] = rand() % 256;
		}
	}

#pragma omp parallel for
	for (int i = 0; i < HistogramSize; i++)
	{
		HistogramResult[i] = 0;
	}
#pragma omp parallel for
	for (int j = 0; j < ImageWidthSize; j++)
		for (int k = 0; k < ImageHeightSize; k++)
			//gets value of image pixelsData[j][k] that is between 0 and 255 and uses it as indexing
			HistogramResult[ImagePixelsData[j][k]]++; 
		


	printf("histogram result from 0 to 255 =\n");
	for (int i = 0; i < HistogramSize; i++)
	{
		printf("%d: %d\n", i, HistogramResult[i]);
	}

	return 0;
}