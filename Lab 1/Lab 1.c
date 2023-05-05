#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define POINTS 1<<4
int arr[POINTS];
int disablePrint = 0;
void printarr(int start , int end,int pivot) {
	if (disablePrint)
		return;
	int stride = 16;
	for (int i = 0; i < POINTS; ++i) {
		if (i % stride == 0)
			printf("\n");
		if (i == pivot) {
			printf("#");
		}
		else if (i >= start && i < end) {
			printf("*");
		}
		printf("%d\t", arr[i]);
	}
	printf("\n");
	//getchar();
}

void swap(int* a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}

int isSorted(int* parr, int len) {
	for (int i = 0; i < len-1; ++i) {
		if (parr[i] > parr[i + 1])
			return 0;
	}
	return 1;
}

//start inclusive , end exclusive
void quick(int start, int end) {
	if (start >= end-1)
		return;

	int piv = start + rand() % (end - start);
	int pivElem = arr[piv];
	int newIndex = piv;

	//Count strictly smaller numbers
	int lower = 0;
	for (int i = start; i < end; ++i) {
		if (arr[i] < pivElem)
			lower++;
	}
	lower += start;
	//Swap whatever is in lower with pivot element
	swap(arr + lower, arr + piv);
	newIndex = lower;
	//Now arrange all strictly smaller ones to left of lower
	for (int i = start; i < newIndex; ++i) {
		if (arr[i] >= pivElem) {

			while (arr[lower] >= pivElem) {
				lower++;
			}
			swap(&arr[i], &arr[lower]);

		}
	}

	printarr(start, end,newIndex);
	quick(start, newIndex);
	quick(newIndex + 1, end);
}


int main() {
	long seed = (long)time(NULL);
	//seed = 1670427859;
	srand(seed);
	int c1;
	c1 = 0;
	int counts = 100000;
	for (int i = 0; i < counts; ++i) {
		for (int i = 0; i < POINTS; ++i)
			arr[i] = rand();

		//disablePrint = 0;
		printarr(-1, -1, -1);
		disablePrint = 1;
		quick(0, POINTS);
		//disablePrint = 0;
		printarr(-1, -1, -1);
		if (isSorted(arr, POINTS))
			c1++;

	}
	printf("Sort count out of %d = %d", counts, c1);
	return 0;
}
