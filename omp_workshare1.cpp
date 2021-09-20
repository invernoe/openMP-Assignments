#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

const int VECTOR_LENGTH = 10000;
const int NUM_THREADS = 4;
const int CHUNK = VECTOR_LENGTH / NUM_THREADS;
int a[VECTOR_LENGTH] = {};
int b[VECTOR_LENGTH] = {};
int c[VECTOR_LENGTH] = {};

void fillVector(int* arr, int size) {
	for(int i = 0; i < size; i++)
		*(arr++) = rand();
}

int main() {
	fillVector(a, VECTOR_LENGTH);
	fillVector(b, VECTOR_LENGTH);

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int start = id * CHUNK;
		int end = start + CHUNK;

		for (int i = start; i < end; i++)
		{
			c[i] = a[i] + b[i];
		}
	}

	printf("vector C result:\n[");

	for (int i = 0; i < VECTOR_LENGTH - 1; i++)
	{
		printf("%d,\n", c[i]);
	}

	printf("%d]", c[VECTOR_LENGTH - 1]);

	return 0;
}