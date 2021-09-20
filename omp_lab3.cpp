#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

const int VECTOR_LENGTH = 10000;
const int NUM_THREADS = 4;

int a[VECTOR_LENGTH] = {};

void fillVector(int* arr, int size) {
	for (int i = 0; i < size; i++)
		*(arr++) = rand() % 100;
}

int main() {
	fillVector(a, VECTOR_LENGTH);
	omp_set_num_threads(NUM_THREADS);
	int target;

	printf("enter the target integer to be found: ");
	scanf_s("%d", &target);
	

#pragma omp parallel for shared(target)
		for (int i = 0; i < VECTOR_LENGTH; i++)
		{
			if (a[i] == target)
				printf("target number %d found in index %d\n", target, i);
		}

	return 0;
}